#pragma GCC optimize("O3")
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
		char buffer[12];
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
INT dfn[maxn];
INT seq[maxn * 2];
INT depth[maxn];
void dfs(INT node, INT parent)
{
	depth[node] = depth[parent] + 1;
	seq[++seq[0]] = node;
	dfn[node] = seq[0];
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		if (to == parent) continue;
		dfs(to, node);
		seq[++seq[0]] = node;
	}
}
INT rmq[20][maxn * 2];
void goRMQ()
{
	INT N = seq[0];
	while (1 << (size + 1) < N) size++;
	for (int i = 1; i <= N; i++)
		rmq[0][i] = seq[i];
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j + (1 << i) - 1 <= N; j++)
		{
			if (depth[rmq[i - 1][j]] <= depth[rmq[i - 1][j + (1 << (i - 1))]])
				rmq[i][j] = rmq[i - 1][j];
			else
				rmq[i][j] = rmq[i - 1][j + (1 << (i - 1))];
		}
	}
}
INT LCA(INT u, INT v)
{
	u = dfn[u];
	v = dfn[v];
	if (u > v) std::swap(u, v);

	INT length = v - u + 1;
	INT k = 0;
	while (1 << (k + 1) < length) k++;
	if (depth[rmq[k][u]] < depth[rmq[k][v - (1 << k) + 1]])
		return rmq[k][u];
	else
		return rmq[k][v - (1 << k) + 1];
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
	dfs(root, 0);
	goRMQ();
	while (m--)
	{
		INT u = readIn();
		INT v = readIn();
		printOut(LCA(u, v));
	}
}

int main()
{
	run();
	return 0;
}
