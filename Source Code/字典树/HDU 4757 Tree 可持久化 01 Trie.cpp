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
int n, q;
int a[maxn];

struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxn * 2];
	int i;
	int head[maxn];
	void clear()
	{
		i = 0;
		memset(head, -1, sizeof(int) * (n + 1));
	}
	void addEdge(int from, int to)
	{
		edges[i].to = to;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
#define idx(x) idx_##x
#define wander(G, node) for (int idx(G) = G.head[node]; ~idx(G); idx(G) = G.edges[idx(G)].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx(G)]; int to = e.to
} G;

class Func01Trie
{
	static const int bitlen = 16;
	struct Node
	{
		int val;
		Node* ch[2];
	};
	Node* null;
	Node pool[17 * maxn];
	Node* cnt;

	int size;
	Node* version[maxn];
	Node* clone(Node* src) { return new(cnt++) Node(*src); }

	int g_Val;
	void insert(Node* &node, int depth, Node* src)
	{
		node = clone(src);
		node->val++;
		if (!~depth) return;
		bool bit = g_Val & (1 << depth);
		insert(node->ch[bit], depth - 1, src->ch[bit]);
	}
	int query(Node* a1, Node* a2, Node* d1, Node* d2)
	{
		int ret = 0;
		for (int i = bitlen - 1; ~i; i--)
		{
			bool bit = g_Val & (1 << i);
			bool c = false;
			if (a1->ch[!bit]->val + a2->ch[!bit]->val - d1->ch[!bit]->val - d2->ch[!bit]->val) c = true;
			if (c)
				ret |= 1 << i;
			a1 = a1->ch[bit ^ c];
			a2 = a2->ch[bit ^ c];
			d1 = d1->ch[bit ^ c];
			d2 = d2->ch[bit ^ c];
		}
		return ret;
	}

public:
	Func01Trie()
	{
		null = new Node;
		null->ch[0] = null->ch[1] = null;
		null->val = 0;
	}
	void clear()
	{
		cnt = pool;
		size = 0;
		version[0] = null;
	}
	int clone(int ver)
	{
		assert(ver <= size);
		size++;
		version[size] = version[ver];
		return size;
	}
	void insert(int x)
	{
		g_Val = x;
		insert(version[size], bitlen - 1, version[size]);
	}
	int query(int a1, int a2, int d1, int d2, int x)
	{
		g_Val = x;
		return query(version[a1], version[a2], version[d1], version[d2]);
	}
} trie;

int maxk;
int parent[18][maxn];
int ver[maxn];
int depth[maxn];
void DFS(int node)
{
	depth[node] = depth[parent[0][node]] + 1;
	for (int i = 1; i <= maxk; i++)
		parent[i][node] = parent[i - 1][parent[i - 1][node]];
	ver[node] = trie.clone(ver[parent[0][node]]);
	trie.insert(a[node]);
	wander(G, node)
	{
		DEF(G);
		if (to == parent[0][node]) continue;
		parent[0][to] = node;
		DFS(to);
	}
}
int LCA(int x, int y)
{
	if (depth[x] < depth[y]) std::swap(x, y);
	for (int i = maxk; ~i; i--)
	{
		if (depth[parent[i][x]] < depth[y]) continue;
		x = parent[i][x];
	}
	if (x != y)
	{
		for (int i = maxk; ~i; i--)
		{
			if (parent[i][x] == parent[i][y]) continue;
			x = parent[i][x];
			y = parent[i][y];
		}
		x = parent[0][x];
	}
	return x;
}

void run()
{
	while (~scanf("%d%d", &n, &q))
	{
		for (int i = 1; i <= n; i++)
			a[i] = readIn();
		G.clear();
		for (int i = 1; i < n; i++)
		{
			int from = readIn();
			int to = readIn();
			G.addEdge(from, to);
			G.addEdge(to, from);
		}
		maxk = 0;
		while (1 << maxk < n) maxk++;

		trie.clear();
		DFS(1);

		while (q--)
		{
			int x = readIn();
			int y = readIn();
			int d = readIn();
			int lca = LCA(x, y);
			printOut(trie.query(ver[x], ver[y], ver[lca], ver[parent[0][lca]], d));
		}
	}
}

int main()
{
	run();
	return 0;
}