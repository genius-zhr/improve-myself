grade={"张三": 85, "李四": 58, "王五": 72}
grade["李四"]=60
for name,score in grade.items():
    if score>=60:
        print(f"{name}:{score}")
for name,score in sorted(grade.items(),key=lambda x:x[1],reverse=False):
    print(f"{name}:{score}")