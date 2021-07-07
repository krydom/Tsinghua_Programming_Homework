#include <cstdio>
#include <algorithm>
#define FOR(i, l, r) for(int i = l; i <= r; ++i)

using namespace std;

const int inf = 1 << 30;
const int N = 101;
const int M = N * N;

struct edge{int to, next, v;} e[M];
int n, m, s, t, x, y, z, cnt, sum;
int head[N], d[N], h[N], f[N];
 
void ins(int x, int y, int z)
{
    e[++cnt].to = y; e[cnt].next = head[x]; e[cnt].v = z; head[x] = cnt;
    e[++cnt].to = x; e[cnt].next = head[y]; e[cnt].v = z; head[y] = cnt;
}

bool bfs()
{
    FOR(i, 1, n) d[i] = inf;
    int l = 0, r = 1; h[1] = s; d[s] = 0;
    while (l < r)
    {
        for(int i = head[h[++l]]; i; i = e[i].next)
            if (e[i].v && d[e[i].to] > d[h[l]] + 1)
            {
                d[e[i].to] = d[h[l]] + 1;
                h[++r] = e[i].to;
            }
    }
    return d[t] != inf;
}
    
int dfs(int x,int flow)
{
    if (x == t) return flow;
	int tt = 0, i = f[x];
    for(; i && tt < flow; i = e[i].next)
        if (e[i].v && d[e[i].to] == d[x] + 1)
        {
            int tmp = dfs(e[i].to, min(flow - tt, e[i].v));
            tt += tmp; e[i].v -= tmp; e[i ^ 1].v += tmp;
            if (e[i].v) f[x] = i;
        }
    if (!tt) d[x] = -1; 
	return tt;
} 

int main()
{
	cnt = 1;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	FOR(i, 1, m)
	{
		scanf("%d%d%d", &x, &y, &z);
		ins(x, y, z);
	}
	while (bfs())
	{
		FOR(i, 1, n) f[i] = head[i];
		sum += dfs(s, inf);
	}
    printf("%d\n", sum);
	return 0;
}
