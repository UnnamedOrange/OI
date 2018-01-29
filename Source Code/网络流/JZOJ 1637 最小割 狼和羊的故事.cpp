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
INT n, m;
INT rect[maxn][maxn];

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
	void addEdge(INT from, INT to, INT cap)
	{
		edges.push_back(Edge(from, to, cap));
		edges.push_back(Edge(to, from, 0));
		INT t = edges.size();
		G[from].push_back(t - 2);
		G[to].push_back(t - 1);
	}

	NetworkFlow() : G(n * m + 2), cnt(n * m + 2), level(n * m + 2) {}

	std::vector<INT> level;
	std::vector<INT> cnt;
	INT DFS(INT node, INT opt)
	{
		if (node == t || !opt)
			return opt;
		INT flow = 0;
		INT f;
		for (INT& i = cnt[node]; i < G[node].size(); i++)
		{
			Edge& e = edges[G[node][i]];
			if (level[node] + 1 == level[e.to] && (f = DFS(e.to, std::min(opt, e.cap - e.flow))) > 0)
			{
				e.flow += f;
				edges[G[node][i] ^ 1].flow -= f;
				flow += f;
				opt -= f;
				if (!opt) break;
			}
		}
		return flow;
	}
	bool BFS()
	{
		std::vector<bool> vis(n * m + 2);
		std::queue<INT> q;
		q.push(s);
		level[s] = 0;
		vis[s] = true;
		while (!q.empty())
		{
			INT from = q.front();
			q.pop();
			for (int i = 0; i < G[from].size(); i++)
			{
				Edge& e = edges[G[from][i]];
				if (!vis[e.to] && e.cap > e.flow)
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
			cnt.clear();
			cnt.resize(n * m + 2);
			flow += DFS(s, INF);
		}
		return flow;
	}
};

inline int code(INT x, INT y)
{
	return (x - 1) * m + y;
}
inline bool inRange(INT x, INT y)
{
	return x >= 1 && x <= n && y >= 1 && y <= m;
}
inline void build(NetworkFlow& nf)
{
	nf.s = 0;
	nf.t = n * m + 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			INT cnt = code(i, j);
			if (rect[i][j] == 0)
			{
				if (inRange(i - 1, j) && rect[i - 1][j] != 1)
					nf.addEdge(cnt, code(i - 1, j), 1);
				if (inRange(i + 1, j) && rect[i + 1][j] != 1)
					nf.addEdge(cnt, code(i + 1, j), 1);
				if (inRange(i, j - 1) && rect[i][j - 1] != 1)
					nf.addEdge(cnt, code(i, j - 1), 1);
				if (inRange(i, j + 1) && rect[i][j + 1] != 1)
					nf.addEdge(cnt, code(i, j + 1), 1);
			}
			else if (rect[i][j] == 1)
			{
				nf.addEdge(nf.s, cnt, INF);
				if (inRange(i - 1, j) && rect[i - 1][j] != 1)
					nf.addEdge(cnt, code(i - 1, j), 1);
				if (inRange(i + 1, j) && rect[i + 1][j] != 1)
					nf.addEdge(cnt, code(i + 1, j), 1);
				if (inRange(i, j - 1) && rect[i][j - 1] != 1)
					nf.addEdge(cnt, code(i, j - 1), 1);
				if (inRange(i, j + 1) && rect[i][j + 1] != 1)
					nf.addEdge(cnt, code(i, j + 1), 1);
			}
			else if (rect[i][j] == 2)
				nf.addEdge(code(i, j), nf.t, INF);
		}
	}
}
void run()
{
	n = readIn();
	m = readIn();

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			rect[i][j] = readIn();

	NetworkFlow nf;
	build(nf);
	printOut(nf.MaxFlow());
}

int main()
{
	run();
	return 0;
}