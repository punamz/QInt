#include <iostream>
#include <bitset>
class QInt
{
private:
	long long arrayBits[2];
public:
	QInt();
	QInt(std::string);
	QInt(const QInt&);
	~QInt();

	std::string getBin();
	std::string binToDec(std::string Bin);
	std::string binToHex(std::string Bin);

	std::string decToBin(std::string Dec);

	std::string hexToBin(std::string Hex);

	QInt operator=(const QInt&);
	QInt operator+(const QInt&);
	QInt operator-(const QInt&);
	QInt operator*(const QInt&);
	QInt operator/(const QInt&);


	//operator and or xor not
	QInt operator&(const QInt&);
	QInt operator|(const QInt&);
	QInt operator^(const QInt&);
	QInt operator~();

	//operator dịch trái dịch phải
	QInt operator<<(int);
	QInt operator>>(int);

	void rotateLeft();
	void rotateRight();
};
