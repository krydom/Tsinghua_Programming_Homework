#include "C_Integer.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <complex>
#include <cmath>

using namespace std;

const double pi = acos(-1);

C_Integer::C_Integer() // Ĭ�Ϲ���
{
	m_status = INTEGER_ZERO;
}

C_Integer::C_Integer(long long x) // ��ֵ����
{
	if (x == 0) m_status = INTEGER_ZERO;     // ������������
	if (x > 0) m_status = INTEGER_POS_VALUE;
	if (x < 0) m_status = INTEGER_NEG_VALUE;
	x = std::abs(x);
	while (x)                                // �������ľ���ֵ
	{
		m_data.push_back((unsigned char)'0' + x % 10);
		x /= 10;
	}
}

void C_Integer::mb_setnum(long long x) // ����������ֵ
{
	if (x == 0) m_status = INTEGER_ZERO;     // ������������
	if (x > 0) m_status = INTEGER_POS_VALUE;
	if (x < 0) m_status = INTEGER_NEG_VALUE;
	m_data.clear();                          // �������ľ���ֵ
	x = std::abs(x);
	while (x)
	{
		m_data.push_back((unsigned char)'0' + x % 10);
		x /= 10;
	}
}

void C_Integer::mb_randomSet(int n) // �������������ֵ������Ϊn
{
	m_status = INTEGER_POS_VALUE;
	m_data.clear();
	for (int i = 0; i < n; ++i)
		m_data.push_back((unsigned char)'0' + rand() % 10);
	while (m_data.size() && m_data[m_data.size() - 1] == '0') m_data.pop_back();
	if (!m_data.size()) m_status = INTEGER_ZERO;
}

void C_Integer::mb_show(const char* s) // ���������
{
	cout << s;
	if (m_status == INTEGER_NEG_VALUE) cout << "-"; // �������������
	if (m_status == INTEGER_ZERO) cout << '0'; // ����0����Ϊ����ֵ��������������0
	else for(int i = m_data.size() - 1; ~i; --i) cout << m_data[i]; // ������ľ���ֵ
	cout << endl;
}

void C_Integer::mb_input(const char* s) // ����һ��������
{
	cout << s << endl;
	m_data.clear();

	string S;
	bool fl, outvis = 0; // outvis��ʾ�Ƿ��ǵ�һ�����룬������Ǹ�����ʾ��Ϣ, fl=1��ʾ��ǰ����Ĳ���һ���Ϸ�������
	int FIRST; // FIRST�����һ����0���ֵ�λ�ã����û���򱣴��һ��0��λ��

	do
	{
		if (outvis) cout << "����Ĳ�������������������:" << endl;
		getline(cin, S);
		outvis = 1;

		fl = 0;
		FIRST = -1;                                 // FIRST=-1��ʾû������
		for (int i = 0; i < S.length(); ++i)
		{
			if ((S[i] > '9' || S[i] < '0') && S[i] != '+' && S[i] != '-') // �������ֺ�+-֮����ַ�����������
			{
				fl = 1;
				break;
			}
			if (i && (S[i] == '+' || S[i] == '-')) // +-�ڵ�һ��λ��֮���λ�ó��֣����Ƿ��ϱ�׼������
			{
				fl = 1;
				break;
			}
			if (S[i] == '0' && FIRST == -1) FIRST = i;
			if (S[i] >= '1' && S[i] <= '9')
				if (FIRST == -1 || S[FIRST] == '0') FIRST = i;
		}
		if (FIRST == -1) fl = 1;                   // û������
	} while (fl);

	if (S[0] == '-') m_status = INTEGER_NEG_VALUE; // ������������
	else m_status = INTEGER_POS_VALUE;
	if (S[FIRST] == '0') m_status = INTEGER_ZERO;
	if (m_status != INTEGER_ZERO)                  // �������ľ���ֵ
	{
		for (int i = S.length() - 1; i >= FIRST; --i)
			m_data.push_back(S[i]);
	}
}

