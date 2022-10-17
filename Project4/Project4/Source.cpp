#include <iostream>
#include "BigInteger.h"

using namespace std;

int main() {
	string num1, num2;
	int base;
	char oper;
	cout << "請輸入要進行n進制的運算(2、8、16)：";
	cin >> base;
	cout << endl;
	cout << "請輸入第1個"<<base<<"進制數num1：";
	cin >> num1;
	cout << endl;
	cout << "請輸入第2個" << base << "進制數num2：";
	cin >> num2;
	cout << endl;
	cout << "請輸入要進行什麼運算(+、-、*)：";
	cin >> oper;
	cout << endl;
	cout << "------------------------------------------運算中------------------------------------------" << endl;

	string res = BigInteger::BaseOperation(num1, num2, base, oper);
	cout << "運算結果：num1 " << oper << " num2 = " << res <<"\t("<<base<<"進制)" << endl;


}