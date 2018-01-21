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

const INT maxn = 1010;
const INT maxm = 5005;
struct Graph
{
	struct Node
	{
		INT to;
		INT cost;
		INT next;
	} edges[maxm * 2];
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
INT well[maxn];

void run()
{
	while (~scanf("%d%d%d", &n, &m, &p))
	{
		for (int i = 1; i <= n; i++)
			well[i] = readIn();
		for (int i = 1; i <= p; i++)
		{
			INT from = readIn();
			INT to = readIn();
			INT cost = readIn();
			G.addEdge(from, to, cost);
			G.addEdge(to, from, cost);
		}
	}
}

int main()
{
	run();
	return 0;
}