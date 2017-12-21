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
		Node* ch[2];
		Node() : sum(), ch() {}
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

	INT query(PARAM)
	{
		alloc(node);
		if (g_L <= l && r <= g_R)
		{
			return node->sum;
		}
		DEF;
		INT ret = 0;
		if (g_L <= mid) ret += query(LC);
		if (g_R > mid) ret += query(RC);
		return ret;
	}
	void add(PARAM)
	{
		alloc(node);
		if (l == r)
		{
			node->sum += g_Val;
			return;
		}
		DEF;
		if (g_Pos <= mid) add(LC);
		else if (g_Pos > mid) add(RC);
		node->update();
	}
	static void exchange(Node* &r1, Node* &r2, INT l, INT r)
	{
		if (g_L <= l && r <= g_R)
		{
			std::swap(r1, r2);
			return;
		}
		alloc(r1);
		alloc(r2);
		DEF;
		if (g_L <= mid) exchange(r1->ch[0], r2->ch[0], l, mid);
		if (g_R > mid) exchange(r1->ch[1], r2->ch[1], mid + 1, r);
		r1->update();
		r2->update();
	}

public:
	SegTree() : root() {}
	INT query(INT l, INT r)
	{
		if (l > r) return 0;
		g_L = l;
		g_R = r;
		return query(root, 1, 2 * n);
	}
	void add(INT pos, INT val)
	{
		g_Pos = pos;
		g_Val = val;
		add(root, 1, 2 * n);
	}
	static void exchange(SegTree& a, SegTree& b, INT l, INT r)
	{
		g_L = l;
		g_R = r;
		exchange(a.root, b.root, 1, 2 * n);
	}
};
SegTree::Node* SegTree::null = SegTree::Init::InitNull();
INT SegTree::g_L, SegTree::g_R, SegTree::g_Pos, SegTree::g_Val;

INT color[maxn];
INT weight[maxn];
SegTree st[10];

INT size;
INT parent[17][maxn];
INT depth[maxn];
INT euler[maxn * 2];
INT end[maxn * 2];
void DFS(INT node)
{
	static INT clock = 0;
	euler[node] = ++clock;

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
	end[node] = ++clock;
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
		st[color[i]].add(euler[i], weight[i]);
		st[color[i]].add(end[i], -weight[i]);
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
			SegTree::exchange(st[x], st[y], euler[u], end[u]);
		}
		else if (ins[0] == 'A')
		{
			INT u = readIn() + 1;
			INT v = readIn() + 1;
			INT c = readIn();
			INT lca = LCA(u, v);
			printOut(st[c].query(1, euler[u]) + st[c].query(1, euler[v]) - st[c].query(1, euler[lca]) - st[c].query(1, euler[parent[0][lca]]));
		}
		else if (ins[0] == 'S')
		{
			INT u = readIn() + 1;
			INT c = readIn();
			INT v = readIn();

			INT o = 0;
			for (int i = 0; i < 10; i++)
			{
				if (st[i].query(euler[u], euler[u]))
				{
					o = i;
					st[i].add(euler[u], -weight[u]);
					st[i].add(end[u], weight[u]);
					break;
				}
			}

			st[c].add(euler[u], v);
			st[c].add(end[u], -v);
			weight[u] = v;
		}
	}
}

int main()
{
	run();
	return 0;
}