#include <iostream>
#include "BigInteger.h"
using namespace std;



int main() {
	string num1, num2;
	cout << "Ոݔ�뱻������" << endl;
	cin >> num1;
	cout << "Ոݔ�������" << endl;
	cin >> num2;
	BigInteger bigNum1(num1);
	BigInteger bigNum2(num2);
	BigInteger remainder;
	BigInteger quotient = bigNum1.calcQuotientAndRemainder(bigNum2, remainder);
	cout << "=====================================" << endl;

	cout << "�̔��飺" << quotient << endl;
	cout << "�N���飺" << remainder << endl;
	return 0;
}