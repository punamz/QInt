#include "QInt.h"
//constructor
QInt::QInt()
{
	this->arrayBits[0] = 0;
	this->arrayBits[1] = 0;
}
//constructor từ chuỗi bit truyền vào
QInt::QInt(std::string Bin)
{
	while (Bin.size() < 128)
		Bin = '0' + Bin;

	std::bitset<64> foo1(std::string(Bin.substr(0, 64)));
	std::bitset<64> foo2(std::string(Bin.substr(64, 64)));

	this->arrayBits[0] = foo1.to_ullong();
	this->arrayBits[1] = foo2.to_ullong();

}
//copy constructor
QInt::QInt(const QInt& other)
{
	this->arrayBits[0] = other.arrayBits[0];
	this->arrayBits[1] = other.arrayBits[1];
}
//destructor
QInt::~QInt() {}

//================================================LONG=====================================================//

void QInt::twoComplementQInt() {
	QInt soMot("1");
	*this = ~*this;
	*this = *this + soMot;
}

void QInt::scanQInt(std::string str, std::string base) {
	if (base == "10") {
		//convert decToBin
		str = decToBin(str);
	}
	else if (base == "16") {
		//convert 16 to bin
		str = hexToBin(str);
	}

	if (str.length() < N_BITS) {
		str.insert(0, N_BITS - str.length(), '0');
	}
	std::bitset<64> foo1(std::string(str.substr(0, 64)));
	std::bitset<64> foo2(std::string(str.substr(64, 64)));

	this->arrayBits[0] = foo1.to_ullong();
	this->arrayBits[1] = foo2.to_ullong();
}

std::string QInt::toDec() {
	std::string bin = this->toBin();
	std::string dec = binToDec(bin);
	return dec;
}

std::string QInt::toHex() {
	std::string bin = this->toBin();
	std::string hex = binToHex(bin);
	return hex;
}

std::string QInt::toBin() {
	std::bitset<64> foo1 = this->arrayBits[0];
	std::bitset<64> foo2 = this->arrayBits[1];

	std::string bin = foo1.to_string() + foo2.to_string();
	while (bin[0] == '0') {
		bin.erase(bin.begin());
	}
	return bin;
}

//================================================LUAN=====================================================//
QInt QInt::operator=(const QInt& other) {
	this->arrayBits[0] = other.arrayBits[0];
	this->arrayBits[1] = other.arrayBits[1];
	return *this;

};

QInt QInt::operator+(const QInt& other) {
	//lấy bit của số QInt this
	std::bitset<64> foo1 = this->arrayBits[0];
	std::bitset<64> foo2 = this->arrayBits[1];
	std::string thisBin = foo1.to_string() + foo2.to_string();
	//lấy bit của số Qint other
	foo1 = other.arrayBits[0];
	foo2 = other.arrayBits[1];
	std::string otherBin = foo1.to_string() + foo2.to_string();

	std::string sum(128, '0');
	char Q = 0;
	char i = N_BITS - 1;

	while (i >= 0) {
		sum[i] = (((thisBin[i] - '0') ^ (otherBin[i] - '0')) ^ Q) + '0';
		if (Q == 1 && (((thisBin[i] - '0') ^ (otherBin[i] - '0')) == 1))
			Q = 1;
		else
			Q = (thisBin[i] - '0') & (otherBin[i] - '0');
		i--;
	}
	return QInt(sum);
};

QInt QInt::operator-(const QInt& other) {
	QInt temp = other;
	temp.twoComplementQInt();
	return *this + temp;
};

QInt QInt::operator*(const QInt& other) {
	std::string thisBin = this->toBin();
	addBitZero(thisBin);
	QInt otherQ = other;
	std::string otherBin = otherQ.toBin();
	addBitZero(otherBin);
	std::string temp(128, '0');
	std::string result(128, '0');
	for (int i = N_BITS - 1; i >= 0; i--) {
		for (int j = N_BITS - 1; j >= 0; j--) {
			temp[j] = (thisBin[j] & otherBin[i]);
		}
		temp = shiftLeft(temp, N_BITS - 1 - i);
		result = add(result, temp);
	}
	return result;
};

