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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1))) >> 1;
const INT maxn = 200005;
const INT maxm = 500005;
INT n, m, k;
struct Edge
{
	INT to;
	INT cost;
	INT next;
} edges[maxm * 2];
INT head[maxn];
void addEdge(INT from, INT to, INT cost)
{
	static INT i;
	i++;
	edges[i].to = to;
	edges[i].cost = cost;
	edges[i].next = head[from];
	head[from] = i;
}

INT dis[maxn];
INT disT[maxn];

struct Node
{
	INT from;
	INT dis;
	Node() {}
	Node(INT from, INT dis) : from(from), dis(dis) {}
	bool operator< (const Node& b) const
	{
		return dis > b.dis;
	}
};
void Dijkstra(INT s, INT* d)
{
	std::fill(d, d + 1 + n, INF);
	d[s] = 0;
	std::priority_queue<Node> q;
	q.push(Node(s, 0));
	while (!q.empty())
	{
		Node node = q.top();
		INT from = node.from;
		q.pop();
		if (node.dis > d[from])
			continue;
		for (int i = head[from]; i; i = edges[i].next)
		{
			Edge& e = edges[i];
			if (d[from] + e.cost < d[e.to])
			{
				d[e.to] = d[from] + e.cost;
				q.push(Node(e.to, d[e.to]));
			}
		}
	}
}

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	for (int i = 1; i < m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT cost = readIn();
		addEdge(from, to, cost);
		addEdge(to, from, cost);
	}
	Dijkstra(1, dis);
	Dijkstra(n, disT);

	INT u = readIn();
	INT v = readIn();
	INT pre = std::min(dis[u] + disT[v], dis[v] + disT[u]);
	while (k--)
	{
		INT t = readIn();
		INT ans = std::min(dis[n], pre + t);
		if (ans >= INF)
			puts("+Inf");
		else
			printOut(ans);
	}
}

int main()
{
#ifndef LOCAL
	freopen("monogatari.in", "r", stdin);
	freopen("monogatari.out", "w", stdout);
#endif
	run();
	return 0;
}