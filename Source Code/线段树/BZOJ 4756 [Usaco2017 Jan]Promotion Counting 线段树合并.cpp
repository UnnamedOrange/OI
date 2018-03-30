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
int a[maxn];
int parent[maxn];
int bound;
int disc[maxn];
void discretize()
{
	memcpy(disc, a, sizeof(disc));
	std::sort(disc + 1, disc + 1 + n);
	bound = std::unique(disc + 1, disc + 1 + n) - (disc + 1);
	for (int i = 1; i <= n; i++)
		a[i] = std::lower_bound(disc + 1, disc + 1 + bound, a[i]) - disc;
}

class SegTree
{
	struct Node
	{
		int sum;
		Node *lc, *rc;
		Node() : sum() {}
	};
	static Node* null;
	static struct Initializer
	{
		Initializer()
		{
			(*this)();
		}
		void operator()()
		{
			static bool initialized;
			if (!initialized)
			{
				initialized = true;
				null = new Node;
				null->lc = null->rc = null;
			}
		}
	} initializer;
	static void alloc(Node* &node)
	{
		if (node == null)
		{
			node = new Node;
			node->lc = node->rc = null;
		}
	}
	Node* root;
	static int g_Pos, g_Val, g_L, g_R;
	void add(Node* &node, int l, int r)
	{
		alloc(node);
		if (l == r)
		{
			node->sum += g_Val;
			return;
		}
		int mid = (l + r) >> 1;
		if (g_Pos <= mid) add(node->lc, l, mid);
		else add(node->rc, mid + 1, r);
		node->sum = node->lc->sum + node->rc->sum;
	}
	int query(Node* &node, int l, int r)
	{
		if (node == null) return 0;
		if (g_L <= l && r <= g_R)
		{
			return node->sum;
		}
		int mid = (l + r) >> 1;
		int ret = 0;
		if (g_L <= mid) ret += query(node->lc, l, mid);
		if (g_R > mid) ret += query(node->rc, mid + 1, r);
		return ret;
	}
	static void merge(Node* &des, Node* &src)
	{
		if (src == null) return;
		if (des == null)
		{
			des = src;
			src = null;
			return;
		}
		merge(des->lc, src->lc);
		merge(des->rc, src->rc);
		des->sum += src->sum; // note
		delete src;
		src = null;
	}

public:
	SegTree()
	{
		initializer();
		root = null;
	}
	void add(int pos, int val)
	{
		g_Pos = pos;
		g_Val = val;
		add(root, 1, n);
	}
	int query(int l, int r)
	{
		g_L = l;
		g_R = r;
		return query(root, 1, n);
	}
	static void merge(SegTree& des, SegTree& src)
	{
		merge(des.root, src.root);
	}
};
SegTree::Node* SegTree::null;
SegTree::Initializer SegTree::initializer;
int SegTree::g_Pos, SegTree::g_Val, SegTree::g_L, SegTree::g_R;

struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxn];
	int head[maxn];
	int i;
	Graph() : i()
	{
		memset(head, -1, sizeof(head));
	}
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
} G;
int ans[maxn];
SegTree DFS(int node)
{
	SegTree st;
	st.add(a[node], 1);
	wander(G, node)
	{
		DEF(G);
		SegTree child = DFS(to);
		SegTree::merge(st, child);
	}
	if (a[node] != bound)
		ans[node] = st.query(a[node] + 1, bound);
	return st;
}

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++) a[i] = readIn();
	discretize();
	for (int i = 2; i <= n; i++)
	{
		parent[i] = readIn();
		G.addEdge(parent[i], i);
	}
	DFS(1);
	for (int i = 1; i <= n; i++)
		printOut(ans[i]);
}

int main()
{
	run();
	return 0;
}