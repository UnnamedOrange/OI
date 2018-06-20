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
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = int;
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
const int maxn = 55;
const int maxtime = 200;
int n;
int park[maxn];
int track[maxn];
int quick[maxn];
int slow[maxn];

int invalid[maxn][maxtime + 5];

struct NetworkFlow
{
	struct Edge
	{
		int from, to, cap, flow = 0;
		Edge() = default;
		Edge(int from, int to, int cap) : from(from), to(to), cap(cap) {}
	};
	std::vector<Edge> edges;
	std::vector<std::vector<int>> G;
	void addEdge(int from, int to, int cap)
	{
		edges.push_back(Edge(from, to, cap));
		edges.push_back(Edge(to, from, 0));
		int i = edges.size();
		G[from].push_back(i - 2);
		G[to].push_back(i - 1);
	}
	int s, t;

	std::vector<int> level;
	std::vector<int> cur;
	int Dinic(int node, int opt)
	{
		if (node == t || !opt) return opt;
		int flow = 0;
		for (int& i = cur[node]; i < G[node].size(); i++)
		{
			Edge& e = edges[G[node][i]];
			int t;
			if (level[node] + 1 == level[e.to] && (t = Dinic(e.to, std::min(opt, e.cap - e.flow))))
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

	struct Queue
	{
		int c[maxn * maxtime + 5];
		int head, tail;
		void clear() { head = tail = 0; }
		void push(int x) { c[tail++] = x; }
		void pop() { head++; }
		int front() { return c[head]; }
		bool empty() { return head == tail; }
	} q;
	std::vector<bool> vis;
	bool BFS()
	{
		q.clear();
		vis.clear();
		vis.resize(G.size());
		q.push(s);
		vis[s] = true;
		level[s] = 0;
		while (!q.empty())
		{
			int from = q.front();
			q.pop();
			for (int i = 0; i < G[from].size(); i++)
			{
				const Edge& e = edges[G[from][i]];
				if (e.flow < e.cap && !vis[e.to])
				{
					vis[e.to] = true;
					level[e.to] = level[from] + 1;
					q.push(e.to);
				}
			}
		}
		return vis[t];
	}

	int maxFlow()
	{
		level.clear();
		level.resize(G.size());

		int flow = 0;
		while (BFS())
		{
			cur.clear();
			cur.resize(G.size());
			flow += Dinic(s, INF);
		}
		return flow;
	}
} nf;

void run()
{
	n = readIn();
	for (int i = 0; i <= n; i++)
		park[i] = readIn();
	for (int i = 0; i <= n; i++)
		track[i] = readIn();
	for (int i = 0; i <= n; i++)
		quick[i] = readIn();
	for (int i = 0; i <= n; i++)
		slow[i] = readIn();

	int a, b;
	while (~(a = readIn()) && ~(b = readIn()))
		for (int i = b; i <= n; a += quick[i], i++)
			for (int j = std::max(0, a - (slow[i] - quick[i]) + 1); j < a; j++)
				invalid[i][j]++;

	nf.G.resize(1 + (n + 1) * (maxtime + 1) + 1);
	nf.s = 0;
	nf.t = nf.G.size() - 1;
	for (int i = 0; i <= maxtime; i++)
		nf.addEdge(nf.s, 1 + i * (n + 1), INF);
	for (int i = 0; i <= n; i++)
		for (int j = 0; j < maxtime; j++)
			nf.addEdge(1 + i + j * (n + 1), 1 + i + (j + 1) * (n + 1), park[i]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j + slow[i] <= maxtime; j++)
			nf.addEdge(1 + i + j * (n + 1), 1 + i + 1 + (j + slow[i]) * (n + 1), track[i] - invalid[i][j]);

	for (int j = 0; j <= maxtime - slow[n]; j++)
		nf.addEdge(1 + n + j * (n + 1), nf.t, track[n] - invalid[n][j]);
	printOut(nf.maxFlow());
}

int main()
{
#ifndef LOCAL
	freopen("express.in", "r", stdin);
	freopen("express.out", "w", stdout);
#endif
	run();
	return 0;
}