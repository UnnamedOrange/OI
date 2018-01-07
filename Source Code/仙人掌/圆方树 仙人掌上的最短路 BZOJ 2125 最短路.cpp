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

const INT maxn = 10005;
INT n, m, q;
struct Graph
{
	INT i;
	struct Edge
	{
		INT from;
		INT to;
		INT cost;
		INT next;
	} edges[maxn * 4];
	INT head[maxn * 2];
	Graph() : i(), head() {}
	void addEdge(INT from, INT to, INT cost)
	{
		i++;
		edges[i].from = from;
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i;
	}
#define wander(G, node) for(int i = G.head[node]; i; i = G.edges[i].next)
#define DEF(G) const Graph::Edge& e = G.edges[i]; INT from = e.from; INT to = e.to; INT cost = e.cost
} cactus, tree;

INT dfn[maxn];
INT low[maxn];
INT N;
INT belong[maxn];
std::stack<Graph::Edge> s;
void Tarjan(INT node, INT parent)
{
	static INT clock;
	clock++;
	low[node] = dfn[node] = clock;
	INT child = 0;
	wander(cactus, node)
	{
		DEF(cactus);
		if (to == parent) continue;
		if (!dfn[to])
		{
			s.push(e);
			child++;
			Tarjan(to, node);
			low[node] = std::min(low[node], low[to]);
			if (low[to] >= dfn[node])
			{
				//找到割顶，就是找到了一个点双连通分量
				N++;
				Graph::Edge x;
				do
				{
					x = s.top();
					s.pop();
					if (belong[x.from] != N)
					{
						tree.addEdge(x.from, N, 0);
						tree.addEdge(N, x.from, 0);
						belong[x.from] = N;
					}
					if (belong[x.to] != N)
					{
						tree.addEdge(x.to, N, 0);
						tree.addEdge(N, x.to, 0);
						belong[x.to] = N;
					}
				} while (!(x.from == e.from && x.to == e.to));
			}
		}
		else if (dfn[to] < dfn[node])
		{
			s.push(e);
			low[node] = std::min(low[node], dfn[to]);
		}
	}
}

void run()
{
	n = readIn();
	m = readIn();
	q = readIn();
	for (int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT cost = readIn();
		cactus.addEdge(from, to, cost);
		cactus.addEdge(to, from, cost);
	}
	N = n;
	Tarjan(1, 0);

	while (q--)
	{
		INT u = readIn();
		INT v = readIn();

	}
}

int main()
{
	run();
	return 0;
}