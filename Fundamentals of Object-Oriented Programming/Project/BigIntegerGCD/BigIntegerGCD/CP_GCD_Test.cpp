#include "CP_GCD.h"
#include "random.h"
#include "C_Integer.h"
#include <iostream>
#include <ctime>

using namespace std;

void gcdAutoTest()
{
	randomSet();
	int tmp = 1, n;
	cout << "�������������(-1��ʾ����):";
	cin >> n;
	while (tmp <= n || n == -1)
	{
		long long x1 = random(), x2 = random(), x3 = random();
		x1 *= x3, x2 *= x3;
		C_Integer X1(x1), X2(x2), X3, X4, X5(gcd(x1, x2));
		X3 = gcd_half(X1, X2);
		X4 = gcd_division(X1, X2); 
		if (X3 != X4 || X3 != X5)
		{
			cout << "WA! " << x1 << ' ' << x2 << endl;
			return;
		}
		else
		{
			cout << "Test Case # " << tmp << " : ";
			cout << "Accepted!" << endl;
		}
		++tmp;
	}
}

void gcdManualTest()
{
	C_Integer X1, X2, X3, X4;
	X1.mb_input("�������һ��������X1��ֵ");
	X2.mb_input("������ڶ���������X2��ֵ");
	X3 = gcd_half(X1, X2);                               // ʹ�ø�����𷨼���
	X3.mb_show("������𷨵Ľ��: gcd(X1,X2)=");
	X4 = gcd_division(X1, X2);                           // ʹ��շת���������
	X4.mb_show("շת������Ľ��: gcd(X1,X2)=");
}

void gcdTimeTest() // ʱ�����
{
	randomSet();
	int halfTime = 0, divisionTime = 0, t1, t2, n, T;
	cout << "������������ݴ�������λ��" << endl;
	cin >> n;
	cout << "�������������" << endl;
	cin >> T;
	for (int i = 1; i <= T; ++i)
	{
		cout << "Test Case # " << i << endl;
		C_Integer X1, X2, X3;
		X1.mb_randomSet(n), X2.mb_randomSet(n);
		X1.mb_show("X1=");
		X2.mb_show("X2=");
		
		t1 = clock();
		X3 = gcd_half(X1, X2);
		t2 = clock();
		halfTime += t2 - t1;

		t1 = clock();
		X3 = gcd_division(X1, X2);
		t2 = clock();
		divisionTime += t2 - t1;
		X3.mb_show("gcd(X1, X2)=");

		cout << endl;
	}
	cout << "������𷨵�ʱ����:" << halfTime / T << "ms" << endl;
	cout << "շת�������ʱ����:" << divisionTime / T << "ms" << endl;
}