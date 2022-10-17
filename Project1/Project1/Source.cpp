#include <iostream>
#include "BigInteger.h"
#include <string>
#include <fstream>

using namespace std;

#define STOREPATH "store.txt"

// ���_STOREPATH�ļ������l�Fnum�ִ���������num�����ؔ�
bool isPrime(string num) {
	ifstream ifs(STOREPATH, ios::in);
	string buf;
	while (getline(ifs,buf)) {
		if (buf == num)return false;
	}
	ifs.close();
	return true;
}

// Eratosthenes�Y��
void Eratosthenes(string n) {
	
	ofstream ofs;

	// ÿ�ζ������֮ǰ�Y�x��ӛ�
	ofs.open(STOREPATH, ios::trunc);
	ofs.close();

	BigInteger i("2");
	BigInteger end(n);
	for (; i <= end; ++i) {
		if (isPrime(i.toString())) {
			cout << i << endl;

			// Eratosthenes�Y���ĺ��Č��F��
			if (i * i <= end) {
				// j = i*2
				BigInteger j = i * BigInteger("2");
				ofs.open(STOREPATH, ios::app);
				while(j <= end) {
					ofs << j.toString() << endl;
					// j = 3*j ,j = 4*j, ... , j = k*j����v�����ؔ��ı���
					j = j + i;
				}
				ofs.close();
			}
		}
	}

}

int main() {
	cout << "Ոݔ������( 10�M��300λ�ԃ� )��" << endl;
	string bigNum;
	cin >> bigNum;
	cout << "������[2," << bigNum << "]�����ȵ������ؔ�( Ո���ĵȴ� )��" << endl;
	Eratosthenes(bigNum);

	return 0;
}