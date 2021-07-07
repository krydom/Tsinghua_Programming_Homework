#include <iostream>
#include "CP_PositiveInteger.h"

using namespace std;

int CP_PositiveInteger::mb_getInput() // 输入
{
	double x = 0;
	cout << "请输入一个正整数：";
	cin >> x;
	while (x <= 0 || cin.rdstate() == ios_base::failbit || (x != (int)x && x != (int)x + 1))
	{
		cout << "您输入的不是正整数" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "请输入一个正整数：";
		cin >> x;
	}
	if (x == (int)x) m_data = x; else m_data = x + 1;
	return m_data;
}

int CP_PositiveInteger::mb_showData() // 输出现在的值
{
	cout << "您输入的整数是" << m_data << endl;
	return m_data;
}

int CP_PositiveInteger::integerOddOrEven() //判断奇偶性，偶数返回0奇数返回1
{
	return m_data & 1;
}