bool C_Integer::mb_checkZero() // �жϴ������Ƿ���0
{
	return m_status == INTEGER_ZERO;
}

int C_Integer::parity() // ����������ż��
{
	if (m_status == INTEGER_ZERO) return 0; // 0��ż��
	return (m_data[0] - (unsigned char) '0') % 2; // ���򿴴����������һλ
}

C_Integer C_Integer::abs() // �������ľ���ֵ
{
	C_Integer x = *this;
	if (x.m_status < 0) x.m_status = INTEGER_POS_VALUE; // ����Ǹ����ĳ��������
	return x;
}

bool C_Integer::operator == (C_Integer x) // ���
{
	if (m_status != x.m_status) return 0; 
	if (m_data.size() != x.m_data.size()) return 0;
	for (int i = 0; i < m_data.size(); ++i)
		if (m_data[i] != x.m_data[i]) return 0;
	return 1;
}

bool C_Integer::operator < (C_Integer x) // С��
{
	if (m_status < x.m_status) return 1;
	if (m_status > x.m_status) return 0;
	if (m_status == INTEGER_ZERO) return 0;
	if (m_status == INTEGER_NEG_VALUE) // ��������ֵ���С
	{
		if (m_data.size() > x.m_data.size()) return 1;
		if (m_data.size() < x.m_data.size()) return 0;
		for (int i = m_data.size() - 1; ~i; --i)
		{
			if (m_data[i] > x.m_data[i]) return 1;
			if (m_data[i] < x.m_data[i]) return 0;
		}
	}
	else if (m_status == INTEGER_POS_VALUE) // ��������ֵС��С
	{
		if (m_data.size() > x.m_data.size()) return 0;
		if (m_data.size() < x.m_data.size()) return 1;
		for (int i = m_data.size() - 1; ~i; --i)
		{
			if (m_data[i] > x.m_data[i]) return 0;
			if (m_data[i] < x.m_data[i]) return 1;
		}
	}
	return 0;
}

bool C_Integer::operator > (C_Integer x) // ����
{
	if (m_status < x.m_status) return 0;
	if (m_status > x.m_status) return 1;
	if (m_status == INTEGER_ZERO) return 0;
	if (m_status == INTEGER_NEG_VALUE) // ��������ֵ���С
	{
		if (m_data.size() > x.m_data.size()) return 0;
		if (m_data.size() < x.m_data.size()) return 1;
		for (int i = m_data.size() - 1; ~i; --i)
		{
			if (m_data[i] > x.m_data[i]) return 0;
			if (m_data[i] < x.m_data[i]) return 1;
		}
	}
	else if (m_status == INTEGER_POS_VALUE) // ��������ֵС��С
	{
		if (m_data.size() > x.m_data.size()) return 1;
		if (m_data.size() < x.m_data.size()) return 0;
		for (int i = m_data.size() - 1; ~i; --i)
		{
			if (m_data[i] > x.m_data[i]) return 1;
			if (m_data[i] < x.m_data[i]) return 0;
		}
	}
	return 0;
}

bool C_Integer::operator >= (C_Integer x)
{
	return (*this > x || *this == x);
}

bool C_Integer::operator <= (C_Integer x)
{
	return (*this < x || *this == x);
}

bool C_Integer::operator != (C_Integer x)
{
	return !(*this == x);
}

