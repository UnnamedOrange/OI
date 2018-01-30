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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1))) >> 1;
const INT maxn = 105;
INT n, m, k;
char buffer[30];
std::map<std::string, int> mapSI;
inline INT code(const char* s)
{
	if (mapSI.count(s))
		return mapSI[s];
	return mapSI[s] = mapSI.size() + 1;
}
INT base[maxn];
INT device[maxn];
struct Switcher
{
	INT from;
	INT to;
} switchers[maxn];

struct NetworkFlow
{
	struct Edge
	{
		INT from, to, cap, flow;
		Edge() {}
		Edge(INT from, INT to, INT cap) : from(from), to(to), cap(cap), flow() {}
	};
	std::vector<Edge> edges;
	std::vector<std::vector<int> > G;

	INT s, t;
	void initialize()
	{
		edges.clear();
		G.clear();
		G.resize(1 + mapSI.size() + 1);
		s = 0;
		t = G.size() - 1;
	}
	void addEdge(INT from, INT to, INT cap)
	{
		edges.push_back(Edge(from, to, cap));
		edges.push_back(Edge(to, from, 0));
		int i = edges.size();
		G[from].push_back(i - 2);
		G[to].push_back(i - 1);
	}
	void build()
	{
		for (int i = 1; i <= m; i++)
			addEdge(s, device[i], 1);
		for (int i = 1; i <= n; i++)
			addEdge(base[i], t, 1);
		for (int i = 1; i <= k; i++)
			addEdge(switchers[i].from, switchers[i].to, INF);
	}

	INT cnt[maxn * 4];
	INT level[maxn * 4];
	INT DFS(INT node, INT opt)
	{
		if (!opt || node == t)
			return opt;
		INT flow = 0;
		INT f;
		for (int& i = cnt[node]; i < G[node].size(); i++)
		{
			Edge& e = edges[G[node][i]];
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
		INT c[maxn * 4];
		INT head, tail;
		Queue() : head(), tail() {}
		void clear() { head = tail = 0; }
		void push(INT x) { c[tail++] = x; }
		void pop() { head++; }
		INT front() { return c[head]; }
		bool empty() { return head == tail; }
	} q;
	bool vis[maxn * 4];
	bool BFS()
	{
		memset(vis, 0, sizeof(vis));
		q.clear();
		q.push(s);
		vis[s] = true;
		level[s] = 0;
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
	INT T = readIn();
	while (T--)
	{
		static bool printed;
		if (printed)
			putchar('\n');
		printed = true;
		mapSI.clear();
		n = readIn();
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", buffer);
			base[i] = code(buffer);
		}

		m = readIn();
		for (int i = 1; i <= m; i++)
		{
			scanf("%s", buffer);
			scanf("%s", buffer);
			device[i] = code(buffer);
		}

		k = readIn();
		for (int i = 1; i <= k; i++)
		{
			scanf("%s", buffer);
			switchers[i].from = code(buffer);
			scanf("%s", buffer);
			switchers[i].to = code(buffer);
		}

		nf.initialize();
		nf.build();
		printOut(m - nf.MaxFlow());
	}
}

int main()
{
	run();
	return 0;
}