"""
FashionMNIST 图像分类完整流程
=============================
1. 下载数据集（torchvision 自动下载到 data/ 目录，只需联网一次）
2. 构建 Dataset / DataLoader（批量化、打乱、归一化）
3. 定义 CNN 模型
4. 训练 + 每轮在测试集上评估
5. 保存模型权重和预测结果图

运行: python fashionMNIST.py
"""

from pathlib import Path

import torch
import torch.nn as nn
from torch.utils.data import DataLoader
from torchvision import datasets, transforms

import matplotlib
matplotlib.use("Agg")          # 无显示器的环境（如 WSL）也能出图
import matplotlib.pyplot as plt

# ----------------------------------------------------------------------
# 0. 路径与全局配置
# ----------------------------------------------------------------------
BASE_DIR = Path(__file__).resolve().parent   # 本文件所在的文件夹
DATA_DIR = BASE_DIR / "data"                 # 数据集存放位置
OUT_DIR = BASE_DIR / "output"                # 训练结果（图片、模型）存放位置
OUT_DIR.mkdir(exist_ok=True)

BATCH_SIZE = 64        # 一个批次多少张图
EPOCHS = 5             # 训练轮数（全部数据过几遍）
LEARNING_RATE = 1e-3   # Adam 常用起始学习率

# 设备选择：有 CUDA 就用 GPU，否则用 CPU
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# FashionMNIST 的 10 个类别
CLASS_NAMES = ["T恤/上衣", "裤子", "套头衫", "连衣裙", "外套",
               "凉鞋", "衬衫", "运动鞋", "包", "短靴"]

# 训练集和测试集可以使用不同的数据增强，这里先保持简单：都只做标准化
transform = transforms.Compose([
    transforms.ToTensor(),                          # PIL图片 / numpy -> [0,1] 的 float32 张量
    transforms.Normalize((0.2860,), (0.3530,)),     # FashionMNIST 官方统计的单通道均值/标准差
])


# ----------------------------------------------------------------------
# 1. 下载 + 加载数据
# ----------------------------------------------------------------------
def get_dataloaders():
    print("=" * 60)
    print("1. 准备数据集")
    print("=" * 60)
    print(f"数据目录: {DATA_DIR}")

    # download=True：如果 data/ 里没有数据，就自动联网下载
    # 下载源是 torchvision 内置的镜像地址，不用手动下
    train_dataset = datasets.FashionMNIST(
        root=DATA_DIR, train=True, download=True, transform=transform
    )
    test_dataset = datasets.FashionMNIST(
        root=DATA_DIR, train=False, download=True, transform=transform
    )

    print(f"训练集样本数: {len(train_dataset)}")
    print(f"测试集样本数: {len(test_dataset)}")
    print(f"单张图片形状: {train_dataset[0][0].shape}  (通道数, 高, 宽)")
    print(f"单张图片标签: {train_dataset[0][1]} -> {CLASS_NAMES[train_dataset[0][1]]}")

    # DataLoader 负责：按 batch 分组、打乱顺序、多进程读取
    train_loader = DataLoader(train_dataset, batch_size=BATCH_SIZE,
                              shuffle=True, num_workers=2, pin_memory=True)
    test_loader = DataLoader(test_dataset, batch_size=BATCH_SIZE,
                             shuffle=False, num_workers=2, pin_memory=True)
    return train_loader, test_loader


def save_sample_grid(loader):
    """把第一批 32 张图拼成一张图保存，方便肉眼确认数据加载正确"""
    images, labels = next(iter(loader))   # images: [B,1,28,28]
    fig, axes = plt.subplots(4, 8, figsize=(12, 6))
    for i, ax in enumerate(axes.flatten()):
        # 反标准化再显示，否则整体偏暗/偏白
        img = images[i, 0] * 0.3530 + 0.2860
        ax.imshow(img.numpy(), cmap="gray")#matplotlib不能显示张量要转numpy
        ax.set_title(CLASS_NAMES[labels[i].item()], fontsize=9)#fontsize是字体大小
        ax.axis("off")#关闭坐标轴
    fig.suptitle("FashionMNIST 训练集样例")#整张图的大标题
    fig.tight_layout()#自动调整子图间距
    path = OUT_DIR / "samples.png"
    fig.savefig(path, dpi=120)
    plt.close(fig)
    print(f"样例图片已保存: {path}")


