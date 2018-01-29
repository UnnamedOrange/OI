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

const INT maxn = 1010;
const INT maxm = 5005;
struct Graph
{
	struct Edge
	{
		INT to;
		INT cost;
		INT next;
	} edges[maxm * 2 + maxn * 2];
	INT i;
	INT head[maxn];
	Graph() { clear(); }
	void clear()
	{
		i = 0;
		memset(head, -1, sizeof(head));
	}
	void addEdge(INT from, INT to, INT cost)
	{
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
#define wander(G, node) for(int i = G.head[node]; ~i; i = G.edges[i].next)
#define DEF(G) const Graph::Edge& e = G.edges[i]; INT to = e.to; INT cost = e.cost
} G;
INT n, m, p;

INT INF;
INT f[maxn][1 << 6];
struct Queue
{
	INT c[maxn];
	INT head, tail;
	Queue() : head(), tail() {}
	void clear() { head = tail = 0; }
	bool empty() { return head == tail; }
	INT front() { return c[head]; }
	void pop() { head = (head + 1) % maxn; }
	void push(INT x) { c[tail] = x; tail = (tail + 1) % maxn; }
};
void SPFA(int S)
{
	static bool inQ[maxn];
	static Queue q;
	q.clear();
	for (int i = 0; i <= n + m; i++)
		if (f[i][S] <= INF)
		{
			q.push(i);
			inQ[i] = true;
		}

	while (!q.empty())
	{
		INT from = q.front();
		q.pop();
		inQ[from] = false;
		wander(G, from)
		{
			DEF(G);
			if (f[from][S] + cost < f[to][S])
			{
				f[to][S] = f[from][S] + cost;
				if (!inQ[to])
				{
					q.push(to);
					inQ[to] = true;
				}
			}
		}
	}
}
void SteinerTree()
{
	INT U = 1 << (n + 1);
	memset(f, 0x3f, sizeof(f));
	INF = f[0][0];
	for (int i = 0; i <= n; i++)
		f[i][1 << i] = 0;

	for (int S = 0; S < U; S++)
	{
		for (int i = 0; i <= n + m; i++)
		{
			for (int S0 = (S - 1) & S; S0; S0 = (S0 - 1) & S)
			{
				int S1 = S ^ S0;
				f[i][S] = std::min(f[i][S], f[i][S0] + f[i][S1]);
			}
		}
		SPFA(S);
	}

	INT ans = INF;
	for (int i = 0; i <= n + m; i++)
		ans = std::min(ans, f[i][U - 1]);
	printOut(ans);
}

void run()
{
	while (~scanf("%d%d%d", &n, &m, &p))
	{
		G.clear();
		for (int i = 1; i <= n + m; i++)
		{
			INT cost = readIn();
			G.addEdge(0, i, cost);
			G.addEdge(i, 0, cost);
		}
		for (int i = 1; i <= p; i++)
		{
			INT from = readIn();
			INT to = readIn();
			INT cost = readIn();
			G.addEdge(from, to, cost);
			G.addEdge(to, from, cost);
		}

		SteinerTree();
	}
}

int main()
{
	run();
	return 0;
}