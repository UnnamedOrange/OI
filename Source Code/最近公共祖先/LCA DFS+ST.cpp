//LCA DFS+ST
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
	while(!(ch >= '0' && ch <= '9')) ch = getchar();
	while(ch >= '0' && ch <= '9')
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
std::vector<int> vis;
std::vector<int> sequence;
std::vector<int> depth;

struct RMQ
{
	std::vector<std::vector<int> > rmq;
	int N;

	RMQ()
	{
		N = 2 * n - 1;
		int size = 0;
		while(1 << (size + 1) <= N) size++;
		rmq.resize(size + 1);
		for(int i = 0; i <= size; i++)
		{
			rmq[i].resize(N + 1);
		}

		for(int i = 1; i <= N; i++)
		{
			rmq[0][i] = sequence[i];
		}
		for(int k = 1; 1 << k <= N; k++)
		{
			for(int i = 1; i + (1 << k) - 1 <= N; i++)
			{
				if(depth[rmq[k - 1][i]] < depth[rmq[k - 1][i + (1 << (k - 1))]])
					rmq[k][i] = rmq[k - 1][i];
				else
					rmq[k][i] = rmq[k - 1][i + (1 << (k - 1))];
			}
		}
	}

	int query(int x, int y)
	{
		int length = y - x + 1;
		int k = 0;
		while(1 << (k + 1) <= length) k++;
		if(depth[rmq[k][x]] < depth[rmq[k][y - (1 << k) + 1]])
			return rmq[k][x];
		else
			return rmq[k][y - (1 << k) + 1];
	}
};

void dfs(int node, int parent = 0)
{
	vis[node] = sequence.size();
	sequence.push_back(node);
	if(parent && edges[node].size() == 1) //Ò¶½áµã
	{
		return;
	}
	for(int i = 0; i < edges[node].size(); i++)
	{
		int& to = edges[node][i];
		if(to == parent) continue;
		depth[to] = depth[node] + 1;
		dfs(to, node);
		sequence.push_back(node);
	}
}

int main()
{
	int a = readIn();
	while(a--)
	{
		n = readIn();
		edges.clear();
		edges.resize(n + 1);
		isntRoot.clear();
		isntRoot.resize(n + 1);
		for(int i = 1; i <= n - 1; i++)
		{
			int from = readIn();
			int to = readIn();
			isntRoot[to] = true;
			edges[from].push_back(to);
			edges[to].push_back(from);
		}

		int root = 0;
		for(int i = 1; i <= n; i++)
		{
			if(!isntRoot[i])
			{
				root = i;
				break;
			}
		}
		sequence.clear();
		sequence.push_back(0);
		vis.clear();
		vis.resize(n + 1);
		depth.clear();
		depth.resize(n + 1);
		dfs(root);

		RMQ rmq;
		int l = vis[readIn()];
		int r = vis[readIn()];
		if(l > r) std::swap(l, r);
		printf("%d\n", rmq.query(l, r));
	}
	return 0;
}
