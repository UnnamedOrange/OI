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

const INT maxn = 30005;
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

INT n;
INT a[maxn];

namespace DOC
{
	INT size[maxn];
	bool vis[maxn];
	void DFS(INT node, INT parent)
	{
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
	INT GetRoot(INT node, INT parent, const INT& s)
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

	const INT maxi = 16;
	INT center[maxi][maxn];
	INT belong[maxi][maxn];
	INT dis[maxi][maxn];

	void statistic(INT node, INT parent, const INT& level, const INT& cntCenter, INT cntBelong)
	{
		center[level][node] = cntCenter;
		belong[level][node] = cntBelong;
		wander(G, node)
		{
			DEF(G);
			if (to == parent || vis[to])
				continue;
			dis[level][to] = dis[level][node] + cost;
			statistic(to, node, level, cntCenter, cntBelong ? cntBelong : to);
		}
	}

	void solve(INT node, INT level = 1)
	{
		DFS(node, 0);
		node = GetRoot(node, 0, size[node]);

		statistic(node, 0, level, node, 0);

		vis[node] = true;
		wander(G, node)
		{
			DEF(G);
			if (vis[to])
				continue;
			solve(to, level + 1);
		}
	}
}
using namespace DOC;

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 2; i <= n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT cost = readIn();
		G.addEdge(from, to, cost);
		G.addEdge(to, from, cost);
	}

	solve(1);

	INT t = readIn();
	while (t--)
	{

	}
}

int main()
{
	run();
	return 0;
}