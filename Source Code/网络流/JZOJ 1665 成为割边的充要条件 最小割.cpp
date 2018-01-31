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
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1))) >> 1;
const INT maxn = 4005;
const INT maxm = 60005;
INT n, m, s, t;
struct Edge
{
	INT from, to;
} edges[maxm];

struct NetworkFlow
{
	struct Edge
	{
		INT from, to, cap, flow;
		Edge() {}
		Edge(INT from, INT to, INT cap) : from(from), to(to), cap(cap), flow() {}
	};
	std::vector<Edge> edges;
	std::vector<int> G[maxn];
	void addEdge(INT from, INT to, INT cap)
	{
		edges.push_back(Edge(from, to, cap));
		edges.push_back(Edge(to, from, 0));
		int s = edges.size();
		G[from].push_back(s - 2);
		G[to].push_back(s - 1);
	}

	INT level[maxn];
	INT cnt[maxn];
	INT DFS(INT node, INT opt)
	{
		if (node == t || !opt)
			return opt;
		INT flow = 0;
		INT f;
		for (int& i = cnt[node]; i < G[node].size(); i++)
		{
			Edge& e = edges[G[node][i]];
			if (level[e.from] + 1 == level[e.to] && (f = DFS(e.to, std::min(opt, e.cap - e.flow))))
			{
				opt -= f;
				flow += f;
				e.flow += f;
				edges[G[node][i] ^ 1].flow -= f;
				if (!opt) break;
			}
		}
		return flow;
	}
	struct Queue
	{
		INT c[maxn];
		INT head, tail;
		Queue() : head(), tail() {}
		void clear() { head = tail = 0; }
		void push(INT x) { c[tail++] = x; }
		INT front() { return c[head]; }
		void pop() { head++; }
		bool empty() { return head == tail; }
	} q;
	struct Stack
	{
		INT c[maxn];
		Stack() : c() {}
		void clear() { c[0] = 0; }
		void push(INT x) { c[++c[0]] = x; }
		INT top() { return c[c[0]]; }
		void pop() { c[0]--; }
		bool empty() { return !c[0]; }
	};
	bool vis[maxn];
	bool BFS(INT start = s)
	{
		memset(vis, 0, sizeof(vis));
		q.clear();
		q.push(start);
		vis[start] = true;
		level[start] = 0;
		while (!q.empty())
		{
			INT from = q.front();
			q.pop();
			for (int i = 0; i < G[from].size(); i++)
			{
				const Edge& e = edges[G[from][i]];
				if (!vis[e.to] && e.cap - e.flow > 0)
				{
					vis[e.to] = true;
					level[e.to] = level[from] + 1;
					q.push(e.to);
				}
			}
		}
		return vis[t];
	}

	void MaxFlow()
	{
		while (BFS())
		{
			memset(cnt, 0, sizeof(cnt));
			DFS(s, INF);
		}
	}

	int clock;
	int dfn[maxn];
	int low[maxn];
	int belong[maxn];
	bool inStack[maxn];
	Stack S;
	void TS(INT node)
	{
		clock++;
		low[node] = dfn[node] = clock;
		S.push(node);
		inStack[node] = true;
		for (int i = 0; i < G[node].size(); i++)
		{
			const Edge& e = edges[G[node][i]];
			if (e.cap - e.flow <= 0)
				continue;
			if (!dfn[e.to])
			{
				TS(e.to);
				low[node] = std::min(low[node], low[e.to]);
			}
			else if (inStack[e.to])
			{
				low[node] = std::min(low[node], dfn[e.to]);
			}
		}
		if (low[node] == dfn[node])
		{
			static int N;
			N++;
			INT top;
			do
			{
				top = S.top();
				S.pop();
				inStack[top] = false;
				belong[top] = N;
			} while (top != node);
		}
	}
	void Tarjan()
	{
		for (int i = 1; i <= n; i++)
			if (!dfn[i])
				TS(i);
	}
} nf;

void run()
{
	n = readIn();
	m = readIn();
	s = readIn();
	t = readIn();
	for (int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT cap = readIn();
		edges[i].from = from;
		edges[i].to = to;
		nf.addEdge(from, to, cap);
	}
	nf.MaxFlow();

	nf.Tarjan();
	for (int i = 1; i <= m; i++)
	{
		const NetworkFlow::Edge& e = nf.edges[(i - 1) * 2];
		printOut(e.cap == e.flow && nf.belong[edges[i].from] != nf.belong[edges[i].to]);
		putchar(' ');
		printOut(e.cap == e.flow && nf.belong[edges[i].from] == nf.belong[s] && nf.belong[edges[i].to] == nf.belong[t]);
		putchar('\n');
	}
}

int main()
{
	run();
	return 0;
}