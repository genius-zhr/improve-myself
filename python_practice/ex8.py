scores = {"张三": 85, "李四": 60, "王五": 72}
for score in sorted(scores.items(),key=lambda x:x[0],reverse=True):
    print(f"{score[0]}的成绩{score[1]}")
datas = [("算法", 3), ("部署", 5), ("视觉", 2)]
for data in sorted(datas,key=lambda x:x[1],reverse=True):
    print(f"{data[0]}的学分{data[1]}")
def compare(x1,x2):
    if x1[1] != x2[1]:
        return x2[1] < x1[1]
    return x1[0] > x2[0]
scores = {"张三": 85, "李四": 85, "王五": 72}
for score in sorted(scores.items(),compare):
    print(f"{score[0]}的成绩{score[1]}")