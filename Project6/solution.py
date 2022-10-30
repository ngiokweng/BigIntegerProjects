# 编程实现Diffie-Hellman 密钥共享算法。(要求对十进制300位以上的整数实现)。


from math import gcd
from random import randint

def quickMulMod(a,b,m):
    '''a*b%m,  quick'''
    ret = 0
    while b:
        if b&1:
            ret = (a+ret)%m
        b//=2
        a = (a+a)%m
    return ret

def quickPowMod(a,b,m):
    '''a^b %m, quick,  O(logn)'''
    ret =1
    while b:
        if b&1:
            ret =quickMulMod(ret,a,m)
        b//=2
        a = quickMulMod(a,a,m)
    return ret


def isPrime(n,t=5):
    '''miller rabin primality test,  a probability result
        t is the number of iteration(witness)
    '''
    t = min(n-3,t)
    if n<2:
        print('[Error]: {} can\'t be classed with prime or composite'.format(n))
        return
    if n==2: return True
    d = n-1
    r = 0
    while d%2==0:
        r+=1
        d//=2
    tested=set()
    for i in range(t):
        a = randint(2,n-2)
        while a in tested:
            a = randint(2,n-2)
        tested.add(a)
        x= quickPowMod(a,d,n)
        if x==1 or x==n-1: continue  #success,
        for j in range(r-1):
            x= quickMulMod(x,x,n)
            if x==n-1:break
        else:
            return False
    return True

if __name__ == "__main__":

    flag = True
    # 1.  Alice(或Bob) 选取素数 p 和正整数 g , 1≤g≤p且(g, p)＝1. 公开 p 和 g.
    while flag:
        p = int(input("Alice(或Bob)選取的素數p = "))
        g = int(input("Alice(或Bob)選取的正整數g (1≤g≤p且與p亙素) = "))
        if isPrime(p) and gcd(p,g) == 1:
            flag = False
        else:
            print("輸入有誤，請重新輸入")
    
    # 2.  Alice 选取 x 屬於 {1, 2, … , p-1}，计算R1＝g^x (mod p) 并将R1 发送给Bob
    x = int(input("Alice選取x (範圍：0~p-1) = "))
    R1 = quickPowMod(g,x,p)
    print("R1 = (g^x)(mod p) = ",R1)
    # 3.  Bob 选取 y 屬於 {1, 2, … , p-1} ，计算 R2＝g^y (mod p)并将R2 发送给Alice
    y = int(input("Bob選取y (範圍：0~p-1) = "))
    R2 = quickPowMod(g,y,p)
    print("R2 = (g^y)(mod p) = ",R2)

    # 4. 计算密钥 
    k = quickMulMod(R2,x,p)
    print("最終雙方計算得到密鑰k = ",k)


    
