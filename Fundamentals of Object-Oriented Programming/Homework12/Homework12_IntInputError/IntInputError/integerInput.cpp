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
			cout << "��������ַ���Ϊ�ա�" << endl;
			break;

		case INTEGER_DOTINVALID:
			cout << "��������ַ���������2��С���㡣" << endl;
			break;

		case INTEGER_SIGNINVALID:
			cout << "��������ַ����ڳ��˵�һ��λ�ó�����+-�š�" << endl;
			break;

		case INTEGER_CHARINVALID:
			cout << "��������ַ���������16����������ַ���" << endl;
			break;

		case INTEGER_DOTSIGNINVALID:
			cout << "��������ַ���������2��С���㡣" << endl;
			cout << "��������ַ����ڳ��˵�һ��λ�ó�����+-�š�" << endl;
			break;

		case INTEGER_DOTCHARINVALID:
			cout << "��������ַ���������2��С���㡣" << endl;
			cout << "��������ַ���������16����������ַ���" << endl;
			break
				;
		case INTEGER_SIGNCHARINVALID:
			cout << "��������ַ����ڳ��˵�һ��λ�ó�����+-�š�" << endl;
			cout << "��������ַ���������16����������ַ���" << endl;
			break;

		case INTEGER_DOTSIGNCHARINVALID:
			cout << "��������ַ���������2��С���㡣" << endl;
			cout << "��������ַ����ڳ��˵�һ��λ�ó�����+-�š�" << endl;
			cout << "��������ַ���������16����������ַ���" << endl;
			break;

		case INTEGER_DECIMAL:
			cout << "���������һ��ʮ����С����������������" << endl;
			break;

		case INTEGER_DECIMALINT:
			cout << "���������һ��ʮ����С�����������Ա�ʾΪһ��������" << endl;
			cout << "�����Ա�ʾΪ��������: " << m.transferredInteger << endl;
			break;

		case INTEGER_STRINGINT:
			cout << "������Ĳ���ʮ���ƣ��������Ա�ʾΪһ��ʮ������������" << endl;
			cout << "�����Ա�ʾΪ��ʮ������������ʮ���Ʊ�ʾ��: " << m.transferredInteger16 << endl;
			break;

		case INTEGER_STRINGDECIMAL:
			cout << "������Ĳ���ʮ���ƣ����Ա�ʾΪʮ������С����������������" << endl;
			break;

		case INTEGER_STRINGDECIMALINT:
			cout << "������Ĳ���ʮ���ƣ����Ա�ʾΪʮ������С���ҿ��Ա�ʾΪ������" << endl;
			cout << "�����Ա�ʾΪ��ʮ������������ʮ���Ʊ�ʾ��: " << m.transferredInteger16 << endl;
			break;
		}
	}
	if (m.strType() == INTEGER_STANDARD)
	{
		cout << "�������ʮ����������: " << m.transferredInteger << endl;
	}
}