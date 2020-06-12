#include "handleString.h"
void addBitZero(std::string& binStr) {
	int len = binStr.length();
	if (len < N_BITS) {
		binStr.insert(0, N_BITS - len, '0');
	}
}

std::string decToBin(std::string str) {
	bool isNegative = false;
	if (str[0] == '-') {
		isNegative = true;
		str.erase(str.begin());
	}

	//convert to Bin
	std::string bin = "";
	int remainder;

	while (str != "") {
		remainder = (int)(str[str.length() - 1] - '0') % 2;
		if (remainder == 1) {
			bin.insert(bin.begin(), '1');
		}
		else {
			bin.insert(bin.begin(), '0');
		}
		str = divByTwo_String(str);
	}
	addBitZero(bin);

	if (isNegative) {
		// lay Bin bu 2 cua String
		bin = calTwoComplement_String(bin);
	}
	return bin;
}
std::string divByTwo_String(std::string str) {
	std::string quotient;
	int temp = str[0] - '0';
	int len = str.length();
	int i = 0;
	while (temp == 0 || temp == 1) {
		temp = (int)(str[++i] - '0') + temp * 10;
	}
	while (len > i) {
		quotient += (int)(temp / 2 + '0');
		i++;
		if (str[i]) {
			temp = (temp % 2) * 10 + (int)(str[i] - '0');
		}
	}
	return quotient;
}
std::string calTwoComplement_String(std::string str) {
	// Fplit bit string
	int len = str.length();
	while (len > 0) {
		str[len - 1] = str[len - 1] == '1' ? '0' : '1';
		len--;
	}
	// Plus str with 1
	char Q = 0, i = N_BITS - 1;
	std::string sum(N_BITS, '0');
	std::string numberOne(N_BITS, '0');
	numberOne[N_BITS - 1] = '1';
	while (i >= 0) {
		sum[i] = (((str[i] - '0') ^ (numberOne[i] - '0')) ^ Q) + '0';
		if (Q == 1 && (((str[i] - '0') ^ (numberOne[i] - '0')) == 1)) Q = 1;
		else Q = (str[i] - '0') & (numberOne[i] - '0');
		i--;
	}
	return sum;
}
std::string hexToBin(std::string str)
{
	std::string bin;
	char hexs[] = { '0','1','2','3','4','5','6','7',
					'8','9','A','B','C','D','E','F' };
	std::string bins[] = { "0000","0001","0010","0011","0100","0101","0110",
		"0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	int len = str.length();

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < 16; j++) {
			if (str[i] == hexs[j]) {
				bin += bins[j];
				break;
			}
		}
	}
	return bin;
}


