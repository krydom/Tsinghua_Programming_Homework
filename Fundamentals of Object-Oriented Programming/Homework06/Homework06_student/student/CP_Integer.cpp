#include <iostream>
#include "CP_Integer.h"

using namespace std;

int CP_Integer::mb_getInput() // ����
{
	double x = 0;
	//cout << "������һ��������";
	cin >> x;
	while (cin.rdstate() == ios_base::failbit || (x != (int) x && x != (int) x + 1))
	{
		cout << "������Ĳ�������" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "������һ��������";
		cin >> x;
	}
	if (x == (int)x) m_data = x; else m_data = x + 1;
	return m_data;
}

int CP_Integer::mb_showData() // ������ڵ�ֵ
{
	cout << "�������������" << m_data << endl;
	return m_data;
}

int CP_Integer::integerPlus(int plusNumber)             //�ӷ�
{
	m_data += plusNumber;
	return m_data;
}

int CP_Integer::integerMultiply(int multiplyNumber)     //�˷�
{
	m_data *= multiplyNumber;
	return m_data;
}

int CP_Integer::integerOddOrEven() //�ж���ż�ԣ�ż������0��������1
{
	return m_data & 1;
}
