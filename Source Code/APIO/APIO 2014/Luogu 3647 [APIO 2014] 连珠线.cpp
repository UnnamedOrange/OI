#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <functional>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef LL INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const LL INF = (~(int(1) << (sizeof(int) * 8 - 1)));
const int maxn = int(2e5) + 5;
struct Graph
{
	struct Edge
	{
		int to;
		int cost;
		int next;
	} edges[maxn * 2];
	int i;
	int head[maxn];
	Graph() : i() { memset(head, -1, sizeof(head)); }
	void addEdge(int from, int to, int cost)
	{
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
#define idx(G) idx_##G
#define wander(G, node) for (int idx(G) = G.head[node]; ~idx(G); idx(G) = G.edges[idx(G)].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx(G)]; int to = e.to; int cost = e.cost
} G;
int n;

#define RunInstance(x) delete new x
struct brute
{
	LL f[2][maxn];
	void DFS(int node, int parent)
	{
		f[0][node] = 0;
		f[1][node] = -INF;
		bool bOk = false;
		wander(G, node)
		{
			DEF(G);
			if (to == parent) continue;
			DFS(to, node);
			f[0][node] += std::max(f[0][to], f[1][to] + cost);
			bOk = true;
		}
		if (bOk)
		{
			wander(G, node)
			{
				DEF(G);
				if (to == parent) continue;
				f[1][node] = std::max(f[1][node],
					f[0][node] - std::max(f[0][to], f[1][to] + cost) +
					f[0][to] + cost);
			}
		}
	}

	brute()
	{
		LL ans = 0;
		for (int i = 1; i <= n; i++)
		{
			DFS(i, 0);
			ans = std::max(ans, f[0][i]);
		}
		printOut(ans);
	}
};
struct work
{
	LL f[2][maxn];
	LL g[2][maxn];
	void DFS1(int node, int parent)
	{
		f[0][node] = 0;
		f[1][node] = -INF;
		bool bOk = false;
		wander(G, node)
		{
			DEF(G);
			if (to == parent) continue;
			DFS1(to, node);
			f[0][node] += std::max(f[0][to], f[1][to] + cost);
			bOk = true;
		}
		if (bOk)
		{
			wander(G, node)
			{
				DEF(G);
				if (to == parent) continue;
				f[1][node] = std::max(f[1][node],
					f[0][node] - std::max(f[0][to], f[1][to] + cost) +
					f[0][to] + cost);
			}
		}
	}
	LL F[2][maxn];
	void DFS2(int node, int parent, int pc)
	{
		LL major = -INF, minor = -INF;
		int majorIdx = 0, minorIdx = 0;
		if (parent)
		{
			g[0][node] = f[0][node] + std::max(F[0][node], F[1][node] + pc);
			g[1][node] = std::max(
				f[1][node] + std::max(F[0][node], F[1][node] + pc),
				f[0][node] + F[0][node] + pc);
			majorIdx = parent;
			major = F[0][node] + pc - std::max(F[0][node], F[1][node] + pc);
		}
		wander(G, node)
		{
			DEF(G);
			if (to == parent) continue;

			F[0][to] = g[0][node] - std::max(f[0][to], f[1][to] + cost);
			LL t = f[0][to] + cost - std::max(f[0][to], f[1][to] + cost);
			if (t > minor)
			{
				if (t > major)
				{
					minor = major;
					minorIdx = majorIdx;
					major = t;
					majorIdx = to;
				}
				else
				{
					minor = t;
					minorIdx = to;
				}
			}
		}
		wander(G, node)
		{
			DEF(G);
			if (to == parent) continue;

			F[1][to] = majorIdx == to ? F[0][to] + minor : F[0][to] + major;
			DFS2(to, node, cost);
		}
	}

	work()
	{
		DFS1(1, 0);
		g[0][1] = f[0][1];
		g[1][1] = f[1][1];
		DFS2(1, 0, 0);
		LL ans = 0;
		for (int i = 1; i <= n; i++)
			ans = std::max(ans, g[0][i]);
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i < n; i++)
	{
		int from = readIn();
		int to = readIn();
		int cost = readIn();
		G.addEdge(from, to, cost);
		G.addEdge(to, from, cost);
	}

	RunInstance(work);
}

int main()
{
	run();
	return 0;
}