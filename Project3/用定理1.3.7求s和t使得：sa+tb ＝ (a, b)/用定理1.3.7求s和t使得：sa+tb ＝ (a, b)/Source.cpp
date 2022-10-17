#include <iostream>
#include <string>
#include "BigInteger.h"

using namespace std;

int n = 0;

int gcd(int a, int b) {
	if (b == 0)return a;
	n++;
	return gcd(b, a % b);
}

int r(int i, int a, int b) {
	if (i == -2) {
		return a;
	}
	if (i == -1) {
		return b;
	}

	return r(i - 2, a, b) % r(i - 1, a, b);
}

int sfunc(int a,int b,int i) {
	if (i == -2)return 1;
	if (i == -1)return 0;
	int q = r(i - 2, a, b) / r(i-1, a, b);

	return q* (-1) * sfunc(a, b, i - 1) + sfunc(a, b, i - 2);

}

int tfunc(int a, int b, int i) {
	if (i == -2)return 0;
	if (i == -1)return 1;
	int q = r(i - 2, a, b) / r(i-1, a, b);

	return q* (-1) * tfunc(a, b, i - 1) + tfunc(a, b, i - 2);

}




int main() {
	string num1, num2;
	cout << "請輸入正整數a：" << endl;
	cin >> num1;
	cout << "請輸入正整數b：" << endl;
	cin >> num2;
	BigInteger a(num1);
	BigInteger b(num2);
	BigInteger count("0");
	cout << "=============計算中=============" << endl;

	BigInteger s;
	BigInteger t;
	if (a > b) {
		BigInteger::gcd(a, b, count);
		s = BigInteger::calc_s(a, b, count - BigInteger("2"));
		t = BigInteger::calc_t(a, b, count - BigInteger("2"));
		cout <<"s == " << s << "\tt == " << t << endl;	
	}
	else {
		BigInteger::gcd(b, a, count);
		s = BigInteger::calc_s(b, a, count - BigInteger("2"));
		t = BigInteger::calc_t(b, a, count - BigInteger("2"));
		cout << "s == " << t << "\tt == " << s << endl;
	}

	return 0;
}