#pragma GCC optimize(3)
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

const double EPS = 1e-8;
const char noans[] = "CanNotFindTreasure!";
const int maxn = 1005;
int n;
const double INF = 2e8;
struct NetworkFlow
{
	struct Edge
	{
		int from, to;
		double cap, flow;
		Edge() {}
		Edge(int from, int to, double cap) : flow(), from(from), to(to), cap(cap) {}
	};
	std::vector<Edge> edges;
	std::vector<std::vector<int> > G;
	void addEdge(int from, int to, double cap)
	{
		edges.push_back(Edge(from, to, cap));
		edges.push_back(Edge(to, from, 0));
		int i = edges.size();
		G[from].push_back(i - 2);
		G[to].push_back(i - 1);
	}

	int s, t;

	int cur[maxn];
	int level[maxn];
	double DFS(int node, double opt)
	{
		if (node == t || std::abs(opt) < EPS) return opt;
		double flow = 0;
		for (int& i = cur[node]; i < G[node].size(); i++)
		{
			Edge& e = edges[G[node][i]];
			double t;
			if (level[node] + 1 == level[e.to] && (t = DFS(e.to, std::min(opt, e.cap - e.flow))))
			{
				flow += t;
				opt -= t;
				e.flow += t;
				edges[G[node][i] ^ 1].flow -= t;
				if (std::abs(opt) < EPS) break;
			}
		}
		return flow;
	}

	int vis[maxn];
	bool BFS()
	{
		static int stamp;
		stamp++;
		std::queue<int> q;
		q.push(s);
		vis[s] = stamp;
		while (!q.empty())
		{
			int from = q.front();
			q.pop();
			for (int i = 0; i < G[from].size(); i++)
			{
				const Edge& e = edges[G[from][i]];
				if (std::abs(e.cap - e.flow) > EPS && e.flow < e.cap && vis[e.to] != stamp)
				{
					level[e.to] = level[from] + 1;
					vis[e.to] = stamp;
					q.push(e.to);
				}
			}
		}
		return vis[t] == stamp;
	}

	double Dinic()
	{
		double flow = 0;
		while (BFS())
		{
			memset(cur, 0, sizeof(int) * (n + 2));
			flow += DFS(s, INF);
		}
		return flow;
	}

	void clear()
	{
		for (int i = 0; i < edges.size(); i++)
			edges[i].flow = 0;
	}
} nf;

int a[maxn];
int b[maxn];

int start;
double check(double k)
{
	double accum = 0;
	for (int i = start, j = 1; i < nf.edges.size(); i += 4, j++)
	{
		double val = a[j] - k * b[j];
		if (val > 0)
		{
			nf.edges[i].cap = val;
			nf.edges[i + 2].cap = 0;
			accum += val;
		}
		else if (val < 0)
		{
			nf.edges[i].cap = 0;
			nf.edges[i + 2].cap = -val;
		}
	}
	nf.clear();
	return accum - nf.Dinic();
}

void run()
{
	n = readIn();
	nf.G.resize(n + 2);
	nf.s = 0;
	nf.t = n + 1;
	for (int i = 1; i <= n; i++)
	{
		int c = readIn();
		while (c--)
		{
			int to = readIn();
			nf.addEdge(i, to, INF);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		a[i] = readIn();
		b[i] = readIn();
	}

	start = nf.edges.size();
	for (int i = 1; i <= n; i++)
	{
		nf.addEdge(0, i, 0);
		nf.addEdge(i, n + 1, 0);
	}
	double l = 0, r = INF;
	while (r - l >= 1e-6)
	{
		double mid = (l + r) / 2;
		if (check(mid) > 0) // note
			l = mid;
		else
			r = mid;
	}
	if (l + 0.5 >= INF) puts(noans);
	else printf("%.6f", 1 / l);
}

int main()
{
	run();
	return 0;
}