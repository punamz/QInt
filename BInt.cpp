#include "QInt.h"
//constructor
QInt::QInt()
{
	this->arrayBits[0] = 0;
	this->arrayBits[1] = 0;
}

//QInt::QInt(std::string Bin)
//{
//
//}

//copy constructor
QInt::QInt(const QInt& other)
{
	this->arrayBits[0] = other.arrayBits[0];
	this->arrayBits[1] = other.arrayBits[1];
}
QInt::~QInt(){}
//overloading operator AND ( & )
QInt QInt::operator&(const QInt& other)
{
	QInt temp;
	temp.arrayBits[0] = this->arrayBits[0] & other.arrayBits[0];
	temp.arrayBits[1] = this->arrayBits[1] & other.arrayBits[0];
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
QInt QInt::operator<<(int k)
{
	QInt temp(*this);
	for (auto i = 0; i < k; ++i)
	{
		temp.arrayBits[0] <<= 1;
		if (temp.arrayBits[1] < 0)
			temp.arrayBits[0] |= 1;
		temp.arrayBits[1] <<= 1;
	}
	return temp;
}
