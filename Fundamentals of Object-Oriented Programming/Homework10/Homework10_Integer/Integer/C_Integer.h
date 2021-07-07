#ifndef C_INTEGER_H
#define C_INTEGER_H
#include <vector>
#include <complex>

using namespace std;

typedef enum cinterger_status
{
	INTEGER_INVALID = -3, //非数
	INTEGER_NEG_INF = -2, //负无穷大
	INTEGER_NEG_VALUE = -1, //常规负数
	INTEGER_ZERO = 0, //0 
	INTEGER_POS_VALUE = 1, //常规正数
	INTEGER_POS_INF = 2 //正无穷大
} IntegerStatus;

class C_Integer 
{ 
protected:
	IntegerStatus m_status;
	vector<unsigned char> m_data;

public:
	C_Integer();
	C_Integer(long long x);

	void mb_setnum(long long x);
	void mb_show(const char* s);
	void mb_input(const char* s);
	C_Integer abs();

	bool operator < (C_Integer x);
	bool operator > (C_Integer x);
	bool operator <= (C_Integer x);
	bool operator >= (C_Integer x);
	bool operator == (C_Integer x);
	bool operator != (C_Integer x);
	C_Integer operator + (C_Integer x);
	C_Integer operator - (C_Integer x);
	C_Integer operator * (C_Integer x);
	C_Integer operator / (long long x);
	C_Integer operator / (C_Integer x);
};

extern void fft(vector<complex<double> > &a, int f, int n, int L);

#endif // !C_INTEGER_H
