from random import random
from math import gcd

 # b^n mod m
def Mod_Repeat_Square(b,n,m):
    a = 1
    # 將指數轉為2進制的形式
    while n!=0:
        if n%2 == 1:
            a = (a*b)%m
        b = (b**2)%m
        n//=2
    return a          

# Fermat素性檢驗
# n為待檢測的整數，rounds為檢測的輪數
# 1為通過素性檢驗，反之
def fermat_test(n, rounds):
    for i in range(rounds):
        b = int((n - 4) * random() + 2)# 生成一個[2,n-2]之間的隨機數
        if gcd(b, n) > 1:
            return 0
        r = Mod_Repeat_Square(b, n - 1, n)
        if r != 1:
            return 0
    return 1

num = int(input("請輸入要檢測的整數num = "))
rounds = int(input("請輸入檢測的輪數t = "))
res = fermat_test(num,rounds)
if not res:
    print(f"{num}沒有通過Fermat素性檢驗，一定不是素數")
else:
    print(f"{num}通過了Fermat素性檢驗，是素數的可能性>{(1-1/(2**rounds))*100}%")
