#include<bits/stdc++.h>
#define inf 1e9
#define L long long
using namespace std;
const int MaxV = 510, MaxE = 20010;
namespace dinic {
	struct edge {
		int to, nxt, cap;
	}e[MaxE]; int cnt = 1, lst[MaxV];
	void ins(int a, int b, int c) { e[++cnt] = (edge) { b, lst[a], c }; lst[a] = cnt; }
	void lnk(int a, int b, int c) { ins(a, b, c); ins(b, a, 0); }
	int h[MaxV]; queue<int>q;
	bool bfs(int s, int t) {
		memset(h, -1, sizeof(h));
		h[s] = 0; q.push(s);
		while (!q.empty()) {
			int c = q.front(); q.pop();
			for (int i = lst[c], b; b = e[i].to, i; i = e[i].nxt) {
				if (!~h[b] && e[i].cap > 0) {
					h[b] = h[c] + 1;
					q.push(b);
				}
			}
		}
		return ~h[t];
	}
	int dfs(int v, int t, int f) {
		if (v == t) return f;
		int used = 0, w;
		for (int i = lst[v], b; b = e[i].to, i; i = e[i].nxt)
			if (h[b] > h[v] && e[i].cap > 0) {
				w = dfs(b, t, min(f - used, e[i].cap));
				e[i].cap -= w; e[i ^ 1].cap += w;
				if ((used += w) == f) return f;
			}
		if (!used) h[v] = -1;
		return used;
	}
	int max_flow(int s, int t) {
		int ans = 0;
		while (bfs(s, t))
		{
			int k = dfs(s, t, 1e9);
			if (k > 1e8)
				return -1;
			ans += k;
		}
		return ans;
	}
	void clear()
	{
		memset(lst, 0, sizeof(lst)), cnt = 1;
	}
}
using dinic::lnk;
using dinic::max_flow;
using dinic::clear;
int t, n, m, p, q, x, y, z, a, b, c, d, e, f, u[510], ans;
int main()
{
	//freopen("variable.in","r",stdin);
	freopen("variable.out", "w", stdout);
	int i;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d%d%d", &n, &m, &p, &q);
		for (i = 1; i <= n; i++)
			u[i] = 1;
		for (i = 1; i <= p; i++)
		{
			scanf("%d%d%d%d%d%d%d%d%d", &x, &y, &z, &a, &b, &c, &d, &e, &f);
			lnk(x, y, 2 * a);
			lnk(y, x, 2 * a);
			lnk(y, z, 2 * b);
			lnk(z, y, 2 * b);
			lnk(z, x, 2 * c);
			lnk(x, z, 2 * c);
			u[x] += d - f;
			u[y] += e - d;
			u[z] += f - e;
		}
		for (i = 1; i <= q; i++)
		{
			scanf("%d%d%d", &x, &y, &z);
			if (z == 1)
			{
				lnk(x, y, inf);
				lnk(y, x, inf);
			}
			else if (z == 2)
			{
				lnk(x, n + 1, inf);
				lnk(0, y, inf);
			}
			else
				lnk(x, y, inf);
		}
		for (i = 1; i <= n; i++)
		{
			ans -= abs(u[i]);
			if (u[i] > 0)
				lnk(i, n + 1, 2 * u[i]);
			else if (u[i] < 0)
				lnk(0, i, -2 * u[i]);
		}
		ans += max_flow(0, n + 1);
		printf("%lld\n", (L)ans*m);
		ans = 0;
		clear();
	}
	return 0;
}