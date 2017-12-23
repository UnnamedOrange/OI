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
typedef long long INT;
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

const INT maxn = 10005;
INT n, len;
struct Graph
{
	INT i;
	struct Edge
	{
		INT to;
		INT cost;
		INT next;
	} edges[maxn * 2];
	INT head[maxn];
	Graph() : i(), head() {}

	void addEdge(INT from, INT to, INT cost)
	{
		i++;
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i;
	}

#define wander(G, node) for(int i = G.head[node]; i; i = G.edges[i].next)
#define DEF(G) const Graph::Edge& e = G.edges[i]; INT to = e.to; INT cost = e.cost
} G;

INT ans;
INT vis[maxn];
INT size[maxn];
INT dis[maxn];
INT buf[maxn];
void DFS(INT node, INT parent)
{
	buf[++buf[0]] = node;
	size[node] = 1;
	wander(G, node)
	{
		DEF(G);
		if (to == parent || vis[to])
			continue;
		DFS(to, node);
		size[node] += size[to];
	}
}
void GetDis(INT node, INT parent)
{
	wander(G, node)
	{
		DEF(G);
		if (to == parent || vis[to])
			continue;
		dis[to] = dis[node] + cost;
		GetDis(to, node);
	}
}
INT GetRoot(INT node, INT parent, INT s)
{
	wander(G, node)
	{
		DEF(G);
		if (to == parent || vis[to])
			continue;
		if (size[to] > s / 2)
			return GetRoot(to, node, s);
	}
	return node;
}
void solve(INT node)
{
	buf[0] = 0;
	DFS(node, 0);
	if (ans)
	{
		std::sort(buf + 1, buf + 1 + buf[0], [](const INT& x, const INT& y) { return dis[x] < dis[y]; });
		INT j = 0;
		for (int i = buf[0]; i >= 1; i--)
		{
			while (j < i - 1 && dis[buf[i]] + dis[buf[j + 1]] <= len)
				j++;
			if (i == j)
				j--;
			ans -= j;
		}
	}

	node = GetRoot(node, 0, size[node]);
	vis[node] = true;
	dis[node] = 0;
	GetDis(node, 0);

	INT j = 0;
	std::sort(buf + 1, buf + 1 + buf[0], [](const INT& x, const INT& y) { return dis[x] < dis[y]; });
	for (int i = buf[0]; i >= 1; i--)
	{
		while (j < i - 1 && dis[buf[i]] + dis[buf[j + 1]] <= len)
			j++;
		if (i == j)
			j--;
		ans += j;
	}

	wander(G, node)
	{
		DEF(G);
		if (vis[to])
			continue;
		solve(to);
	}
}

void run()
{
	n = readIn();
	len = readIn();
	for (int i = 2; i <= n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT cost = readIn();
		G.addEdge(from, to, cost);
		G.addEdge(to, from, cost);
	}

	solve(1);
	printOut(ans);
}

int main()
{
	run();
	return 0;
}