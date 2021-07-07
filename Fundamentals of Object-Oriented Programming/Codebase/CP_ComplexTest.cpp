#include "CP_ComplexTest.h"
#include "CP_Complex.h"
#include <complex>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

double doubleRandom()
{
	long long tmp = (((((rand() << 15) || rand()) << 15) || rand()) << 15) || rand();
	tmp -= (1LL << 59);
	return (double) tmp / ((double)(1 << 30) * 1.0);
}

int intRandom()
{
	return ((rand() << 15) || rand()) - (1 << 29);
}

void complexManualTest()
{
	CP_Complex c[4];
	c[0].m_real = 114; c[1].m_imaginary = -514; c[3].m_real = -19.19; c[3].m_imaginary = 810;
	double D[3] = { 114.514, 0, -1919.810 };
	int d[3] = { 114, 0, -514 };

	for(int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			CP_Complex C = c[i] + c[j];
			cout << "c" << i + 1 << "+c" << j + 1;
			C.mb_show("=");
		}
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 3; ++j)
		{
			CP_Complex C = c[i] + D[j];
			cout << "c" << i + 1 << "+d" << j + 1;
			C.mb_show("=");
			C = D[j] + c[i];
			cout << "d" << j + 1 << "+c" << i + 1;
			C.mb_show("=");
		}
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 3; ++j)
		{
			CP_Complex C = c[i] + d[j];
			cout << "c" << i + 1 << "+d" << j + 4;
			C.mb_show("=");
			C = d[j] + c[i];
			cout << "d" << j + 4 << "+c" << i + 1;
			C.mb_show("=");
		}
	system("pause");

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			CP_Complex C = c[i] - c[j];
			cout << "c" << i + 1 << "-c" << j + 1;
			C.mb_show("=");
		}
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 3; ++j)
		{
			CP_Complex C = c[i] - D[j];
			cout << "c" << i + 1 << "-d" << j + 1;
			C.mb_show("=");
			C = D[j] - c[i];
			cout << "d" << j + 1 << "-c" << i + 1;
			C.mb_show("=");
		}
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 3; ++j)
		{
			CP_Complex C = c[i] - d[j];
			cout << "c" << i + 1 << "-d" << j + 4;
			C.mb_show("=");
			C = d[j] - c[i];
			cout << "d" << j + 4 << "-c" << i + 1;
			C.mb_show("=");
		}
	system("pause");

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			CP_Complex C = c[i] * c[j];
			cout << "c" << i + 1 << "*c" << j + 1;
			C.mb_show("=");
		}
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 3; ++j)
		{
			CP_Complex C = c[i] * D[j];
			cout << "c" << i + 1 << "*d" << j + 1;
			C.mb_show("=");
			C = D[j] * c[i];
			cout << "d" << j + 1 << "*c" << i + 1;
			C.mb_show("=");
		}
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 3; ++j)
		{
			CP_Complex C = c[i] * d[j];
			cout << "c" << i + 1 << "*d" << j + 4;
			C.mb_show("=");
			C = d[j] * c[i];
			cout << "d" << j + 4 << "*c" << i + 1;
			C.mb_show("=");
		}
	system("pause");

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			CP_Complex C = c[i] / c[j];
			cout << "c" << i + 1 << "/c" << j + 1;
			C.mb_show("=");
		}
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 3; ++j)
		{
			CP_Complex C = c[i] / D[j];
			cout << "c" << i + 1 << "/d" << j + 1;
			C.mb_show("=");
			C = D[j] / c[i];
			cout << "d" << j + 1 << "/c" << i + 1;
			C.mb_show("=");
		}
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 3; ++j)
		{
			CP_Complex C = c[i] / d[j];
			cout << "c" << i + 1 << "/d" << j + 4;
			C.mb_show("=");
			C = d[j] / c[i];
			cout << "d" << j + 4 << "/c" << i + 1;
			C.mb_show("=");
		}
	system("pause");

	for (int i = 0; i < 4; ++i)
	{
		CP_Complex C1 = c[i], C2;
		C2 = C1++;
		cout << "c" << i + 1;
		C1.mb_show("++=");
		C2.mb_show("返回值=");

		C1 = c[i];
		C2 = ++C1;
		cout << "++c" << i + 1;
		C1.mb_show("=");
		C2.mb_show("返回值=");

		C1 = c[i], C2;
		C2 = C1--;
		cout << "c" << i + 1;
		C1.mb_show("--=");
		C2.mb_show("返回值=");

		C1 = c[i];
		C2 = --C1;
		cout << "--c" << i + 1;
		C1.mb_show("=");
		C2.mb_show("返回值=");
	}
	system("pause");
}

