#include <cstdio>
#include <bitset>

using namespace std;

int n, m, t, x;
bitset<101> a[15], now, tmp;
int f[1 << 15], v[1 << 15];

inline int dfs(int x)
{
	if (f[x] != n + 1) return f[x];
	for(int i = x; i; i = (i - 1) & x)
		if (v[i]) f[x] = min(f[x], dfs(i ^ x) + 1);
	return f[x];	
}

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", &t);
		while (t--)
		{
			scanf("%d", &x);
			a[i][x] = 1;
		}
	}
	for(int i = 0; i < (1 << n); ++i)
	{
		f[i] = n + 1;
		now = 0; 
		bool fl = 1;
		for(int j = 0; j < n; ++j)
			if (i & (1 << j))
			{
				tmp = now & a[j];
				if (tmp.count())
				{
					fl = 0;
					break;
				}
				now |= a[j];
			}
		if (fl) v[i] = 1;
	}
	f[0] = 0;
	printf("%d\n", dfs((1 << n) - 1));
	return 0;
} 
