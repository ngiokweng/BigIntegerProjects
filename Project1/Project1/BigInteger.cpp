#include "BigInteger.h"

//乘法操作
BigInteger BigInteger::operator*(BigInteger bi) {
	BigInteger res;
	int n1 = this->len, n2 = bi.len;
	res.s.resize(n1 + n2 + 1);
	for (int i = 0; i<n1; i++) {
		int carry = 0;
		for (int j = 0; j<n2; j++) {
			int cur = this->s[i] * bi.s[j];
			carry = cur / BASE;

			res.s[i + j] += cur;
			if (res.s[i + j] >= BASE) {
				res.s[i + j + 1] += res.s[i + j] / BASE;
				res.s[i + j] %= BASE;
				res.len = i + j + 2;
			}
			else {
				res.len = i + j + 1;
			}

			//res.s[i + j + 1] += carry;
			////記錄長度，方便遍歷
			//if (res.s[i + j + 1] != 0) {
			//	res.len = i + j + 2;
			//}
			//else {
			//	res.len = i + j+1;
			//}
			//cur %= BASE;
			//res.s[i + j] += cur;
			//if (res.s[i + j] >= BASE) {
			//	res.s[i + j + 1] += res.s[i + j] / BASE;
			//	res.s[i + j] %= BASE;
			//}
		}
	}
	return res;
}

//初始化構造
BigInteger::BigInteger(string num) {
	if (num == "") {
		len = 0;
		return;
	}
	//注：低位數據存放在this->s的低索引處
	int n = num.length();
	//保存大數數組長度
	len = n % WIDTH == 0 ? n / WIDTH : n / WIDTH + 1;
	int i,k = 0;
    bool flag = true;
	for (i = n - 1; i >= 0 && flag; i-=4) {
		int val = 0;
		for (int j = 0; j < 4; j++) {
			if (i - j < 0) {
				flag = false;
				break;
			}
			val += (num[i - j] - '0') * pow(10, WIDTH - 4 + j);
		}
		this->s.emplace_back(val);
	}

}


ostream& operator<<(ostream& cout, BigInteger& b) {
	for (int i = b.len-1; i >= 0; i--) {
		//當不為最高位時，若大數數組不足WIDTH位需補0在前
		if (i != b.len-1) {
			int tmp = b.s[i];
			// 若為0直接補3個'0'，之後cout << b.s[i]，共輸出4個'0'
			if (tmp == 0) {
				cout << "000";
				
			}
			else {
				while (tmp< pow(10, b.WIDTH - 1)) {
					cout << '0';
					tmp *= 10;
				}
			}
		}

		cout << b.s[i];
	}
	return cout;
}

BigInteger& BigInteger::operator++() {
	int i,lim = pow(10, WIDTH);
	for (i = 0; i < this->len; i++) {
		//若不超出單位儲存格規定的上限時，就直接++
		if (this->s[i] + 1 < lim) {
			this->s[i]++;
			break;
		}
		else {  //否則需要進位
			this->s[i] = 0;
			// 當是【數組最後一個】需要進位時
			if (i == len - 1) {
				// 判斷空間是否足夠，若不夠：
				if (this->s.size() == len) {
					this->s.emplace_back(1);
					this->len++;
				}
				else {
					this->s[i+1]++;
				}
				break;
			}
			else {
				this->s[i + 1]++;
				// 當本次進位不會使下次也進位時，直接break
				if (this->s[i + 1] < lim)break;
			}

		}
	}

	
	return *this;
}

BigInteger& BigInteger::operator+=(int addNum) {
	int i, lim = pow(10, WIDTH);
	this->s[0] += addNum;
	int carry = this->s[0]/BASE;
	if (carry != 0) {
		this->s[0] %= BASE;
		for (i = 1; i < this->len && carry!=0; i++) {
			this->s[i] += carry;
			carry = this->s[i] / BASE;
			this->s[i] %= BASE;
		}

		//最後要作特別處理
		if (i == len && carry!=0) {
			// 判斷空間是否足夠，若不夠：
			if (this->s.size() == len) {
				this->s.emplace_back(1);
				this->len++;
			}
			else {
				this->s[i + 1]++;
			}
		}
	}
	return *this;
}

BigInteger BigInteger::operator+(BigInteger bi) {
	BigInteger res;
	int newSize = max(this->len, bi.len) + 1;
	res.s.resize(newSize);
	int carry = 0,minSize = min(this->len, bi.len);
	int i;
	for (i = 0; i < minSize; i++) {
		res.s[i] = this->s[i] + bi.s[i] + carry;
		carry = res.s[i] / BASE;
		res.s[i] %= BASE;
		res.len++;
	}

	for (; i < newSize - 1; i++) {
		if (this->len > bi.len)
			res.s[i] = this->s[i] + carry;
		else
			res.s[i] = bi.s[i] + carry;

		carry = res.s[i] / BASE;
		res.s[i] %= BASE;
		res.len++;
	}

	if (carry != 0) {
		res.s[i] += carry;
		res.len++;
	}
	return res;
}

string BigInteger::toString() {
	string str = "";
	for (int i = len - 1; i >= 0; i--) {
		//當不為最高位時，若大數數組不足WIDTH位需補0在前
		if (i != len - 1) {
			int tmp = s[i];
			// 若為0直接補3個'0'，之後cout << b.s[i]，共輸出4個'0'
			if (tmp == 0) {
				str+="000";

			}
			else {
				while (tmp < pow(10, WIDTH - 1)) {
					str += '0';
					tmp *= 10;
				}
			}
		}

		str += to_string(s[i]);
	}
	return str;
}

bool BigInteger::operator<(BigInteger bi) {
	if (this->len < bi.len)return true;
	else if (this->len > bi.len)return false;

	for (int i = this->len - 1; i >= 0; i--) {
		if (this->s[i] < bi.s[i])return true;
		else if (this->s[i] > bi.s[i])return false;
	}
	return false;
}

bool BigInteger::operator<=(BigInteger bi) {
	if (this->len < bi.len)return true;
	else if (this->len > bi.len)return false;

	for (int i = this->len - 1; i >= 0; i--) {
		if (this->s[i] < bi.s[i])return true;
		else if(this->s[i] > bi.s[i])return false;
	}
	return true;
	
}