#include "integerInput.h"
#include "stringToInt.h"
#include <iostream>

using namespace std;

void integerInput()
{
	stringToInt m;
	m.input();
	try
	{
		m.transfer();
	}
	catch (cinterger_status ST)
	{
		switch (ST)
		{
		case INTEGER_EMPTY:
			cout << "您输入的字符串为空。" << endl;
			break;

		case INTEGER_DOTINVALID:
			cout << "您输入的字符串有至少2个小数点。" << endl;
			break;

		case INTEGER_SIGNINVALID:
			cout << "您输入的字符串在除了第一个位置出现了+-号。" << endl;
			break;

		case INTEGER_CHARINVALID:
			cout << "您输入的字符串出现了16进制以外的字符。" << endl;
			break;

		case INTEGER_DOTSIGNINVALID:
			cout << "您输入的字符串有至少2个小数点。" << endl;
			cout << "您输入的字符串在除了第一个位置出现了+-号。" << endl;
			break;

		case INTEGER_DOTCHARINVALID:
			cout << "您输入的字符串有至少2个小数点。" << endl;
			cout << "您输入的字符串出现了16进制以外的字符。" << endl;
			break
				;
		case INTEGER_SIGNCHARINVALID:
			cout << "您输入的字符串在除了第一个位置出现了+-号。" << endl;
			cout << "您输入的字符串出现了16进制以外的字符。" << endl;
			break;

		case INTEGER_DOTSIGNCHARINVALID:
			cout << "您输入的字符串有至少2个小数点。" << endl;
			cout << "您输入的字符串在除了第一个位置出现了+-号。" << endl;
			cout << "您输入的字符串出现了16进制以外的字符。" << endl;
			break;

		case INTEGER_DECIMAL:
			cout << "您输入的是一个十进制小数，但不是整数。" << endl;
			break;

		case INTEGER_DECIMALINT:
			cout << "您输入的是一个十进制小数，但它可以表示为一个整数。" << endl;
			cout << "它可以表示为的整数是: " << m.transferredInteger << endl;
			break;

		case INTEGER_STRINGINT:
			cout << "您输入的不是十进制，但它可以表示为一个十六进制整数。" << endl;
			cout << "它可以表示为的十六进制整数的十进制表示是: " << m.transferredInteger16 << endl;
			break;

		case INTEGER_STRINGDECIMAL:
			cout << "您输入的不是十进制，可以表示为十六进制小数，但不是整数。" << endl;
			break;

		case INTEGER_STRINGDECIMALINT:
			cout << "您输入的不是十进制，可以表示为十六进制小数且可以表示为整数。" << endl;
			cout << "它可以表示为的十六进制整数的十进制表示是: " << m.transferredInteger16 << endl;
			break;
		}
	}
	if (m.strType() == INTEGER_STANDARD)
	{
		cout << "您输入的十进制整数是: " << m.transferredInteger << endl;
	}
}