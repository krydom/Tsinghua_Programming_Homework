#ifndef STRINGTOINT_H
#define STRINGTOINT_H
#include <string>

using namespace std;

typedef enum cinterger_status
{
	INTEGER_DOTINVALID = -1,           //有至少2个小数点
	INTEGER_SIGNINVALID = -2,          //在除了第一个位置出现+-号
	INTEGER_CHARINVALID = -3,          //出现了16进制以外的字符
	INTEGER_DOTSIGNINVALID = -12,      //有至少2个小数点，在除了第一个位置出现+-号
	INTEGER_DOTCHARINVALID = -13,      //有至少2个小数点，出现了16进制以外的字符
	INTEGER_SIGNCHARINVALID = -23,     //在除了第一个位置出现+-号，出现了16进制以外的字符
	INTEGER_DOTSIGNCHARINVALID = -123, //有至少2个小数点，在除了第一个位置出现+-号，出现了16进制以外的字符
	INTEGER_EMPTY = 0,                 //字符串为空

	INTEGER_STANDARD = 1,              //标准的十进制整数
	INTEGER_DECIMAL = 21,              //有一个小数点的十进制小数，且一定不是整数
	INTEGER_DECIMALINT = 22,           //有一个小数点的十进制小数，但小数点后都是0
	INTEGER_STRINGINT = 3,             //有非小数点和数字和负号的其他字符，但可能是标准的十六进制整数
	INTEGER_STRINGDECIMAL = 41,        //有一个小数点的十六进制实数，且一定不是整数
	INTEGER_STRINGDECIMALINT = 42      //有一个小数点的十六进制实数，但小数点后都是0
} IntegerStatus;

class stringToInt
{
public:
	long long transferredInteger, transferredInteger16;
	string str;

public:
	stringToInt() { transferredInteger = transferredInteger16 = 0; str = ""; }
	~stringToInt() {}

	void input();
	cinterger_status strType();
	void transfer();
};;

#endif // !STRINGTOINT_H

