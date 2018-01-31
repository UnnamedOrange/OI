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
const INT maxn = 55;
INT n, m;
INT d, f, b;
INT rect[maxn][maxn];

inline int code(INT x, INT y)
{
	return (x - 1) * m + y;
}
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
	INT s, t;

	void init()
	{
		edges.clear();
		G.clear();
		G.resize(n * m + 2);
		s = 0;
		t = n * m + 1;
	}
	void addEdge(INT from, INT to, INT cap)
	{
		edges.push_back(Edge(from, to, cap));
		edges.push_back(Edge(to, from, 0));
		int i = edges.size();
		G[from].push_back(i - 2);
		G[to].push_back(i - 1);
	}

	INT level[maxn * maxn];
	INT cnt[maxn * maxn];
	INT DFS(INT node, INT opt)
	{
		if (!opt || node == t)
			return opt;
		INT flow = 0;
		for (int& i = cnt[node]; i < G[node].size(); i++)
		{
			Edge& e = edges[G[node][i]];
			INT f;
			if (level[e.to] == level[e.from] + 1 && (f = DFS(e.to, std::min(opt, e.cap - e.flow))))
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
		static const int size = maxn * maxn;
		INT c[size];
		INT head, tail;
		Queue() : head(), tail() {}
		void clear() { head = tail = 0; }
		bool empty() { return head == tail; }
		void push(INT x) { c[tail++] = x; }
		void pop() { head++; }
		INT front() { return c[head]; }
	} q;
	bool vis[maxn * maxn];
	bool BFS()
	{
		memset(vis, 0, sizeof(vis));
		q.clear();
		level[s] = 0;
		q.push(s);
		vis[s] = true;
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
	INT MaxFlow()
	{
		INT flow = 0;
		while (BFS())
		{
			memset(cnt, 0, sizeof(cnt));
			flow += DFS(s, INF);
		}
		return flow;
	}
} nf;

void run()
{
	memset(&INF, 0x3f, sizeof(INF));
	INT T = readIn();
	while (T--)
	{
		m = readIn();
		n = readIn();
		d = readIn();
		f = readIn();
		b = readIn();
		nf.init();

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				char ch = getchar();
				while (ch != '#' && ch != '.') ch = getchar();
				rect[i][j] = ch == '#';
			}
		}

		INT ans = 0;
		for (int i = 1; i <= m; i++)
		{
			if (!rect[1][i])
			{
				rect[1][i] = true;
				ans += f;
			}
			if (!rect[n][i])
			{
				rect[n][i] = true;
				ans += f;
			}
			nf.addEdge(nf.s, code(1, i), INF);
			nf.addEdge(nf.s, code(n, i), INF);
		}
		for (int i = 2; i < n; i++)
		{
			if (!rect[i][1])
			{
				rect[i][1] = true;
				ans += f;
			}
			if (!rect[i][m])
			{
				rect[i][m] = true;
				ans += f;
			}
			nf.addEdge(nf.s, code(i, 1), INF);
			nf.addEdge(nf.s, code(i, m), INF);
		}
		for (int i = 2; i < n; i++)
		{
			for (int j = 2; j < m; j++)
			{
				if (rect[i][j])
					nf.addEdge(nf.s, code(i, j), d);
				else
					nf.addEdge(code(i, j), nf.t, f);
			}
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				int cnt = code(i, j);
				const INT vecx[] = { 1, -1, 0, 0 };
				const INT vecy[] = { 0, 0, 1, -1 };
				for (int k = 0; k < 4; k++)
				{
					int newx = i + vecx[k];
					int newy = j + vecy[k];
					if (newx >= 1 && newx <= n && newy >= 1 && newy <= m)
					{
						nf.addEdge(cnt, code(newx, newy), b);
					}
				}
			}
		}

		printOut(ans + nf.MaxFlow());
	}
}

int main()
{
	run();
	return 0;
}