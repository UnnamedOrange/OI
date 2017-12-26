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

const INT maxn = 100005;
INT n, m;
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
bool isBlack[maxn];

namespace DissectionOfVertex
{
	bool vis[maxn];
	INT size[maxn];
	void DFS(INT node, INT parent)
	{
		size[node] = 1;
		wander(G, node)
		{
			DEF(G);
			if (vis[to] || to == parent)
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
			if (vis[to] || to == parent)
				continue;
			if (size[to] > s / 2)
				return GetRoot(to, node, s);
		}
		return node;
	}

	const INT maxi = 18;
	INT center[maxi][maxn];
	INT belong[maxi][maxn];
	INT dis[maxi][maxn];
	INT ans[maxn];
	INT exclude[maxi][maxn];
	INT num[maxn];
	INT excludeNum[maxi][maxn];
	void statistic(INT node, INT parent, const INT& level, const INT& cntCenter, const INT& cntBelong)
	{
		center[level][node] = cntCenter;
		belong[level][node] = cntBelong;
		wander(G, node)
		{
			DEF(G);
			if (vis[to] || to == parent)
				continue;
			dis[level][to] = dis[level][node] + cost;
			statistic(to, node, level, cntCenter, cntBelong ? cntBelong : to);
		}
	}

	void solve(INT node, const INT& level = 1)
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

	void modify(INT node, INT level)
	{
		num[center[level][node]]++;
		if (center[level][node] == node)
			return;
		ans[center[level][node]] += dis[level][node];
		exclude[level][belong[level][node]] += dis[level][node];
		excludeNum[level][belong[level][node]]++;
		modify(node, level + 1);
	}
	INT query(INT node, INT level)
	{
		if (center[level][node] == node)
			return ans[node];
		return ans[center[level][node]] - exclude[level][belong[level][node]] +
			dis[level][node] * (num[center[level][node]] - excludeNum[level][belong[level][node]]) +
			query(node, level + 1);
	}
}
using namespace DissectionOfVertex;

void run()
{
	n = readIn();
	m = readIn();
	std::vector<INT> from(n + 1), cost(n + 1);
	for (int i = 2; i <= n; i++)
		from[i] = readIn() + 1;
	for (int i = 2; i <= n; i++)
		cost[i] = readIn();
	for (int i = 2; i <= n; i++)
	{
		G.addEdge(from[i], i, cost[i]);
		G.addEdge(i, from[i], cost[i]);
	}

	solve(1);

	while (m--)
	{
		INT ins = readIn();
		INT x = readIn() + 1;
		if (ins == 1)
		{
			if (!isBlack[x])
			{
				isBlack[x] = true;
				modify(x, 1);
			}
		}
		else if (ins == 2)
		{
			printOut(query(x, 1));
		}
	}
}

int main()
{
	run();
	return 0;
}