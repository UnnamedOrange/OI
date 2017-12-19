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

const INT maxn = INT(5e4) + 5;
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
#define wander(G, v) for(int i = G.head[v]; i; i = G.edges[i].next)
} G;
typedef Graph::Edge Edge;

class SegTree
{
	struct Node
	{
		INT sum;
		INT lazy;
		Node* ch[2];
		Node() : sum(), lazy(), ch() {}
		void update()
		{
			sum = ch[0]->sum + ch[1]->sum;
		}
	};
	static Node* null;

public:
	struct Init
	{
		static Node* InitNull()
		{
			Node* ret = new Node;
			ret->ch[0] = ret->ch[1] = ret;
			return ret;
		}
	};

private:
	Node * root;
	static Node* alloc()
	{
		Node* r = new Node;
		r->ch[0] = r->ch[1] = null;
		return r;
	}
	static void alloc(Node* &r)
	{
		if (!r || r == null)
			r = alloc();
	}

	static INT g_L, g_R;
	static INT g_Pos, g_Val;
#define PARAM Node* &node, INT l, INT r
#define DEF INT mid = (l + r) >> 1;
#define LC node->ch[0], l, mid
#define RC node->ch[1], mid + 1, r
#define CNT node, l, r

	static void cover(PARAM, INT val)
	{
		alloc(node);
		node->sum += val * (r - l + 1);
		node->lazy += val;
	}
	static void pushdown(PARAM)
	{
		if (node->lazy)
		{
			DEF;
			cover(LC, node->lazy);
			cover(RC, node->lazy);
			node->lazy = 0;
		}
	}
	INT query(PARAM)
	{
		alloc(node);
		if (l == r)
		{
			return node->sum;
		}
		DEF;
		pushdown(CNT);
		INT ret = 0;
		if (g_Pos <= mid) ret += query(LC);
		else if (g_Pos > mid) ret += query(RC);
		return ret;
	}
	void add(PARAM)
	{
		alloc(node);
		if (g_L <= l && r <= g_R)
		{
			cover(CNT, g_Val);
			return;
		}
		DEF;
		pushdown(CNT);
		if (g_L <= mid) add(LC);
		if (g_R > mid) add(RC);
		node->update();
	}
	static void change(Node* &r1, Node* &r2, INT l, INT r)
	{
		if (g_L <= l && r <= g_R)
		{
			std::swap(r1, r2);
			return;
		}
		alloc(r1);
		alloc(r2);
		pushdown(r1, l, r);
		pushdown(r2, l, r);
		DEF;
		if (g_L <= mid) change(r1->ch[0], r2->ch[0], l, mid);
		if (g_R > mid) change(r1->ch[1], r2->ch[1], mid + 1, r);
		r1->update();
		r2->update();
	}

public:
	SegTree() : root() {}
	INT query(INT pos)
	{
		if (!pos) return 0;
		g_Pos = pos;
		return query(root, 1, n);
	}
	void add(INT l, INT r, INT val)
	{
		g_L = l;
		g_R = r;
		g_Val = val;
		add(root, 1, n);
	}
	static void change(SegTree& a, SegTree& b, INT l, INT r)
	{
		g_L = l;
		g_R = r;
		change(a.root, b.root, 1, n);
	}
};
SegTree::Node* SegTree::null = SegTree::Init::InitNull();
INT SegTree::g_L, SegTree::g_R, SegTree::g_Pos, SegTree::g_Val;

INT color[maxn];
INT weight[maxn];
SegTree st[10];
SegTree cst[10];

INT size;
INT parent[17][maxn];
INT depth[maxn];
INT seq[maxn];
INT dfn[maxn];
INT end[maxn];
void DFS(INT node)
{
	static INT clock = 0;
	dfn[node] = ++clock;
	seq[clock] = node;

	depth[node] = depth[parent[0][node]] + 1;
	wander(G, node)
	{
		const Edge& e = G.edges[i];
		INT to = e.to;
		if (to == parent[0][node])
			continue;
		parent[0][to] = node;
		DFS(to);
	}
	end[node] = clock;
}
void goDouble()
{
	while (1 << size < n) size++;
	for (int i = 1; i <= size; i++)
		for (int j = 0; j < n; j++)
			parent[i][j] = parent[i - 1][parent[i - 1][j]];
}
INT LCA(INT x, INT y)
{
	if (depth[x] < depth[y])
		std::swap(x, y);
	for (int i = size; ~i; i--)
	{
		if (depth[parent[i][x]] < depth[y])
			continue;
		x = parent[i][x];
	}
	if (x != y)
	{
		for (int i = size; ~i; i--)
		{
			if (parent[i][x] == parent[i][y])
				continue;
			x = parent[i][x];
			y = parent[i][y];
		}
		x = parent[0][x];
	}
	return x;
}

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		color[i] = readIn();
	for (int i = 1; i <= n; i++)
		weight[i] = readIn();
	for (int i = 2; i <= n; i++)
	{
		INT from = readIn() + 1;
		INT to = readIn() + 1;
		G.addEdge(from, to);
		G.addEdge(to, from);
	}
	DFS(1);
	goDouble();
	for (int i = 1; i <= n; i++)
	{
		st[color[i]].add(dfn[i], end[i], weight[i]);
		cst[color[i]].add(dfn[i], dfn[i], 1);
	}

	INT m = readIn();
	while (m--)
	{
		char ins[10];
		scanf("%s", ins);
		if (ins[0] == 'C')
		{
			INT u = readIn() + 1;
			INT x = readIn();
			INT y = readIn();
			SegTree::change(st[x], st[y], dfn[u], end[u]);
			SegTree::change(cst[x], cst[y], dfn[u], end[u]);
		}
		else if (ins[0] == 'A')
		{
			INT u = readIn() + 1;
			INT v = readIn() + 1;
			INT c = readIn();
			INT lca = LCA(u, v);
			printOut(st[c].query(dfn[u]) + st[c].query(dfn[v]) - st[c].query(dfn[lca]) - st[c].query(dfn[parent[0][lca]]));
		}
		else if (ins[0] == 'S')
		{
			INT u = readIn() + 1;
			INT c = readIn();
			INT v = readIn();

			INT o = 0;
			for (int i = 0; i < 10; i++)
			{
				if (cst[i].query(dfn[u]))
				{
					o = i;
					cst[i].add(dfn[u], dfn[u], -1);
					break;
				}
			}
			cst[c].add(dfn[u], dfn[u], 1);

			st[o].add(dfn[u], end[u], -weight[u]);
			st[c].add(dfn[u], end[u], v);
			color[u] = c;
			weight[u] = v;
		}
	}
}

int main()
{
	run();
	return 0;
}