#ifndef CP_UNIONDOUBLELONGLONG_H
#define CP_UNIONDOUBLELONGLONG_H

union U_DoubleUnsignedlonglong
{
	double m_double;
	unsigned long long m_int64;
	U_DoubleUnsignedlonglong(unsigned long long i = 0) : m_int64(i) {}
	U_DoubleUnsignedlonglong(double d) : m_double(d) {}
	U_DoubleUnsignedlonglong(const U_DoubleUnsignedlonglong& u) : m_int64(u.m_int64) {}
	~U_DoubleUnsignedlonglong() {}
};

extern void gb_showDoubleBinMemory(const U_DoubleUnsignedlonglong& u);
extern void gb_testDoubleUnsignedlonglong();
extern void testInfNan();

#endif // !CP_UNIONDOUBLE_H
