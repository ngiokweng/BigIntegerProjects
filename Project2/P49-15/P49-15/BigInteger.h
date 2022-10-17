#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;


class BigInteger {
friend ostream& operator<<(ostream& cout, BigInteger& p);
public:
    BigInteger(string num = "");

    BigInteger operator*(BigInteger bi);
    BigInteger operator+(BigInteger bi);
    BigInteger operator-(BigInteger bi);
    BigInteger operator%(BigInteger divisor);
    BigInteger& operator++();
    BigInteger& operator+=(int);

    /***** 只能對正整數進行比較 *****/
    bool operator<(BigInteger bi);
    bool operator<=(BigInteger bi);
    bool operator==(BigInteger bi);
    bool operator!=(BigInteger bi);

    // 類型轉換：BigInteger -> string
    string toString();
    //將bi的位數擴展到與*this相同 or 相差1 ( 即將bi.s長度+1，令bi.s[0+addbit]=0，原本的值全部順移)
    BigInteger expandBit(BigInteger bi);

public:
    static const int BASE = 10000;  
    static const int WIDTH = 4; // s數組每格存放的位數
    vector<int> s; // 低索引存放低位。例如"12345"，s[0] = 2345, s[1] = 1
    int len;
    bool isNegative = false;  // 是否負數

};