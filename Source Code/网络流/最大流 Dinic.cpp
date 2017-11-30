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
typedef int INT;
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
INT n, m, s, t;
struct Dinic
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
	inline void addEdge(INT from, INT to, INT cap)
	{
		edges.push_back(Edge(from, to, 0, cap));
		edges.push_back(Edge(to, from, 0, 0));
		G[from].push_back(edges.size() - 2);
		G[to].push_back(edges.size() - 1);
	}

	Dinic() : G(n + 1) {}

	bool vis[maxn];
	INT level[maxn];
	INT cnt[maxn];

	bool BFS()
	{
		memset(vis, 0, sizeof(vis));
		std::queue<INT> q;
		q.push(s);
		level[s] = 0;
		vis[s] = true;
		while(!q.empty())
		{
			INT from = q.front();
			q.pop();
			for(int i = 0; i < G[from].size(); i++)
			{
				Edge& e = edges[G[from][i]];
				if(!vis[e.to] && e.flow < e.cap)
				{
					level[e.to] = level[from] + 1;
					vis[e.to] = true;
					q.push(e.to);
				}
			}
		}
		return vis[t];
	}

	INT DFS(INT from, INT minCap = INF)
	{
		if(from == t || !minCap) return minCap;
		INT flow = 0;
		for(INT& i = cnt[from]; i < G[from].size(); i++)
		{
			Edge& e = edges[G[from][i]];
			INT f;
			if(level[e.to] == level[from] + 1 && (f = DFS(e.to, std::min(minCap, e.cap - e.flow)) > 0))
			{
				e.flow += f;
				edges[G[from][i] ^ 1].flow -= f;
				flow += f;
				minCap -= f;
				if(!minCap) break;
			}
		}
		return flow;
	}

	INT maxFlow()
	{
		INT ans = 0;
		while(BFS())
		{
			memset(cnt, 0, sizeof(cnt));
			ans += DFS(s);
		}
		return ans;
	}

} dinic;

void run()
{
	n = readIn();
	m = readIn();
	s = readIn();
	t = readIn();

	new (&dinic) Dinic;
	for(int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT cap = readIn();
		dinic.addEdge(from, to, cap);
	}
	cout << dinic.maxFlow() << endl;
}

int main()
{
	run();
	return 0;
}
