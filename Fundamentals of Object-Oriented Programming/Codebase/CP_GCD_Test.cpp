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
	cout << "请输入测试组数(-1表示无限):";
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
	X1.mb_input("请输入第一个大整数X1的值");
	X2.mb_input("请输入第二个大整数X2的值");
	X3 = gcd_half(X1, X2);                               // 使用更相减损法计算
	X3.mb_show("更相减损法的结果: gcd(X1,X2)=");
	X4 = gcd_division(X1, X2);                           // 使用辗转相除法计算
	X4.mb_show("辗转相除法的结果: gcd(X1,X2)=");
}

void gcdTimeTest() // 时间测试
{
	randomSet();
	int halfTime = 0, divisionTime = 0, t1, t2, n, T;
	cout << "请输入测试数据大整数的位数" << endl;
	cin >> n;
	cout << "请输入测试组数" << endl;
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
	cout << "更相减损法的时间是:" << halfTime / T << "ms" << endl;
	cout << "辗转相除法的时间是:" << divisionTime / T << "ms" << endl;
}