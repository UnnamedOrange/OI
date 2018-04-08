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
	putchar('\n');
}

const int INF = (~(int(1) << (sizeof(int) * 8 - 1))) >> 1;
const int maxn = 155;
int n, m;

struct Networkflow
{
	struct Edge
	{
		int from, to, cap, flow;
		Edge() {}
		Edge(int from, int to, int cap) : from(from), to(to), cap(cap), flow() {}
	};
	std::vector<Edge> edges;
	std::vector<std::vector<int> > G;
	int s, t;
	void addEdge(int from, int to, int cap)
	{
		edges.push_back(Edge(from, to, cap));
		edges.push_back(Edge(to, from, 0));
		int i = edges.size();
		G[from].push_back(i - 2);
		G[to].push_back(i - 1);
	}

	std::vector<int> cur;
	std::vector<int> level;
	int DFS(int node, int opt)
	{
		if (node == t || !opt) return opt;
		int flow = 0;
		for (int& i = cur[node]; i < G[node].size(); i++)
		{
			Edge& e = edges[G[node][i]];
			int t;
			if (level[node] + 1 == level[e.to] && (t = DFS(e.to, std::min(opt, e.cap - e.flow))))
			{
				flow += t;
				opt -= t;
				e.flow += t;
				edges[G[node][i] ^ 1].flow -= t;
				if (!opt) break;
			}
		}
		return flow;
	}

	std::vector<int> vis;
	int stamp;
	bool BFS()
	{
		stamp++;
		std::queue<int> q;
		q.push(s);
		vis[s] = stamp;
		level[s] = 0;
		while (!q.empty())
		{
			int from = q.front();
			q.pop();
			for (int i = 0; i < G[from].size(); i++)
			{
				const Edge& e = edges[G[from][i]];
				if (e.flow < e.cap && vis[e.to] != stamp)
				{
					vis[e.to] = stamp;
					level[e.to] = level[from] + 1;
					q.push(e.to);
				}
			}
		}
		return vis[t] == stamp;
	}

	int Dinic()
	{
		int flow = 0;
		while (BFS())
		{
			memset(cur.data(), 0, sizeof(int) * cur.size());
			flow += DFS(s, INF);
		}
		return flow;
	}

	void clear(int newSize)
	{
		edges.clear();
		G.clear();
		G.resize(newSize);
		vis.resize(newSize);
		level.resize(newSize);
		cur.resize(newSize);
	}
	void reset()
	{
		for (int i = 0; i < edges.size(); i++)
			edges[i].flow = 0;
	}
} nf;

int depth[maxn];
int parent[maxn];
int cost[maxn];
void GomoryHu()
{
	depth[1] = 1;
	parent[1] = 0;
	cost[1] = 0;
	for (int i = 2; i <= n; i++)
		parent[i] = 1;
	for (int i = 2; i <= n; i++)
	{
		nf.s = i;
		nf.t = parent[i];
		nf.reset();
		cost[nf.s] = nf.Dinic();
		depth[nf.s] = depth[nf.t] + 1;
		for (int j = i + 1; j <= n; j++)
			if (parent[j] == nf.t && nf.vis[j] == nf.stamp)
				parent[j] = nf.s;
	}
}
int minVal(int u, int v)
{
	int ret = INF;
	if (depth[u] < depth[v]) std::swap(u, v);
	while (depth[u] > depth[v])
	{
		ret = std::min(ret, cost[u]);
		u = parent[u];
	}
	while (u != v)
	{
		ret = std::min(ret, std::min(cost[u], cost[v]));
		u = parent[u];
		v = parent[v];
	}
	return ret;
}

void run()
{
	int T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();
		nf.clear(n + 1);
		for (int i = 1; i <= m; i++)
		{
			int from = readIn();
			int to = readIn();
			int cost = readIn();
			nf.addEdge(from, to, cost);
			nf.addEdge(to, from, cost);
		}
		GomoryHu();
		int q[35];
		q[0] = readIn();
		for (int i = 1; i <= q[0]; i++)
			q[i] = readIn();
		int idx[35];
		for (int i = 1; i <= q[0]; i++) idx[i] = i;
		std::sort(idx + 1, idx + 1 + q[0],
			[q](const int& a, const int& b)
		{
			return q[a] < q[b];
		});
		int sort[35];
		for (int i = 1; i <= q[0]; i++)
			sort[i] = q[idx[i]];
		int rank[35];
		for (int i = 1; i <= q[0]; i++)
			rank[idx[i]] = i;

		int ans[35] = {};
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
			{
				int val = minVal(i, j);
				ans[std::lower_bound(sort + 1, sort + 1 + q[0], val) - sort]++;
			}
		for (int i = 1; i <= q[0]; i++)
			ans[i] += ans[i - 1];
		for (int i = 1; i <= q[0]; i++)
			printOut(ans[rank[i]]);
		putchar('\n');
	}
}

int main()
{
	run();
	return 0;
}