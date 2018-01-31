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
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1))) >> 1;
const INT maxn = 505;
const INT maxm = 100005;
INT n, N, m;

struct E
{
	INT to;
	INT cost;
	E() {}
	E(INT to, INT cost) : to(to), cost(cost) {}
};
std::vector<std::vector<E> > es;

struct Edge
{
	INT from;
	INT to;
	INT flow;
	INT cap;

	Edge() {}
	Edge(INT from, INT to, INT cap) : from(from), to(to), flow(), cap(cap) {}
};
std::vector<Edge> edges;
std::vector<std::vector<INT> > G;
void addEdge(INT from, INT to, INT cap)
{
	edges.push_back(Edge(from, to, cap));
	edges.push_back(Edge(to, from, 0));
	INT s = edges.size();
	G[from].push_back(s - 2);
	G[to].push_back(s - 1);
}

INT s, t;

INT dis[maxn];
void SPFA_INIT()
{
	memset(dis, 0x3f, sizeof(dis));
	dis[1] = 0;

	std::queue<INT> q;
	std::vector<bool> inQ(n + 1);
	q.push(1);
	inQ[1] = true;
	while (!q.empty())
	{
		INT from = q.front();
		q.pop();
		inQ[from] = false;

		for (int i = 0; i < es[from].size(); i++)
		{
			E& e = es[from][i];
			INT to = e.to;
			INT cost = e.cost;
			if (dis[to] > dis[from] + cost)
			{
				dis[to] = dis[from] + cost;
				if (!inQ[to])
				{
					inQ[to] = true;
					q.push(to);
				}
			}
		}
	}
}
void SPFA_BUILD()
{
	std::queue<INT> q;
	std::vector<bool> inQ(n + 1);
	q.push(1);
	inQ[1] = true;
	while (!q.empty())
	{
		INT from = q.front();
		q.pop();
		inQ[from] = false;

		for (int i = 0; i < es[from].size(); i++)
		{
			E& e = es[from][i];
			INT to = e.to;
			INT cost = e.cost;
			if (dis[to] == dis[from] + cost)
			{
				addEdge(from * 2, to * 2 - 1, INF);
				if (!inQ[to])
				{
					inQ[to] = true;
					q.push(to);
				}
			}
		}
	}
}

INT EdmondKarps(INT s, INT t)
{
	std::vector<INT> pre(N + 1);
	std::vector<INT> opt(N + 1);

	std::queue<INT> q;
	opt[s] = INF;
	q.push(s);

	while (!q.empty())
	{
		INT from = q.front();
		q.pop();
		for (int i = 0; i < G[from].size(); i++)
		{
			Edge& e = edges[G[from][i]];
			if (e.flow < e.cap && !opt[e.to])
			{
				opt[e.to] = std::min(opt[from], e.cap - e.flow);
				pre[e.to] = G[from][i];
				q.push(e.to);
			}
		}
		if (opt[t]) break;
	}

	if (!opt[t]) return 0;
	for (int i = t; i != s; i = edges[pre[i]].from)
	{
		edges[pre[i]].flow += opt[t];
		edges[pre[i] ^ 1].flow -= opt[t];
	}
	return opt[t];
}

INT MaxFlow()
{
	INT s = 2;
	INT t = 2 * n - 1;
	INT flow = 0;

	while (INT f = EdmondKarps(s, t)) flow += f;
	return flow;
}

void run()
{
	n = readIn();
	m = readIn();
	N = n << 1;
	es.resize(n + 1);
	G.resize(N + 1);

	for (int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT cost = readIn();
		es[from].push_back(E(to, cost));
		es[to].push_back(E(from, cost));
	}
	SPFA_INIT();
	SPFA_BUILD();

	for (int i = 1; i <= n; i++)
	{
		INT cap = readIn();
		addEdge(i * 2 - 1, i * 2, cap);
		addEdge(i * 2, i * 2 - 1, cap);
	}

	cout << MaxFlow() << endl;
}

int main()
{
#ifndef JUDGE
	freopen("network.in", "r", stdin);
	freopen("network.out", "w", stdout);
#endif
	run();
	return 0;
}
