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
}

LL INF;
const int maxn = 105;
const int maxk = 1005;
int n, m, k;
int b[maxn][maxk];
int s[maxn][maxk];

struct Graph
{
	struct Edge
	{
		int to;
		double cost;
		int next;
	} edges[maxn * maxn];
	int i;
	int head[maxn];
	Graph() : i() { memset(head, -1, sizeof(head)); }
	void addEdge(int from, int to, double cost)
	{
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
	void clear()
	{
		i = 0;
		memset(head, -1, sizeof(head));
	}
#define idx(G) idx_##G
#define wander(G, node) for (int idx(G) = G.head[node]; ~idx(G); idx(G) = G.edges[idx(G)].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx(G)]; int to = e.to; double cost = e.cost
} G;

LL earn[maxn][maxn];
double path[maxn][maxn];

struct Queue
{
	int c[maxn];
	int head, tail;
	void clear() { head = tail = 0; }
	Queue() { clear(); }
	void push(int x) { c[tail] = x; tail = tail + 1 >= maxn ? 0 : tail + 1; }
	void pop() { head = head + 1 >= maxn ? 0 : head + 1; }
	int front() { return c[head]; }
	bool empty() { return head == tail; }
} q;
bool inQ[maxn];
int enter[maxn];
bool SPFA(const Graph& G, int s, double dis[maxn])
{
	memset(inQ, false, sizeof(inQ));
	memset(enter, 0, sizeof(enter));
	std::fill(dis, dis + 1 + n, 1e20);
	q.clear();
	q.push(s);
	inQ[s] = true;
	dis[s] = 0;
	enter[s] = 1;
	while (!q.empty())
	{
		int from = q.front();
		q.pop();
		inQ[from] = false;
		wander(G, from)
		{
			DEF(G);
			if (dis[from] + cost < dis[to])
			{
				dis[to] = dis[from] + cost;
				if (++enter[to] >= n) return true;
				if (!inQ[to])
				{
					q.push(to);
					inQ[to] = true;
				}
			}
		}
	}
	return false;
}

Graph T;
double dis[maxn];
bool check(double s)
{
	T.clear();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i != j)
				T.addEdge(i, j, -(earn[i][j] - path[i][j] * s));

	return SPFA(T, 1, dis);
}

void run()
{
	memset(&INF, 0x3f, sizeof(INF));

	n = readIn();
	m = readIn();
	k = readIn();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k; j++)
		{
			b[i][j] = readIn();
			s[i][j] = readIn();
		}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			LL& t = earn[i][j];
			t = 0;
			for (int l = 1; l <= k; l++)
				if (b[i][l] != -1 && s[j][l] != -1)
					t = std::max(t, (LL)s[j][l] - b[i][l]);
		}
	}

	for (int i = 1; i <= m; i++)
	{
		int from = readIn();
		int to = readIn();
		int cost = readIn();
		G.addEdge(from, to, cost);
	}

	for (int i = 1; i <= n; i++)
		SPFA(G, i, path[i]);

	double l = 0, r = 1e11;
	while (r - l >= 1e-2)
	{
		double mid = (l + r) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}
	printOut(r);
}

int main()
{
	run();
	return 0;
}