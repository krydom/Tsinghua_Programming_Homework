#ifndef C_INTEGER_H
#define C_INTEGER_H
#include <vector>
#include <complex>

using namespace std;

typedef enum cinterger_status
{
	INTEGER_INVALID = -3,   //����
	INTEGER_NEG_INF = -2,   //�������
	INTEGER_NEG_VALUE = -1, //���渺��
	INTEGER_ZERO = 0,       //0 
	INTEGER_POS_VALUE = 1,  //��������
	INTEGER_POS_INF = 2     //�������
} IntegerStatus;

class C_Integer 
{ 
protected:
	IntegerStatus m_status;        // ��������
	vector<unsigned char> m_data;  // ���ľ���ֵ

public:
	C_Integer();            // Ĭ�Ϲ���
	C_Integer(long long x); // ��ֵ����

	void mb_setnum(long long x);  // ����������ֵ
	void mb_randomSet(int n);     // �������������ֵ������Ϊn
	void mb_show(const char* s);  // �����ʾ�Ĵ�����
	void mb_input(const char* s); // ����һ��������
	bool mb_checkZero();          // �жϴ������Ƿ���0
	int parity();                 // ����������ż�ԣ�0��ʾż����1��ʾ����
	C_Integer abs();              // �������ľ���ֵ

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

extern void fft(vector<complex<double> > &a, int f, int n, int L); // ���ٸ���Ҷ�任

#endif // !C_INTEGER_H
