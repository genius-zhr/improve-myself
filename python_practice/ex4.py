import random
with open ("scores.txt","w",encoding="utf-8") as f:
    for i in range(0,5):
        name="学生"+str(i+1)
        score=random.randint(0,100)
        f.write(f"{name}:{score}\n")
nums=[]
with open("scores.txt","r",encoding="utf-8") as f:
    for line in f:
        name,score=line.strip().split(":")
        nums.append(int(score))
print("个数:",len(nums))
print("总分:",sum(nums))
print("平均分:",sum(nums)/len(nums))

    