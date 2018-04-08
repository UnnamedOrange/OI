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

const int INF = (~(int(1) << (sizeof(int) * 8 - 1))) >> 1;
const int maxn = 855;
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

	int cur[maxn];
	int level[maxn];
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

	int vis[maxn];
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
			memset(cur, 0, sizeof(int) * (n + 1));
			flow += DFS(s, INF);
		}
		return flow;
	}

	void reset()
	{
		for (int i = 0; i < edges.size(); i++)
			edges[i].flow = 0;
	}
} nf;

void GomoryHu()
{
	int parent[maxn];
	for (int i = 2; i <= n; i++)
		parent[i] = 1;
	std::set<int> set;
	for (int i = 2; i <= n; i++)
	{
		nf.s = i;
		nf.t = parent[i];
		nf.reset();
		set.insert(nf.Dinic());
		for (int j = i + 1; j <= n; j++)
			if (parent[j] == nf.t && nf.vis[j] == nf.stamp)
				parent[j] = nf.s;
	}
	printOut(set.size());
}

void run()
{
	n = readIn();
	m = readIn();
	nf.G.resize(n + 1);
	for (int i = 1; i <= m; i++)
	{
		int from = readIn();
		int to = readIn();
		int cost = readIn();
		nf.addEdge(from, to, cost);
		nf.addEdge(to, from, cost);
	}
	GomoryHu();
}

int main()
{
	run();
	return 0;
}