# ----------------------------------------------------------------------
# 2. 模型定义
# ----------------------------------------------------------------------
class FashionCNN(nn.Module):
    """
    结构:
      输入 [B,1,28,28]
      Conv(1->32) + ReLU + MaxPool  -> [B,32,14,14]
      Conv(32->64) + ReLU + MaxPool -> [B,64,7,7]
      Flatten                       -> [B, 64*7*7=3136]
      Linear(3136->128) + ReLU + Dropout
      Linear(128->10)               -> 10 个类别的打分(logits)
    """

    def __init__(self):
        super().__init__()
        self.features = nn.Sequential(
            # padding=1 让 28x28 卷积后仍是 28x28，再池化成 14x14
            nn.Conv2d(in_channels=1, out_channels=32, kernel_size=3, padding=1),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2, stride=2),
            nn.Conv2d(32, 64, kernel_size=3, padding=1),
            nn.ReLU(),
            nn.MaxPool2d(2, 2),
        )
        self.classifier = nn.Sequential(
            nn.Flatten(),
            nn.Linear(64 * 7 * 7, 128),
            nn.ReLU(),
            nn.Dropout(0.3),          # 随机丢弃 30% 的神经元，缓解过拟合
            nn.Linear(128, 10),
        )

    def forward(self, x):
        x = self.features(x)
        x = self.classifier(x)
        return x


# ----------------------------------------------------------------------
# 3. 训练 / 评估
# ----------------------------------------------------------------------
def train_one_epoch(model, loader, criterion, optimizer):
    model.train()                     # 切换到训练模式（Dropout 会生效）
    total_loss, correct, total = 0.0, 0, 0

    for images, labels in loader:
        images, labels = images.to(device), labels.to(device)#数据搬到运行设备上，数据和模型要在同一设备上才能计算

        outputs = model(images)                 # 前向：得到 10 类 logits，前提必须有 forward() 方法
        loss = criterion(outputs, labels)       # 交叉熵内部含 softmax

        optimizer.zero_grad()                   # 清空上一步的梯度
        loss.backward()                         # 反向传播求梯度
        optimizer.step()                        # 用梯度更新参数

        total_loss += loss.item() * images.size(0)
        correct += (outputs.argmax(dim=1) == labels).sum().item()
        total += images.size(0)

    return total_loss / total, correct / total


@torch.no_grad()                     # 评估不需要梯度，省显存也更快
def evaluate(model, loader, criterion):
    model.eval()                     # 切换到评估模式（Dropout 关闭）
    total_loss, correct, total = 0.0, 0, 0

    for images, labels in loader:
        images, labels = images.to(device), labels.to(device)
        outputs = model(images)
        loss = criterion(outputs, labels)

        total_loss += loss.item() * images.size(0)
        correct += (outputs.argmax(dim=1) == labels).sum().item()
        total += images.size(0)

    return total_loss / total, correct / total


def save_prediction_grid(model, loader):
    """取一批测试图，把预测结果画出来保存"""
    images, labels = next(iter(loader))
    images_gpu = images.to(device)

    model.eval()
    preds = model(images_gpu).argmax(dim=1).cpu()

    fig, axes = plt.subplots(4, 8, figsize=(14, 7))
    for i, ax in enumerate(axes.flatten()):
        img = images[i, 0] * 0.3530 + 0.2860#反归一化
        ax.imshow(img.numpy(), cmap="gray")
        is_right = preds[i].item() == labels[i].item()
        color = "green" if is_right else "red"
        ax.set_title(f"真: {CLASS_NAMES[labels[i]]}\n预: {CLASS_NAMES[preds[i]]}",
                     fontsize=8, color=color)
        ax.axis("off")
    fig.suptitle("测试集预测结果（绿色=正确，红色=错误）")
    fig.tight_layout()
    path = OUT_DIR / "predictions.png"
    fig.savefig(path, dpi=120)
    plt.close(fig)
    print(f"预测结果图已保存: {path}")


# ----------------------------------------------------------------------
# 4. 主流程
# ----------------------------------------------------------------------
def main():
    # 中文显示设置（图里要用中文标题）
    plt.rcParams["font.sans-serif"] = ["SimHei", "Microsoft YaHei", "DejaVu Sans"]
    plt.rcParams["axes.unicode_minus"] = False

    print(f"使用设备: {device}")

    train_loader, test_loader = get_dataloaders()
    save_sample_grid(train_loader)

    model = FashionCNN().to(device)#模型搬到运行设备上，数据和模型要在同一设备上才能计算
    print("\n模型结构:")
    print(model)

    # 交叉熵损失：适合多分类，输入 logits，标签是类别下标
    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=LEARNING_RATE)

    print("\n" + "=" * 60)
    print("2. 开始训练")
    print("=" * 60)

    test_acc = 0.0
    for epoch in range(1, EPOCHS + 1):
        train_loss, train_acc = train_one_epoch(model, train_loader, criterion, optimizer)
        test_loss, test_acc = evaluate(model, test_loader, criterion)
        print(f"第 {epoch}/{EPOCHS} 轮 | "
              f"训练损失 {train_loss:.4f} 训练准确率 {train_acc:.2%} | "
              f"测试损失 {test_loss:.4f} 测试准确率 {test_acc:.2%}")

    print("\n" + "=" * 60)
    print(f"训练完成，最终测试准确率: {test_acc:.2%}")
    print("=" * 60)

    save_prediction_grid(model, test_loader)

    model_path = OUT_DIR / "fashion_mnist_cnn.pth"
    torch.save(model.state_dict(), model_path)
    print(f"模型权重已保存: {model_path}")


if __name__ == "__main__":
    main()
