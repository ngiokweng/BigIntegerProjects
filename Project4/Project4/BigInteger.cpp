#include "BigInteger.h"


//初始化構造
BigInteger::BigInteger(string num) {
	if (num == "") {
		len = 0;
		return;
	}
	
	// 判斷是否負數
	if (num[0] == '-') {
		num = num.substr(1); // 截取【-】後的數字
		this->isNegative = true;
	}

	//注：低位數據存放在this->s的低索引處
	int n = num.length();
	//保存大數數組長度
	len = n % WIDTH == 0 ? n / WIDTH : n / WIDTH + 1;
	int i,k = 0;
    bool flag = true;

	//從字串最高位開始讀( 每次4位 )，這樣比較方便
	for (i = n - 1; i >= 0 && flag; i-=4) {
		int val = 0;
		for (int j = 0; j < 4; j++) {
			if (i - j < 0) { // 當餘下字串不足4位時代表讀取完成
				flag = false;
				break;
			}
			val += (num[i - j] - '0') * pow(10, WIDTH - 4 + j);  // WIDTH是數組每格的位數
		}
		this->s.emplace_back(val);
	}

}


ostream& operator<<(ostream& cout, BigInteger& b) {
	if (b.isNegative)cout << '-';
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
		// 當為最高位，且最高位為0時，直接continue ( 排除只有一位且為0的情況 )
		else {
			if (b.s[i] == 0 && b.len!=1)continue;
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
	/*** 當加數、被加數為1正1負的情況時，調用operator-來處理 ***/
	if (this->isNegative && !bi.isNegative) {
		this->isNegative = false;
		return bi.operator-(*this);
	}
	else if (!this->isNegative && bi.isNegative) {
		bi.isNegative = false;
		return this->operator-(bi);
	}

	BigInteger res;
	int newSize = max(this->len, bi.len) + 1;
	res.s.resize(newSize);
	// 當加數、被加數都為負時，res需設為負
	if (this->isNegative && bi.isNegative)res.isNegative = true;

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

BigInteger BigInteger::operator-(BigInteger bi) {
	BigInteger res;
	int newSize = max(this->len, bi.len), minSize = min(this->len, bi.len);
	res.s.resize(newSize);
	int borrow = 0; // 減法的借位

	// 若 *this<bi，則用bi - *this，最後再設res.isNegative = true ( 代表負數 )
	if (*this < bi) {
		int i = 0;
		for (; i < minSize; i++) {
			borrow = (bi.s[i] - this->s[i])<0?1:0;
			if (borrow == 1)res.s[i + 1]=-1;
			res.s[i] += borrow * BASE + bi.s[i] - this->s[i];
			res.len++;
		}

		for (; i < newSize; i++) {
			res.s[i] += bi.s[i];
			res.len++;
		}

		res.isNegative = true;
	}
	// 若 *this >= bi，則用 *this - bi，最後結果是正數
	else {
		int i = 0;
		for (; i < minSize; i++) {
			borrow = (this->s[i] - bi.s[i]) < 0 ? 1 : 0;
			if (borrow == 1)res.s[i + 1] = -1;
			res.s[i] += borrow * BASE +  this->s[i] - bi.s[i];
			res.len++;
		}

		// 當【被減數】與【減數】長度不同時才會走下面這步
		for (; i < newSize; i++) {
			// 若為0要直接break，否則res的長度會多1，導致各種問題
			if (this->s[i] == 0)break;
			res.s[i] += this->s[i];
			res.len++;
		}

		// 清除多余的前置0( 邏輯上清除 )
		int prevLen = res.len;
		for (int i = prevLen-1; i > 0; i--) { // 索引0不用遍歷
			if (prevLen == 1)break; // 當長度為1時不需清除
			if (res.s[i] != 0)break;
			res.len--;
		}
	}
	return res;
	
}

BigInteger BigInteger::operator%(BigInteger divisor) {
	//注：*this為被除數，bi為除數

	// 被除數
	BigInteger dividend = *this;

	if (dividend == divisor) {
		return BigInteger("0");
	}

	if (dividend < divisor) {
		return *this;
	}

	/*** 當被除數(dividend)的位數大於除數(divisor)的位數時，要對除數(bi) "擴位" ***/
	BigInteger expand_divisor = dividend.expandBit(divisor);
	BigInteger tmp_dividend = dividend;
	while (divisor < dividend) {

		while (1){
			tmp_dividend = dividend - expand_divisor;
			if (tmp_dividend.isNegative) {
				break;
			}
			else {
				dividend = tmp_dividend;
			}
		}
		// 重新擴位
		expand_divisor = dividend.expandBit(divisor);
	}
	return dividend;
 
}

BigInteger BigInteger::operator/(BigInteger divisor) {
	//注：*this為被除數，bi為除數

	// 被除數
	BigInteger dividend = *this;

	if (dividend == divisor) {
		return BigInteger("1");
	}

	if (dividend < divisor) {
		return BigInteger("0");
	}

	string quotientStr = ""; // 商數
	BigInteger expand_divisor; // 除數擴位
	int bitOfQuotient = dividend.expandBit_Ex(divisor,expand_divisor); // 商數的某一位
	//保存商數
	quotientStr = to_string(bitOfQuotient);
	BigInteger tmp_dividend = dividend;
	while (1) {

		while (1) {
			tmp_dividend = dividend - expand_divisor;
			if (tmp_dividend.isNegative) {
				break;
			}
			else {
				dividend = tmp_dividend;
			}
		}
		//當被除數比除數小時直接break
		if (dividend < divisor)break;
		// 重新擴位
		bitOfQuotient = dividend.expandBit_Ex(divisor,expand_divisor);

		string partOfQuotient = to_string(bitOfQuotient);

		/*
		補0，因為bitOfQuotient不一定為4位，可能是像498這樣的，這時要在前面補個0，即0498，否則在最終的商數中會出錯
		可用下例來測試：

		BigInteger a("456963956347984569783569478456963956347984569783569478456963956347984569783569478");
		BigInteger b("3657983975834567896357894936434563456784593879834693459625");
		BigInteger c = a / b;
		cout << c << endl;

		*/
		for (int i = 0; i < 4 - partOfQuotient.length(); i++) {
			quotientStr += '0';
		}
		quotientStr += partOfQuotient;
	}
	return BigInteger(quotientStr);
}

BigInteger BigInteger::operator*(BigInteger bi) {
	BigInteger res;
	int n1 = this->len, n2 = bi.len;
	res.s.resize(n1 + n2 + 1);

	//當1正1負時，res需設為負
	if (!bi.isNegative && this->isNegative || bi.isNegative && !this->isNegative) {
		res.isNegative = true;
	}

	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++) {
			int cur = this->s[i] * bi.s[j];
			res.s[i + j] += cur;
			// 進位&&記錄長度
			if (res.s[i + j] >= BASE) {
				res.s[i + j + 1] += res.s[i + j] / BASE;
				res.s[i + j] %= BASE;
				res.len = i + j + 2;
			}
			else {
				res.len = i + j + 1;
			}
		}
	}
	return res;
}


