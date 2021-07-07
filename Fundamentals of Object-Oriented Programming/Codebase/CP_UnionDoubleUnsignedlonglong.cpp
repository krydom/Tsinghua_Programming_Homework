#include "CP_UnionDoubleUnsignedlonglong.h"
#include <iostream>
#include <bitset>
#include <string>
#include <cmath>

using namespace std;

void gb_showDoubleBinMemory(const U_DoubleUnsignedlonglong& u)
{
	cout << u.m_double;
	cout << "在内存当中存储的数据是0b";
	bitset<64> LL(u.m_int64);
	string str(LL.to_string());
	cout << str << endl;
}

void gb_testDoubleUnsignedlonglong()
{
	cout << "请输入一个双精度浮点数。" << endl;
	double data;
	cin >> data;
	gb_showDoubleBinMemory(U_DoubleUnsignedlonglong(data));
}

void testInfNan()
{
	cout << endl;
	double zero = 0, posInf, negInf, ind, nan;
	posInf = 1.0 / zero;
	gb_showDoubleBinMemory(U_DoubleUnsignedlonglong(posInf));    // inf
	negInf = -1.0 / zero;
	gb_showDoubleBinMemory(U_DoubleUnsignedlonglong(negInf));    // -inf
	ind = zero / zero;
	gb_showDoubleBinMemory(U_DoubleUnsignedlonglong(ind));       // ind
	nan = -ind;
	gb_showDoubleBinMemory(U_DoubleUnsignedlonglong(nan));       // nan

	cout << endl;
	double a[5] = { posInf, negInf, ind, nan, 1 };
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
		{
			cout << a[i] << "+" << a[j] << "=" << a[i] + a[j] << endl;
			cout << a[i] << "-" << a[j] << "=" << a[i] - a[j] << endl;
			cout << a[i] << "*" << a[j] << "=" << a[i] * a[j] << endl;
			cout << a[i] << "/" << a[j] << "=" << a[i] / a[j] << endl << endl;
		}
}