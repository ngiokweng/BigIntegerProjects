#include <iostream>
#include "BigInteger.h"

using namespace std;

int main() {
	string numA, numB;
	cout << "請輸入整數A：" << endl;
	cin >> numA;
	cout << "請輸入整數B：" << endl;
	cin >> numB;
	BigInteger a(numA);
	BigInteger b(numB);
	BigInteger c = a % b;
	cout << "=====================================" << endl;
	if (c == BigInteger("0")) {
		cout << "A能被B整除" << endl;
	}
	else {
		cout << "A不能被B整除" << endl;
	}
}