C_Integer C_Integer::operator + (C_Integer x) // �ӷ�
{
	if (m_status * x.m_status != INTEGER_NEG_VALUE) // ͬ�����ӷ�
	{
		C_Integer y;
		if (m_data.size() < x.m_data.size()) // �ӷ�
		{
			y.m_data = x.m_data;
			for (int i = 0; i < m_data.size(); ++i)
				y.m_data[i] += m_data[i] - '0';
		}
		else
		{
			y.m_data = m_data;
			for (int i = 0; i < x.m_data.size(); ++i)
				y.m_data[i] += x.m_data[i] - '0';
		}
		
		for (int i = 0; i + 1 < y.m_data.size(); ++i) // ��λ
			if (y.m_data[i] > '9')
			{
				y.m_data[i] -= 10;
				y.m_data[i + 1] += 1;
			}
		if (!y.m_data.empty())
			if (y.m_data[y.m_data.size() - 1] > '9')
			{
				y.m_data[y.m_data.size() - 1] -= 10;
				y.m_data.push_back((unsigned char) '1');
			}

		if (m_status > 0 || x.m_status > 0) y.m_status = INTEGER_POS_VALUE;      // �ж���������
		else if (m_status < 0 || x.m_status < 0) y.m_status = INTEGER_NEG_VALUE;
		else y.m_status = INTEGER_ZERO;

		return y;
	}
	else // �������֮��������
	{
		x.m_status = m_status;
		return *this - x;
	}
}

C_Integer C_Integer::operator - (C_Integer x)
{
	if (x.m_status == INTEGER_ZERO) return *this; // �й�0������
	if (m_status == INTEGER_ZERO)
	{
		if (x.m_status == INTEGER_NEG_VALUE) x.m_status = INTEGER_POS_VALUE;
		else if (x.m_status == INTEGER_POS_VALUE) x.m_status = INTEGER_NEG_VALUE;
		return x;
	}

	if (m_status * x.m_status != INTEGER_NEG_VALUE) // ͬ��������
	{
		C_Integer y = *this;
		if (y.abs() < x.abs())
		{
			swap(y.m_data, x.m_data);
			if (y.m_status == INTEGER_NEG_VALUE) y.m_status = INTEGER_POS_VALUE;
			else if (y.m_status == INTEGER_POS_VALUE) y.m_status = INTEGER_NEG_VALUE;
		}
		for (int i = 0; i < x.m_data.size(); ++i) // ����
			y.m_data[i] -= x.m_data[i] - '0';
		for (int i = 0; i < y.m_data.size(); ++i) // ��λ
			if (y.m_data[i] < '0')
			{
				y.m_data[i] += 10;
				y.m_data[i + 1] -= 1;
			}
		while (!y.m_data.empty() && y.m_data[y.m_data.size() - 1] == '0') // ȥ��ǰ��0
			y.m_data.pop_back();

		if (y.m_data.empty()) y.m_status = INTEGER_ZERO; // ���0֮����

		return y;
	}
	else // �������֮�����ӷ�
	{
		x.m_status = m_status;
		return *this + x;
	}
}

void fft(vector<complex<double> > &a, int f, int n, int L) // ���ٸ���Ҷ�任
{
	vector<int> R;
	R.push_back(0);
	for (int i = 1; i < n; i++) R.push_back((R[i >> 1] >> 1) | ((i & 1) << (L - 1))); // ��������

	for (int i = 0; i < n; i++)if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1; i < n; i <<= 1)
	{
		complex<double> wn(cos(pi / i), f * sin(pi / i));
		for (int j = 0; j < n; j += (i << 1))
		{
			complex<double> w(1, 0);
			for (int k = 0; k < i; ++k, w *= wn)
			{
				complex<double> x = a[j + k], y = w * a[j + k + i];
				a[j + k] = x + y; a[j + k + i] = x - y;
			}
		}
	}
	if (f == -1) for (int i = 0; i < n; ++i) a[i] /= n;
}

