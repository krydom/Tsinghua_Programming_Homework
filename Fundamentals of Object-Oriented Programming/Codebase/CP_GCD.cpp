#include "C_Integer.h"
#include "CP_GCD.h"
#include <iostream>

using namespace std;

long long gcd(long long x, long long y) // շת��������������Լ��
{
	if (x < 0) x = -x;
	if (y < 0) y = -y;
	if (!y) return x;
	return gcd(y, x % y);
}

C_Integer gcd_half(C_Integer x, C_Integer y)     // ������������Լ��
{
	x = x.abs(), y = y.abs(); C_Integer ans(1);
	while (1)
	{
		if (x.mb_checkZero()) return y * ans;
		if (y.mb_checkZero()) return x * ans;
		while (x.parity() == 0 && y.parity() == 0) x = x / 2, y = y / 2, ans = ans * 2; 
		while (x.parity() == 0) x = x / 2;
		while (y.parity() == 0) y = y / 2;
		if (x < y) y = y - x; else x = x - y;
	}
}

C_Integer gcd_division(C_Integer x, C_Integer y) // շת����������Լ��
{
	x = x.abs(), y = y.abs();
	if (x.mb_checkZero()) return y;
	while (!y.mb_checkZero())
	{
		C_Integer tmp = x % y;
		x = y;
		y = tmp;
	}
	return x;
}