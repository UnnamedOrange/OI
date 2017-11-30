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

const INT maxn = 10005;
const INT maxm = 100005;
INT n, m;
INT s, t;

struct EdmondsKarp
{
	static const INT INF = ~(INT(1) << (sizeof(INT) * 8 - 1));
	struct Edge
	{
		INT from;
		INT to;
		INT flow;
		INT cap;
		Edge() {}
		Edge(INT u, INT v, INT f, INT c) : from(u), to(v), flow(f), cap(c) {}
	};
	std::vector<Edge> edges;
	std::vector<std::vector<INT> > G;

	EdmondsKarp() : G(n + 1) {}

	inline void addEdge(INT from, INT to, INT cap)
	{
		edges.push_back(Edge(from, to, 0, cap));
		edges.push_back(Edge(to, from, 0, 0));
		G[from].push_back(edges.size() - 2);
		G[to].push_back(edges.size() - 1);
	}

	INT maxFlow()
	{
		INT ans = 0;
		while(true)
		{
			std::vector<INT> a(n + 1);
			std::vector<INT> pre(n + 1); //save the previous edge
			std::queue<INT> q;
			a[s] = INF;
			q.push(s);
			while(!q.empty())
			{
				INT from = q.front();
				q.pop();
				for(int i = 0; i < G[from].size(); i++)
				{
					INT Index = G[from][i];
					Edge& e = edges[Index];
					if(!a[e.to] && e.cap > e.flow)
					{
						pre[e.to] = Index;
						a[e.to] = std::min(a[from], e.cap - e.flow);
						q.push(e.to);
					}
				}
				if(a[t]) break;
			}
			if(!a[t]) break;

			for(int u = t; u != s; u = edges[pre[u]].from)
			{
				edges[pre[u]].flow += a[t];
				edges[pre[u] ^ 1].flow -= a[t];
			}
			ans += a[t];
		}
		return ans;
	}
} ek;

void run()
{
	n = readIn();
	m = readIn();
	s = readIn();
	t = readIn();

	new (&ek) EdmondsKarp;
	for(int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT cap = readIn();
		ek.addEdge(from, to, cap);
	}
	cout << ek.maxFlow() << endl;
}

int main()
{
	run();
	return 0;
}
