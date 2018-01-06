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
	while(!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if(ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if(minus) a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	if(x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
	}
	while(x /= 10);
	do
	{
		putchar(buffer[--length]);
	}
	while(length);
	putchar('\n');
}

const INT maxn = 100005;
INT n, q, T;
INT color[maxn];
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
INT end[maxn];
INT seq[maxn];
void DFS(INT node, INT parent)
{
	static INT dfsClock;
	dfsClock++;
	dfn[node] = dfsClock;
	seq[dfsClock] = node;
	wander(G, node)
	{
		DEF(G);
		if(to == parent) continue;
		DFS(to, node);
	}
	end[node] = dfsClock;
}
INT lastAns;

#define RunInstance(x) delete new x
struct brute
{
	bool appear[maxn];
	INT buf[maxn];
	brute() : appear(), buf()
	{
		while(q--)
		{
			INT ins = readIn();
			if(ins == 1)
			{
				INT u = readIn();
				INT l = readIn();
				INT r = readIn();
				if(T)
				{
					u ^= lastAns;
					l ^= lastAns;
					r ^= lastAns;
				}
				INT ans = 0;
				for(int i = dfn[u]; i <= end[u]; i++)
				{
					INT c = color[seq[i]];
					if(l <= c && c <= r && !appear[c])
					{
						appear[c] = true;
						ans++;
						buf[++buf[0]] = c;
					}
				}
				while(buf[0]) appear[buf[buf[0]--]] = false;
				printOut(lastAns = ans);
			}
			else if(ins == 2)
			{
				INT u = readIn();
				INT c = readIn();
				if(T)
				{
					u ^= lastAns;
					c ^= lastAns;
				}
				color[u] = c;
			}
		}
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
	q = readIn();
	T = readIn();
	for(int i = 1; i <= n; i++)
		color[i] = readIn();
	for(int i = 2; i <= n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		G.addEdge(from, to);
		G.addEdge(to, from);
	}
	DFS(1, 0);

	if(n <= 5000 && q <= 5000)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("xmastree1.in", "r", stdin);
	freopen("xmastree1.out", "w", stdout);
#endif
	run();
	return 0;
}
