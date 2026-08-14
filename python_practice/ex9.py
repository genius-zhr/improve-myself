words = ["apple", "banana", "apple", "cherry", "banana", "apple", "date"]
count={}
for w in words:
    count[w]=count.get(w,0)+1
print("统计结果:",count)
for w,c in sorted(count.items(),key=lambda x:x[1]):
    if c>=2:
        print(f"{w}:{c}")