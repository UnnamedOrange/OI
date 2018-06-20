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
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = LL;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-'))
		ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = int(2.5e5) + 5;
int n;
int a[maxn], b[maxn];
struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxn * 2];
	int i;
	int head[maxn * 2];
	int size[maxn * 2];
	Graph() : i(), size() { std::memset(head, -1, sizeof(head)); }
	void addEdge(int from, int to)
	{
		size[from]++;
		edges[i].to = to;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
#define idx(G) idx_##G
#define wander(G, node) for (int idx(G) = G.head[node]; ~idx(G); idx(G) = G.edges[idx(G)].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx(G)]; int to = e.to
};

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		int U = 1 << n;
		LL ans = 0;
		for (int S = 0; S < U; S++)
		{
			int t[10];
			for (int i = 0; i < n; i++)
				if (S & (1 << i))
					t[i] = a[i + 1];
				else
					t[i] = b[i + 1];
			std::sort(t, t + n);
			if (std::unique(t, t + n) != t + n)
				continue;
			LL sum = 0;
			for (int i = 0; i < n; i++)
				if (S & (1 << i))
					sum += b[i + 1];
				else
					sum += a[i + 1];
			ans = std::max(ans, sum);
		}
		printOut(ans);
	}
};
struct work
{
	int bound;
	int disc[maxn * 2];
	void discretize()
	{
		for (int i = 1; i <= n; i++)
		{
			disc[++bound] = a[i];
			disc[++bound] = b[i];
		}
		std::sort(disc + 1, disc + 1 + bound);
		bound = std::unique(disc + 1, disc + 1 + bound) - (disc + 1);
		for (int i = 1; i <= n; i++)
		{
			a[i] = std::lower_bound(disc + 1, disc + 1 + bound, a[i]) - disc;
			b[i] = std::lower_bound(disc + 1, disc + 1 + bound, b[i]) - disc;
		}
	}

	Graph G;
	bool vis[maxn * 2];
	LL sum;
	int max;
	bool valid;
	void DFS1(int node, int parent)
	{
		max = std::max(max, disc[node]);
		sum += (LL)disc[node] * (G.size[node] - 1);

		vis[node] = true;
		wander(G, node)
		{
			if (parent == (idx(G) >> 1)) continue;
			DEF(G);
			if (!vis[to])
				DFS1(to, idx(G) >> 1);
			else
				valid = false;
		}
	}

	work() : bound(), vis()
	{
		discretize();
		for (int i = 1; i <= n; i++)
		{
			G.addEdge(a[i], b[i]);
			G.addEdge(b[i], a[i]);
		}

		sum = 0;
		for (int i = 1; i <= bound; i++)
			if (!vis[i])
			{
				max = 0;
				valid = true;
				DFS1(i, -1);
				if (valid) sum += max;
			}

		printOut(sum);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		a[i] = readIn();
		b[i] = readIn();
	}

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("building.in", "r", stdin);
	freopen("building.out", "w", stdout);
#endif
	run();
	return 0;
}