bool BigInteger::operator<(BigInteger bi) {


	// 對長度進行對比
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

bool BigInteger::operator>(BigInteger bi) {
	if (this->len > bi.len)return true;
	else if (this->len < bi.len)return false;

	for (int i = this->len - 1; i >= 0; i--) {
		if (this->s[i] > bi.s[i])return true;
		else if (this->s[i] < bi.s[i])return false;
	}
	return false;
}

bool BigInteger::operator>=(BigInteger bi) {
	if (this->len > bi.len)return true;
	else if (this->len < bi.len)return false;

	for (int i = this->len - 1; i >= 0; i--) {
		if (this->s[i] > bi.s[i])return true;
		else if (this->s[i] < bi.s[i])return false;
	}
	return true;

}

bool BigInteger::operator==(BigInteger bi) {
	// 判斷1正1負的情況
	if (this->isNegative && !bi.isNegative || !this->isNegative && bi.isNegative)return false;

	if (this->len != bi.len)return false;

	for (int i = this->len - 1; i >= 0; i--) {
		if (this->s[i] != bi.s[i])return false;
	}
	return true;

}

bool BigInteger::operator!=(BigInteger bi) {
	if (this->len != bi.len)return true;

	for (int i = this->len - 1; i >= 0; i--) {
		if (this->s[i] != bi.s[i])return true;
	}
	return false;

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

BigInteger BigInteger::expandBit(BigInteger bi) {
	if (*this < bi)return bi;

	BigInteger tmp;
	tmp.s.resize(this->len+1);  // 直接設置為最大的位數
	tmp.len = bi.len; // 目前還未擴位，因此len還是bi.len，之後會再++
	int addBit = 0; // 存儲擴了多少位
	while (1) {
		tmp.s[addBit++] = 0; // 相當於在尾段補0000
		for (int i = 0; i < bi.len; i++) {
			tmp.s[i + addBit] = bi.s[i];
		}
		tmp.len++;

		// 當擴完位後仍比被除數少時才繼續
		if (tmp < *this) {
			continue;
		}
		else if (*this < tmp) {
			// 當擴完位後比被除數大時，直接退1位
			for (int i = 0; i < tmp.len-1; i++) {
				tmp.s[i] = tmp.s[i + 1];
			}
			tmp.len--;
			addBit--;
			break;
		}
		else {
			return tmp;
		}
	}
	return tmp;
}

int BigInteger::expandBit_Ex(BigInteger bi, BigInteger& res) {

	//先將bi擴大到位數相同
	BigInteger newBi = expandBit(bi);
	

	//再通過分別 乘2、乘3、...、乘n，找到最接近被除數的那個數
	BigInteger i("2");
	BigInteger tmp;
	while (1) {
		tmp = newBi * i;
		// 當乘完後後仍比被除數少時才繼續
		if (tmp < *this) {
			++i;
			continue;
		}
		else if (*this < tmp) {
			i = i - BigInteger("1");
			res = i * newBi;
			// 因為必定小於BASE，所以直接return i.s[0]就可以
			return i.s[0];
		}
		else {
			res = tmp;
			// 因為必定小於BASE，所以直接return i.s[0]就可以
			return i.s[0];
		}
		
	}
}

BigInteger BigInteger::calcQuotientAndRemainder(BigInteger divisor, BigInteger& remainder) {
	//注：*this為被除數，bi為除數

	// 被除數
	BigInteger dividend = *this;

	if (dividend == divisor) {
		return BigInteger("1");
	}

	if (dividend < divisor) {
		return BigInteger("0");
	}

	string quotientStr = ""; // 商數
	BigInteger expand_divisor; // 除數擴位
	int bitOfQuotient = dividend.expandBit_Ex(divisor, expand_divisor); // 商數的某一位
	//保存商數
	quotientStr = to_string(bitOfQuotient);
	BigInteger tmp_dividend = dividend;
	while (1) {

		while (1) {
			tmp_dividend = dividend - expand_divisor;
			if (tmp_dividend.isNegative) {
				break;
			}
			else {
				dividend = tmp_dividend;
			}
		}
		//當被除數比除數小時直接break
		if (dividend < divisor)break;
		// 重新擴位
		bitOfQuotient = dividend.expandBit_Ex(divisor, expand_divisor);

		string partOfQuotient = to_string(bitOfQuotient);

		for (int i = 0; i < 4 - partOfQuotient.length(); i++) {
			quotientStr += '0';
		}
		quotientStr += partOfQuotient;
	}
	//保存餘數
	remainder = dividend;
	//返回除數
	return BigInteger(quotientStr);
}

BigInteger BigInteger::gcd(BigInteger a, BigInteger b,BigInteger& count) {
	if (b == BigInteger("0")) {
		return a;
	}
	++count;
	return gcd(b, a % b,count);
}

BigInteger BigInteger::calc_s(BigInteger a, BigInteger b, BigInteger i) {

	if (i == BigInteger("-2"))return BigInteger("1");
	if (i == BigInteger("-1"))return BigInteger("0");
	BigInteger q = calc_r(a, b, i - BigInteger("2")) / calc_r(a, b, i - BigInteger("1"));
	return q * BigInteger("-1") * calc_s(a, b, i - BigInteger("1")) + calc_s(a, b, i - BigInteger("2"));
}

BigInteger BigInteger::calc_t(BigInteger a, BigInteger b, BigInteger i) {
	if (i == BigInteger("-2"))return BigInteger("0");
	if (i == BigInteger("-1"))return BigInteger("1");
	BigInteger q = calc_r(a, b, i - BigInteger("2")) / calc_r(a, b, i - BigInteger("1"));
	return q * BigInteger("-1") * calc_t(a, b, i - BigInteger("1")) + calc_t(a, b, i - BigInteger("2"));
}

BigInteger BigInteger::calc_r(BigInteger a, BigInteger b, BigInteger i) {

	if (i == BigInteger("-2")) {
		return a;
	}
	if (i == BigInteger("-1")) {
		return b;
	}
	return calc_r(a, b, i - BigInteger("2")) % calc_r(a, b, i - BigInteger("1"));
}

void BigInteger::myPow(BigInteger& a, int n) {
	if (n == 0) {
		a = BigInteger("1");
		return;
	}
	BigInteger initNum = a;
	for (int i = 0; i < n-1; i++) {
		a = a * initNum;
	}
}

BigInteger BigInteger::BuildBigIntFormBinOrOct(string str, int i) {
	// 保存是多少進制
	BigInteger base;
	if (i == 2)
		base = BigInteger("2");
	else if(i == 8)
		base = BigInteger("8");

	BigInteger res("0");
	
	int len = str.length();
	for (int i = len - 1,j = 0; i >= 0; i--,j++) {
		if (str[i] == '0')continue;
		BigInteger tmp = base;
		myPow(tmp, j);
		string curNum = " ";
		curNum[0] = str[i];
		tmp = tmp * BigInteger(curNum);
		res = res + tmp;
	}
	return res;
}

BigInteger BigInteger::BuildBigIntFormHex(string str) {
	// 保存是多少進制
	BigInteger base = BigInteger("16");

	// 構建一個表，方便等等讀取'A'、'B'等等這些值
	unordered_map<char, string> table;
	for (char ch = '0'; ch <= '9'; ch++) {
		string str = " ";
		str[0] = ch;
		table[ch] = str;
	}
	for (char ch = 'a'; ch <= 'f'; ch++) {
		
		table[ch] = to_string(ch-'a'+10);
	}
	
	for (char ch = 'A'; ch <= 'F'; ch++) {

		table[ch] = to_string(ch - 'A' + 10);
	}

	BigInteger res("0");

	int len = str.length();
	for (int i = len - 1, j = 0; i >= 0; i--, j++) {
		if (str[i] == '0')continue;
		BigInteger tmp = base;
		myPow(tmp, j);
		tmp = tmp * BigInteger(table[str[i]]);
		res = res + tmp;
	}
	return res;
}

string BigInteger::toBinString() {
	BigInteger zero("0");
	BigInteger base = BigInteger("2");
	string res = "";

	bool isNeg = this->isNegative;

	//若為0直接返回0
	if (*this == zero)return "0";

	while (*this != zero) {
		BigInteger r = *this % base;
		string cur = r.toString();
		res.insert(0, cur);
		*this = *this / base;
	}

	// 若為負數，最後要加個'-'
	if(isNeg)res.insert(0, "-");

	return res;
}

string BigInteger::toOctString() {
	BigInteger zero("0");
	BigInteger base = BigInteger("8");
	string res = "";

	bool isNeg = this->isNegative;

	//若為0直接返回0
	if (*this == zero)return "0";

	while (*this != zero) {
		BigInteger r = *this % base;
		string cur = r.toString();
		res.insert(0, cur);
		*this = *this / base;
	}

	// 若為負數，最後要加個'-'
	if (isNeg)res.insert(0, "-");
	return res;
}

string BigInteger::toHexString() {
	BigInteger zero("0");
	BigInteger base = BigInteger("16");
	string res = "";
	string table = "0123456789ABCDEF";

	bool isNeg = this->isNegative;

	//若為0直接返回0
	if (*this == zero)return "0";

	while (*this != zero) {
		BigInteger r = *this % base;
		string cur = "";
		cur += table[r.s[0]];
		res.insert(0, cur);
		*this = *this / base;
	}

	// 若為負數，最後要加個'-'
	if (isNeg)res.insert(0, "-");
	return res;
}

string BigInteger::BaseOperation(string num1, string num2, int base,char oper) {
	BigInteger bInt1;
	BigInteger bInt2;

	// 根據進制構造BigInteger
	switch (base)
	{
	case 2:
		bInt1 = BuildBigIntFormBinOrOct(num1, 2);
		bInt2 = BuildBigIntFormBinOrOct(num2, 2);
		break;
	case 8:
		bInt1 = BuildBigIntFormBinOrOct(num1, 8);
		bInt2 = BuildBigIntFormBinOrOct(num2, 8);
		break;
	case 16:
		bInt1 = BuildBigIntFormHex(num1);
		bInt2 = BuildBigIntFormHex(num2);
		break;
	default:
		return "";
	}

	BigInteger res;
	// 根據oper進行運算
	switch (oper)
	{
	case '+':
		res = bInt1 + bInt2;
		break;
	case '-':
		res = bInt1 - bInt2;
		break;
	case '*':
		res = bInt1 * bInt2;
		break;
	default:
		return "";
	}

	// 根據進制返回對應進制字串
	switch (base)
	{
	case 2:
		return res.toBinString();
	case 8:
		return res.toOctString();
	case 16:
		return res.toHexString();
	}

}