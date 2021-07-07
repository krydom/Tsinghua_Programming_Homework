#include <iostream>
#include "CP_PositiveInteger.h"

using namespace std;

int CP_PositiveInteger::mb_getInput() // 输入
{
	m_data = 0;
	while (m_data <= 0)
	{
		cout << "请输入一个正整数：";
		cin >> m_data;
		if (m_data <= 0) cout << "您输入的不是正整数" << endl;
	}
	return m_data;
}

int CP_PositiveInteger::mb_showData() // 输出现在的值
{
	cout << "您输入的整数是" << m_data << endl;
	return m_data;
}

int CP_PositiveInteger::integerPlus(int plusNumber)             //加法
{
	m_data += plusNumber;
	return m_data;
}

int CP_PositiveInteger::integerMultiply(int multiplyNumber)     //乘法
{
	m_data *= multiplyNumber;
	return m_data;
}

int CP_PositiveInteger::integerOddOrEven() //判断奇偶性，偶数返回0奇数返回1
{
	return m_data & 1;
}