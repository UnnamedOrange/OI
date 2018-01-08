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

const INT maxn = 30005;
INT n;
struct Graph
{
	struct Edge
	{
		INT to;
		INT next;
	} edges[maxn * 2];
	INT i;
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
#define DEF const Graph::Edge& e = G.edges[i]; INT to = e.to
} G;
INT w[maxn];
INT r[maxn];

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{

	}
};
struct work
{
	work()
	{

	}
};

void run()
{
	n = readIn();
	for (int i = 2; i <= n; i++)
	{
		INT from, to;
		G.addEdge(from, to);
		G.addEdge(to, from);
	}
	for (int i = 1; i <= n; i++)
	{
		w[i] = readIn();
		r[i] = readIn();
	}

	if (n <= 10)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("xmastree2.in", "r", stdin);
	freopen("xmastree2.out", "w", stdout);
#endif
	run();
	return 0;
}