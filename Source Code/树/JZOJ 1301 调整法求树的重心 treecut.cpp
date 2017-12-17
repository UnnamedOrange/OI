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
#include <list>
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = INT(1e5) + 5;
INT n;
struct Graph
{
	INT count_;
	struct Edge
	{
		INT to;
		INT next;
	} edges[maxn * 2];
	INT head[maxn];
	Graph() : count_(), head() {}
	void addEdge(INT from, INT to)
	{
		count_++;
		edges[count_].to = to;
		edges[count_].next = head[from];
		head[from] = count_;
	}
} G;
typedef Graph::Edge Edge;

INT parent[maxn];
INT size[maxn];
void DFS(INT node)
{
	size[node] = 1;
	for (int i = G.head[node]; i; i = G.edges[i].next)
	{
		const Edge& e = G.edges[i];
		INT to = e.to;
		if (to == parent[node])
			continue;
		parent[to] = node;
		DFS(to);
		size[node] += size[to];
	}
}

INT adjust(INT root)
{
	INT maxIdx = 0;
	for (int i = G.head[root]; i; i = G.edges[i].next)
	{
		const Edge& e = G.edges[i];
		INT to = e.to;
		if (to == parent[root])
			continue;
		if (size[to] > n / 2)
		{
			maxIdx = to;
			break;
		}
	}
	return maxIdx;
}

void run()
{
	n = readIn();
	for (int i = 2; i <= n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		G.addEdge(from, to);
		G.addEdge(to, from);
	}

	DFS(1);
	INT center = 1;
	while (INT t = adjust(center))
		center = t;

	INT center2 = 0;
	if (!(n & 1))
	{
		for (int i = G.head[center]; i; i = G.edges[i].next)
		{
			const Edge& e = G.edges[i];
			INT to = e.to;
			if (to == parent[center])
				continue;
			if (size[to] == n / 2)
			{
				center2 = to;
				break;
			}
		}
		//center 是从上往下找过来的，所以不用找父结点
		if (center2 && center > center2)
			std::swap(center, center2);
	}
	printOut(center);
	if (center2)
		printOut(center2);
}

int main()
{
	run();
	return 0;
}