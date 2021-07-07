#include "stringToInt.h"
#include <string>
#include <iostream>

using namespace std;

void stringToInt::input()
{
	cout << "������һ������:" << endl;
	getline(cin, str);
}

cinterger_status stringToInt::strType()
{
	if (str.length() == 0) return INTEGER_EMPTY; // �ַ���Ϊ��

	bool strfl = 0, signerr = 0, charerr = 0;
	int dotNumber = 0, lastDot = -1;
	if ((str[0] < '0' || str[0] > '9') && (str[0] < 'a' || str[0] > 'f') && (str[0] < 'A' || str[0] > 'F') && str[0] != '-' && str[0] != '+' && str[0] != '.') charerr = 1;
	if (str[0] == '.') dotNumber++, lastDot = 0;
	for (int i = 1; i < str.length(); ++i)
	{
		if ((str[i] >= 'a' && str[i] <= 'f') || (str[i] >= 'A' && str[i] <= 'F')) strfl = 1;
		if (str[i] == '.') dotNumber++, lastDot = i;

		if (str[i] == '+' || str[i] == '-') signerr = 1; //�ڳ��˵�һ��λ�ó���+-��
		if ((str[i] < '0' || str[i] > '9') && (str[i] < 'a' || str[i] > 'f') && (str[i] < 'A' || str[i] > 'F') && str[i] != '.' && str[i] != '-' && str[i] != '+') charerr = 1; //������16����������ַ�
	}

	if (dotNumber > 1 && !signerr && !charerr) return INTEGER_DOTINVALID; //������2��С����
	if (dotNumber <= 1 && signerr && !charerr) return INTEGER_SIGNINVALID; //�ڳ��˵�һ��λ�ó���+-��
	if (dotNumber <= 1 && !signerr && charerr) return INTEGER_CHARINVALID; //������16����������ַ�
	if (dotNumber > 1 && signerr && !charerr) return INTEGER_DOTSIGNINVALID; //������2��С���㣬�ڳ��˵�һ��λ�ó���+-��
	if (dotNumber > 1 && !signerr && charerr) return INTEGER_DOTCHARINVALID; //������2��С���㣬������16����������ַ�
	if (dotNumber <= 1 && signerr && charerr) return INTEGER_SIGNCHARINVALID; //�ڳ��˵�һ��λ�ó���+-�ţ�������16����������ַ�
	if (dotNumber > 1 && signerr && charerr) return INTEGER_DOTSIGNCHARINVALID;  //������2��С���㣬�ڳ��˵�һ��λ�ó���+-�ţ�������16����������ַ�

	if (dotNumber == 0 && !strfl) return INTEGER_STANDARD; //��׼��ʮ��������
	if (dotNumber == 0 && strfl) return INTEGER_STRINGINT; //�����Ǳ�׼��ʮ����������

	bool ZERO = 1;
	for (int i = lastDot + 1; i < str.length(); ++i)
		if (str[i] != '0') ZERO = 0;

	if (ZERO && !strfl) return INTEGER_DECIMALINT;      //��׼��ʮ����С������С�������0
	if (ZERO && strfl) return INTEGER_STRINGDECIMALINT; //�����Ǳ�׼��ʮ������С������С�������0
	if (!ZERO && !strfl) return INTEGER_DECIMAL;        //��׼��ʮ����С�����Ҳ�������
	if (!ZERO && strfl) return INTEGER_STRINGDECIMAL;   //�����Ǳ�׼��ʮ������С�����Ҳ�������
}

int num(char ch)
{
	if (ch >= '0' && ch <= '9') return ch - '0';
	if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
	if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
	return 0;
}

void stringToInt::transfer()
{
	cinterger_status ST = strType();
	if (ST == INTEGER_EMPTY) throw ST;

	int ty = 1;
	if (str[0] == '-') ty = -1;

	for (int i = (str[0] == '+' || str[0] == '-') ? 1 : 0; i < str.length() && str[i] != '.'; ++i)
	{
		transferredInteger = transferredInteger * 10 + num(str[i]);
		transferredInteger16 = transferredInteger16 * 16 + num(str[i]);
	}
	transferredInteger *= ty;
	transferredInteger16 *= ty;

	if (ST != INTEGER_STANDARD) throw ST;
}