QInt QInt::operator/(const QInt& other) {
	std::string thisBin = this->toBin();
	addBitZero(thisBin);
	QInt otherQ = other;
	std::string otherBin = otherQ.toBin();
	addBitZero(otherBin);
	std::string A(N_BITS, '0');
	std::string res(N_BITS, '0');
	int k = N_BITS;

	bool negative = false;
	if ((thisBin[0] - '0') == 1) { // If Q and M are negative, ignore the "-" sign

		thisBin = calTwoComplement_String(thisBin);
		negative = true;

	}
	if ((otherBin[0] - '0') == 1) {
		otherBin = calTwoComplement_String(otherBin);
		negative = true;
	}


	res.insert(res.end(), thisBin.begin(), thisBin.end());

	int nBits = res.size();
	while (k > 0) {
		res = shiftLeft256(res, 1);

		for (int i = 0; i < N_BITS; i++) {
			A[i] = res[i];
		}
		if ((thisBin[0] - '0') ^ (otherBin[0] - '0') == 1) {
			A = add(A, otherBin);
		}
		else {
			A = add(A, calTwoComplement_String(otherBin));
		}

		if (A[0] == '1') { // if A is negative
			res[nBits - 1] = '0';
			A = add(A, otherBin);
		}
		else {
			res[nBits - 1] = '1';
			for (int i = 0; i < N_BITS; i++) {
				res[i] = A[i];
			}
		}
		k--;
	}
	// dao bit thuong
	std::string ketqua(N_BITS, '0');
	std::string quotient(N_BITS, '0');
	if (negative) {
		for (int i = 0; i < N_BITS; i++) {
			quotient[i] = res[i + N_BITS];
		}
		quotient = calTwoComplement_String(quotient);
		for (int i = 0; i < N_BITS; i++) {
			res[i + N_BITS] = quotient[i];
			ketqua[i] = quotient[i];
		}
	}
	else {
		for (int i = 0; i < N_BITS; i++) {
			quotient[i] = res[i + N_BITS];
		}
		for (int i = 0; i < N_BITS; i++) {
			ketqua[i] = quotient[i];
		}
	}

	return QInt(ketqua);
}
//=========================================================================================================//

//overloading operator ( != )
bool QInt::operator!=(const QInt& other)
{
	if ((other.arrayBits[0] != this->arrayBits[0])
		|| (other.arrayBits[1] != this->arrayBits[1]))
		return true;
	else
		return false;
}
//overloading operator AND ( & )
QInt QInt::operator&(const QInt& other)
{
	QInt temp;
	temp.arrayBits[0] = this->arrayBits[0] & other.arrayBits[0];
	temp.arrayBits[1] = this->arrayBits[1] & other.arrayBits[1];
	return temp;
}
//overloading operator OR ( | )
QInt QInt::operator|(const QInt& other)
{
	QInt temp;
	temp.arrayBits[0] = this->arrayBits[0] | other.arrayBits[0];
	temp.arrayBits[1] = this->arrayBits[1] | other.arrayBits[1];
	return temp;
}
//overloading operator XOR ( ^ )
QInt QInt::operator^(const QInt& other)
{
	QInt temp;
	temp.arrayBits[0] = this->arrayBits[0] ^ other.arrayBits[0];
	temp.arrayBits[1] = this->arrayBits[1] ^ other.arrayBits[1];
	return temp;
}
//overloading operator NOT ( ~ )
QInt QInt::operator~()
{
	QInt temp;
	temp.arrayBits[0] = ~this->arrayBits[0];
	temp.arrayBits[1] = ~this->arrayBits[1];
	return temp;
}
//overloading operator shift left ( << )
QInt QInt::operator<<(QInt other)
{
	QInt temp(*this);
	QInt Num0("0");
	QInt Num1("1");
	while (other != Num0)
	{
		temp.arrayBits[0] <<= 1;
		if (temp.arrayBits[1] < 0)
			temp.arrayBits[0] |= 1;
		temp.arrayBits[1] <<= 1;
		other = other - Num1;
	}
	return temp;
}
//overloading operator shift right ( >> )
QInt QInt::operator>>(QInt other)
{
	QInt temp(*this);
	QInt Num0("0");
	QInt Num1("1");

	//lưu bit dấu của QInt
	char LSB = '0';
	if (temp.arrayBits[0] < 0)
		LSB = '1';

	//lấy bit của số QInt temp
	std::bitset<64> foo1 = temp.arrayBits[0];
	std::bitset<64> foo2 = temp.arrayBits[1];
	std::string thisBin = foo1.to_string() + foo2.to_string();

	while (other != Num0)
	{
		thisBin = LSB + thisBin;
		other = other - Num1;
	}

	
	thisBin.resize(128);
	foo1 = (std::bitset<64>)(std::string(thisBin.substr(0, 64)));
	foo2 = (std::bitset<64>)(std::string(thisBin.substr(64, 64)));

	temp.arrayBits[0] = foo1.to_ullong();
	temp.arrayBits[1] = foo2.to_ullong();


	return temp;
}
//rotate left function
void QInt::rotateLeft()
{
	int temp = 0;
	if (this->arrayBits[0] < 0)
		temp = 1;
	QInt Num1("1");
	*this = *this << Num1;
	this->arrayBits[1] |= temp;
}
//ratate right function
void QInt::rotateRight()
{
	int temp = 1;
	temp &= this->arrayBits[1]; //lưu bit cuối cùng của QInt
	QInt Num1("1");
	*this = *this >> Num1;
	if (temp == 1)  //bật bit đầu tiên (bit trái cùng)
	{
		std::bitset<64> foo = this->arrayBits[0];
		foo.set(63, 1); //set bit trái cùng = 1 
		this->arrayBits[0] = foo.to_ullong();
	}
	else //tắt bit đầu tiên (bit trái cùng)
	{
		std::bitset<64> foo = this->arrayBits[0];
		foo.set(63, 0); //set bit trái cùng = 0
		this->arrayBits[0] = foo.to_ullong();
	}
}