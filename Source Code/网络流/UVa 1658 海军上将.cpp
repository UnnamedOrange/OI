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
typedef int INT;
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
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

INT INF;
const INT maxn = 1005;
INT n, m;

struct NetworkFlow
{
	struct Edge
	{
		INT from, to, cap, cost, flow;
		Edge() {}
		Edge(INT from, INT to, INT cap, INT cost) : flow(), from(from), to(to), cap(cap), cost(cost) {}
	};
	std::vector<Edge> edges;
	std::vector<std::vector<int> > G;
	INT s, t, limit;

	void addEdge(INT from, INT to, INT cap, INT cost)
	{
		edges.push_back(Edge(from, to, cap, cost));
		edges.push_back(Edge(to, from, 0, -cost));
		INT i = edges.size();
		G[from].push_back(i - 2);
		G[to].push_back(i - 1);
	}
	void init()
	{
		edges.clear();
		G.clear();
		G.resize(n * 2);
		s = 1;
		t = 2 * n - 2;
		limit = 2;
	}
	struct Queue
	{
		static const INT size = maxn * 2;
		INT c[size];
		INT head, tail;
		Queue() : head(), tail() {}
		void clear() { head = tail = 0; }
		void push(INT x) { c[tail] = x; tail = (tail + 1) % size; }
		void pop() { head = (head + 1) % size; }
		INT front() { return c[head]; }
		bool empty() { return head == tail; }
	} q;
	INT dis[maxn * 2];
	bool inQ[maxn * 2];
	INT opt[maxn * 2];
	INT pre[maxn * 2];
	bool Bellman_Ford(INT& flow, INT& cost)
	{
		memset(dis, 0x3f, sizeof(dis));
		memset(opt, 0, sizeof(opt));
		q.clear();
		q.push(s);
		inQ[s] = true;
		opt[s] = INF;
		dis[s] = 0;
		while (!q.empty())
		{
			INT from = q.front();
			q.pop();
			inQ[from] = false;
			for (int i = 0; i < G[from].size(); i++)
			{
				Edge& e = edges[G[from][i]];
				if (e.cap - e.flow > 0 && dis[e.to] > dis[from] + e.cost)
				{
					dis[e.to] = dis[from] + e.cost;
					opt[e.to] = std::min(opt[from], e.cap - e.flow);
					pre[e.to] = G[from][i];
					if (!inQ[e.to])
					{
						q.push(e.to);
						inQ[e.to] = true;
					}
				}
			}
		}
		opt[t] = std::min(opt[t], limit - flow);
		if (!opt[t]) return false;
		for (int u = t; u != s; u = edges[pre[u]].from)
		{
			edges[pre[u]].flow += opt[t];
			edges[pre[u] ^ 1].flow -= opt[t];
		}
		flow += opt[t];
		cost += opt[t] * dis[t];
		return true;
	}
	INT MinCost()
	{
		INT flow = 0, cost = 0;
		while (Bellman_Ford(flow, cost));
		return cost;
	}
} nf;

void run()
{
	memset(&INF, 0x3f, sizeof(INF));
	while (~scanf("%d%d", &n, &m))
	{
		nf.init();
		for (int i = 1; i <= n; i++)
			nf.addEdge((i - 1) * 2, (i - 1) * 2 + 1, 1, 0);
		for (int i = 1; i <= m; i++)
		{
			INT from = readIn();
			INT to = readIn();
			INT cost = readIn();
			nf.addEdge((from - 1) * 2 + 1, (to - 1) * 2, 1, cost);
		}
		printOut(nf.MinCost());
	}
}

int main()
{
	run();
	return 0;
}