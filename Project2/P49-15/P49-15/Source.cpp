#include <iostream>
#include "BigInteger.h"

using namespace std;

int main() {
	string numA, numB;
	cout << "Ոݔ������A��" << endl;
	cin >> numA;
	cout << "Ոݔ������B��" << endl;
	cin >> numB;
	BigInteger a(numA);
	BigInteger b(numB);
	BigInteger c = a % b;
	cout << "=====================================" << endl;
	if (c == BigInteger("0")) {
		cout << "A�ܱ�B����" << endl;
	}
	else {
		cout << "A���ܱ�B����" << endl;
	}
}