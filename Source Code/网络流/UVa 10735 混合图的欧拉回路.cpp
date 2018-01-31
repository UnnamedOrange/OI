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

INT INF;
const char NoSolution[] = "No euler circuit exist";
const INT maxn = 105;
const INT maxm = 505;
INT n, m;

#define ZeroMemory(x) memset(x, 0, sizeof(x))
INT dd[maxn]; //degree delta

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

	int s, t;
	void addEdge(INT from, INT to, INT cap)
	{
		edges.push_back(Edge(from, to, cap));
		edges.push_back(Edge(to, from, 0));
		size_t i = edges.size();
		G[from].push_back(i - 2);
		G[to].push_back(i - 1);
	}
	void init()
	{
		edges.clear();
		G.clear();
		G.resize(n + 2);
		s = 0;
		t = n + 1;
	}

	int level[maxn];
	int cnt[maxn];
	INT DFS(int node, INT opt)
	{
		if (!opt || node == t)
			return opt;
		INT flow = 0;
		for (int& i = cnt[node]; i < G[node].size(); i++)
		{
			Edge& e = edges[G[node][i]];
			INT f;
			if (level[e.to] == level[node] + 1 && (f = DFS(e.to, std::min(opt, e.cap - e.flow))))
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
	bool vis[maxn];
	struct Queue
	{
		int c[maxn];
		int head, tail;
		Queue() : head(), tail() {}
		void clear() { head = tail = 0; }
		void push(int x) { c[tail++] = x; }
		int front() { return c[head]; }
		void pop() { head++; }
		bool empty() { return head == tail; }
	} q;
	bool BFS()
	{
		ZeroMemory(vis);
		q.clear();
		level[s] = 0;
		vis[s] = true;
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
	INT MaxFlow()
	{
		INT flow = 0;
		while (BFS())
		{
			ZeroMemory(cnt);
			flow += DFS(s, INF);
		}
		return flow;
	}
} nf;

std::vector<std::vector<int> > G;
std::stack<int> seq;
void Euler(INT node)
{
	for (int i = 0; i < G[node].size(); i++)
	{
		int to = G[node][i];
		G[node][i] = 0;
		if (!to) continue;
		Euler(to);
	}
	seq.push(node);
}

void run()
{
	memset(&INF, 0x3f, sizeof(INF));
	INT T = readIn();
	while (T--)
	{
		static bool printed;
		if (printed)
			putchar('\n');
		printed = true;
		ZeroMemory(dd);
		G.clear();

		n = readIn();
		m = readIn();
		nf.init();
		G.resize(n + 1);
		for (int i = 1; i <= m; i++)
		{
			INT from = readIn();
			INT to = readIn();
			char type = getchar();
			while (type != 'U' && type != 'D')
				type = getchar();

			dd[from]++;
			dd[to]--;
			if (type == 'U')
				nf.addEdge(from, to, 1);
			else
				G[from].push_back(to);
		}

		int accum = 0;
		bool bOk = true;
		for (int i = 1; i <= n; i++)
		{
			if (dd[i] % 2)
			{
				puts(NoSolution);
				bOk = false;
				break;
			}
			dd[i] /= 2;
			if (dd[i] > 0)
			{
				accum += dd[i];
				nf.addEdge(nf.s, i, dd[i]);
			}
			else if (dd[i] < 0)
				nf.addEdge(i, nf.t, -dd[i]);
		}
		if (!bOk) continue;

		if (accum != nf.MaxFlow())
		{
			puts(NoSolution);
			continue;
		}

		for (int i = 0; i < nf.edges.size(); i += 2)
		{
			const NetworkFlow::Edge& e = nf.edges[i];
			if (e.from == nf.s || e.to == nf.t)
				continue;
			if (!e.flow)
				G[e.from].push_back(e.to);
			else
				G[e.to].push_back(e.from);
		}

		int ptd = false;
		Euler(1);
		while (!seq.empty())
		{
			if (ptd)
				putchar(' ');
			ptd = true;
			printOut(seq.top());
			seq.pop();
		}
		putchar('\n');
	}
}

int main()
{
	run();
	return 0;
}