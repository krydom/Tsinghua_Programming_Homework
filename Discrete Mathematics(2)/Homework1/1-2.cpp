#include <cstdio>
#include<algorithm>
#define pa pair<double, int>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;
using namespace __gnu_pbds;

const int N = 200;
const int M = 10000;
const int inf = 1e9;

typedef __gnu_pbds::priority_queue<pa, greater<pa>, pairing_heap_tag > heap;
heap::point_iterator id[N];
heap h;

struct edge
{
	int to, next;
	double v;
} e[M];

double ans;
int n, m, cnt, U1, U2, U3, D1, D2, D3;

double d[N];
int u[M], v[M], X[N], Y[N], head[N];

void ins(int x, int y, double D)
{
	e[++cnt].to = y; e[cnt].v = D; e[cnt].next = head[x]; head[x] = cnt;
	e[++cnt].to = x; e[cnt].v = D; e[cnt].next = head[y]; head[y] = cnt; 
}
 
double Distance(int a, int b)
{
	return sqrt((X[a] - X[b]) * (X[a] - X[b]) + (Y[a] - Y[b]) * (Y[a] - Y[b]));
}

void init_graphBuild()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)	scanf("%d%d", &X[i], &Y[i]);
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i)
	{
		scanf("%d%d", &u[i], &v[i]);
		ins(u[i], v[i], Distance(u[i], v[i]));
	}
	scanf("%d%d%d%d%d%d", &U1, &D1, &U2, &D2, &U3, &D3);
}

void dijkstra(int u1, int d1, int u2, int d2)
{
	for(int i = 1; i <= n; ++i) d[i] = inf, id[i] = 0;
	d[u[u1]] = d1, d[v[u1]] = Distance(u[u1], v[u1]) - d1;
	id[u[u1]] = h.push(make_pair(d[u[u1]], u[u1]));
	id[v[u1]] = h.push(make_pair(d[v[u1]], v[u1]));
		
	while (!h.empty())
    {
        int now = h.top().second; h.pop();
        for(int i = head[now]; i; i = e[i].next)
            if (d[e[i].to] > d[now] + e[i].v)
            {
                d[e[i].to] = d[now] + e[i].v;
                if (id[e[i].to] != 0)
                    h.modify(id[e[i].to], make_pair(d[e[i].to], e[i].to)); else
					id[e[i].to] = h.push(make_pair(d[e[i].to], e[i].to));
            }
    }
    
    ans += min(d[u[u2]] + d2, d[v[u2]] + Distance(u[u2], v[u2]) - d2);
}

int main()
{
	init_graphBuild();
	dijkstra(U1, D1, U2, D2);
	dijkstra(U2, D2, U3, D3);
	printf("%.2lf\n", ans);
	return 0;
} 
