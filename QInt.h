#pragma once

#include "handleString.h"

#include <bitset>

class QInt
{
private:
	long long arrayBits[2];
public:
	// Init QInt = 0;
	QInt();
	QInt(std::string);
	QInt(const QInt&);
	~QInt();
public:
	// So QInt bu 2
	void twoComplementQInt();
	// Đọc số QInt từ một chuõi
	void scanQInt(std::string str, std::string base);
	// Chuyển số QInt thành chuỗi Bin
	std::string toBin();
	// Chuyển số QInt thành chuỗi Dec
	std::string toDec();
	// Chuyển số QInt thành chuỗi Hex
	std::string toHex();
public:
	QInt operator=(const QInt&);
	QInt operator+(const QInt&);
	QInt operator-(const QInt&);
	QInt operator*(const QInt&);
	QInt operator/(const QInt&);

public:
	// not equal to 
	bool operator!=(const QInt&);
	//operator and or xor not

	//AND
	QInt operator&(const QInt&);
	//OR
	QInt operator|(const QInt&);
	// XOR
	QInt operator^(const QInt&);
	// NOT
	QInt operator~();

	//shift left
	QInt operator<<(QInt);
	//shift right
	QInt operator>>(QInt);

	//rotate left function
	void rotateLeft();
	//ratate right function
	void rotateRight();
};