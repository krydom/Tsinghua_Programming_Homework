#include <cstdio>

using namespace std;

const int n = 100;
const int M = 2010;

struct egde
{
	int to, next;
} e[M];

int m, cnt, st;
int head[n + 5], d[n + 5], pvis[n + 5], vis[M], chose[M];

void ins(int x, int y) // 插入一条边 
{
	e[++cnt].to = y; e[cnt].next = head[x]; head[x] = cnt; ++d[x];
}

void init_graphBuild() // 输入以及建图 
{
	scanf("%d", &m);
	int x, y; cnt = 1;
	for(int i = 1; i <= m; ++i)
	{
		scanf("%d%d", &x, &y);
		ins(x, y); ins(y, x);
		st = x; 
	}
}

void chooseOrigin() // 选取欧拉路径的起点 
{
	for(int i = 1; i <= n; ++i)
		if (d[i] & 1) st = i;
}

void dfs(int x) // 判断去掉若干边后的图是否连通，dfs算法 
{
	pvis[x] = 1;
	for(int i = head[x]; i; i = e[i].next)
		if (!vis[i >> 1])
		{
			vis[i >> 1] = 1;
			if (!pvis[e[i].to])
				dfs(e[i].to);
		}
}

bool testConnect(int st) // 判断去掉若干边后的图是否连通 
{
	for(int i = 1; i <= n; ++i) pvis[i] = 0;
	for(int i = 1; i <= m; ++i) vis[i] = chose[i << 1];
	dfs(st);
	for(int i = 1; i <= m; ++i)
		if (!vis[i]) return 0;
	return 1;
}

void eulerSolve(int st) // 递归选择欧拉路径的走法 
{
	for(int i = head[st]; i; i = e[i].next)
		if (!chose[i])
		{
			chose[i] = chose[i ^ 1] = 1;
			if (testConnect(e[i].to))
			{
				printf("%d ", i >> 1);
				eulerSolve(e[i].to);
				return; 
			} 
			else chose[i] = chose[i ^ 1] = 0;
		} 
}

int main()
{
	init_graphBuild();
	chooseOrigin();
	eulerSolve(st);
	return 0;
}
