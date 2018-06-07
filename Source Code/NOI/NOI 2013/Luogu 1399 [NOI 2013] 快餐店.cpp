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
typedef int INT_PUT;
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

const int maxn = int(1e5) + 5;
int n;
struct Graph
{
	struct Edge
	{
		int to;
		int cost;
		int next;
	} edges[maxn * 2];
	int head[maxn];
	int i;
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

#define RunInstance(x) delete new x
struct brute
{
	bool vis[maxn];
	std::vector<int> onRing;
	int tag;

	bool DFS1(int node, int parent)
	{
		vis[node] = true;
		wander(G, node)
		{
			DEF(G);
			if (to == parent) continue;
			if (vis[to])
			{
				tag = to;
				onRing.push_back(idx(G) >> 1);
				return true;
			}
			if (DFS1(to, node) && tag != to)
			{
				onRing.push_back(idx(G) >> 1);
				return true;
			}
		}
		return false;
	}

	LL d;
	LL f[maxn];
	void DFS2(int node, int parent)
	{
		LL major = 0, minor = 0;
		wander(G, node)
		{
			if ((idx(G) >> 1) == tag) continue;
			DEF(G);
			if (to == parent) continue;
			DFS2(to, node);
			f[node] = std::max(f[node], f[to] + cost);
			if (f[to] + cost > minor)
				if (f[to] + cost > major)
				{
					minor = major;
					major = f[to] + cost;
				}
				else
					minor = f[to] + cost;
		}
		d = std::max(d, major + minor);
	}

	brute() : vis()
	{
		DFS1(1, 0);

		LL ans = LLONG_MAX;
		for (int i = 0; i < onRing.size(); i++)
		{
			tag = onRing[i];
			memset(f, 0, sizeof(LL) * (n + 1));
			d = 0;
			DFS2(1, 0);
			ans = std::min(ans, d);
		}
		printf("%.1f", (double)ans / 2);
	}
};
LL f[maxn];
int vs[maxn * 2];
LL cost[maxn * 2];
struct work
{
	bool vis[maxn];
	std::vector<int> onRing;
	std::vector<int> vertex;
	std::vector<int> dis;
	int tag;

	bool DFS1(int node, int parent)
	{
		vis[node] = true;
		wander(G, node)
		{
			DEF(G);
			if (to == parent) continue;
			if (vis[to])
			{
				tag = to;
				onRing.push_back(idx(G) >> 1);
				vertex.push_back(to);
				dis.push_back(cost);
				return true;
			}
			if (DFS1(to, node) && tag != to)
			{
				onRing.push_back(idx(G) >> 1);
				vertex.push_back(to);
				dis.push_back(cost);
				return true;
			}
		}
		return false;
	}

	LL D[maxn];
	void DFS2(int node, int parent)
	{
		LL major = 0, minor = 0;
		D[node] = 0;
		f[node] = 0;
		wander(G, node)
		{
			DEF(G);
			if (vis[to] || to == parent) continue;
			DFS2(to, node);
			f[node] = std::max(f[node], f[to] + cost);
			D[node] = std::max(D[node], D[to]);

			if (f[to] + cost > minor)
				if (f[to] + cost > major)
				{
					minor = major;
					major = f[to] + cost;
				}
				else
					minor = f[to] + cost;
			D[node] = std::max(D[node], major + minor);
		}
	}

	int l;

	struct Comp1
	{
		bool operator()(const int& a, const int& b) const
		{
			return f[vs[a]] + cost[a] > f[vs[b]] + cost[b];
		}
	};
	struct Comp2
	{
		bool operator()(const int& a, const int& b) const
		{
			return f[vs[a]] - cost[a] > f[vs[b]] - cost[b];
		}
	};

	work() : vis()
	{
		DFS1(1, 0);
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < vertex.size(); i++)
			vis[vertex[i]] = true;
		for (int i = 0; i < vertex.size(); i++)
		{
			int v = vertex[i];
			DFS2(v, 0);
		}
		l = vertex.size();
		for (int i = 0; i < l; i++)
		{
			vs[i + 1] = vertex[i];
			cost[i + 2] = dis[i];
		}
		for (int i = l + 1; i <= (l << 1); i++)
		{
			vs[i] = vs[i - l];
			cost[i + 1] = cost[i + 1 - l];
		}

		for (int i = 2; i <= (l << 1) + 1; i++)
			cost[i] += cost[i - 1];
		std::multiset<int, Comp1> set1;
		std::multiset<int, Comp2> set2;

		for (int i = 1; i <= l; i++)
		{
			set1.insert(i);
			set2.insert(i);
		}
		LL ans = LLONG_MAX;
		for (int i = l + 1; i <= (l << 1); i++)
		{
			auto it11 = set1.begin();
			auto it12 = it11; it12++;
			auto it21 = set2.begin();
			auto it22 = it21; it22++;
			if (*it11 != *it21)
				ans = std::min(ans, f[vs[*it11]] + f[vs[*it21]] + cost[*it11] - cost[*it21]);
			else
			{
				ans = std::min(ans,
					std::max(f[vs[*it12]] + f[vs[*it21]] + cost[*it12] - cost[*it21],
						f[vs[*it11]] + f[vs[*it22]] + cost[*it11] - cost[*it22]));
			}

			set1.erase(set1.find(i - l));
			set2.erase(set2.find(i - l));
			set1.insert(i);
			set2.insert(i);
		}

		for (int i = 0; i < vertex.size(); i++)
			ans = std::max(ans, D[vertex[i]]);
		printf("%.1f", (double)ans / 2);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
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