C_Integer C_Integer::operator * (C_Integer x) // �˷�
{
	if (m_status == 0) return *this; // �й�0������
	if (x.m_status == 0) return x;
	C_Integer y;
	if (m_status == x.m_status) y.m_status = INTEGER_POS_VALUE; // �жϽ���ķ���
	else y.m_status = INTEGER_NEG_VALUE;

	int m = m_data.size() + x.m_data.size() - 2, n = 0, L = 0;  // ��C_Integer�ĸ�ʽת��Ϊ�ʺ�FFT����ʽ
	for (n = 1; n <= m; n <<= 1) ++L;
	vector<complex<double> > a, b;
	for (int i = 0; i < m_data.size(); ++i) a.push_back(m_data[i] - (unsigned char)'0');
	for (int i = m_data.size(); i <= n; ++i) a.push_back(0);
	for (int i = 0; i < x.m_data.size(); ++i) b.push_back(x.m_data[i] - (unsigned char)'0');
	for (int i = x.m_data.size(); i <= n; ++i) b.push_back(0);
	fft(a, 1, n, L); fft(b, 1, n, L); // ��ϵ��ת��Ϊ��ֵ
	for (int i = 0; i <= n; i++) a[i] *= b[i];
	fft(a, -1, n, L);                 // ����ֵת��Ϊϵ��
	vector<int> ans;
	for (int i = 0; i <= m; ++i) ans.push_back((int)(a[i].real() + 0.1)); // ת��ΪC_Integer�ĸ�ʽ
	for (int i = 0; i <= m; i++)
		if (ans[i] > 9)
		{
			if (i == m) ++m, ans.push_back(0);
			ans[i + 1] += ans[i] / 10, ans[i] %= 10;
		}
	for (int i = 0; i <= m; ++i) y.m_data.push_back((unsigned char)'0' + ans[i]);

	return y;
}

C_Integer C_Integer::operator / (long long x) // ����
{
	if (m_status == INTEGER_ZERO) return *this; // �жϽ���ķ���
	C_Integer y;
	if (x < 0) 
	{
		if (m_status == INTEGER_NEG_VALUE) y.m_status = INTEGER_POS_VALUE;
		else y.m_status = INTEGER_NEG_VALUE;
	}
	else y.m_status = m_status;
	x = std::abs(x);

	long long tmp = 0;
	vector<int> a;
	for (int i = m_data.size() - 1; ~i; --i) // ��ʽ����
	{
		tmp = tmp * 10 + (m_data[i] - (unsigned char)'0');
		a.push_back(tmp / x); tmp %= x;
	}
	if (a.empty())
	{
		y.m_status = INTEGER_ZERO;
		return y;
	}
	for (int i = a.size() - 1; ~i; --i)      // �����ת��ΪC_Integer�ĸ�ʽ
		y.m_data.push_back(a[i] + (unsigned char)'0');

	while (!y.m_data.empty() && y.m_data[y.m_data.size() - 1] == '0') // ȥ��ǰ��0
		y.m_data.pop_back();
	if (y.m_data.empty()) y.m_status = INTEGER_ZERO; // ���0֮����

	return y;
}

C_Integer C_Integer::operator / (C_Integer x) // �������ĳ���
{
	if (m_status == INTEGER_ZERO) return *this;

	C_Integer l, r, ans(0), mid, one(1), ABS, ABSX;
	int wl = max(0, (int)m_data.size() - (int)x.m_data.size()), wr = max(0, (int)m_data.size() - (int)x.m_data.size() + 1); // �������ķ�Χ[l,r]����֤l<=r<=99*l
	if (!wl) l.m_status = INTEGER_ZERO;
	else
	{
		l.m_status = INTEGER_POS_VALUE;
		for (int i = 0; i < wl - 1; ++i) l.m_data.push_back('0');
		l.m_data.push_back('1');
	}
	if (!wr) r.m_status = INTEGER_ZERO;
	else
	{
		r.m_status = INTEGER_POS_VALUE;
		for (int i = 0; i < wr; ++i) r.m_data.push_back('9');
	}
	ABSX = x.abs(), ABS = abs();

	while (l <= r) // ���ַ�����������
	{
		mid = (l + r) / 2;
		if (ABSX * mid <= ABS) ans = mid, l = mid + one;
		else r = mid - one;
	}

	if (ans.m_status == INTEGER_ZERO) return ans;
	if (m_status != x.m_status) ans.m_status = INTEGER_NEG_VALUE; // �ж���������
	return ans;
}

C_Integer C_Integer::operator % (C_Integer x) // ����
{
	return *this - *this / x * x;
}
