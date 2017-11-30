//LCA Tarjan
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
using std::cin;
using std::cout;
using std::endl;
inline int readIn()
{
	int a = 0;
	char ch = getchar();
	while (!(ch >= '0' && ch <= '9')) ch = getchar();
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	return a;
}

int n;
std::vector<std::vector<int> > edges;
std::vector<bool> isntRoot;
struct ASK
{
	int u;
	int v;
	int ans;
} ask[1];

struct DS
{
	std::vector<int> parent;

	void rebuild()
	{
		parent.clear();
		parent.resize(n + 1);
		for (int i = 1; i <= n; i++)
		{
			parent[i] = i;
		}
	}

	int find(int x)
	{
		if (x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}

	void unite(int x, int y)
	{
		int px = find(x);
		int py = find(y);
		parent[py] = px;
	}
} ds;

std::vector<bool> vis;
void Tarjan(int node, int parent = 0)
{
	vis[node] = true;
	for (int i = 0; i < edges[node].size(); i++)
	{
		int& to = edges[node][i];
		if (to == parent) continue;
		Tarjan(to, node);
		ds.unite(node, to);
	}
	for (int i = 0; i < 1; i++)
	{
		if (!ask[i].ans)
		{
			if (node == ask[i].u && vis[ask[i].v])
			{
				ask[i].ans = ds.find(ask[i].v);
			}
			else if (node == ask[i].v && vis[ask[i].u])
			{
				ask[i].ans = ds.find(ask[i].u);
			}
		}
	}
}

int main()
{
	int a = readIn();
	while (a--)
	{
		n = readIn();
		edges.clear();
		edges.resize(n + 1);
		isntRoot.clear();
		isntRoot.resize(n + 1);
		for (int i = 1; i <= n - 1; i++)
		{
			int from = readIn();
			int to = readIn();
			isntRoot[to] = true;
			edges[from].push_back(to);
			edges[to].push_back(from);
		}
		ask[0].u = readIn();
		ask[0].v = readIn();
		ask[0].ans = 0;

		int root = 0;
		for (int i = 1; i <= n; i++)
		{
			if (!isntRoot[i])
			{
				root = i;
				break;
			}
		}
		ds.rebuild();
		vis.clear();
		vis.resize(n + 1);
		Tarjan(root);
		printf("%d\n", ask[0].ans);
	}
	return 0;
}
