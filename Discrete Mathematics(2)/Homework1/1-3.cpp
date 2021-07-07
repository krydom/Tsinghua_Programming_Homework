#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 200;

vector<int> pre[N], nxt[N];

int n, Mx, tot, x;
int ans[N], postPone[N], c[N], d[N], work[N];

void init_graphBuild()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d%d", &c[i], &d[i]);
		if (!d[i]) work[++tot] = i;
		for(int j = 1; j <= d[i]; ++j)
		{
			scanf("%d", &x);
			nxt[x].push_back(i);
			pre[i].push_back(x);
		}	
	}	
}

void solve()
{
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < nxt[work[i]].size(); ++j)
		{
			ans[nxt[work[i]][j]] = max(ans[nxt[work[i]][j]], ans[work[i]] + c[work[i]]);
			if (!(--d[nxt[work[i]][j]])) work[++tot] = nxt[work[i]][j];
		}
	for(int i = 1; i <= n; ++i) 
		ans[i] += c[i];
}

void testPostpone()
{
	for(int i = 1; i <= n; ++i) 
		Mx = max(Mx, ans[i]);
	tot = 0;
	for(int i = 1; i <= n; ++i)
		if (ans[i] == Mx) work[++tot] = i, postPone[i] = 1;
	for(int i = 1; i <= tot; ++i)
		for(int j = 0; j < pre[work[i]].size(); ++j)
			if (ans[work[i]] - c[work[i]] == ans[pre[work[i]][j]] && !postPone[pre[work[i]][j]]) 
			{
				work[++tot] = pre[work[i]][j];
				postPone[pre[work[i]][j]] = 1;
			}
}

int main()
{
	init_graphBuild();
	solve();
	testPostpone();
	for(int i = 1; i <= n; ++i)
		printf("%d %d\n", ans[i], postPone[i]);
	return 0;
}
