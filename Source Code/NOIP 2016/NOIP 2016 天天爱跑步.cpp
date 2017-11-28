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
	char buffer[15];
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
}

const INT maxn = 300005;
INT n, m;
struct Edge
{
	INT to;
	INT next;
} edges[maxn * 2];
INT head[maxn];
void addEdge(INT from, INT to)
{
	static INT i;
	i++;
	edges[i].to = to;
	edges[i].next = head[from];
	head[from] = i;
}
INT w[maxn];

INT size;
INT depth[maxn];
INT next[20][maxn];
void dfs(INT node)
{
	depth[node] = depth[next[0][node]] + 1;
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		if (to == next[0][node]) continue;
		next[0][to] = node;
		dfs(to);
	}
}
void goDouble()
{
	while (1 << size < n) size++;
	for (int i = 1; i <= size; i++)
		for (int j = 1; j <= n; j++)
			next[i][j] = next[i - 1][next[i - 1][j]];
}
INT LCA(INT u, INT v)
{
	if (depth[u] < depth[v]) std::swap(u, v);
	for (int i = size; ~i; i--)
	{
		if (depth[next[i][u]] < depth[v]) continue;
		u = next[i][u];
	}
	if (u != v)
	{
		for (int i = size; ~i; i--)
		{
			if (next[i][u] == next[i][v]) continue;
			u = next[i][u];
			v = next[i][v];
		}
		u = next[0][u];
	}
	return u;
}
struct Men
{
	INT u;
	INT v;
	INT t;
	INT lca;

	void read()
	{
		u = readIn();
		v = readIn();
		lca = LCA(u, v);
		t = depth[u] + depth[v] - (depth[lca] << 1);
	}
} men[maxn];

INT ans[maxn];
std::vector<INT> atlcaup[maxn];
std::vector<INT> atlcadown[maxn];
std::vector<INT> atv[maxn];
INT countu[maxn];
INT countv[maxn];
INT buf[maxn * 2];

void dfs1(INT node)
{
	INT k = depth[node] + w[node];
	INT pre = buf[k];
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		if (to == next[0][node]) continue;
		dfs1(to);
	}
	buf[depth[node]] += countu[node];
	for (int i = 0; i < atlcaup[node].size(); i++)
		buf[atlcaup[node][i]]--;
	ans[node] += buf[k] - pre;
}
void dfs2(INT node)
{
	INT k = depth[node] - w[node] + n;
	INT pre = buf[k];
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		if (to == next[0][node]) continue;
		dfs2(to);
	}
	for (int i = 0; i < atv[node].size(); i++)
		buf[atv[node][i] + n]++;
	for (int i = 0; i < atlcadown[node].size(); i++)
		buf[atlcadown[node][i] + n]--;
	ans[node] += buf[k] - pre;
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i < n; i++)
	{
		INT u = readIn();
		INT v = readIn();
		addEdge(u, v);
		addEdge(v, u);
	}
	for (int i = 1; i <= n; i++) w[i] = readIn();
	dfs(1);
	goDouble();

	for (int i = 1; i <= m; i++)
	{
		men[i].read();
		atlcaup[men[i].lca].push_back(depth[men[i].u]);
		atlcadown[men[i].lca].push_back(depth[men[i].v] - men[i].t);
		atv[men[i].v].push_back(depth[men[i].v] - men[i].t);
		countu[men[i].u]++;
		if (depth[men[i].u] - depth[men[i].lca] == w[men[i].lca]) ans[men[i].lca]++;
	}
	dfs1(1);
	dfs2(1);
	for (int i = 1; i <= n; i++)
	{
		static bool print;
		if (print) putchar(' ');
		printOut(ans[i]);
		print = true;
	}
}

int main()
{
	run();
	return 0;
}
