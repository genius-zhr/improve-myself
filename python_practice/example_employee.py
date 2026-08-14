# -*- coding: utf-8 -*-
# =========================================================
# 示例:Python 版「员工管理」——对照你的 C++ 职工管理系统
#
# 跑法:  python3 example_employee.py
#
# 步骤:
#   1. 先整体读一遍,重点看注释里「≈ C++ 的什么」
#   2. 跑起来,看输出
#   3. 动手改一改:加个字段、加个查询函数,跑通就行
#   4. 然后去做 练习_Week3巩固.md 里的题
# =========================================================

# ---------- 1. 数据:dict + list ≈ C++ 的 struct / map / vector ----------
# dict 用 {键: 值},list 用 [],都不用声明类型
employees = [
    {"name": "张三", "salary": 5000, "dept": "算法"},
    {"name": "李四", "salary": 8000, "dept": "部署"},
]

# ---------- 2. 函数:def,不需要写返回类型 ----------
def avg_salary(emp_list):
    # 列表推导式的变体「生成器表达式」: 对每个 e 取 e["salary"] 再求和
    if not emp_list:
        return 0
    return sum(e["salary"] for e in emp_list) / len(emp_list)

def find_by_dept(emp_list, dept):
    # 列表推导式: [对每个元素做什么  for 元素 in 列表  if 条件]
    return [e["name"] for e in emp_list if e["dept"] == dept]

# ---------- 3. 类:__init__ ≈ 构造函数,self ≈ this ----------
class Employee:
    def __init__(self, name, salary, dept):
        self.name = name          # ≈ this->name = name
        self.salary = salary
        self.dept = dept

    def info(self):               # ≈ 成员函数
        return f"{self.name} | {self.salary} | {self.dept}"   # f-string 拼字符串

    def raise_salary(self, amount):
        self.salary += amount

# ---------- 4. 文件读写:with ≈ RAII,自动关文件 ----------
def save_to_file(emp_list, path):
    with open(path, "w", encoding="utf-8") as f:
        for e in emp_list:
            f.write(f"{e.name},{e.salary},{e.dept}\n")

def load_from_file(path):
    result = []
    with open(path, "r", encoding="utf-8") as f:
        for line in f:
            name, salary, dept = line.strip().split(",")   # 元组解包:一行拆成三个变量
            result.append(Employee(name, int(salary), dept))
    return result

# ---------- 5. 主流程:只有直接跑这个文件时才执行 ----------
# (别的文件 import 它时不会执行,这是 Python 的常用写法)
if __name__ == "__main__":
    print("平均工资:", avg_salary(employees))
    print("算法部门的人:", find_by_dept(employees, "算法"))

    staff = [Employee("张三", 5000, "算法"), Employee("李四", 8000, "部署")]
    staff.append(Employee("王五", 6000, "算法"))   # append ≈ vector.push_back
    staff[0].raise_salary(1000)                    # 张三 5000 -> 6000

    print("\n-- 员工列表 --")
    for e in staff:
        print(e.info())

    save_to_file(staff, "staff.txt")
    print("\n-- 从 staff.txt 读回 --")
    for e in load_from_file("staff.txt"):
        print(e.info())
