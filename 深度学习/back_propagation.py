import torch
import torch.nn as nn
#数据
x=torch.tensor([[1.0]])#输入值,一般包含两个参数，一十batch_size（样本个数）和input_size，这里batch_size=1,input_size=1
t=torch.tensor([[1.0]])#目标值
#网络
model=nn.Sequential(
    nn.Linear(1,1,bias=False),
    nn.ReLU(),
    nn.Linear(1,1,bias=False),
    nn.ReLU(),
    nn.Linear(1,1,bias=False)
)
#初始化权重
with torch.no_grad():
    model[0].weight.fill_(2.0)
    model[2].weight.fill_(3.0)
    model[4].weight.fill_(1.0)
#损失函数 + 随机梯度下降优化器
criterion=nn.MSELoss()
optimizer=torch.optim.SGD(model.parameters(),lr=0.01)
#训练
for epoch in range(200):
    loss=criterion(model(x),t)
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()
    if epoch%10==0:
        print(f"Epoch {epoch+1}, 预测值: {model(x).item():7.4f} | 损失: {loss.item():.4f}")