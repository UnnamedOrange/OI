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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = 1000005;
INT n, m;
struct Graph
{
	INT i;
	struct Edge
	{
		INT to;
		INT next;
	} edges[maxn];
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
} G, G2;

INT clock_;
INT dfn[maxn];
INT low[maxn];
INT stack[maxn];
bool inStack[maxn];
INT N;
INT belong[maxn];
INT x[maxn];
void Tarjan(INT node)
{
	clock_++;
	dfn[node] = low[node] = clock_;
	stack[++stack[0]] = node;
	inStack[node] = true;
	wander(G, node)
	{
		DEF(G);
		if (!dfn[to])
		{
			Tarjan(to);
			low[node] = std::min(low[node], low[to]);
		}
		else if (inStack[to])
		{
			low[node] = std::min(low[node], dfn[to]);
		}
	}
	if (dfn[node] == low[node])
	{
		N++;
		INT top;
		do
		{
			top = stack[stack[0]--];
			inStack[top] = false;
			belong[top] = N;
			x[N]++;
		} while (top != node);
	}
}

void rebuild()
{
	for (int from = 1; from <= n; from++)
	{
		wander(G, from)
		{
			DEF(G);
			if (belong[from] != belong[to])
				G2.addEdge(belong[from], belong[to]);
		}
	}
}

INT f[maxn];
INT dp(INT node)
{
	INT& ans = f[node];
	if (ans != -1)
		return ans;
	ans = x[node];
	wander(G2, node)
	{
		DEF(G2);
		ans = std::max(ans, x[node] + dp(to));
	}
	return ans;
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
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			Tarjan(i);

	rebuild();

	memset(f, -1, sizeof(f));
	INT ans = 0;
	for (int i = 1; i <= N; i++)
		ans = std::max(ans, dp(i));
	printOut(ans);
}

int main()
{
#ifndef LOCAL
	freopen("bomb.in", "r", stdin);
	freopen("bomb.out", "w", stdout);
#endif
	run();
	return 0;
}