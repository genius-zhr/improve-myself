import random
path="students.txt"
with open(path, "w",encoding="utf-8") as f:
   names = ["张三", "李四", "王五", "赵六", "钱七"]
   for name in names:
      f.write(f"{name},{random.randint(1,100)}\n")
students=[]
with open(path,"r",encoding="utf-8") as fl:
   for line in fl:
       name,score = line.strip().split(",")
       students.append((str(name), int(score)))
print(students)
sorted_students = sorted(students,key=lambda x:x[1],reverse=True)
print(sorted_students)
name,score=sorted_students[0]
print(f"最高分的同学是{name},成绩是{score}")
avg=sum(score for _,score in students)/len(students)
print(f"平均分是:{avg}")
print("不及格的人有:\n"+"\n".join(f"{name}:{score}" for name,score in students if score<60))
