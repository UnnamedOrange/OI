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

const INT maxn = 1005;
const INT maxm = 3005;
const INT maxp = 10;
INT n, m, p;
struct Graph
{
	struct Edge
	{
		INT to;
		INT cost;

		INT next;
	} edges[maxm * 2];
	INT i;
	INT head[maxn];
	void addEdge(INT from, INT to, INT cost)
	{
		i++;
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i;
	}
#define wander(G, node) for(int i = G.head[node]; i; i = G.edges[i].next)
#define DEF(G) const Graph::Edge& e = G.edges[i]; INT to = e.to; INT cost = e.cost
} G;
INT vip[maxp + 5][2]; //0 - channel, 1 - index

INT U;
INT INF;
INT f[maxn][1 << maxp];
INT g[1 << maxp];
struct Queue
{
	INT c[maxn];
	INT head, tail;
	Queue() : head(), tail() {}
	bool empty() { return head == tail; }
	void push(INT x) { c[tail] = x; tail = (tail + 1) % maxn; }
	INT front() { return c[head]; }
	void pop() { head = (head + 1) % maxn; }
};
void SPFA(int S)
{
	static bool inQ[maxn];
	static Queue q;
	for (int i = 1; i <= n; i++)
	{
		if (f[i][S] < INF)
		{
			q.push(i);
			inQ[i] = true;
		}
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
	U = 1 << p;
	memset(f, 0x3f, sizeof(f));
	memset(&INF, 0x3f, sizeof(INF));
	for (int i = 0; i < p; i++)
		f[vip[i][1]][1 << i] = 0;

	for (int S = 0; S < U; S++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int S0 = (S - 1) & S; S0; S0 = (S0 - 1) & S)
			{
				int S1 = S ^ S0;
				f[i][S] = std::min(f[i][S], f[i][S0] + f[i][S1]);
			}
		}
		SPFA(S);
	}
}

int groupMask[maxp];
bool isComplete[1 << maxp];

void init()
{
	for (int S = 0; S < U; S++)
	{
		bool isOk = true;
		for (int i = 0; i < maxp; i++)
		{
			if (!((S & groupMask[i]) == groupMask[i] || !(S & groupMask[i])))
			{
				isOk = false;
				break;
			}
		}
		isComplete[S] = isOk;
	}
}
void run()
{
	n = readIn();
	m = readIn();
	p = readIn();
	for (int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT cost = readIn();
		G.addEdge(from, to, cost);
		G.addEdge(to, from, cost);
	}
	for (int i = 0; i < p; i++)
	{
		vip[i][0] = readIn();
		vip[i][1] = readIn();
		groupMask[vip[i][0] - 1] |= 1 << i;
	}

	SteinerTree();
	memset(g, 0x3f, sizeof(g));
	for (int S = 0; S < U; S++)
		for (int i = 1; i <= n; i++)
			g[S] = std::min(g[S], f[i][S]);

	init();
	for (int S = 0; S < U; S++)
	{
		if (!isComplete[S]) continue;
		for (int S0 = (S - 1) & S; S0; S0 = (S0 - 1) & S)
		{
			int S1 = S ^ S0;
			if (!isComplete[S0]) continue;
			g[S] = std::min(g[S], g[S0] + g[S1]);
		}
	}
	printOut(g[U - 1]);
}

int main()
{
	run();
	return 0;
}