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

const int maxn = 200005;
int n, m;
struct Graph
{
	struct Edge
	{
		int to;
		INT cost;
		int next;
	} edges[maxn];
	int i;
	int head[maxn];
	Graph() : i(), head() {}
	void addEdge(INT from, INT to, INT cost)
	{
		i++;
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i;
	}
#define wander(G, node) for(int i = G.head[node]; i; i = G.edges[i].next)
#define DEF(G) const Graph::Edge& e = G.edges[i]; int to = e.to; INT cost = e.cost
} G, GT;

INT disG[maxn];
INT disGT[maxn];
struct Queue
{
	INT c[maxn];
	INT head, tail;
	Queue() : head(), tail() {}
	void clear() { head = tail = 0; }
	bool empty() { return head == tail; }
	void push(INT x) { c[tail] = x; tail = (tail + 1) % maxn; }
	void pop() { head = (head + 1) % maxn; }
	INT front() { return c[head]; }
} q;
bool inQ[maxn];
void SPFA(const Graph& g, int s, INT dis[maxn])
{
	memset(dis, 0x3f, sizeof(INT) * (n + 1));
	dis[s] = 0;
	q.push(s);
	inQ[s] = true;
	while (!q.empty())
	{
		INT from = q.front(); q.pop();
		inQ[from] = false;
		wander(g, from)
		{
			DEF(g);
			if (dis[to] > dis[from] + cost)
			{
				dis[to] = dis[from] + cost;
				if (!inQ[to])
				{
					q.push(to);
					inQ[to] = true;
				}
			}
		}
	}
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT cost = readIn();
		G.addEdge(from, to, cost);
		GT.addEdge(to, from, cost);
	}

	SPFA(G, 1, disG);
	SPFA(GT, n, disGT);

	printOut(disG[n]);
	INT ans = disG[n];
	for (int from = 1; from <= n; from++)
	{
		wander(G, from)
		{
			DEF(G);
			ans = std::min(ans, disG[from] + disGT[e.to]);
		}
	}
	printOut(ans);
}

int main()
{
#ifndef LOCAL
	freopen("wander.in", "r", stdin);
	freopen("wander.out", "w", stdout);
#endif
	run();
	return 0;
}
