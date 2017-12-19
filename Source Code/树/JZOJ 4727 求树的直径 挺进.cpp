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
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = INT(1e5) + 5;
INT n;
struct Graph
{
	INT count_;
	struct Edge
	{
		INT to;
		INT cost;
		INT next;
	} edges[maxn * 2];
	INT head[maxn];
	Graph() : count_(), head() {}
	void addEdge(INT from, INT to, INT cost)
	{
		count_++;
		edges[count_].to = to;
		edges[count_].cost = cost;
		edges[count_].next = head[from];
		head[from] = count_;
	}
#define wander(G, v) for(int i = G.head[v]; i; i = G.edges[i].next)
} G;
typedef Graph::Edge Edge;

void update3(INT l, INT w, INT node, INT length[][3], INT who[][3])
{
	if (l > length[node][2])
	{
		if (l > length[node][1])
		{
			if (l > length[node][0])
			{
				length[node][2] = length[node][1];
				who[node][2] = who[node][1];
				length[node][1] = length[node][0];
				who[node][1] = who[node][0];
				length[node][0] = l;
				who[node][0] = w;
			}
			else
			{
				length[node][2] = length[node][1];
				who[node][2] = who[node][1];
				length[node][1] = l;
				who[node][1] = w;
			}
		}
		else
		{
			length[node][2] = l;
			who[node][2] = w;
		}
	}
}

INT parent[maxn];
INT pCost[maxn];
INT length[maxn][3];
INT who[maxn][3];
INT d[maxn];
void DFS1(INT node)
{
	wander(G, node)
	{
		const Edge& e = G.edges[i];
		INT to = e.to;
		if (to == parent[node]) continue;
		parent[to] = node;
		INT cost = e.cost;
		pCost[to] = cost;
		DFS1(to);
		d[node] = std::max(d[node], d[to]);

		INT t = length[to][0] + cost;
		update3(t, to, node, length, who);
	}
	d[node] = std::max(d[node], length[node][0] + length[node][1]);
}
INT length2[maxn][3];
INT who2[maxn][3];
INT d2[maxn][3];
INT where[maxn][3];
void DFS2(INT node)
{
	if (node != 1)
	{
		INT l = length2[parent[node]][0];
		INT w = who2[parent[node]][0];
		if (w == node)
		{
			l = length2[parent[node]][1];
			w = who2[parent[node]][1];
		}
		l += pCost[node];
		update3(l, w, node, length2, who2);

		w = parent[node];
		//d2 实际上只需要最大和次大，这里只是为了方便，定义成了保存前三大
		if (where[w][0] != node)
			update3(d2[w][0], where[w][0], node, d2, where);
		if (where[w][1] != node)
			update3(d2[w][1], where[w][1], node, d2, where);

		if (who2[w][0] == node)
			l = length2[w][1] + length2[w][2];
		else if (who2[w][1] == node)
			l = length2[w][0] + length2[w][2];
		else
			l = length2[w][0] + length2[w][1];
		update3(l, w, node, d2, where);
	}
	wander(G, node)
	{
		const Edge& e = G.edges[i];
		INT to = e.to;
		if (to != parent[node])
			update3(d[to], to, node, d2, where);
	}
	wander(G, node)
	{
		const Edge& e = G.edges[i];
		INT to = e.to;
		if (to != parent[node]) DFS2(to);
	}
}

void run()
{
	n = readIn();
	for (int i = 2; i <= n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT cost = readIn();
		G.addEdge(from, to, cost);
		G.addEdge(to, from, cost);
	}

	DFS1(1);
	memcpy(length2, length, sizeof(length2));
	memcpy(who2, who, sizeof(who2));
	DFS2(1);

	INT ans = 0;
	for (int i = 2; i <= n; i++)
	{
		INT temp = 0;
		INT p = parent[i];
		if (i == who2[p][0])
			temp = length2[p][1] + length2[p][2];
		else if (i == who2[p][1])
			temp = length2[p][0] + length2[p][2];
		else
			temp = length2[p][0] + length2[p][1];

		if (i == where[p][0])
			temp = std::max(temp, d2[p][1]);
		else if (i == where[p][1])
			temp = std::max(temp, d2[p][0]);

		temp += d[i];
		ans = std::max(ans, temp);
	}
	printOut(ans);
}

int main()
{
	run();
	return 0;
}