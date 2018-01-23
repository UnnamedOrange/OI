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
#include <list>
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
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
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = 50005;
INT n, q;
INT color[maxn];
struct Graph
{
	struct Edge
	{
		INT to, next;
	} edges[maxn * 2];
	INT i;
	INT head[maxn];
	void addEdge(INT from, INT to)
	{
		edges[i].to = to;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
#define wander(G, node) for(int i = G.head[node]; ~i; i = G.edges[i].next)
#define DEF(G) const Graph::Edge& e = G.edges[i]; INT to = e.to
} G;
INT root;
struct Query
{
	INT u, v;
	INT A, B;
	INT ans;

	INT lca;
	INT l, r;
	void read()
	{
		u = readIn();
		v = readIn();
		A = readIn();
		B = readIn();
	}
} querys[100005];

INT maxk;
INT parent[17][maxn];
INT depth[maxn];
INT seq[maxn * 2];
INT dfn[maxn];
INT end[maxn];
void DFS(INT node)
{
	depth[node] = depth[parent[0][node]] + 1;
	static INT clock;
	clock++;
	seq[clock] = node;
	dfn[node] = clock;
	wander(G, node)
	{
		DEF(G);
		if (to == parent[0][node]) continue;
		parent[0][node] = to;
		DFS(to);
	}
	clock++;
	seq[clock] = node;
	end[node] = clock;
}
void GoDouble()
{
	while (1 << maxk < n) maxk++;
	for (int i = 1; i <= maxk; i++)
		for (int j = 1; j <= n; j++)
			parent[i][j] = parent[i - 1][parent[i - 1][j]];
}
INT LCA(INT u, INT v)
{
	if (depth[u] < depth[v])
		std::swap(u, v);
	for (int i = maxk; ~i; i--)
	{
		if (depth[parent[i][u]] < depth[v])
			continue;
		u = parent[i][u];
	}
	if (u != v)
	{
		for (int i = maxk; ~i; i--)
		{
			if (parent[i][u] == parent[i][v])
				continue;
			u = parent[i][u];
			v = parent[i][v];
		}
		u = parent[0][u];
	}
	return u;
}

void run()
{
	n = readIn();
	q = readIn();
	for (int i = 1; i <= n; i++)
		color[i] = readIn();
	for (int i = 1; i <= n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		if (!from || !to)
		{
			root = std::max(from, to);
			continue;
		}
		G.addEdge(from, to);
		G.addEdge(to, from);
	}
	for (int i = 1; i <= q; i++)
		querys[i].read();
	DFS(root);

	GoDouble();
	for (int i = 1; i <= q; i++)
	{
		Query& Q = querys[i];
		Q.lca = LCA(Q.l, Q.r);
		if (dfn[Q.u] > dfn[Q.v])
			std::swap(dfn[Q.u], dfn[Q.v]);
	}
}

int main()
{
	run();
	return 0;
}