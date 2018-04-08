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

struct NetworkFlow
{
	struct Edge
	{
		int from, to, cap, flow;
		Edge() {}
		Edge(int from, int to, int cap) : flow(), from(from), to(to), cap(cap) {}
	};
	std::vector<Edge> edges;
	std::vector<std::vector<int> > G;
	void addEdge(int from, int to, int cap)
	{
		edges.push_back(Edge(from, to, cap));
		edges.push_back(Edge(to, from, 0));
		int i = edges.size();
		G[from].push_back(i - 2);
		G[to].push_back(i - 1);
	}
	int s, t;
	void clear(int newSize)
	{
		edges.clear();
		G.clear();
		G.resize(newSize);
		cur.resize(newSize);
		level.resize(newSize);
		vis.resize(newSize);
	}
	std::vector<int> cur;
	std::vector<int> level;
	std::vector<int> vis;

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
	bool BFS()
	{
		static int stamp;
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
					level[e.to] = level[from] + 1;
					vis[e.to] = stamp;
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
} nf;

const int maxm = 1005;
int n, m;
int accum[2000];
int g[maxm];
int girl[370][105];
int girlEdge[370][105];
int lbound[370][105];

int baseDay, baseGirl;

void run()
{
	while (~scanf("%d%d", &n, &m))
	{
		memset(accum, 0, sizeof(accum));
		nf.clear(n + m + 4);
		baseDay = 0;
		baseGirl = n;
		nf.s = n + m + 2;
		nf.t = n + m + 3;
		nf.addEdge(n + m + 1, 0, INF);
		for (int i = 1; i <= m; i++)
		{
			g[i] = readIn();
			accum[baseGirl + i] -= g[i];
			accum[n + m + 1] += g[i];
			nf.addEdge(baseGirl + i, n + m + 1, INF - g[i]);
		}
		for (int i = 1; i <= n; i++)
		{
			girl[i][0] = 0;
			int c = readIn();
			int d = readIn();
			nf.addEdge(0, baseDay + i, d);
			for (int j = 1; j <= c; j++)
			{
				int t = girl[i][++girl[i][0]] = readIn() + 1;
				int l = readIn();
				int r = readIn();
				accum[baseGirl + t] += l;
				accum[baseDay + i] -= l;
				nf.addEdge(baseDay + i, baseGirl + t, r - l);
				girlEdge[i][girl[i][0]] = nf.edges.size() - 2;
				lbound[i][girl[i][0]] = l;
			}
		}

		int extra = 0;
		for (int i = 0; i < n + m + 2; i++)
		{
			if (accum[i] > 0)
			{
				extra += accum[i];
				nf.addEdge(nf.s, i, accum[i]);
			}
			else if (accum[i] < 0)
				nf.addEdge(i, nf.t, -accum[i]);
		}

		int lower_bound = nf.Dinic();
		if (lower_bound != extra)
			printOut(-1);
		else
		{
			nf.s = 0;
			nf.t = n + m + 1;
			printOut(nf.Dinic());
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= girl[i][0]; j++)
					printOut(lbound[i][j] + nf.edges[girlEdge[i][j]].flow);
		}

		putchar('\n');
	}
}

int main()
{
	run();
	return 0;
}