#include <iostream>
#include <string>
#include "BigInteger.h"

using namespace std;

int main() {
	string num1, num2;
	cout << "請輸入整數1：" << endl;
	cin >> num1;
	cout << "請輸入整數2：" << endl;
	cin >> num2;
	BigInteger a(num1);
	BigInteger b(num2);
	BigInteger res;
	cout << "============================" << endl;
	if (a < b)
		res = BigInteger::gcd(b, a);
	else
		res = BigInteger::gcd(a, b);
	
	cout << "這兩個整數的最大公因數為：" << res << endl;
	

	return 0;
}