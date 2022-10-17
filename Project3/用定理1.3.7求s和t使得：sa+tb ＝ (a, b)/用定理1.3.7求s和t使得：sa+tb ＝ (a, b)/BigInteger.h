#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;


class BigInteger {
friend ostream& operator<<(ostream& cout, BigInteger& p);
public:
    BigInteger(string num = "");

    //乘法：兼容正數or負數的乘法
    BigInteger operator*(BigInteger bi);
    // 加法：兼容正數or負數的加法
    BigInteger operator+(BigInteger bi);
    // 減法：*this是被減數，bi是減數，要用【正數 - 正數】
    BigInteger operator-(BigInteger bi);
    BigInteger operator%(BigInteger divisor);
    BigInteger operator/(BigInteger divisor);
    BigInteger& operator++();
    BigInteger& operator+=(int);


    /***** 只能對正整數進行比較 *****/
    bool operator<(BigInteger bi);
    bool operator<=(BigInteger bi);
    bool operator>(BigInteger bi);
    bool operator>=(BigInteger bi);
    bool operator==(BigInteger bi);
    bool operator!=(BigInteger bi);

    //功能：類型轉換，BigInteger -> string
    string toString();
    //功能：將bi的位數擴展到與*this相同 or 相差1 ( 即將bi.s長度+1，令bi.s[0+addbit]=0，原本的值全部順移)
    BigInteger expandBit(BigInteger bi);
    //功能：返回調用expandBit()後，需要乘上多少(n)才能與被除數最接近( n小於BASE )，res擴位存放結果
    int expandBit_Ex(BigInteger bi,BigInteger& res);
    //功能：在實現方面與operator/基本一樣，差別在於會從參數中【返回餘數】
    BigInteger calcQuotientAndRemainder(BigInteger divisor,BigInteger& remainder);
    //功能：求最大公因數( a需要>=b )，count為次數
    static BigInteger gcd(BigInteger a,BigInteger b,BigInteger& count);
    /************** 計算貝祖係數(s,t)相關的API ***************/
    static BigInteger calc_s(BigInteger a, BigInteger b, BigInteger i); // 計算系數s
    static BigInteger calc_t(BigInteger a, BigInteger b, BigInteger i); // 計算系數t
    static BigInteger calc_r(BigInteger a, BigInteger b, BigInteger i); // 計算餘數( 進而求得"不完全商" )

    

public:
    static const int BASE = 10000;  // 基數
    static const int WIDTH = 4; // s數組每格存放的位數
    vector<int> s; // 低索引存放低位。例如"12345"，s[0] = 2345, s[1] = 1
    int len;
    bool isNegative = false;  // 是否負數

};