#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 210;
const int M = N * N;

int s, t, n, m, cnt;
int head[N], f[N];

struct Edge{int to, next, v;} e[N];
struct edge{int u, v, w;} a[M];
bool operator < (edge a, edge b) {return a.w > b.w;}
 
void add(int x, int y, int z)
{
	e[++cnt].to = y; e[cnt].next = head[x]; e[cnt].v = z; head[x] = cnt;
	e[++cnt].to = x; e[cnt].next = head[y]; e[cnt].v = z; head[y] = cnt;
}

int find(int x) {return f[x] == x ? x : f[x] = find(f[x]);}

void dfs(int x, int y, int z)
{
	if (x == t) 
	{
		printf("%d\n", z);
		return;
	}
	for(int i = head[x]; i; i = e[i].next)
		if (e[i].to != y) dfs(e[i].to, x, min(z, e[i].v));
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for(int i = 1; i <= m; ++i) scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
	sort(a + 1, a + m + 1);
	for(int i = 1; i <= n; ++i) f[i] = i;
	for(int i = 1; i <= m; ++i)
	{
		int p = find(a[i].u), q = find(a[i].v);
		if (p == q) continue; f[p] = q;
		add(a[i].u, a[i].v, a[i].w);	
	}
	dfs(s, 0, 1 << 30);
	return 0;
} 
