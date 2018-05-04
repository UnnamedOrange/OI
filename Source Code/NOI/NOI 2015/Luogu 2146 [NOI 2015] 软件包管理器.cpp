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
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = int(1e5) + 5;
int n;
struct Graph
{
	struct Edge
	{
		int to, next;
	} edges[maxn];
	int i;
	int head[maxn];
	Graph() : i() { memset(head, -1, sizeof(head)); }
	void addEdge(int from, int to)
	{
		edges[i].to = to;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
#define idx(G) idx_##G
#define wander(G, node) for (int idx(G) = G.head[node]; ~idx(G); idx(G) = G.edges[idx(G)].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx(G)]; int to = e.to
} T;

class TreeChain
{
	Graph& G;

public:
	TreeChain() : G(T) {}

private:
	int parent[maxn];
	int size[maxn];
	int heavy[maxn];
	void DFS1(int node)
	{
		heavy[node] = -1;
		size[node] = 1;
		wander(G, node)
		{
			DEF(G);
			parent[to] = node;
			DFS1(to);
			size[node] += size[to];
			if (!~heavy[node] || size[heavy[node]] < size[to])
				heavy[node] = to;
		}
	}
	int dfn[maxn];
	int end[maxn];
	int top[maxn];
	int stamp;
	void DFS2(int node, int belong)
	{
		if (belong == -1)
			belong = node;
		dfn[node] = ++stamp;
		top[node] = belong;
		if (heavy[node] != -1)
			DFS2(heavy[node], belong);
		wander(G, node)
		{
			DEF(G);
			if (to == heavy[node]) continue;
			DFS2(to, -1);
		}
		end[node] = stamp;
	}

	class SegTree
	{
		struct Node
		{
			int sum;
			int lazy;
			bool bLazy;
			Node() : sum(), lazy(), bLazy() {}
		} nodes[maxn * 2];
		static inline int code(int l, int r)
		{
			return (l + r) | (l != r);
		}

		int g_L, g_R, g_Val;
		inline void cover(Node& t, int l, int r, int v)
		{
			t.sum = v * (r - l + 1);
			t.lazy = v;
			t.bLazy = true;
		}
		inline void pushdown(int l, int r)
		{
			Node& t = nodes[code(l, r)];
			if (t.bLazy)
			{
				int mid = (l + r) >> 1;
				Node& lc = nodes[code(l, mid)];
				Node& rc = nodes[code(mid + 1, r)];
				cover(lc, l, mid, t.lazy);
				cover(rc, mid + 1, r, t.lazy);
				t.bLazy = false;
			}
		}
		int handle(int l, int r)
		{
			Node& t = nodes[code(l, r)];
			int ret = 0;
			if (g_L <= l && r <= g_R)
			{
				ret = t.sum;
				cover(t, l, r, g_Val);
				return ret;
			}
			pushdown(l, r);
			int mid = (l + r) >> 1;
			if (g_L <= mid) ret += handle(l, mid);
			if (g_R > mid) ret += handle(mid + 1, r);
			t.sum = nodes[code(l, mid)].sum + nodes[code(mid + 1, r)].sum;
			return ret;
		}

	public:
		int queryAndModify(int l, int r, int v)
		{
			g_L = l;
			g_R = r;
			g_Val = v;
			return handle(1, n);
		}
	} st;

public:
	void init()
	{
		parent[0] = -1;
		DFS1(0);
		DFS2(0, -1);
	}
	int modifySubtree(int node)
	{
		int sum = st.queryAndModify(dfn[node], end[node], 0);
		return sum;
	}
	int modifyChain(int node)
	{
		int sum = 0;
		while (~node)
		{
			sum += (dfn[node] - dfn[top[node]] + 1) - st.queryAndModify(dfn[top[node]], dfn[node], 1);
			node = parent[top[node]];
		}
		return sum;
	}
} tc;

void run()
{
	n = readIn();
	for (int i = 1; i < n; i++)
		T.addEdge(readIn(), i);
	tc.init();

	int m = readIn();
	while (m--)
	{
		char ins[15];
		scanf("%s", ins);
		if (ins[0] == 'i')
			printOut(tc.modifyChain(readIn()));
		else if (ins[0] == 'u')
			printOut(tc.modifySubtree(readIn()));
	}
}

int main()
{
	run();
	return 0;
}