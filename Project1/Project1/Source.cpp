#include <iostream>
#include "BigInteger.h"
#include <string>
#include <fstream>

using namespace std;

#define STOREPATH "store.txt"

// 打開STOREPATH文件，若發現num字串，即代表num不是素數
bool isPrime(string num) {
	ifstream ifs(STOREPATH, ios::in);
	string buf;
	while (getline(ifs,buf)) {
		if (buf == num)return false;
	}
	ifs.close();
	return true;
}

// Eratosthenes篩法
void Eratosthenes(string n) {
	
	ofstream ofs;

	// 每次都先清空之前篩選的記錄
	ofs.open(STOREPATH, ios::trunc);
	ofs.close();

	BigInteger i("2");
	BigInteger end(n);
	for (; i <= end; ++i) {
		if (isPrime(i.toString())) {
			cout << i << endl;

			// Eratosthenes篩法的核心實現：
			if (i * i <= end) {
				// j = i*2
				BigInteger j = i * BigInteger("2");
				ofs.open(STOREPATH, ios::app);
				while(j <= end) {
					ofs << j.toString() << endl;
					// j = 3*j ,j = 4*j, ... , j = k*j，遍歷所有素數的倍數
					j = j + i;
				}
				ofs.close();
			}
		}
	}

}

int main() {
	cout << "請輸入整數( 10進制300位以內 )：" << endl;
	string bigNum;
	cin >> bigNum;
	cout << "以下是[2," << bigNum << "]範圍內的所有素數( 請耐心等待 )：" << endl;
	Eratosthenes(bigNum);

	return 0;
}