void complexAutoTest()
{
	srand(time(0));
	double c1real, c1imaginary, c2real, c2imaginary;
	int d1; double d2;
	while (1)
	{
		c1real = doubleRandom(), c1imaginary = doubleRandom(), c2real = doubleRandom(), c2imaginary = doubleRandom(), d2 = doubleRandom(), d1 = intRandom();
		CP_Complex c1(c1real, c1imaginary), c2(c2real, c2imaginary), c3, cs;
		complex<double> C1(c1real, c1imaginary), C2(c2real, c2imaginary), C3, D1(d1), D2(d2);

		c3 = c1 + c2; C3 = C1 + C2; cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 复+复
		if (cs != c3)
		{
			c1.mb_show("c1=");
			c2.mb_show("c2=");
			cout << "运算:+" << endl;
			return;
		}

		c3 = c1 - c2; C3 = C1 - C2; cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 复-复
		if (cs != c3)
		{
			c1.mb_show("c1=");
			c2.mb_show("c2=");
			cout << "运算:-" << endl;
			return;
		}

		c3 = c1 * c2; C3 = C1 * C2; cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 复*复
		if (cs != c3)
		{
			c1.mb_show("c1=");
			c2.mb_show("c2=");
			cout << "运算:*" << endl;
			return;
		}

		c3 = c1 / c2; C3 = C1 / C2; cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 复/复
		if (cs != c3)
		{
			c1.mb_show("c1=");
			c2.mb_show("c2=");
			cout << "运算:/" << endl;
			return;
		}

		c3 = c1 + d1; C3 = C1 + D1;  cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 复+整
		if (cs != c3)
		{
			c1.mb_show("c1=");
			cout << "d1=" << d1 << endl;
			cout << "运算:+" << endl;
			return;
		}

		c3 = c1 - d1; C3 = C1 - D1;  cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 复-整
		if (cs != c3)
		{
			c1.mb_show("c1=");
			cout << "d1=" << d1 << endl;
			cout << "运算:-" << endl;
			return;
		}

		c3 = c1 * d1; C3 = C1 * D1;  cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 复*整
		if (cs != c3)
		{
			c1.mb_show("c1=");
			cout << "d1=" << d1 << endl;
			cout << "运算:*" << endl;
			return;
		}

		if (d1 != 0)
		{
			c3 = c1 / d1; C3 = C1 / D1;  cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 复/整
			if (cs != c3)
			{
				c1.mb_show("c1=");
				cout << "d1=" << d1 << endl;
				cout << "运算:/" << endl;
				return;
			}
		}

		c3 = d1 + c1; C3 = D1 + C1;  cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 整+复
		if (cs != c3)
		{
			cout << "d1=" << d1 << endl;
			c1.mb_show("c1=");
			cout << "运算:+" << endl;
			return;
		}

		c3 = d1 - c1; C3 = D1 - C1;  cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 整-复
		if (cs != c3)
		{
			cout << "d1=" << d1 << endl;
			c1.mb_show("c1=");
			cout << "运算:-" << endl;
			return;
		}

		c3 = d1 * c1; C3 = D1 * C1;  cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 整*复
		if (cs != c3)
		{
			cout << "d1=" << d1 << endl;
			c1.mb_show("c1=");
			cout << "运算:*" << endl;
			return;
		}

		c3 = d1 / c1; C3 = D1 / C1;  cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 整/复
		if (cs != c3)
		{
			cout << "d1=" << d1 << endl;
			c1.mb_show("c1=");
			cout << "运算:/" << endl;
			return;
		}

		c3 = c1 + d2; C3 = C1 + D2;  cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 复+实
		if (cs != c3)
		{
			c1.mb_show("c1=");
			cout << "d2=" << d2 << endl;
			cout << "运算:+" << endl;
			return;
		}

		c3 = c1 - d2; C3 = C1 - D2;  cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 复-实
		if (cs != c3)
		{
			c1.mb_show("c1=");
			cout << "d2=" << d2 << endl;
			cout << "运算:-" << endl;
			return;
		}

		c3 = c1 * d2; C3 = C1 * D2;  cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 复*实
		if (cs != c3)
		{
			c1.mb_show("c1=");
			cout << "d2=" << d2 << endl;
			cout << "运算:*" << endl;
			return;
		}

		c3 = c1 / d2; C3 = C1 / D2;  cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 复/实
		if (cs != c3)
		{
			c1.mb_show("c1=");
			cout << "d2=" << d2 << endl;
			cout << "运算:/" << endl;
			return;
		}

		c3 = d2 + c1; C3 = D2 + C1;  cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 实+复
		if (cs != c3)
		{
			cout << "d2=" << d2 << endl;
			c1.mb_show("c1=");
			cout << "运算:+" << endl;
			return;
		}

		c3 = d2 - c1; C3 = D2 - C1;  cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 实-复
		if (cs != c3)
		{
			cout << "d2=" << d2 << endl;
			c1.mb_show("c1=");
			cout << "运算:-" << endl;
			return;
		}

		c3 = d2 * c1; C3 = D2 * C1;  cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 实*复
		if (cs != c3)
		{
			cout << "d2=" << d2 << endl;
			c1.mb_show("c1=");
			cout << "运算:*" << endl;
			return;
		}

		c3 = d2 / c1; C3 = D2 / C1;  cs.m_real = C3.real(), cs.m_imaginary = C3.imag(); // 实/复
		if (cs != c3)
		{
			cout << "d2=" << d2 << endl;
			c1.mb_show("c1=");
			cout << "运算:/" << endl;
			return;
		}

		c2 = c1++; cs.m_real = c2.m_real + 1, cs.m_imaginary = c2.m_imaginary;          // 复++
		if (c1 != cs)
		{
			c2.mb_show("c1=");
			cout << "运算:后++" << endl;
			return;
		}

		c2 = c1; c3 = ++c1; cs.m_real = c2.m_real + 1, cs.m_imaginary = c2.m_imaginary; // ++复
		if (c1 != cs || c3 != cs)
		{
			c2.mb_show("c1=");
			cout << "运算:前++" << endl;
			return;
		}

		c2 = c1--; cs.m_real = c2.m_real - 1, cs.m_imaginary = c2.m_imaginary;          // 复--
		if (c1 != cs)
		{
			c2.mb_show("c1=");
			cout << "运算:后++" << endl;
			return;
		}

		c2 = c1; c3 = --c1; cs.m_real = c2.m_real - 1, cs.m_imaginary = c2.m_imaginary; // --复
		if (c1 != cs || c3 != cs)
		{
			c2.mb_show("c1=");
			cout << "运算:前++" << endl;
			return;
		}

		cout << "Accepted!" << endl;
	}
}