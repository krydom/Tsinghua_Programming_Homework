#include "CP_Complex.h"
#include <iostream>
#include <cmath>

using namespace std;

const double EPS = 1E-10;

void CP_Complex::mb_show(const char* s)
{
	cout << s;
	bool f1 = 0, f2 = 0;
	if (fabs(m_real) >= EPS)
	{
		cout << m_real;
		f1 = 1;
	}
	if (fabs(m_real) >= EPS && m_imaginary > EPS) cout << "+";
	if (fabs(m_imaginary) >= EPS)
	{
		if (fabs(1 - m_imaginary) >= EPS && fabs(-1 - m_imaginary) >= EPS) cout << m_imaginary;
		if (fabs(-1 - m_imaginary) < EPS) cout << "-";
		cout << "i";
		f2 = 1;
	}
	if (!(f1 || f2)) cout << "0";
	cout << endl;
}

CP_Complex operator + (CP_Complex& c1, CP_Complex& c2)
{
	CP_Complex CP(c1.m_real + c2.m_real, c1.m_imaginary + c2.m_imaginary);
	return CP;
}

CP_Complex operator + (double& c1, CP_Complex& c2)
{
	CP_Complex CP(c1 + c2.m_real, c2.m_imaginary);
	return CP;
}

CP_Complex operator + (int& c1, CP_Complex& c2)
{
	CP_Complex CP(c1 + c2.m_real, c2.m_imaginary);
	return CP;
}

CP_Complex operator + (CP_Complex& c1, double& c2)
{
	CP_Complex CP(c2 + c1.m_real, c1.m_imaginary);
	return CP;
}

CP_Complex operator + (CP_Complex& c1, int& c2)
{
	CP_Complex CP(c2 + c1.m_real, c1.m_imaginary);
	return CP;
}

CP_Complex operator - (CP_Complex& c1, CP_Complex& c2)
{
	CP_Complex CP(c1.m_real - c2.m_real, c1.m_imaginary - c2.m_imaginary);
	return CP;
}

CP_Complex operator - (double& c1, CP_Complex& c2)
{
	CP_Complex CP(c1 - c2.m_real, -c2.m_imaginary);
	return CP;
}

CP_Complex operator - (int& c1, CP_Complex& c2)
{
	CP_Complex CP(c1 - c2.m_real, -c2.m_imaginary);
	return CP;
}

CP_Complex operator - (CP_Complex& c1, double& c2)
{
	CP_Complex CP(c1.m_real - c2, c1.m_imaginary);
	return CP;
}

CP_Complex operator - (CP_Complex& c1, int& c2)
{
	CP_Complex CP(c1.m_real - c2, c1.m_imaginary);
	return CP;
}

CP_Complex operator * (CP_Complex& c1, CP_Complex& c2)
{
	CP_Complex CP(c1.m_real * c2.m_real - c1.m_imaginary * c2.m_imaginary, c1.m_imaginary * c2.m_real + c1.m_real * c2.m_imaginary);
	return CP;
}

CP_Complex operator * (double& c1, CP_Complex& c2)
{
	CP_Complex CP(c1 * c2.m_real, c1 * c2.m_imaginary);
	return CP;
}

CP_Complex operator * (int& c1, CP_Complex& c2)
{
	CP_Complex CP(c1 * c2.m_real, c1 * c2.m_imaginary);
	return CP;
}

CP_Complex operator * (CP_Complex& c1, double& c2)
{
	CP_Complex CP(c2 * c1.m_real, c2 * c1.m_imaginary);
	return CP;
}

CP_Complex operator * (CP_Complex& c1, int& c2)
{
	CP_Complex CP(c2 * c1.m_real, c2 * c1.m_imaginary);
	return CP;
}

CP_Complex operator / (CP_Complex& c1, CP_Complex& c2)
{
	CP_Complex CP((c1.m_real * c2.m_real + c1.m_imaginary * c2.m_imaginary) / (c2.m_real * c2.m_real + c2.m_imaginary * c2.m_imaginary), 
				  (c1.m_imaginary * c2.m_real - c1.m_real * c2.m_imaginary) / (c2.m_real * c2.m_real + c2.m_imaginary * c2.m_imaginary));
	return CP;
}

CP_Complex operator / (double& c1, CP_Complex& c2)
{
	CP_Complex CP((c1 * c2.m_real) / (c2.m_real * c2.m_real + c2.m_imaginary * c2.m_imaginary),
				  (-c1 * c2.m_imaginary) / (c2.m_real * c2.m_real + c2.m_imaginary * c2.m_imaginary));
	return CP;
}

CP_Complex operator / (int& c1, CP_Complex& c2)
{
	CP_Complex CP((c1 * c2.m_real) / (c2.m_real * c2.m_real + c2.m_imaginary * c2.m_imaginary),
				  (-c1 * c2.m_imaginary) / (c2.m_real * c2.m_real + c2.m_imaginary * c2.m_imaginary));
	return CP;
}

CP_Complex operator / (CP_Complex& c1, double& c2)
{
	CP_Complex CP(c1.m_real / c2, c1.m_imaginary / c2);
	return CP;
}

CP_Complex operator / (CP_Complex& c1, int& c2)
{
	CP_Complex CP(c1.m_real / c2, c1.m_imaginary / c2);
	return CP;
}

CP_Complex& operator ++ (CP_Complex& c)
{
	c.m_real += 1;
	return c;
}

CP_Complex operator ++ (CP_Complex& c, int)
{
	CP_Complex old = c;
	c.m_real += 1;
	return old;
}

CP_Complex& operator -- (CP_Complex& c)
{
	c.m_real -= 1;
	return c;
}

CP_Complex operator -- (CP_Complex& c, int)
{
	CP_Complex old = c;
	c.m_real -= 1;
	return old;
}

bool operator == (CP_Complex& c1, CP_Complex& c2)
{
	bool f1 = 0, f2 = 0;
	if (fabs(c1.m_real - c2.m_real) < EPS || fabs(c1.m_real - c2.m_real) / c1.m_real < EPS) f1 = 1;
	if (fabs(c1.m_imaginary - c2.m_imaginary) < EPS || fabs(c1.m_imaginary - c2.m_imaginary) / c1.m_imaginary < EPS) f2 = 1;
	return f1 && f2;
}

bool operator != (CP_Complex& c1, CP_Complex& c2)
{
	bool f1 = 0, f2 = 0;
	if (fabs(c1.m_real - c2.m_real) >= EPS && fabs(c1.m_real - c2.m_real) / c1.m_real >= EPS) f1 = 1;
	if (fabs(c1.m_imaginary - c2.m_imaginary) >= EPS && fabs(c1.m_imaginary - c2.m_imaginary) / c1.m_imaginary >= EPS) f2 = 1;
	return f1 || f2;
}