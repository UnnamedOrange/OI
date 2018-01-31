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
typedef long long INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9')))
		ch = getchar();
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
	if (minus)
		a = -a;
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
const INT maxn = 505;
INT n;
INT W;
INT p, q;
const INT maxp = 1005;
struct P
{
	INT x, y, z, a, b, c, d, e, f;
	void read()
	{
		x = readIn();
		y = readIn();
		z = readIn();
		a = readIn();
		b = readIn();
		c = readIn();
		d = readIn();
		e = readIn();
		f = readIn();
	}
	INT calc(INT set)
	{
		INT wx = (set & (1 << (x - 1))) ? W : -W;
		INT wy = (set & (1 << (y - 1))) ? W : -W;
		INT wz = (set & (1 << (z - 1))) ? W : -W;
		return a * std::abs(wx - wy) +
			b * std::abs(wy - wz) +
			c * std::abs(wz - wx) +
			d * (wx - wy) + e * (wy - wz) + f * (wz - wx);
	}
} ps[maxp];
struct Q
{
	INT x, y, r;
	void read()
	{
		x = readIn();
		y = readIn();
		r = readIn();
	}
	bool check(INT set)
	{
		INT wx = (set & (1 << (x - 1))) ? W : -W;
		INT wy = (set & (1 << (y - 1))) ? W : -W;
		if (r == 0)
			return wx <= wy;
		else if (r == 1)
			return wx == wy;
		else if (r == 2)
			return wx < wy;
	}
} qs[maxp];

#define RunInstance(x) delete new x
struct brute
{
	static INT sigmaW(INT set)
	{
		INT ret = 0;
		for (int i = 0; i < n; i++)
			ret += ((set & (1 << i)) ? W : -W);
		return ret;
	}
	brute()
	{
		INT ans = INF;
		INT U = 1 << n;
		for (int S = 0; S < U; S++)
		{
			bool bOk = true;
			for (int i = 1; i <= q; i++)
			{
				if (!qs[i].check(S))
				{
					bOk = false;
					break;
				}
			}
			if (!bOk) continue;
			INT sum = sigmaW(S);
			for (int i = 1; i <= p; i++)
				sum += ps[i].calc(S);
			ans = std::min(ans, sum);
		}
		printOut(ans);
	}
};
struct work
{
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
			G.resize(n + 2);
			s = 0;
			t = n + 1;
		}
		void addEdge(INT from, INT to, INT cap)
		{
			edges.push_back(Edge(from, to, cap));
			edges.push_back(Edge(to, from, 0));
			int i = edges.size();
			G[from].push_back(i - 2);
			G[to].push_back(i - 1);
		}

		INT level[maxn];
		INT cnt[maxn];
		INT DFS(INT node, INT opt)
		{
			if (!opt || node == t)
				return opt;
			INT flow = 0;
			for (INT& i = cnt[node]; i < G[node].size(); i++)
			{
				Edge& e = edges[G[node][i]];
				INT f;
				if (level[node] + 1 == level[e.to] && (f = DFS(e.to, std::min(opt, e.cap - e.flow))))
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
			INT c[maxn];
			INT head, tail;
			Queue() : head(), tail() {}
			void clear() { head = tail = 0; }
			bool empty() { return head == tail; }
			void push(INT x) { c[tail++] = x; }
			void pop() { head++; }
			INT front() { return c[head]; }
		} q;
		bool BFS()
		{
			memset(vis, 0, sizeof(vis));
			q.clear();
			vis[s] = true;
			q.push(s);
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
	};
	static NetworkFlow nf;
	INT sum[maxn];
	work()
	{
		std::fill(sum, sum + maxn, 1);
		nf.init();
		for (int i = 1; i <= q; i++)
		{
			if (qs[i].r == 0)
			{
				nf.addEdge(qs[i].y, qs[i].x, INF);
			}
			else if (qs[i].r == 1)
			{
				nf.addEdge(qs[i].x, qs[i].y, INF);
				nf.addEdge(qs[i].y, qs[i].x, INF);
			}
			else if (qs[i].r == 2)
			{
				nf.addEdge(nf.s, qs[i].x, INF);
				nf.addEdge(qs[i].y, nf.t, INF);
			}
		}

		for (int i = 1; i <= p; i++)
		{
			nf.addEdge(ps[i].x, ps[i].y, 2 * ps[i].a);
			nf.addEdge(ps[i].y, ps[i].x, 2 * ps[i].a);
			nf.addEdge(ps[i].y, ps[i].z, 2 * ps[i].b);
			nf.addEdge(ps[i].z, ps[i].y, 2 * ps[i].b);
			nf.addEdge(ps[i].x, ps[i].z, 2 * ps[i].c);
			nf.addEdge(ps[i].z, ps[i].x, 2 * ps[i].c);
			sum[ps[i].x] += ps[i].d - ps[i].f;
			sum[ps[i].y] += ps[i].e - ps[i].d;
			sum[ps[i].z] += ps[i].f - ps[i].e;
		}

		for (int i = 1; i <= n; i++)
			if (sum[i] > 0)
				nf.addEdge(nf.s, i, 2 * sum[i]);
			else if (sum[i] < 0)
				nf.addEdge(i, nf.t, -2 * sum[i]);

		INT ans = nf.MaxFlow();
		for (int i = 1; i <= n; i++)
			ans -= std::abs(sum[i]);
		printOut(W * ans);
	}
};
work::NetworkFlow work::nf;

void run()
{
	memset(&INF, 0x3f, sizeof(INT));
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		W = readIn();
		p = readIn();
		q = readIn();
		for (int i = 1; i <= p; i++)
			ps[i].read();
		for (int i = 1; i <= q; i++)
			qs[i].read();

		if (n <= 15)
			RunInstance(brute);
		else
			RunInstance(work);
	}
}

int main()
{
#ifndef LOCAL
	freopen("variable.in", "r", stdin);
	freopen("variable.out", "w", stdout);
#endif
	run();
	return 0;
}