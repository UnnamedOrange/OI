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
const INT maxn = 105;
INT n, m;
long long ans;

inline int code(int i, int j)
{
	return (i - 1) * m + j;
}
struct NetworkFlow
{
	struct Edge
	{
		INT from, to, cap, flow;
		INT next;
		Edge() {}
	} edges[maxn * maxn * maxn];
	INT count_;
	INT head[maxn * maxn];
	INT s, t;


	void clear()
	{
		s = 0;
		t = n * m + 1;
		count_ = 0;
		memset(head, -1, sizeof(head));
	}
	void addEdge(INT from, INT to, INT cap)
	{
		for (int i = 0; i < 2; i++)
		{
			Edge& e = edges[count_];
			e.flow = 0;
			e.from = from;
			e.to = to;
			e.cap = cap;
			e.next = head[from];
			head[from] = count_;
			count_++;

			std::swap(from, to);
			cap = 0;
		}
	}

	INT cnt[maxn * maxn];
	INT level[maxn * maxn];
	INT DFS(INT node, INT opt)
	{
		if (!opt || node == t)
			return opt;
		INT flow = 0;
		for (int& i = cnt[node]; ~i; i = edges[i].next)
		{
			Edge& e = edges[i];
			INT f;
			if (level[node] + 1 == level[e.to] && (f = DFS(e.to, std::min(opt, e.cap - e.flow))))
			{
				flow += f;
				opt -= f;
				e.flow += f;
				edges[i ^ 1].flow -= f;
				if (!opt) break;
			}
		}
		return flow;
	}
	struct Queue
	{
		INT c[maxn * maxn];
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
		q.clear();
		memset(vis, 0, sizeof(vis));
		level[s] = 0;
		q.push(s);
		vis[s] = true;
		while (!q.empty())
		{
			INT from = q.front();
			q.pop();
			for (int i = head[from]; ~i; i = edges[i].next)
			{
				const Edge& e = edges[i];
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
			memcpy(cnt, head, sizeof(cnt));
			flow += DFS(s, INF);
		}
		return flow;
	}
} nf;

INT rect[6][maxn][maxn];

void run()
{
	memset(&INF, 0x3f, sizeof(INF));
	n = readIn();
	m = readIn();
	nf.clear();
	for (int i = 0; i < 2; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= m; k++)
				ans += rect[i][j][k] = readIn();
	for (int i = 2; i < 4; i++)
		for (int j = 1; j < n; j++)
			for (int k = 1; k <= m; k++)
				ans += rect[i][j][k] = readIn();
	for (int i = 4; i < 6; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k < m; k++)
				ans += rect[i][j][k] = readIn();

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			nf.addEdge(nf.s, code(i, j), 2 * rect[0][i][j] + rect[2][i - 1][j] + rect[2][i][j] + rect[4][i][j] + rect[4][i][j - 1]);
			nf.addEdge(code(i, j), nf.t, 2 * rect[1][i][j] + rect[3][i - 1][j] + rect[3][i][j] + rect[5][i][j] + rect[5][i][j - 1]);
			if (i != 1)
				nf.addEdge(code(i, j), code(i - 1, j), rect[2][i - 1][j] + rect[3][i - 1][j]);
			if (i != n)
				nf.addEdge(code(i, j), code(i + 1, j), rect[2][i][j] + rect[3][i][j]);
			if (j != 1)
				nf.addEdge(code(i, j), code(i, j - 1), rect[4][i][j - 1] + rect[5][i][j - 1]);
			if (j != m)
				nf.addEdge(code(i, j), code(i, j + 1), rect[4][i][j] + rect[5][i][j]);
		}
	printOut(ans - nf.MaxFlow() / 2);
}

int main()
{
	run();
	return 0;
}