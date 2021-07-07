#include <iostream>
#include "CP_NaturalInteger.h"

using namespace std;

int CP_NaturalInteger::mb_getInput() // ����
{
	double x = 0;
	cout << "������һ����Ȼ����";
	cin >> x;
	while (x < 0 || cin.rdstate() == ios_base::failbit || (x != (int) x && x != (int) x + 1))
	{
		cout << "������Ĳ�����Ȼ��" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "������һ����Ȼ����";
		cin >> x;
	}
	if (x == (int)x) m_data = x; else m_data = x + 1;
	return m_data;
}

int CP_NaturalInteger::mb_showData() // ������ڵ�ֵ
{
	cout << "�������������" << m_data << endl;
	return m_data;
}

int CP_NaturalInteger::integerPlus(int plusNumber)             //�ӷ�
{
	m_data += plusNumber;
	return m_data;
}

int CP_NaturalInteger::integerMultiply(int multiplyNumber)     //�˷�
{
	m_data *= multiplyNumber;
	return m_data;
}

int CP_NaturalInteger::integerOddOrEven() //�ж���ż�ԣ�ż������0��������1
{
	return m_data & 1;
}
