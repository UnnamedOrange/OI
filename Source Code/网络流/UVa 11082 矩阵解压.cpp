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
const INT maxn = 25;
INT n, m;
INT row[maxn], colum[maxn];

struct NetworkFlow
{
	struct Edge
	{
		INT from, to, cap, flow;
		Edge() {}
		Edge(INT from, INT to, INT cap) : flow(), from(from), to(to), cap(cap) {}
	};
	std::vector<Edge> edges;
	std::vector<std::vector<int> > G;
	void addEdge(INT from, INT to, INT cap)
	{
		edges.push_back(Edge(from, to, cap));
		edges.push_back(Edge(to, from, 0));
		int i = edges.size();
		G[from].push_back(i - 2);
		G[to].push_back(i - 1);
	}

	INT s, t;
	void init()
	{
		edges.clear();
		G.clear();
		G.resize(1 + n + m + 1);
		s = 0;
		t = n + m + 1;
	}
	void build()
	{
		for (int i = 1; i <= n; i++)
			addEdge(s, i, row[i]);
		for (int i = 1, j = n + 1; i <= m; i++, j++)
			addEdge(j, t, colum[i]);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				addEdge(i, n + j, 19);
	}

	INT level[maxn * 2];
	INT cnt[maxn * 2];
	INT DFS(INT node, INT opt)
	{
		if (!opt || node == t)
			return opt;
		INT flow = 0;
		for (int& i = cnt[node]; i < G[node].size(); i++)
		{
			Edge& e = edges[G[node][i]];
			INT f;
			if (level[node] + 1 == level[e.to] && (f = DFS(e.to, std::min(e.cap - e.flow, opt))))
			{
				flow += f;
				opt -= f;
				e.flow += f;
				edges[G[node][i] ^ 1].flow -= f;
				if (!opt) break;
			}
		}
		return flow;
	}
	struct Queue
	{
		static const INT size = maxn * 2;
		INT c[size];
		INT head, tail;
		Queue() : head(), tail() {}
		void clear() { head = tail = 0; }
		bool empty() { return head == tail; }
		void push(INT x) { c[tail++] = x; }
		void pop() { head++; }
		INT front() { return c[head]; }
	} q;
	bool vis[maxn * 2];
	bool BFS()
	{
		memset(vis, 0, sizeof(vis));
		q.clear();
		vis[s] = true;
		level[s] = 0;
		q.push(s);
		while (!q.empty())
		{
			INT from = q.front();
			q.pop();
			for (int i = 0; i < G[from].size(); i++)
			{
				const Edge& e = edges[G[from][i]];
				if (e.cap - e.flow > 0 && !vis[e.to])
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
	INT ans[maxn][maxn];
	void print()
	{
		for (int i = 0; i < edges.size(); i += 2)
		{
			const Edge& e = edges[i];
			if (e.from == s || e.to == t) continue;
			ans[e.from][e.to - n] = e.flow;
		}
		for (int i = 1; i <= n; i++)
		{
			printOut(ans[i][1]);
			for (int j = 2; j <= m; j++)
			{
				putchar(' ');
				printOut(ans[i][j]);
			}
			putchar('\n');
		}
	}
} nf;

void run()
{
	INT T = readIn();
	for (int i = 1, printed = false; i <= T; i++, printed = true)
	{
		if (printed)
			putchar('\n');
		printf("Matrix ");
		printOut(i);
		putchar('\n');

		n = readIn();
		m = readIn();
		for (int i = 1; i <= n; i++)
			row[i] = readIn();
		for (int i = 1; i <= m; i++)
			colum[i] = readIn();
		for (int i = n; i >= 1; i--)
			row[i] -= row[i - 1];
		for (int i = m; i >= 1; i--)
			colum[i] -= colum[i - 1];

		nf.init();
		nf.build();
		nf.MaxFlow();
		nf.print();
	}
}

int main()
{
	run();
	return 0;
}