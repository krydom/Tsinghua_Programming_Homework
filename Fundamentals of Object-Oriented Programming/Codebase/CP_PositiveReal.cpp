#include <iostream>
#include "CP_PositiveReal.h"

using namespace std;

int CP_PositiveReal::mb_getInput() // ����
{
	m_data = 0;
	cout << "������һ����ʵ����";
	cin >> m_data;
	while (m_data <= 0 || cin.rdstate() == ios_base::failbit)
	{
		cout << "������Ĳ�����ʵ��" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "������һ����ʵ����";
		cin >> m_data;
	}
	return m_data;
}

int CP_PositiveReal::mb_showData() // ������ڵ�ֵ
{
	cout << "���������ʵ����" << m_data << endl;
	return m_data;
}