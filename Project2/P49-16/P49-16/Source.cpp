#include <iostream>
#include "BigInteger.h"
using namespace std;



int main() {
	string num1, num2;
	cout << "請輸入被除數：" << endl;
	cin >> num1;
	cout << "請輸入除數：" << endl;
	cin >> num2;
	BigInteger bigNum1(num1);
	BigInteger bigNum2(num2);
	BigInteger remainder;
	BigInteger quotient = bigNum1.calcQuotientAndRemainder(bigNum2, remainder);
	cout << "=====================================" << endl;

	cout << "商數為：" << quotient << endl;
	cout << "餘數為：" << remainder << endl;
	return 0;
}