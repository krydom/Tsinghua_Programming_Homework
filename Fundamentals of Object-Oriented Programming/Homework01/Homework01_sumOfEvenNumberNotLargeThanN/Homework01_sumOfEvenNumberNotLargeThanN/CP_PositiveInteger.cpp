#include <iostream>
#include "CP_PositiveInteger.h"

using namespace std;

int CP_PositiveInteger::mb_getInput() // ����
{
	double x = 0;
	cout << "������һ����������";
	cin >> x;
	while (x <= 0 || cin.rdstate() == ios_base::failbit || (x != (int)x && x != (int)x + 1))
	{
		cout << "������Ĳ���������" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "������һ����������";
		cin >> x;
	}
	if (x == (int)x) m_data = x; else m_data = x + 1;
	return m_data;
}

int CP_PositiveInteger::mb_showData() // ������ڵ�ֵ
{
	cout << "�������������" << m_data << endl;
	return m_data;
}

int CP_PositiveInteger::integerOddOrEven() //�ж���ż�ԣ�ż������0��������1
{
	return m_data & 1;
}