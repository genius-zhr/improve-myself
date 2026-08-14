# Python 巩固练习(Week 3)完整版

> 对应 Week 3 验收:「写个 Python 小脚本」+ 基本语法 / list / dict / tuple / set / 函数 / 类 / numpy。
> **原 1~6 题不变**,新增 7~12(同类型,把对话里讲过的附加小练习也收进来了)。
> 每题一个文件,写完 `python3 exX.py` 跑通 = 过关。
> **卡住 15 分钟还不行 → 回来问我,我给你提示,不许先翻答案文件。**

---

## 第 1 题:list 与循环(热身)— ex1.py
创建 list 存 1~10,打印三行:数字之和、最大值、偶数列表 `[2, 4, 6, 8, 10]`。
提示:`list(range(1, 11))`、`sum()`、`max()`、列表推导式 `[x for x in nums if x % 2 == 0]`

## 第 2 题:tuple 与 set — ex2.py
1. `nums = [1, 2, 2, 3, 4, 4, 4, 5]`,用 set 打印去重后的个数。
2. 写函数 `concat(t1, t2)` 返回两个 tuple 拼接结果,调用 `concat((1, 2), (3, 4))` 打印 `(1, 2, 3, 4)`。
提示:set 用法 `set(nums)`,tuple 拼接直接 `t1 + t2`

## 第 3 题:dict — ex3.py
用 dict 存成绩:`{"张三": 85, "李四": 58, "王五": 72}`
1. 给李四加分到 60;
2. 打印所有及格(≥60)的同学,格式 `名字:分数`;
3. 按分数从高到低打印。
提示:`d.items()` 遍历、`sorted(d.items(), key=lambda x: x[1], reverse=True)`(lambda 就是匿名函数,≈ C++ 仿函数)

**附加小练习**(复习刚讲的排序):改成按**名字**(字典序)升序排,`key=lambda x: x[1]` 要改成什么?跑通后,打印结果应该是 `张三、李四、王五` 的顺序。

## 第 4 题:文件读写(Week 3 验收正题)— ex4.py
1. 若 `scores.txt` 不存在,自己生成它,写入 5 行随机整数(1~100);
2. 读这个文件,统计并打印:总个数、总和、平均值(保留 2 位小数)、最大值。
提示:`random.randint(1, 100)`、`with open(...)`、`int(line.strip())`
跑两遍:第一遍生成,第二遍统计。参考输出 `平均值: 63.40`

**附加小练习**(复习解包报错):跑完统计后,**手动**把 `scores.txt` 里其中一行改成没有逗号/缺数据的格式(比如一行就一个 `42`),再跑一遍程序,看会不会报错、报什么错——把报错贴给我想想为什么。

## 第 5 题:类 — ex5.py
写 `Student` 类:构造时接收 `name` 和一个分数 list;方法 `average()` 返回平均分,`passed()` 返回是否及格(平均 ≥ 60)。
创建 3 个学生,打印每个学生的名字、平均分、是否及格。
提示:还记得 C++ 的 `this->` 吗?Python 里是 `self.`,构造函数名固定叫 `__init__`

## 第 6 题:numpy — ex6.py
1. `import numpy as np`(没有就装:Windows 用 `pip3 install numpy`,WSL 里 `sudo apt install python3-numpy`);
2. 创建 3×4 的随机整数数组,值域 0~9;
3. 打印:形状 shape、转置 T、每列的和(axis=0)、大于 5 的元素个数;
4. 把所有 >5 的元素替换成 0,打印替换后的数组。
提示:`np.random.randint(0, 10, size=(3, 4))`、`arr.shape`、`arr.T`、`arr.sum(axis=0)`、`(arr > 5).sum()`、`arr[arr > 5] = 0`

---

## 第 7 题:元组解包专项 — ex7.py
1. 写 `a, b, c = [10, 20, 30]`,打印三个变量。
2. 用解包**交换**两个变量的值:`a, b = "hello", "world"`,再用一行把 a、b 交换,打印交换后结果(不用临时变量,`a, b = b, a`)。
3. 预言 + 验证:`name, salary, dept = "张三,5000".split(",")` 会报什么错?如果改成 4 个字段 `"张三,5000,算法,备注"` 呢?亲手跑两遍,把两个报错原文贴出来。
提示:解包的死规则——**变量个数必须和值的个数完全相等**,多了少了都报 `ValueError`。

## 第 8 题:排序专项(lambda + key)— ex8.py
1. `scores = {"张三": 85, "李四": 60, "王五": 72}`,按**名字**升序打印;
2. `data = [("算法", 3), ("部署", 5), ("视觉", 2)]`,按元组**第二个元素**(人数)从大到小打印;
3. **挑战**:还是第 1 题的 scores,要求**先按分数降序,分数相同再按名字升序**。提示:`key` 可以返回一个 tuple:`key=lambda x: (x[1], x[0])`——先比第一个,相同再比第二个。
提示:`sorted(可迭代对象, key=提取函数, reverse=布尔)`

## 第 9 题:dict 计数(实用) — ex9.py
`words = ["apple", "banana", "apple", "cherry", "banana", "apple", "date"]`
1. 用 dict 统计每个词出现几次(不能靠数,要遍历累加);
2. 打印出现次数 ≥ 2 的词;
3. 按出现次数从高到低打印 `词:次数`。
提示:计数套路 `count[w] = count.get(w, 0) + 1`(get 取不到就返回 0);排序用 `sorted(count.items(), key=lambda x: x[1], reverse=True)`。这道题把 dict、get、sorted、lambda 全串起来了。

## 第 10 题:字符串 + 函数 — ex10.py
1. `sentence = "hello world python is fun"`,用 `split()` 拆词,打印每个单词长度组成的 list(应是 `[5, 5, 6, 2, 3]`);
2. 写函数 `is_palindrome(s)`:判断字符串是否回文(正反读一样,如 `"level"` 是,`"hello"` 不是);
3. **进阶**:让 `is_palindrome` 忽略大小写和空格,如 `"A man a plan a canal Panama"` 应返回 `True`。
提示:`s[::-1]` 反转字符串;`s.lower()` 转小写;`s.replace(" ", "")` 去空格。

## 第 11 题:文件读写进阶(选做)— ex11.py
生成 `students.txt`,每行 `姓名,成绩`(5 行,名字自拟,成绩用 random 1~100)。
读文件后打印:
1. 成绩**最高**的人(名字+成绩);
2. 平均分;
3. 所有不及格(<60)的人。
提示:把每行解析成 `(name, int(score))` 存进 list;`max(students, key=lambda x: x[1])` 找最高;复用第 4 题的读文件套路。

## 第 12 题:numpy 进阶(选做)— ex12.py
1. `a = np.array([1, 2, 3, 4])`、`b = np.array([10, 20, 30, 40])`,打印 `a + b`、`b - a`、`a * 2`(体会:**对数组整体做运算**,不用写循环);
2. `arr = np.random.randint(0, 100, size=10)`,打印:最大值、最大值**下标**(`np.argmax(arr)`)、所有 > 50 的元素;
3. 把第 6 题的 3×4 随机数组,**每行**求和(提示:`axis=1`,对比第 6 题 `axis=0` 是每列)。
提示:`np.array([...])` 直接构造一维数组;numpy 的 `+ - *` 都是逐元素运算,这是以后训练模型的基础。

---

**怎么跑**:Windows 终端 / VSCode 里 `python ex1.py`;WSL 里 `python3 ex1.py`。
**做完后**:把代码贴给我看,或者对答案文件自查。全部跑通 = Week 3 的 Python 部分过关,脚本可以整理上传 GitHub。
