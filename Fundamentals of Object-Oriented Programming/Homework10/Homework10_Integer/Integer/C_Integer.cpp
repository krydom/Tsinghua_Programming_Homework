#include "C_Integer.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <complex>
#include <cmath>

using namespace std;

const double pi = acos(-1);

C_Integer::C_Integer()
{
	m_status = INTEGER_ZERO;
}

C_Integer::C_Integer(long long x)
{
	if (x == 0) m_status = INTEGER_ZERO;
	if (x > 0) m_status = INTEGER_POS_VALUE;
	if (x < 0) m_status = INTEGER_NEG_VALUE;
	x = std::abs(x);
	while (x)
	{
		m_data.push_back((unsigned char)'0' + x % 10);
		x /= 10;
	}
}

void C_Integer::mb_setnum(long long x)
{
	if (x == 0) m_status = INTEGER_ZERO;
	if (x > 0) m_status = INTEGER_POS_VALUE;
	if (x < 0) m_status = INTEGER_NEG_VALUE;
	m_data.clear();
	x = std::abs(x);
	while (x)
	{
		m_data.push_back((unsigned char)'0' + x % 10);
		x /= 10;
	}
}

void C_Integer::mb_show(const char* s)
{
	cout << s;
	if (m_status == INTEGER_NEG_VALUE) cout << "-";
	if (m_status == INTEGER_ZERO) cout << '0';
	else for(int i = m_data.size() - 1; ~i; --i) cout << m_data[i];
	cout << endl;
}

void C_Integer::mb_input(const char* s)
{
	cout << s << endl;
	m_data.clear();

	string S;
	bool fl, outvis = 0;
	int FIRST;

	do
	{
		if (outvis) cout << "输入的不是整数，请重新输入:" << endl;
		getline(cin, S);
		outvis = 1;

		fl = 0;
		FIRST = -1; // FIRST保存第一个非0数字的位置，如果没有则保存第一个0的位置
		for (int i = 0; i < S.length(); ++i)
		{
			if ((S[i] > '9' || S[i] < '0') && S[i] != '+' && S[i] != '-') // 出现数字和+-之外的字符
			{
				fl = 1;
				break;
			}
			if (i && (S[i] == '+' || S[i] == '-')) // +-在第一个位置之外的位置出现
			{
				fl = 1;
				break;
			}
			if (S[i] == '0' && FIRST == -1) FIRST = i;
			if (S[i] >= '1' && S[i] <= '9')
				if (FIRST == -1 || S[FIRST] == '0') FIRST = i;
		}
		if (FIRST == -1) fl = 1; // 没有数字
	} while (fl);

	if (S[0] == '-') m_status = INTEGER_NEG_VALUE;
	else m_status = INTEGER_POS_VALUE;
	if (S[FIRST] == '0') m_status = INTEGER_ZERO;
	if (m_status != INTEGER_ZERO)
	{
		for (int i = S.length() - 1; i >= FIRST; --i)
			m_data.push_back(S[i]);
	}
}

C_Integer C_Integer::abs()
{
	C_Integer x = *this;
	if (x.m_status < 0) x.m_status = INTEGER_POS_VALUE;
	return x;
}

bool C_Integer::operator == (C_Integer x)
{
	if (m_status != x.m_status) return 0;
	if (m_data.size() != x.m_data.size()) return 0;
	for (int i = 0; i < m_data.size(); ++i)
		if (m_data[i] != x.m_data[i]) return 0;
	return 1;
}

