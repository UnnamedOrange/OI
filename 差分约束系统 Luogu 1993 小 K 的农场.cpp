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
INT n, m;
struct Edge
{
	INT to;
	INT cost;
	Edge() {}
	Edge(INT to, INT cost) : to(to), cost(cost) {}
};
std::vector<std::vector<Edge> > edges;

bool vis[maxn];
INT dis[maxn];
bool DFS(INT node)
{
	vis[node] = true;
	bool bRet = true;
	for(int i = 0; i < edges[node].size(); i++)
	{
		Edge& e = edges[node][i];
		if(dis[node] + e.cost < dis[e.to])
		{
			dis[e.to] = dis[node] + e.cost;
			if(vis[e.to])
			{
				return false;
			}
			else
			{
				bRet = DFS(e.to);
				if(!bRet) return bRet;
			}
		}
	}
	vis[node] = false;
	return bRet;
}

void run()
{
	n = readIn();
	m = readIn();
	edges.resize(n + 1);
	for(int i = 1; i <= m; i++)
	{
		INT ins = readIn();
		INT a = readIn();
		INT b = readIn();
		if(ins == 1)
		{
			INT c = readIn();
			edges[a].push_back(Edge(b, -c));
		}
		else if(ins == 2)
		{
			INT c = readIn();
			edges[b].push_back(Edge(a, c));
		}
		else if(ins == 3)
		{
			edges[a].push_back(Edge(b, 0));
			edges[b].push_back(Edge(a, 0));
		}
	}
	for(int i = 1; i <= n; i++)
	{
		edges[0].push_back(Edge(i, 0));
	}
	memset(dis, 0x3f, sizeof(dis));
	dis[0] = 0;
	bool ans = DFS(0);
	cout << (ans ? "Yes" : "No") << endl;
}

int main()
{
	run();
	return 0;
}
