sentence = "hello world python is fun"
list=[]
for word in sentence.split(" "):
    list.append(len((word).strip()))
print(list)
def is_palindrome(s):
    s=s.lower().replace(" ","")
    return s==s[::-1]
print(is_palindrome("A man a plan a canal Panama") if is_palindrome("A man a plan a canal Panama") else "不是回文")
    