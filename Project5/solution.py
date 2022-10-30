# 编程实现RSA公钥密码算法(要求p和q取10进制300位数以上)。

import base64
from Cryptodome.Cipher import PKCS1_v1_5
from Cryptodome import Random
from Cryptodome.PublicKey import RSA

# ----------------------生成密鑰對--------------------------
def create_rsa_pair():
    '''
    创建rsa公钥私钥对
    :param is_save: default:False
    :return: public_key, private_key
    '''
    f = RSA.generate(3072)
    private_key = f.exportKey("PEM")  # 生成私鑰
    public_key = f.publickey().exportKey()  # 生成公鑰
    return public_key, private_key ,f.p,f.q,f.n


# ------------------------加密------------------------
def encryption(text: str, public_key: bytes):
    # 轉為bytes
    text = text.encode('utf-8')
    # 構建公鑰對象
    cipher_public = PKCS1_v1_5.new(RSA.importKey(public_key))
    # 加密（bytes）
    text_encrypted = cipher_public.encrypt(text)
    # base64編碼，並轉為字符串
    text_encrypted_base64 = base64.b64encode(text_encrypted).decode()
    return text_encrypted_base64


# ------------------------解密------------------------
def decryption(text_encrypted_base64: str, private_key: bytes):
    # 轉為bytes
    text_encrypted_base64 = text_encrypted_base64.encode('utf-8')
    # base64解碼
    text_encrypted = base64.b64decode(text_encrypted_base64)
    # 構建私鑰對象
    cipher_private = PKCS1_v1_5.new(RSA.importKey(private_key))
    # 解密（bytes）
    text_decrypted = cipher_private.decrypt(text_encrypted, Random.new().read)
    # 解码为字符串
    text_decrypted = text_decrypted.decode()
    return text_decrypted


if __name__ == '__main__':

    text = str(input("請輸入要加密的明文："))
    public_key, private_key,p,q,n = create_rsa_pair()
    print("p = ",p)
    print("q = ",q)
    print("n = p * q = ",n )
    text_encrypted_base64 = encryption(text, public_key)
    print('加密後的結果：', text_encrypted_base64)

    # 解密
    text_decrypted = decryption(text_encrypted_base64, private_key)
    print('解密後的結果：', text_decrypted)
