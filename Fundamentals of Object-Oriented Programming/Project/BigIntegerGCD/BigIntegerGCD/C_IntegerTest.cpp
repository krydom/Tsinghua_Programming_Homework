#include "C_Integer.h"
#include "C_IntegerTest.h"
#include "random.h"
#include <iostream>

using namespace std;

void integerTest()
{
	C_Integer x1, x2, x3;
	x1.mb_input("请输入一个整数x1:");
	x2.mb_input("请输入一个整数x2:");
	x1.mb_show("x1 = ");
	x2.mb_show("x2 = ");

	x3 = x1 + x2;
	x3.mb_show("x1 + x2 = ");
	x3 = x2 + x1;
	x3.mb_show("x2 + x1 = ");

	x3 = x1 - x2;
	x3.mb_show("x1 - x2 = ");
	x3 = x2 - x1;
	x3.mb_show("x2 - x1 = ");

	x3 = x1 * x2;
	x3.mb_show("x1 * x2 = ");
	x3 = x2 * x1;
	x3.mb_show("x2 * x1 = ");

	x3 = x1 / 2;
	x3.mb_show("x1 / 2 = ");
	x3 = x2 / 2;
	x3.mb_show("x2 / 2 = ");

	x3 = x1 / x2;
	x3.mb_show("x1 / x2 = ");
	x3 = x2 / x1;
	x3.mb_show("x2 / x1 = ");
}

void integerAutoTest()
{
	randomSet();
	while (1)
	{
		long long x1 = random(), x2 = random();
		C_Integer X1(x1), X2(x2), X3, X4;
		bool fl = 0;

		X3 = X1 + X2, X4.mb_setnum(x1 + x2);
		if (X3 != X4) fl = 1;
		X3 = X2 + X1, X4.mb_setnum(x2 + x1);
		if (X3 != X4) fl = 1;

		X3 = X1 - X2, X4.mb_setnum(x1 - x2);
		if (X3 != X4) fl = 1;
		X3 = X2 - X1, X4.mb_setnum(x2 - x1);
		if (X3 != X4) fl = 1;

		X3 = X1 * X2, X4.mb_setnum(x1 * x2);
		if (X3 != X4) fl = 1;
		X3 = X2 * X1, X4.mb_setnum(x2 * x1);
		if (X3 != X4) fl = 1;

		if (x2 != 0)
		{
			X3 = X1 / X2, X4.mb_setnum(x1 / x2);
			if (X3 != X4) fl = 1;
			X3 = X1 / x2;
			if (X3 != X4) fl = 1;
		}
		if (x1 != 0)
		{
			X3 = X2 / X1, X4.mb_setnum(x2 / x1);
			if (X3 != X4) fl = 1;
			X3 = X2 / x1;
			if (X3 != X4) fl = 1;
		}
		
		if (fl) { cout << "WA! " << x1 << ' ' << x2 << endl; return; }
		cout << "Accepted!" << endl;
	}
}