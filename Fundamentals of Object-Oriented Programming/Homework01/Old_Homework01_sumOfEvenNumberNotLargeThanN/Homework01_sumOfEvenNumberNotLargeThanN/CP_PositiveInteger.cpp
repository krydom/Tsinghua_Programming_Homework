#include <iostream>
#include "CP_PositiveInteger.h"

using namespace std;

int CP_PositiveInteger::mb_getInput() // ����
{
	m_data = 0;
	while (m_data <= 0)
	{
		cout << "������һ����������";
		cin >> m_data;
		if (m_data <= 0) cout << "������Ĳ���������" << endl;
	}
	return m_data;
}

int CP_PositiveInteger::mb_showData() // ������ڵ�ֵ
{
	cout << "�������������" << m_data << endl;
	return m_data;
}

int CP_PositiveInteger::integerPlus(int plusNumber)             //�ӷ�
{
	m_data += plusNumber;
	return m_data;
}

int CP_PositiveInteger::integerMultiply(int multiplyNumber)     //�˷�
{
	m_data *= multiplyNumber;
	return m_data;
}

int CP_PositiveInteger::integerOddOrEven() //�ж���ż�ԣ�ż������0��������1
{
	return m_data & 1;
}