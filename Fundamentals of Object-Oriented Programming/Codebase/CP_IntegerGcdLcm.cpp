#include <iostream>
#include <ctime>
#include <cstdlib>
#include "CP_integerGcdLcm.h"

using namespace std;

int integerGcd(int data1, int data2)
{
	return data2 == 0 ? data1 : integerGcd(data2, data1 % data2);
}

int integerLcm(int data1, int data2)
{
	int m_GCD = integerGcd(data1, data2);
	return data1 / m_GCD * data2;
}

void integerGcdCheck1()
{
	int gcdMatrix[101][101]; // gcd����
	for (int i = 0; i <= 100; ++i) gcdMatrix[i][0] = gcdMatrix[0][i] = i;
	for (int i = 1; i <= 100; ++i)
		for (int j = 1; j <= i; ++j)
			gcdMatrix[j][i] = gcdMatrix[i][j] = gcdMatrix[j][i % j]; // ��ʼ��gcd����

	bool flWrong = 0;
	for (int i = 0; i <= 100; ++i)
		for (int j = 0; j <= 100; ++j)
			if (integerGcd(i, j) != gcdMatrix[i][j]) flWrong = 1; // Ѱ�Ҵ���

	if (!flWrong) cout << "Plan1 : Accept!" << endl; // ���û�д���������������ȷ
}

void integerGcdCheck2(int T)
{
	int Minute = 1;
	srand(time(0));
	while (T != 0)
	{
		int a = ((rand() << 15) | rand()) % 100000000;
		int b = ((rand() << 15) | rand()) % 100000000;
		int Gcd = integerGcd(a, b);

		if (a % Gcd != 0 || b % Gcd != 0) // һ��Ҫ�ǹ�Լ��
		{
			cout << "Wrong Answer! a = " << a << ", b = " << b << ", gcd = " << Gcd << endl;
		}

		a /= Gcd, b /= Gcd; // һ��Ҫ�����Ĺ�Լ��
		for(int i = 2; i * i <= a; ++i)
			if (a % i == 0 && b % i == 0)
			{
				cout << "Wrong Answer! a = " << a << ", b = " << b << ", gcd = " << Gcd << endl;
			}

		--T;
		if (T < 0) T = -1;
	}

	cout << "Plan2 : Accept!" << endl;
}