# 演讲比赛流程管理系统

一个用 C++ 实现的"演讲比赛流程管理系统"课程项目。12 名选手经过两轮比赛，决出冠、亚、季军。

## 项目简介

系统以 `SpeechManager` 类为核心，自动调度一场完整比赛的全过程：

1. 启动时从文件加载 12 名选手名单（没有则自动生成）
2. 用户通过菜单选择：开始比赛 / 查看往届记录 / 清空记录 / 退出
3. 开始比赛后自动跑完两轮：**抽签 → 分组 → 打分 → 晋级 → 排名**，并把结果保存到文件

## 赛制规则

- 共 **12 名选手**，编号 10001~10012
- **第一轮**：抽签后分成两组，每组 6 人；每组前 3 名晋级，共晋级 6 人
- **第二轮**：晋级的 6 人决赛，前 3 名 = 冠军 / 亚军 / 季军
- **计分**：10 位评委打分，去掉一个最高分和一个最低分，剩下 8 个求平均
- 打分由程序随机生成（范围 60~100），免去手动输入

## 编译与运行

在项目目录下（需要能读写同目录的 `speaker.txt` / `record.txt`）：

```bash
g++ -std=c++17 main.cpp manager.cpp speaker.cpp -o speech
./speech
```

菜单操作：`1` 开始比赛，`2` 查看往届记录，`3` 清空记录，`0` 退出。

## 项目结构

```
演讲比赛流程管理系统/
├── main.cpp           # 主程序：菜单循环，程序入口
├── manager.h          # SpeechManager 类声明（私有方法的拆分说明）
├── manager.cpp        # SpeechManager 类实现：比赛调度 + 文件读写
├── speaker.h          # Speaker 类声明：选手信息（编号/姓名/两轮成绩）
├── speaker.cpp        # Speaker 类实现
├── speaker.txt        # 选手名单 + 两轮成绩（运行时读写，不进版本库）
├── record.txt         # 往届比赛记录（运行时读写，不进版本库）
├── README.md          # 本文件
└── .gitignore         # 忽略编译产物、数据文件、个人开发计划
```

`speaker.txt` 每行格式：`编号 姓名 第一轮成绩 第二轮成绩`（成绩 0 表示还没比赛）。

`record.txt` 每行格式：`届次 冠军编号 亚军编号 季军编号`。

## 用到的知识点

### 面向对象（OOP）

- **封装**：`Speaker` 的数据成员私有，通过 getter / setter 访问
- **类设计**：`SpeechManager` 把一场比赛的"状态"（选手、抽签顺序、分组、晋级名单、轮次）和"行为"（抽签、计分、晋级、存盘）组织在一起
- **构造 / 析构**：构造函数里加载历史记录、准备名单；私有方法的拆分体现"每个函数只做一件事"

### 标准模板库（STL）

| 容器 / 算法 | 用途 |
|---|---|
| `map<int, Speaker> m_speakers` | 按编号存选手，`operator[]` / `find` 查名字和成绩 |
| `vector<int>` | 抽签顺序、两组名单、晋级名单——**只存编号，不复制选手** |
| `std::shuffle` + `random_device` + `mt19937` | 抽签：打乱出场顺序 |
| `uniform_int_distribution` | 随机生成评委打分 |
| `sort` + lambda 比较器 | 晋级排名（自定义规则：按轮次成绩降序，同分按编号小在前） |
| `deque<double>` | 存放 10 个评委分，`pop_front` / `pop_back` 去掉最高最低 |
| `accumulate` | 求和后取平均 |
| `istringstream` | 把 record.txt 的一行字符串解析成多个整数 |

其中 **`sort` + 自定义比较器** 是重点：比较器需要访问对象成员，用 lambda 配合 `[this]` 捕获来解决（lambda 会被编译器变成一个隐藏的函数对象类）。

### 文件操作

- `ifstream` / `ofstream` 读写文件
- `is_open()` 判断文件是否存在；`peek() == EOF` 判断是否为空文件
- `ios::app` 追加模式写往届记录（不覆盖上一届）
- `ios::out | ios::trunc` 清空记录
- `getline` 逐行读取 + `istringstream` 解析每行的数据

## 测试

项目附带单元测试 `test_manager.cpp`（未进版本库），覆盖选手类、初始化、抽签、计分、晋级等核心逻辑：

```bash
g++ -std=c++17 manager.cpp speaker.cpp test_manager.cpp -o test_manager
./test_manager
```
