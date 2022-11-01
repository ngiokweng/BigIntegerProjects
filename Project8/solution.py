from functools import reduce
def egcd(a, b):
    if 0 == b:
        return 1, 0, a
    x, y, q = egcd(b, a % b)
    x, y = y, (x - a // b * y)
    return x, y, q
def chinese_remainder(pairs):
    mod_list, remainder_list = [p[0] for p in pairs], [p[1] for p in pairs]
    mod_product = reduce(lambda x, y: x * y, mod_list)
    mi_list = [mod_product//x for x in mod_list]
    mi_inverse = [egcd(mi_list[i], mod_list[i])[0] for i in range(len(mi_list))]
    x = 0
    for i in range(len(remainder_list)):
        x += mi_list[i] * mi_inverse[i] * remainder_list[i]
        x %= mod_product
    return x

if __name__=='__main__':
    size = int(input("請輸入同余式組的大小："))
    pairs = []
    for i in range(0,size):
        print("第{}個同余式為： x ≡ b{}( mod m{} )".format(i+1,i,i))
        b = int(input("     請輸入 b{} = ".format(i)))
        m = int(input("     請輸入 m{} = ".format(i)))
        pairs.append((m,b))

    print("x = ",chinese_remainder(pairs))