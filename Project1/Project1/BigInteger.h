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
    BigInteger& operator++();
    BigInteger& operator+=(int);
    bool operator<(BigInteger bi);
    bool operator<=(BigInteger bi);
    string toString();

public:
    static const int BASE = 10000;
    static const int WIDTH = 4;
    vector<int> s;
    int len;

};