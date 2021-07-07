#ifndef C_INTEGER_H
#define C_INTEGER_H
#include <vector>
#include <complex>

using namespace std;

typedef enum cinterger_status
{
	INTEGER_INVALID = -3,   //非数
	INTEGER_NEG_INF = -2,   //负无穷大
	INTEGER_NEG_VALUE = -1, //常规负数
	INTEGER_ZERO = 0,       //0 
	INTEGER_POS_VALUE = 1,  //常规正数
	INTEGER_POS_INF = 2     //正无穷大
} IntegerStatus;

class C_Integer 
{ 
protected:
	IntegerStatus m_status;        // 数的种类
	vector<unsigned char> m_data;  // 数的绝对值

public:
	C_Integer();            // 默认构造
	C_Integer(long long x); // 赋值构造

	void mb_setnum(long long x);  // 给大整数赋值
	void mb_randomSet(int n);     // 给大整数随机赋值，长度为n
	void mb_show(const char* s);  // 输出表示的大整数
	void mb_input(const char* s); // 输入一个大整数
	bool mb_checkZero();          // 判断大整数是否是0
	int parity();                 // 大整数的奇偶性，0表示偶数，1表示奇数
	C_Integer abs();              // 大整数的绝对值

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
	C_Integer operator % (C_Integer x);
};

extern void fft(vector<complex<double> > &a, int f, int n, int L); // 快速傅里叶变换

#endif // !C_INTEGER_H
