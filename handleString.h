#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define N_BITS 128

template <typename T>
std::string toString(T number)
{
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

// Chuyển từ chuỗi số nguyên lớn sang chuỗi nhị phân 128 bit
std::string decToBin(std::string);
// Chia lấy phần nguyên của chuỗi decimal Eg: "123"/2 = "61"
std::string divByTwo_String(std::string);
// Lấy số bù 2 của chuối số nhị phân 128 bit
std::string calTwoComplement_String(std::string);
// // Chuyển từ chuỗi hexa lớn sang chuỗi nhị phân 128 bit
std::string hexToBin(std::string);


// Convert chuỗi Binary to chuỗi Deciaml
std::string binToDec(std::string);
// Tính tổng 2 chuỗi Decimal
std::string sumTwoUDecStr(std::string, std::string);
// Nhân 2 chuỗi Decimal
std::string multipleTwoDecStr(std::string, std::string);
// Lũy thừa
std::string powString(std::string, int);

std::string binToHex(std::string);

std::string shiftLeft(std::string, int);

std::string shiftLeft256(std::string, int );

std::string add(const std::string&, const std::string&);
void addBitZero(std::string&);