#include <iostream>
#include "BigInteger.h"

using namespace std;

int main() {
	string num1, num2;
	int base;
	char oper;
	cout << "Ոݔ��Ҫ�M��n�M�Ƶ��\��(2��8��16)��";
	cin >> base;
	cout << endl;
	cout << "Ոݔ���1��"<<base<<"�M�Ɣ�num1��";
	cin >> num1;
	cout << endl;
	cout << "Ոݔ���2��" << base << "�M�Ɣ�num2��";
	cin >> num2;
	cout << endl;
	cout << "Ոݔ��Ҫ�M��ʲ�N�\��(+��-��*)��";
	cin >> oper;
	cout << endl;
	cout << "------------------------------------------�\����------------------------------------------" << endl;

	string res = BigInteger::BaseOperation(num1, num2, base, oper);
	cout << "�\��Y����num1 " << oper << " num2 = " << res <<"\t("<<base<<"�M��)" << endl;


}