# -*- coding: utf-8 -*-
# =========================================================
# 参考答案 —— 写完、跑通自己的版本之后,再来对
# 也可以整体跑一遍看参考输出长什么样
# =========================================================

# ===================== 第 1 题 =====================
nums = list(range(1, 11))
print("和:", sum(nums))
print("最大值:", max(nums))
print("偶数:", [x for x in nums if x % 2 == 0])

# ===================== 第 2 题 =====================
nums2 = [1, 2, 2, 3, 4, 4, 4, 5]
print("去重后个数:", len(set(nums2)))

def concat(t1, t2):
    return t1 + t2

print("拼接:", concat((1, 2), (3, 4)))

# ===================== 第 3 题 =====================
scores = {"张三": 85, "李四": 58, "王五": 72}

scores["李四"] += 2          # 58 -> 60
print("-- 及格的同学 --")
for name, score in scores.items():
    if score >= 60:
        print(f"{name}:{score}")

print("-- 按分数从高到低 --")
for name, score in sorted(scores.items(), key=lambda x: x[1], reverse=True):
    print(f"{name}:{score}")

# 附加小练习:按名字升序(把 key 改成取 x[0])
print("-- 按名字升序 --")
for name, score in sorted(scores.items(), key=lambda x: x[0]):
    print(f"{name}:{score}")

# ===================== 第 4 题 =====================
import random

path = "scores.txt"
with open(path, "w", encoding="utf-8") as f:
    for _ in range(5):
        f.write(f"{random.randint(1, 100)}\n")

nums3 = []
with open(path, "r", encoding="utf-8") as f:
    for line in f:
        nums3.append(int(line.strip()))

print("个数:", len(nums3))
print("总和:", sum(nums3))
print(f"平均值: {sum(nums3) / len(nums3):.2f}")
print("最大值:", max(nums3))
# 附加小练习:手动把 scores.txt 改成缺数据的一行,再跑这里,
# int(line.strip()) 会对 "42" 之外的坏数据抛 ValueError

# ===================== 第 5 题 =====================
class Student:
    def __init__(self, name, scores):
        self.name = name
        self.scores = scores

    def average(self):
        return sum(self.scores) / len(self.scores)

    def passed(self):
        return self.average() >= 60

students = [
    Student("张三", [70, 80, 90]),
    Student("李四", [40, 50, 60]),
    Student("王五", [55, 62, 71]),
]
for s in students:
    ok = "及格" if s.passed() else "不及格"
    print(f"{s.name} 平均 {s.average():.1f} {ok}")

# ===================== 第 6 题 =====================
import numpy as np

arr = np.random.randint(0, 10, size=(3, 4))
print("原数组:\n", arr)
print("shape:", arr.shape)
print("转置:\n", arr.T)
print("每列和:", arr.sum(axis=0))
print(">5 的元素数:", (arr > 5).sum())

arr[arr > 5] = 0
print("替换后:\n", arr)

# ===================== 第 7 题 =====================
a, b, c = [10, 20, 30]
print(a, b, c)

a, b = "hello", "world"
a, b = b, a
print(a, b)               # world hello

# 预言验证:
# name, salary, dept = "张三,5000".split(",")
#   -> ValueError: not enough values to unpack (expected 3, got 2)
# name, salary, dept = "张三,5000,算法,备注".split(",")
#   -> ValueError: too many values to unpack (expected 3)

# ===================== 第 8 题 =====================
scores8 = {"张三": 85, "李四": 60, "王五": 72}

print("-- 8.1 按名字升序 --")
for name, score in sorted(scores8.items(), key=lambda x: x[0]):
    print(f"{name}:{score}")

data = [("算法", 3), ("部署", 5), ("视觉", 2)]
print("-- 8.2 按人数从大到小 --")
for name, cnt in sorted(data, key=lambda x: x[1], reverse=True):
    print(f"{name}:{cnt}")

print("-- 8.3 先分数降序,再名字升序 --")
for name, score in sorted(scores8.items(), key=lambda x: (x[1], x[0]), reverse=True):
    print(f"{name}:{score}")

# ===================== 第 9 题 =====================
words = ["apple", "banana", "apple", "cherry", "banana", "apple", "date"]
count = {}
for w in words:
    count[w] = count.get(w, 0) + 1

print("统计结果:", count)
print("-- 出现 >= 2 次 --")
for w, c in count.items():
    if c >= 2:
        print(w, c)
print("-- 按次数从高到低 --")
for w, c in sorted(count.items(), key=lambda x: x[1], reverse=True):
    print(f"{w}:{c}")

# ===================== 第 10 题 =====================
sentence = "hello world python is fun"
print("单词长度:", [len(w) for w in sentence.split()])   # [5, 5, 6, 2, 3]

def is_palindrome(s):
    return s == s[::-1]

print("level 回文?", is_palindrome("level"))
print("hello 回文?", is_palindrome("hello"))

def is_palindrome2(s):
    s = s.lower().replace(" ", "")
    return s == s[::-1]

print("A man a plan... 回文?", is_palindrome2("A man a plan a canal Panama"))

# ===================== 第 11 题 =====================
path11 = "students.txt"
names = ["张三", "李四", "王五", "赵六", "钱七"]
with open(path11, "w", encoding="utf-8") as f:
    for name in names:
        f.write(f"{name},{random.randint(40, 100)}\n")

students11 = []
with open(path11, "r", encoding="utf-8") as f:
    for line in f:
        name, score = line.strip().split(",")
        students11.append((name, int(score)))

scores11 = [s for _, s in students11]
best = max(students11, key=lambda x: x[1])
print(f"最高分: {best[0]} {best[1]}")
print(f"平均分: {sum(scores11) / len(scores11):.2f}")
print("不及格(<60):")
for name, score in students11:
    if score < 60:
        print(f"  {name}:{score}")

# ===================== 第 12 题 =====================
a12 = np.array([1, 2, 3, 4])
b12 = np.array([10, 20, 30, 40])
print("a+b:", a12 + b12)
print("b-a:", b12 - a12)
print("a*2:", a12 * 2)

arr12 = np.random.randint(0, 100, size=10)
print("arr:", arr12)
print("最大值:", arr12.max())
print("最大值下标:", np.argmax(arr12))
print(">50 的元素:", arr12[arr12 > 50])

m12 = np.random.randint(0, 10, size=(3, 4))
print("每行和(axis=1):", m12.sum(axis=1))
