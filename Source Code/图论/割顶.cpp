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

const INT maxn = 100005;
INT n, m;
struct Graph
{
	INT i;
	struct Edge
	{
		INT to;
		INT next;
	} edges[maxn * 2];
	INT head[maxn];
	Graph() : i(), head() {}
	void addEdge(INT from, INT to)
	{
		i++;
		edges[i].to = to;
		edges[i].next = head[from];
		head[from] = i;
	}
#define wander(G, node) for(int i = G.head[node]; i; i = G.edges[i].next)
#define DEF(G) const Graph::Edge& e = G.edges[i]; INT to = e.to
} G;

INT dfn[maxn];
INT low[maxn];
bool isCut[maxn];
void DFS(INT node, INT parent)
{
	static INT clock;
	clock++;
	low[node] = dfn[node] = clock;
	INT child = 0;
	wander(G, node)
	{
		DEF(G);
		if (to == parent) continue;
		if (!dfn[to])
		{
			child++;
			DFS(to, node);
			low[node] = std::min(low[node], low[to]);
			if (low[to] >= dfn[node])
				isCut[node] = true;
		}
		else if (dfn[to] < dfn[node])
			low[node] = std::min(low[node], dfn[to]);
	}
	if (!parent && child == 1)
		isCut[node] = false;
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		G.addEdge(from, to);
		G.addEdge(to, from);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			DFS(i, 0);

	INT ans = 0;
	for (int i = 1; i <= n; i++)
		if (isCut[i])
			ans++;
	printOut(ans);
	putchar('\n');
	for (int i = 1; i <= n; i++)
		if (isCut[i])
		{
			printOut(i);
			putchar(' ');
		}
}

int main()
{
	run();
	return 0;
}