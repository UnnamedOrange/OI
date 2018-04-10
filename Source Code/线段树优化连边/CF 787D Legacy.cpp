#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <functional>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef LL INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar(' ');
}

const int maxn = int(3e5) + 5;
int n, q, s;
struct Edge
{
	int to;
	int cost;
	Edge() {}
	Edge(int to, int cost) : to(to), cost(cost) {}
};
std::vector<std::vector<Edge> > G;

int g_Pos, g_Val, g_L, g_R;
int build1(int l, int r) // 点到区间: 从上往下
{
	if (l == r) return l;
	int mid = (l + r) >> 1;
	int cnt = n + mid;
	G[cnt].push_back(Edge(build1(l, mid), 0));
	G[cnt].push_back(Edge(build1(mid + 1, r), 0));
	return cnt;
}
int build2(int l, int r) // 区间到点: 从下往上
{
	if (l == r) return l;
	int mid = (l + r) >> 1;
	int cnt = n + n - 1 + mid;
	G[build2(l, mid)].push_back(Edge(cnt, 0));
	G[build2(mid + 1, r)].push_back(Edge(cnt, 0));
	return cnt;
}
void link1(int l, int r) // 点到区间
{
	int mid = (l + r) >> 1;
	if (g_L <= l && r <= g_R)
	{
		if (l == r) G[g_Pos].push_back(Edge(l, g_Val));
		else G[g_Pos].push_back(Edge(n + mid, g_Val));
		return;
	}
	if (g_L <= mid) link1(l, mid);
	if (g_R > mid) link1(mid + 1, r);
}
void link2(int l, int r) // 区间到点
{
	int mid = (l + r) >> 1;
	if (g_L <= l && r <= g_R)
	{
		if (l == r) G[l].push_back(Edge(g_Pos, g_Val));
		else G[n + n - 1 + mid].push_back(Edge(g_Pos, g_Val));
		return;
	}
	if (g_L <= mid) link2(l, mid);
	if (g_R > mid) link2(mid + 1, r);
}

LL INF;
LL dis[maxn * 3];
struct HeapNode
{
	int node;
	LL dis;
	HeapNode() {}
	HeapNode(int node, LL dis) : node(node), dis(dis) {}
	bool operator<(const HeapNode& b) const
	{
		return dis > b.dis;
	}
};
void Dijkstra()
{
	memset(&INF, 0x3f, sizeof(INF));
	memset(dis, 0x3f, sizeof(dis));
	std::priority_queue<HeapNode> pq;
	pq.push(HeapNode(s, 0));
	dis[s] = 0;
	while (!pq.empty())
	{
		HeapNode from = pq.top();
		pq.pop();
		if (from.dis != dis[from.node]) continue;
		for (int i = 0; i < G[from.node].size(); i++)
		{
			const Edge& e = G[from.node][i];
			if (dis[from.node] + e.cost < dis[e.to])
			{
				dis[e.to] = dis[from.node] + e.cost;
				pq.push(HeapNode(e.to, dis[e.to]));
			}
		}
	}
}

void run()
{
	n = readIn();
	q = readIn();
	s = readIn();
	G.resize(n * 3);
	build1(1, n);
	build2(1, n);
	for (int i = 1; i <= q; i++)
	{
		int type = readIn();
		if (type == 1)
		{
			int from = readIn();
			int to = readIn();
			int cost = readIn();
			G[from].push_back(Edge(to, cost));
		}
		else if (type == 2)
		{
			g_Pos = readIn();
			g_L = readIn();
			g_R = readIn();
			g_Val = readIn();
			link1(1, n);
		}
		else if (type == 3)
		{
			g_Pos = readIn();
			g_L = readIn();
			g_R = readIn();
			g_Val = readIn();
			link2(1, n);
		}
	}
	Dijkstra();
	for (int i = 1; i <= n; i++)
		if (dis[i] >= INF) printOut(-1);
		else printOut(dis[i]);
}

int main()
{
	run();
	return 0;
}