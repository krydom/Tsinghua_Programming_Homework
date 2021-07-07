#include <iostream>
#include "CP_PositiveReal.h"

using namespace std;

int CP_PositiveReal::mb_getInput() // 输入
{
	m_data = 0;
	cout << "请输入一个正实数：";
	cin >> m_data;
	while (m_data <= 0 || cin.rdstate() == ios_base::failbit)
	{
		cout << "您输入的不是正实数" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "请输入一个正实数：";
		cin >> m_data;
	}
	return m_data;
}

int CP_PositiveReal::mb_showData() // 输出现在的值
{
	cout << "您输入的正实数是" << m_data << endl;
	return m_data;
}