bool C_Integer::operator < (C_Integer x) // 小于
{
	if (m_status < x.m_status) return 1;
	if (m_status > x.m_status) return 0;
	if (m_status == INTEGER_ZERO) return 0;
	if (m_status == INTEGER_NEG_VALUE) // 负数绝对值大的小
	{
		if (m_data.size() > x.m_data.size()) return 1;
		if (m_data.size() < x.m_data.size()) return 0;
		for (int i = m_data.size() - 1; ~i; --i)
		{
			if (m_data[i] > x.m_data[i]) return 1;
			if (m_data[i] < x.m_data[i]) return 0;
		}
	}
	else if (m_status == INTEGER_POS_VALUE) // 正数绝对值小的小
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

bool C_Integer::operator > (C_Integer x) // 大于
{
	if (m_status < x.m_status) return 0;
	if (m_status > x.m_status) return 1;
	if (m_status == INTEGER_ZERO) return 0;
	if (m_status == INTEGER_NEG_VALUE) // 负数绝对值大的小
	{
		if (m_data.size() > x.m_data.size()) return 0;
		if (m_data.size() < x.m_data.size()) return 1;
		for (int i = m_data.size() - 1; ~i; --i)
		{
			if (m_data[i] > x.m_data[i]) return 0;
			if (m_data[i] < x.m_data[i]) return 1;
		}
	}
	else if (m_status == INTEGER_POS_VALUE) // 正数绝对值小的小
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

C_Integer C_Integer::operator + (C_Integer x)
{
	if (m_status * x.m_status != INTEGER_NEG_VALUE) // 同号做加法
	{
		C_Integer y;
		if (m_data.size() < x.m_data.size()) // 加法
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
		
		for (int i = 0; i + 1 < y.m_data.size(); ++i) // 进位
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

		if (m_status > 0 || x.m_status > 0) y.m_status = INTEGER_POS_VALUE;
		else if (m_status < 0 || x.m_status < 0) y.m_status = INTEGER_NEG_VALUE;
		else y.m_status = INTEGER_ZERO;

		return y;
	}
	else // 异号做减法
	{
		x.m_status = m_status;
		return *this - x;
	}
}

C_Integer C_Integer::operator - (C_Integer x)
{
	if (x.m_status == INTEGER_ZERO) return *this; // 有关0的特判
	if (m_status == INTEGER_ZERO)
	{
		if (x.m_status == INTEGER_NEG_VALUE) x.m_status = INTEGER_POS_VALUE;
		else if (x.m_status == INTEGER_POS_VALUE) x.m_status = INTEGER_NEG_VALUE;
		return x;
	}

	if (m_status * x.m_status != INTEGER_NEG_VALUE) // 同号做减法
	{
		C_Integer y = *this;
		if (y.abs() < x.abs())
		{
			swap(y.m_data, x.m_data);
			if (y.m_status == INTEGER_NEG_VALUE) y.m_status = INTEGER_POS_VALUE;
			else if (y.m_status == INTEGER_POS_VALUE) y.m_status = INTEGER_NEG_VALUE;
		}
		for (int i = 0; i < x.m_data.size(); ++i) // 减法
			y.m_data[i] -= x.m_data[i] - '0';
		for (int i = 0; i < y.m_data.size(); ++i) // 退位
			if (y.m_data[i] < '0')
			{
				y.m_data[i] += 10;
				y.m_data[i + 1] -= 1;
			}
		while (!y.m_data.empty() && y.m_data[y.m_data.size() - 1] == '0')
			y.m_data.pop_back();

		if (y.m_data.empty()) y.m_status = INTEGER_ZERO; // 变成0之后变号

		return y;
	}
	else // 异号做加法
	{
		x.m_status = m_status;
		return *this + x;
	}
}

void fft(vector<complex<double> > &a, int f, int n, int L)
{
	vector<int> R;
	R.push_back(0);
	for (int i = 1; i < n; i++) R.push_back((R[i >> 1] >> 1) | ((i & 1) << (L - 1)));

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

C_Integer C_Integer::operator * (C_Integer x)
{
	if (m_status == 0) return *this;
	if (x.m_status == 0) return x;
	C_Integer y;
	if (m_status == x.m_status) y.m_status = INTEGER_POS_VALUE;
	else y.m_status = INTEGER_NEG_VALUE;

	int m = m_data.size() + x.m_data.size() - 2, n = 0, L = 0;
	for (n = 1; n <= m; n <<= 1) ++L;
	vector<complex<double> > a, b;
	for (int i = 0; i < m_data.size(); ++i) a.push_back(m_data[i] - (unsigned char)'0');
	for (int i = m_data.size(); i <= n; ++i) a.push_back(0);
	for (int i = 0; i < x.m_data.size(); ++i) b.push_back(x.m_data[i] - (unsigned char)'0');
	for (int i = x.m_data.size(); i <= n; ++i) b.push_back(0);
	fft(a, 1, n, L); fft(b, 1, n, L);
	for (int i = 0; i <= n; i++) a[i] *= b[i];
	fft(a, -1, n, L);
	vector<int> ans;
	for (int i = 0; i <= m; ++i) ans.push_back((int)(a[i].real() + 0.1));
	for (int i = 0; i <= m; i++)
		if (ans[i] > 9)
		{
			if (i == m) ++m, ans.push_back(0);
			ans[i + 1] += ans[i] / 10, ans[i] %= 10;
		}
	for (int i = 0; i <= m; ++i) y.m_data.push_back((unsigned char)'0' + ans[i]);

	return y;
}

C_Integer C_Integer::operator / (long long x)
{
	if (m_status == INTEGER_ZERO) return *this;
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
	for (int i = m_data.size() - 1; ~i; --i)
	{
		tmp = tmp * 10 + (m_data[i] - (unsigned char)'0');
		a.push_back(tmp / x); tmp %= x;
	}
	if (a.empty())
	{
		y.m_status = INTEGER_ZERO;
		return y;
	}
	for (int i = a.size() - 1; ~i; --i)
		y.m_data.push_back(a[i] + (unsigned char)'0');

	while (!y.m_data.empty() && y.m_data[y.m_data.size() - 1] == '0')
		y.m_data.pop_back();
	if (y.m_data.empty()) y.m_status = INTEGER_ZERO; // 变成0之后变号

	return y;
}

C_Integer C_Integer::operator / (C_Integer x)
{
	if (m_status == INTEGER_ZERO) return *this;

	C_Integer l, r, ans(0), mid, one(1), ABS, ABSX;
	int wl = max(0, (int)m_data.size() - (int)x.m_data.size()), wr = max(0, (int)m_data.size() - (int)x.m_data.size() + 1);
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

	while (l <= r)
	{
		mid = (l + r) / 2;
		if (ABSX * mid <= ABS) ans = mid, l = mid + one;
		else r = mid - one;
	}

	if (ans.m_status == INTEGER_ZERO) return ans;
	if (m_status != x.m_status) ans.m_status = INTEGER_NEG_VALUE;
	return ans;
}