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

const INT maxn = 20005;
const INT maxk = 205;
INT INF;
INT n, m, c, q;
INT center[maxk];
INT isCenter[maxn];
struct Graph
{
	struct Edge
	{
		INT to;
		INT cost;
		INT next;
	} edges[maxn];
	INT i;
	INT head[maxn];
	Graph() : i() { memset(head, -1, sizeof(head)); }
	void addEdge(INT from, INT to, INT cost)
	{
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i++;
	}
#define wander(G, node) for(int i = G.head[node]; ~i; i = G.edges[i].next)
#define DEF(G) const Graph::Edge& e = G.edges[i]; INT to = e.to; INT cost = e.cost
} G;
INT dis[maxk][maxn];
struct Queue
{
	INT c[maxn];
	INT head, tail;
	Queue() : head(), tail() {}
	void push(INT x)
	{
		c[tail] = x;
		tail = (tail + 1) % maxn;
	}
	void pop()
	{
		head = (head + 1) % maxn;
	}
	INT front()
	{
		return c[head];
	}
	bool empty()
	{
		return head == tail;
	}
	void clear()
	{
		head = tail = 0;
	}
} queue;
bool inQ[maxn];
void SPFA(const Graph& g, INT* d, INT s)
{
	memset(d, 0x3f, sizeof(INT) * (n + 1));
	d[s] = 0;
	queue.clear();
	queue.push(s);
	while (!queue.empty())
	{
		INT from = queue.front();
		queue.pop();
		inQ[from] = false;
		wander(g, from)
		{
			DEF(g);
			if (d[from] + cost < d[to])
			{
				d[to] = d[from] + cost;
				if (!inQ[to])
				{
					queue.push(to);
					inQ[to] = true;
				}
			}
		}
	}
}

void input()
{
	memset(&INF, 0x3f, sizeof(INF));
	n = readIn();
	m = readIn();
	c = readIn();
	q = readIn();
	for (int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT cost = readIn();
		G.addEdge(from, to, cost);
	}
	for (int i = 1; i <= c; i++)
		isCenter[center[i] = readIn()] = i;
}
void run()
{
	input();
	for (int i = 1; i <= c; i++)
	{
		SPFA(G, dis[i], center[i]);
	}
	INT ans1 = 0, ans2 = 0;
	while (q--)
	{
		INT from = readIn();
		INT To = readIn();
		if (isCenter[from])
		{
			if (dis[isCenter[from]][To] < INF)
			{
				ans1++;
				ans2 += dis[isCenter[from]][To];
			}
			continue;
		}
		INT minVal = INF;
		wander(G, from)
		{
			DEF(G);
			minVal = std::min(minVal, dis[isCenter[to]][To] + cost);
		}
		if (minVal < INF)
		{
			ans1++;
			ans2 += minVal;
		}
	}
	printOut(ans1);
	printOut(ans2);
}

int main()
{
	run();
	return 0;
}