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
const int maxn = 2005;
int n1, n2, m;

struct NetworkFlow
{
	struct Edge
	{
		int from, to, cap, flow;
		Edge() {}
		Edge(int from, int to, int cap) : from(from), to(to), cap(cap), flow() {}
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

	struct Queue
	{
		int c[maxn * 2];
		int head, tail;
		Queue() { clear(); }
		void clear() { head = tail = 0; }
		void push(int x) { c[tail++] = x; }
		void pop() { head++; }
		int front() { return c[head]; }
		bool empty() { return head == tail; }
	} q;
	int vis[maxn * 2];
	int opt[maxn * 2];
	int pre[maxn * 2];
	bool BFS()
	{
		q.clear();
		static int stamp;
		stamp++;
		memset(opt, 0, sizeof(opt));
		opt[s] = INF;
		vis[s] = stamp;
		q.push(s);
		while (!q.empty())
		{
			int from = q.front();
			q.pop();
			for (int i = 0; i < G[from].size(); i++)
			{
				const Edge& e = edges[G[from][i]];
				if (e.flow < e.cap && vis[e.to] != stamp)
				{
					opt[e.to] = std::min(opt[from], e.cap - e.flow);
					pre[e.to] = G[from][i];
					vis[e.to] = stamp;
					q.push(e.to);
					if (vis[t] == stamp)
					{
						q.clear();
						break;
					}
				}
			}
		}
		if (vis[t] != stamp) return false;
		for (int u = t; u != s; u = edges[pre[u]].from)
		{
			edges[pre[u]].flow += opt[t];
			edges[pre[u] ^ 1].flow -= opt[t];
		}
		return true;
	}

	void maxFlow()
	{
		while (BFS());
	}

	NetworkFlow() {}
} nf;

int base;
void statistic(std::vector<int>& ans)
{
	nf.maxFlow();
	for (int i = 1; i <= m; i++)
		if (!nf.edges[(i - 1) << 1].flow)
			ans.push_back(i);
}

int minDegree = INF;
int degree[maxn * 2];
std::vector<std::vector<int> > ans;

void run()
{
	n1 = readIn();
	n2 = readIn();
	m = readIn();
	nf.G.resize(n1 + n2 + 2);
	nf.s = 0;
	nf.t = n1 + n2 + 1;

	for (int i = 1; i <= m; i++)
	{
		int u = readIn();
		int v = readIn() + n1;
		degree[u]++;
		degree[v]++;
		nf.addEdge(u, v, 1);
	}
	for (int i = 1; i <= n1 + n2; i++)
		minDegree = std::min(minDegree, degree[i]);
	int base = (nf.edges.size() >> 1) - 1;

	for (int i = 1; i <= n1; i++)
		nf.addEdge(nf.s, i, degree[i] - minDegree);
	for (int i = 1; i <= n2; i++)
		nf.addEdge(n1 + i, nf.t, degree[n1 + i] - minDegree);

	ans.resize(minDegree + 1);
	statistic(ans[minDegree]);
	for (int i = minDegree - 1; ~i; i--)
	{
		for (int j = 1; j <= n1 + n2; j++)
			nf.edges[(base + j) << 1].cap++;
		statistic(ans[i]);
	}

	for (int i = 0; i <= minDegree; i++)
	{
		printOut(ans[i].size());
		for (int j = 0; j < ans[i].size(); j++)
		{
			putchar(' ');
			printOut(ans[i][j]);
		}
		putchar('\n');
	}
}

int main()
{
	run();
	return 0;
}