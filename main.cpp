#include "QInt.h"
#include <fstream>

std::string base1, base2; //hệ cơ số yêu cầu
std::string str1, str2; //2 dãy số input
std::string opt; // toán tử (phép tính) yêu cầu

//hàm xử lý yêu cầu
//trả về kết quả (QInt) 
QInt Handle()
{
	QInt result;
	QInt QInt1, QInt2;
	QInt1.scanQInt(str1, base1);

	//nếu yêu cầu là dịch trái ( << ) hay dịch phải ( >> ) 
	//str2 là chuỗi số hệ 10
	if (opt == ">>" || opt == "<<")
		QInt2.scanQInt(str2, "10");
	//những trương hợp opt khác
	else
		QInt2.scanQInt(str2, base2);

	//nếu yêu cầu là chuyển đổi hệ 
	//opt = ""
	if (opt == "")
	{
		result = QInt1;
		return result;
	}
	else
	{
		//phép xoay phải
		if (opt == "ror")
		{
			result = QInt1;
			result.rotateRight();
			return result;
		}
		if (opt == "rol")
		{
			result = QInt1;
			result.rotateLeft();
			return result;
		}
		if (opt == "<<")
		{
			result = QInt1 << QInt2;
			return result;
		}
		if (opt == ">>")
		{
			result = QInt1 >> QInt2;
			return result;
		}
		if (opt == "~")
		{
			result = ~QInt1;
			return result;
		}
		if (opt == "&")
		{
			result = QInt1 & QInt2;
			return result;
		}
		if (opt == "|")
		{
			result = QInt1 | QInt2;
			return result;
		}
		if (opt == "^")
		{
			result = QInt1 ^ QInt2;
			return result;
		}
		if (opt == "+")
		{
			result = QInt1 + QInt2;
			return result;
		}
		if (opt == "-")
		{
			result = QInt1 - QInt2;
			return result;
		}
		if (opt == "*")
		{
			result = QInt1 * QInt2;
			return result;
		}
		if (opt == "/")
		{
			result = QInt1 / QInt2;
			return result;
		}
	}
}



//hàm phân tích chuỗi đọc từ file input
void parse(std::string in_str)
{
	//TH1: nếu là phép toán + - * / => chuỗi in_str có 3 khoảng trắng => có 4 chuỗi con
	//TH2: nếu là chuyến đổi giữa các hệ số hoặc ror/rol, ~ => chuỗi in_str có 2 khoảng trắng => có 3 chuỗi con

	//parse chuỗi str thành các chuỗi con 
	std::vector <std::string> tokens;
	int startPos = 0;
	size_t foundPos = in_str.find(' ', startPos);

	while (foundPos != std::string::npos)
	{
		int length = foundPos - startPos;
	
			tokens.push_back(in_str.substr(startPos, length));

		startPos = foundPos + 1;

		foundPos = in_str.find(' ', startPos);
	}
	int length = in_str.length() - startPos;
	tokens.push_back(in_str.substr(startPos, length));

	//xét TH1:
	if (tokens.size() == 4)
	{
		base1 = tokens[0]; //dịnh dạng hệ nhập vào
		base2 = tokens[0]; //định dạng hệ xuất ra
		str1 = tokens[1];
		opt = tokens[2];
		str2 = tokens[3];
	}
	//xét TH2
	else if (tokens.size() == 3)
	{
		base1 = tokens[0];
		//kiếm tra yêu cầu là chuyển dổi sang hệ sô khác hay ror/rol, ~
		//nếu là yêu cầu chuyển đổi hệ
		if (tokens[1] == "10" || tokens[1] == "16" || tokens[1] =="2")
		{
			base2 = tokens[1];
			opt = "";
		}
		//nếu là phép xoay ror/rol, ~
		else
		{
			base2 = tokens[0]; //định dạng hệ xuất ra giống với base1
			opt = tokens[1];
		}
		str1 = tokens[2];
		str2 = "";
	}
}
void printQInt(QInt& result)
{

}


//hàm main
int main(int argc, char* argv[])
{
	std::string in_str; //string đọc từ file input
	if (argv[1] != NULL && argv[2] != NULL) {
		std::ifstream inFile;
		inFile.open(argv[1]);

		std::ofstream outFile;
		outFile.open(argv[2]);

		while (!inFile.eof())
		{
			std::getline(inFile, in_str);
			if (in_str == "")
				continue;
			parse(in_str);
			QInt resultQInt = Handle();

			std::string resultString;
			if (base2 == "2")
				resultString = resultQInt.toBin();
			if (base2 == "10")
				resultString = resultQInt.toDec();
			if (base2 == "16")
				resultString = resultQInt.toHex();

			outFile << resultString << std::endl;

			//set các chuỗi về mặc định
			in_str.clear();
			base1.clear();
			base2.clear();
			str1.clear();
			str2.clear();
			opt.clear();
		}

		inFile.close();
		outFile.close();
	}

	return 0;
}

