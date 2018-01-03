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

const INT maxn = 100005;
INT n;
INT parent[maxn];
INT color[maxn];
struct Graph
{
	INT i;
	struct Edge
	{
		INT to;
		INT next;
	} edges[maxn];
	INT head[maxn];
	void clear()
	{
		i = 0;
		memset(head, 0, sizeof(head));
	}
	Graph()
	{
		clear();
	}
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

INT f[maxn];
void DFS1(INT node)
{
	if (!G.head[node])
	{
		f[node] = color[node];
		if (f[node] == -1)
			f[node] = 0;
		else if (f[node] == 0)
			f[node] = 1;
		else if (f[node] == 1)
			f[node] = -1;
		return;
	}
	wander(G, node)
	{
		DEF(G);
		DFS1(to);
		f[node] += f[to] ? f[to] / std::abs(f[to]) : 0;
	}
}

INT ans[maxn];
void DFS2(INT node)
{
	if (!G.head[node])
	{
		if (color[node] == -1)
			ans[++ans[0]] = node;
		return;
	}
	wander(G, node)
	{
		DEF(G);
		if (f[to] == 0 || f[to] == -1)
			DFS2(to);
	}
}


void run()
{
	INT T = readIn();
	while (T--)
	{
		memset(f, 0, sizeof(f));
		n = readIn();
		for (int i = 1; i <= n; i++)
			parent[i] = readIn();
		for (int i = 1; i <= n; i++)
			color[i] = readIn();

		G.clear();
		for (int i = 2; i <= n; i++)
			G.addEdge(parent[i], i);

		DFS1(1);
		if (f[1] < 0)
		{
			printOut(-1);
			putchar('\n');
			continue;
		}

		ans[0] = 0;
		if (f[1] > 0)
		{
			for (int i = 1; i <= n; i++)
				if (!G.head[i] && color[i] == -1)
					ans[++ans[0]] = i;
		}
		else
		{
			DFS2(1);
			std::sort(ans + 1, ans + 1 + ans[0]);
		}

		printOut(ans[0]);
		for (int i = 1; i <= ans[0]; i++)
		{
			putchar(' ');
			printOut(ans[i]);
		}
		putchar('\n');
	}
}

int main()
{
#ifndef LOCAL
	freopen("rab.in", "r", stdin);
	freopen("rab.out", "w", stdout);
#endif
	run();
	return 0;
}