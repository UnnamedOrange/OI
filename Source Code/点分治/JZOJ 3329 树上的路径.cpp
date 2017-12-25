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

const INT maxn = 50005;
struct Graph
{
	INT i;
	struct Edge
	{
		INT to;
		INT cost;
		INT next;
	} edges[maxn * 2];
	INT head[maxn];
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
#define DEF(G) const Edge& e = G.edges[i]; INT to = e.to; INT cost = e.cost
} G;
typedef Graph::Edge Edge;
INT n, m;

INT size[maxn];
bool vis[maxn];
void DFS(INT node, INT parent)
{
	size[node] = 1;
	wander(G, node)
	{
		DEF(G);
		if (to == parent || vis[to])
			continue;
		DFS(to, node);
		size[node] += size[to];
	}
}
INT getRoot(INT node, INT parent, const INT& s)
{
	wander(G, node)
	{
		DEF(G);
		if (to == parent || vis[to])
			continue;
		if (size[to] > s / 2)
			return getRoot(to, node, s);
	}
	return node;
}
INT dis[maxn];
struct Node
{
	INT node;
	INT dis;
	INT belong;
	Node() : node(), dis(), belong() {}
	Node(INT node, INT dis, INT belong) : node(node), dis(dis), belong(belong) {}
	bool operator<(const Node& b) const
	{
		return dis < b.dis;
	}
};
std::vector<Node> buf[maxn];
void GetBuf(INT node, INT parent, INT belong, std::vector<Node>& buffer)
{
	buffer.push_back(Node(node, dis[node], belong));
	wander(G, node)
	{
		DEF(G);
		if (to == parent || vis[to])
			continue;
		dis[to] = dis[node] + cost;
		GetBuf(to, node, belong ? belong : to, buffer);
	}
}
void solve(INT node)
{
	DFS(node, 0);
	node = getRoot(node, 0, size[node]);
	dis[node] = 0;
	GetBuf(node, 0, 0, buf[node]);
	std::sort(buf[node].begin(), buf[node].end());

	vis[node] = true;
	wander(G, node)
	{
		DEF(G);
		if (vis[to])
			continue;
		solve(to);
	}
}

struct HeapNode
{
	INT root;
	INT l;
	INT r;
	INT dis;
	HeapNode() : root(-1) {}
	HeapNode(INT root, INT l, INT r) : root(root), l(l), r(r), dis(buf[root][l].dis + buf[root][r].dis) {}
	bool operator< (const HeapNode& b) const
	{
		return dis < b.dis;
	}
	HeapNode next()
	{
		INT L = l - 1;
		while (L > 0 && buf[root][L].belong == buf[root][r].belong)
			L--;
		if (L < 0 || buf[root][L].belong == buf[root][r].belong)
			return HeapNode();
		return HeapNode(root, L, r);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 2; i <= n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT cost = readIn();
		G.addEdge(from, to, cost);
		G.addEdge(to, from, cost);
	}

	solve(1);
	std::priority_queue<HeapNode> pq;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j < buf[i].size(); j++)
		{
			HeapNode h(i, j, j);
			h = h.next();
			if (h.root != -1)
				pq.push(h);
		}
	}

	for (int i = 1; i <= m; i++)
	{
		HeapNode h = pq.top();
		pq.pop();
		printOut(h.dis);
		h = h.next();
		if (h.root != -1)
			pq.push(h);
	}

}

int main()
{
	run();
	return 0;
}