std::string binToDec(std::string binStr) {
	std::string binTmp = binStr;
	addBitZero(binTmp);
	bool negative = false;
	if (binTmp[0] == '1') {
		negative = true;
	}
	if (negative) {
		binTmp = calTwoComplement_String(binTmp);
	}

	std::string decStr = "";
	int len = binTmp.length();
	for (int i = len - 1; i >= 0; i--) {
		if (binTmp[i] == '1')
			decStr = sumTwoUDecStr(decStr, powString("2", len - 1 - i));
	}
	if (negative) decStr = '-' + decStr;
	return decStr;
}
std::string sumTwoUDecStr(std::string str1, std::string str2) {
	// Make sure length of str2 is larger. 
	if (str1.length() > str2.length())
		swap(str1, str2);

	std::string res = "";
	int len1 = str1.length(), len2 = str2.length();

	// Reverse both of strings 
	reverse(str1.begin(), str1.end());
	reverse(str2.begin(), str2.end());
	int carry = 0;
	for (int i = 0; i < len1; i++) {
		// Compute sum of current digits and carry 
		int sum = ((str1[i] - '0') + (str2[i] - '0') + carry);
		res.push_back(sum % 10 + '0');
		// Calculate carry for next step 
		carry = sum / 10;
	}

	// Add remaining digits of larger number 
	for (int i = len1; i < len2; i++)
	{
		int sum = ((str2[i] - '0') + carry);
		res.push_back(sum % 10 + '0');
		carry = sum / 10;
	}

	// Add remaining carry 
	if (carry)
		res.push_back(carry + '0');

	// reverse resultant string 
	std::reverse(res.begin(), res.end());

	return res;
}
std::string multipleTwoDecStr(std::string str1, std::string str2) {
	bool negative = false;
	// Check condition if one string is negative 
	if (str1[0] == '-' && str2[0] != '-') {
		str1 = str1.substr(1);
		negative = true;
	}
	else if (str1[0] != '-' && str2[0] == '-') {
		str2 = str2.substr(1);
		negative = true;
	}
	else if (str1[0] == '-' && str2[0] == '-') {
		str1 = str1.substr(1);
		str2 = str2.substr(1);
	}

	int len1 = str1.length();
	int len2 = str2.length();
	if (len1 == 0 || len2 == 0) return "0";

	// will keep the result number in vector in reverse order 
	std::vector<int> result(len1 + len2, 0);

	// Below two indexes are used to find positions in result.  
	int i_n1 = 0;
	int i_n2 = 0;

	// Go from right to left in str1 
	for (int i = len1 - 1; i >= 0; i--)
	{
		int carry = 0;
		int n1 = str1[i] - '0';

		// To shift position to left after every multiplication of a digit in num2 
		i_n2 = 0;

		// Go from right to left in str2              
		for (int j = len2 - 1; j >= 0; j--)
		{
			int n2 = str2[j] - '0';
			int sum = n1 * n2 + result[i_n1 + i_n2] + carry;
			carry = sum / 10;
			result[i_n1 + i_n2] = sum % 10;

			i_n2++;
		}

		// store carry in next cell 
		if (carry > 0)
			result[i_n1 + i_n2] += carry;

		// To shift position to left after every 
		// multiplication of a digit in num1. 
		i_n1++;
	}

	// ignore '0's from the right 
	int i = result.size() - 1;
	while (i >= 0 && result[i] == 0)
		i--;

	// If all were '0's - means either both or 
	// one of num1 or num2 were '0' 
	if (i == -1)
		return "0";

	// generate the result string 
	std::string sum = "";

	while (i >= 0)
		sum += toString(result[i--]);
	if (negative) {
		sum = '-' + sum;
	}
	return sum;
}
std::string powString(std::string strDec, int exp) {
	std::string res = strDec;
	if (exp == 0) return "1";
	for (int i = 0; i < exp - 1; ++i) {
		res = multipleTwoDecStr(res, strDec);
	}
	return res;
}

std::string binToHex(std::string binStr) {
	addBitZero(binStr);
	std::string hex;
	char hexs[] = { '0','1','2','3','4','5','6','7',
					'8','9','A','B','C','D','E','F' };
	std::string bins[] = { "0000","0001","0010","0011","0100","0101","0110",
		"0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	int len = binStr.length();

	for (int i = 0; i < len; i += 4) {
		for (int j = 0; j < 16; j++) {
			if (binStr.substr(i, 4) == bins[j]) {
				hex += hexs[j];
				break;
			}
		}
	}
	while (hex[0] == '0') {
		hex.erase(hex.begin());
	}
	return hex;
}

std::string shiftLeft(std::string a, int nBitshift) {
	std::string temp = a;
	int i = 0;
	while (i < N_BITS - nBitshift) {
		temp[i] = temp[i + nBitshift];
		i++;
	}
	for (int j = 0; j < nBitshift; j++) {
		temp[N_BITS - j - 1] = '0';
	}
	return temp;
}
std::string shiftLeft256(std::string a, int nBitshift) {
	std::string temp = a;
	int i = 0;
	while (i < N_BITS * 2 - nBitshift) {
		temp[i] = temp[i + nBitshift];
		i++;
	}
	for (int j = 0; j < nBitshift; j++) {
		temp[N_BITS * 2 - j - 1] = '0';
	}
	return temp;
}
std::string add(const std::string& thisBin, const std::string& otherBin) {
	char Q = 0;
	int i = N_BITS - 1;
	std::string sum(N_BITS, '0');
	while (i >= 0) {
		sum[i] = (((thisBin[i] - '0') ^ (otherBin[i] - '0')) ^ Q) + '0';
		if (Q == 1 && (((thisBin[i] - '0') ^ (otherBin[i] - '0')) == 1)) Q = 1;
		else Q = (thisBin[i] - '0') & (otherBin[i] - '0');
		i--;
	}
	return sum;
}
