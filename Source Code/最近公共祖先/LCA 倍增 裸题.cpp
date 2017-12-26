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
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[8];
		INT length = 0;
		while (x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		do
		{
			putchar(buffer[--length]);
		} while (length);
	}
	putchar('\n');
}

const INT maxn = 500005;
INT n, m, root;

struct Edge
{
	INT to;

	INT next;
} edges[maxn * 2];
INT head[maxn];
void addEdge(INT from, INT to)
{
	static INT i = 0;
	i++;
	edges[i].to = to;
	edges[i].next = head[from];
	head[from] = i;
}

INT size;
INT depth[maxn];
INT parent[20][maxn];

void dfs(INT node)
{
	depth[node] = depth[parent[0][node]] + 1;
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		if (to == parent[0][node]) continue;
		parent[0][to] = node;
		dfs(to);
	}
}
void goDouble()
{
	while (1 << size < n) size++;
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			parent[i][j] = parent[i - 1][parent[i - 1][j]];
		}
	}
}

INT LCA(INT u, INT v)
{
	if (depth[u] < depth[v]) std::swap(u, v);
	for (int i = size; ~i; i--)
	{
		if (depth[parent[i][u]] < depth[v]) continue;
		u = parent[i][u];
	}
	if (u != v)
	{
		for (int i = size; ~i; i--)
		{
			if (parent[i][u] == parent[i][v]) continue;
			u = parent[i][u];
			v = parent[i][v];
		}
		u = parent[0][u];
	}
	return u;
}

void run()
{
	n = readIn();
	m = readIn();
	root = readIn();
	for (int i = 1; i < n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		addEdge(from, to);
		addEdge(to, from);
	}
	dfs(root);
	goDouble();

	while (m--)
	{
		printOut(LCA(readIn(), readIn()));
	}
}

int main()
{
	run();
	return 0;
}
