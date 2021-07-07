#ifndef STRINGTOINT_H
#define STRINGTOINT_H
#include <string>

using namespace std;

typedef enum cinterger_status
{
	INTEGER_DOTINVALID = -1,           //������2��С����
	INTEGER_SIGNINVALID = -2,          //�ڳ��˵�һ��λ�ó���+-��
	INTEGER_CHARINVALID = -3,          //������16����������ַ�
	INTEGER_DOTSIGNINVALID = -12,      //������2��С���㣬�ڳ��˵�һ��λ�ó���+-��
	INTEGER_DOTCHARINVALID = -13,      //������2��С���㣬������16����������ַ�
	INTEGER_SIGNCHARINVALID = -23,     //�ڳ��˵�һ��λ�ó���+-�ţ�������16����������ַ�
	INTEGER_DOTSIGNCHARINVALID = -123, //������2��С���㣬�ڳ��˵�һ��λ�ó���+-�ţ�������16����������ַ�
	INTEGER_EMPTY = 0,                 //�ַ���Ϊ��

	INTEGER_STANDARD = 1,              //��׼��ʮ��������
	INTEGER_DECIMAL = 21,              //��һ��С�����ʮ����С������һ����������
	INTEGER_DECIMALINT = 22,           //��һ��С�����ʮ����С������С�������0
	INTEGER_STRINGINT = 3,             //�з�С��������ֺ͸��ŵ������ַ����������Ǳ�׼��ʮ����������
	INTEGER_STRINGDECIMAL = 41,        //��һ��С�����ʮ������ʵ������һ����������
	INTEGER_STRINGDECIMALINT = 42      //��һ��С�����ʮ������ʵ������С�������0
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

