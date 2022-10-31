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



if __name__ == "__main__":
    print("b,n,m的關係為： b^n ( mod m )")
    b = int(input("請輸入b："))
    n = int(input("請輸入n："))
    m = int(input("請輸入m："))
    res = Mod_Repeat_Square(b,n,m)
    print("結果為：",res)
