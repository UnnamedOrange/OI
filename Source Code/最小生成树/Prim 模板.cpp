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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
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
inline void printOut(INT x)
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
}

const INT maxn = 5005;
const INT maxm = 200005;
INT n, m;
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

struct HeapNode
{
	INT node;
	INT dis;
	bool operator< (const HeapNode& b) const
	{
		return dis > b.dis;
	}
	HeapNode() {}
	HeapNode(INT node, INT dis) : node(node), dis(dis) {}
};

INT ans;
INT count_;
bool vis[maxn];
INT dis[maxn];
void prim()
{
	memset(dis, 0x3f, sizeof(dis));
	dis[1] = 0;
	std::priority_queue<HeapNode> pq;
	pq.push(HeapNode(1, 0));
	while (!pq.empty() && count_ < n)
	{
		HeapNode from = pq.top();
		pq.pop();
		if (vis[from.node]) continue;
		ans += dis[from.node];
		count_++;
		vis[from.node] = true;
		for (int i = head[from.node]; i; i = edges[i].next)
		{
			Edge& e = edges[i];
			INT to = e.to;
			INT cost = e.cost;
			if (!vis[to] && cost < dis[to])
			{
				dis[to] = cost;
				pq.push(HeapNode(to, dis[to]));
			}
		}
	}
	if (count_ != n)
		puts("orz");
	else
		printOut(ans);
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		INT u = readIn();
		INT v = readIn();
		INT c = readIn();
		addEdge(u, v, c);
		addEdge(v, u, c);
	}
	prim();
}

int main()
{
	run();
	return 0;
}
