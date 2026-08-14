class Student:
    def __init__(self,name,scores):
        self.name=name
        self.score=scores
    def average(self):
        self.avg=sum(self.score)/len(self.score)
        return self.avg
    def passed(self):
        return self.avg>=60
students=[
    Student("张三",[80,90,70]),
    Student("李四",[50,60,70]),
    Student("王五",[40,50,60])
]
for student in students:
    print(f"{student.name}的平均分为:{student.average()},是否及格:{student.passed()}")
