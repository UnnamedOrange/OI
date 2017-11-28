#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = INT(2e5) + 5;
const INT maxm = INT(1e6) + 5;
INT n, m;
INT count1, count2;
struct Edge
{
	INT to;
	INT next;
} edges[maxm * 2], es[maxn * 2];
INT head[maxn], h[maxn];
void addEdge1(INT from, INT to)
{
	edges[count1].to = to;
	edges[count1].next = head[from];
	head[from] = count1;
	count1++;
}
void addEdge2(INT from, INT to)
{
	es[count2].to = to;
	es[count2].next = h[from];
	h[from] = count2;
	count2++;
}
INT scc;
INT belong[maxn];

#define RunInstance(x) delete new x
struct DFS_Twice
{
	INT clock;
	INT dfn[maxn];
	INT low[maxn];
	bool isBridge[maxm * 2];
	void dfs1(INT node, INT parent)
	{
		clock++;
		dfn[node] = low[node] = clock;
		for (int i = head[node]; ~i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if ((i ^ 1) == parent) continue;
			if (!dfn[to])
			{
				dfs1(to, i);
				low[node] = std::min(low[node], low[to]);
				if (low[to] > dfn[node])
				{
					isBridge[i] = isBridge[i ^ 1] = true;
				}
			}
			else
			{
				low[node] = std::min(low[node], dfn[to]);
			}
		}
	}
	void dfs2(INT node, INT parent)
	{
		belong[node] = scc;
		for (int i = head[node]; ~i; i = edges[i].next)
		{
			if (isBridge[i]) continue;
			INT to = edges[i].to;
			if (to == parent) continue;
			if (!belong[to]) dfs2(to, node);
		}
	}

	DFS_Twice() : clock(), dfn(), isBridge()
	{
		dfs1(1, -1);
		for (int i = 1; i <= n; i++)
		{
			if (!belong[i])
			{
				scc++;
				dfs2(i, 0);
			}
		}
	}
};
struct DFS_Tarjan
{
	INT clock;
	INT dfn[maxn];
	INT low[maxn];
	bool inStack[maxn];
	INT s[maxn];
	void dfs(INT node, INT parent)
	{
		clock++;
		dfn[node] = low[node] = clock;
		s[++s[0]] = node;
		inStack[node] = true;
		for (int i = head[node]; ~i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (i == (parent ^ 1)) continue;
			if (!dfn[to])
			{
				dfs(to, i);
				low[node] = std::min(low[node], low[to]);
			}
			else if (inStack[to])
			{
				low[node] = std::min(low[node], dfn[to]);
			}
		}

		if (dfn[node] == low[node])
		{
			scc++;
			INT top;
			do
			{
				top = s[s[0]--];
				inStack[top] = false;
				belong[top] = scc;
			} while (top != node);
		}
	}

	DFS_Tarjan() : clock(), dfn(), inStack()
	{
		dfs(1, -1);
	}
};

void clear()
{
	memset(head, -1, sizeof(head));
	memset(h, -1, sizeof(h));
	memset(belong, 0, sizeof(belong));
	scc = 0;
	count1 = 0;
	count2 = 0;
}
INT ans;
INT dis[maxn];
bool vis[maxn];
void dfs(INT node, INT parent)
{
	dis[node] = 1;
	vis[node] = true;
	INT major = 0;
	INT minor = 0;
	for (int i = h[node]; ~i; i = es[i].next)
	{
		INT to = es[i].to;
		if (to == parent) continue;
		if (vis[to]) continue;
		dfs(to, node);
		dis[node] = std::max(dis[node], dis[to] + 1);
		if (dis[to] > minor)
		{
			if (dis[to] > major)
			{
				minor = major;
				major = dis[to];
			}
			else
				minor = dis[to];
		}
	}
	ans = std::max(ans, major + minor + 1);
}
void run()
{
	INT T = 0;
	while ((n = readIn()) && (m = readIn()))
	{
		clear();
		for (int i = 1; i <= m; i++)
		{
			INT u = readIn();
			INT v = readIn();
			if (u == v) continue;
			addEdge1(u, v);
			addEdge1(v, u);
		}

		//T = !T;
		if (!T) RunInstance(DFS_Twice);
		else RunInstance(DFS_Tarjan);

		for (int i = 1; i <= n; i++)
			for (int j = head[i]; ~j; j = edges[j].next)
			{
				INT to = edges[j].to;
				if (belong[i] != belong[to])
					addEdge2(belong[i], belong[to]);
			}

		ans = 0;
		memset(vis, 0, sizeof(vis));
		dfs(1, 0);
		printOut(scc - ans);
	}
}

int main()
{
#ifndef LOCAL
	freopen("rebuild.in", "r", stdin);
	freopen("rebuild.out", "w", stdout);
#endif
	run();
	return 0;
}
