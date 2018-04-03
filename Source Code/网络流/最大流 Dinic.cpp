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

const LL INF = (~(LL(1) << (sizeof(LL) * 8 - 1))) >> 1;
const int maxn = 10005;
int n, m;
struct NetworkFlow
{
	struct Edge
	{
		int from;
		int to;
		LL cap;
		LL flow;
		Edge() {}
		Edge(int from, int to, int cap) : from(from), to(to), cap(cap), flow() {}
	};
	std::vector<Edge> edges;
	std::vector<std::vector<int> > G;
	int s, t;
	void addEdge(int from, int to, LL cap)
	{
		edges.push_back(Edge(from, to, cap));
		edges.push_back(Edge(to, from, 0));
		int i = edges.size();
		G[from].push_back(i - 2);
		G[to].push_back(i - 1);
	}

	int level[maxn];
	int cur[maxn];
	LL DFS(int node, LL opt)
	{
		if (node == t || !opt) return opt;
		LL flow = 0;
		for (int& i = cur[node]; i < G[node].size(); i++)
		{
			Edge& e = edges[G[node][i]];
			LL t;
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
	struct queue
	{
		int c[maxn];
		int head, tail;
		queue() : head(), tail() {}
		void clear() { head = tail = 0; }
		void push(int x) { c[tail++] = x; }
		int front() { return c[head]; }
		bool empty() { return head == tail; }
		void pop() { head++; }
	} q;
	bool vis[maxn];
	bool BFS()
	{
		q.clear();
		memset(vis, 0, sizeof(bool) * (n + 1));
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
					level[e.to] = level[from] + 1;
					vis[e.to] = true;
					q.push(e.to);
				}
			}
		}
		return vis[t];
	}

	LL maxflow()
	{
		LL flow = 0;
		while (BFS())
		{
			memset(cur, 0, sizeof(int) * (n + 1));
			flow += DFS(s, INF);
		}
		return flow;
	}
} nf;

void run()
{
	n = readIn();
	m = readIn();
	nf.G.resize(n + 1);
	nf.s = readIn();
	nf.t = readIn();
	for (int i = 1; i <= m; i++)
	{
		int from = readIn();
		int to = readIn();
		int cap = readIn();
		nf.addEdge(from, to, cap);
	}
	printOut(nf.maxflow());
}

int main()
{
	run();
	return 0;
}