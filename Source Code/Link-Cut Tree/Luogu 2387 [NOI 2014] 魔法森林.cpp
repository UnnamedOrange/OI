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
}

const int maxn = 50005;
const int maxm = 100005;
int n, m;
struct Edge
{
	int from, to, a, b;
	void read()
	{
		from = readIn();
		to = readIn();
		a = readIn();
		b = readIn();
	}
	bool operator<(const Edge& b) const
	{
		return a < b.a;
	}
} edges[maxm];

class LCT
{
	struct Node
	{
		Node* parent;
		Node* ch[2];
		bool flag;
		int weight;
		int max;
		int idx;
		int maxIdx;
		void pushdown()
		{
			if (flag)
			{
				std::swap(ch[0], ch[1]);
				ch[0]->flag ^= 1;
				ch[1]->flag ^= 1;
				flag = false;
			}
		}
		void maintain()
		{
			if (weight >= std::max(ch[0]->max, ch[1]->max))
			{
				max = weight;
				maxIdx = idx;
			}
			else if (ch[0]->max > ch[1]->max)
			{
				max = ch[0]->max;
				maxIdx = ch[0]->maxIdx;
			}
			else
			{
				max = ch[1]->max;
				maxIdx = ch[1]->maxIdx;
			}
		}
		void reverse() { flag ^= 1; }
	};
	Node* null;
	Node nodes[maxn + maxm];

	bool isRoot(Node* r) { return r->parent->ch[0] != r && r->parent->ch[1] != r; }
	int trace(Node* r) { return r->parent->ch[1] == r; }
	void rotate(Node* r)
	{
		Node* father = r->parent;
		Node* grand = father->parent;
		int d = trace(r);
		if (!isRoot(father)) grand->ch[trace(father)] = r;
		r->parent = grand;

		father->ch[d] = r->ch[d ^ 1];
		r->ch[d ^ 1]->parent = father;
		father->maintain();

		r->ch[d ^ 1] = father;
		father->parent = r;
		r->maintain();
	}
	void pushdown(Node* r)
	{
		if (isRoot(r)) return void(r->pushdown());
		pushdown(r->parent);
		r->pushdown();
	}
	void splay(Node* r)
	{
		pushdown(r);
		while (!isRoot(r))
		{
			Node* parent = r->parent;
			if (!isRoot(parent)) rotate(trace(r) == trace(parent) ? parent : r);
			rotate(r);
		}
	}

public:
	LCT()
	{
		null = new Node;
		null->max = null->weight = 0;
		null->idx = null->maxIdx = 0;
		null->ch[0] = null->ch[1] = null->parent = null;
	}
	void init()
	{
		for (register int i = 1; i <= n; i++)
		{
			nodes[i].ch[0] = nodes[i].ch[1] = nodes[i].parent = null;
			nodes[i].max = nodes[i].weight = 0;
			nodes[i].maxIdx = nodes[i].idx = i;
		}
		for (register int i = n + 1, j = 1; j <= m; i++, j++)
		{
			nodes[i].ch[0] = nodes[i].ch[1] = nodes[i].parent = null;
			nodes[i].max = nodes[i].weight = edges[j].b;
			nodes[i].maxIdx = nodes[i].idx = i;
		}
	}

	void access(int code)
	{
		Node* node = nodes + code;
		Node* pre = null;
		while (node != null)
		{
			splay(node);
			node->ch[1] = pre;
			node->maintain();
			pre = node;
			node = node->parent;
		}
	}
	void makeroot(int code)
	{
		Node* node = nodes + code;
		access(code);
		splay(node);
		node->reverse();
	}
	int findroot(int code)
	{
		Node* node = nodes + code;
		access(code);
		splay(node);
		while (node->ch[0] != null) node = node->ch[0];
		return splay(node), node - nodes;
	}
	void link(int x, int y)
	{
		makeroot(x);
		if (findroot(y) == x) return;
		(nodes + x)->parent = nodes + y;
	}
	void cut(int x, int y)
	{
		makeroot(x);
		if (findroot(y) != x) return;
		Node* node = nodes + y;
		splay(node);
		if (node->ch[0] != nodes + x || (nodes + x)->ch[1] != null) return;
		(nodes + x)->parent = node->ch[0] = null;
		node->maintain();
	}
	int query()
	{
		makeroot(1);
		access(n);
		Node* node = nodes + n;
		splay(node);
		return node->max;
	}
	int qMax(int x, int y)
	{
		makeroot(x);
		access(y);
		Node* node = nodes + y;
		splay(node);
		return node->maxIdx;
	}
} tree;

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
		edges[i].read();
	std::sort(edges + 1, edges + 1 + m);
	tree.init();

	int ans = -1;
	for (int i = 1; i <= m; i++)
	{
		const Edge& e = edges[i];
		int a = e.a;
		if (e.from == e.to) continue; // note
		if (tree.findroot(e.from) != tree.findroot(e.to))
		{
			tree.link(e.from, n + i);
			tree.link(e.to, n + i);
		}
		else
		{
			int code = tree.qMax(e.from, e.to) - n;
			if (edges[code].b <= e.b) continue;
			tree.cut(code + n, edges[code].from);
			tree.cut(code + n, edges[code].to);
			tree.link(n + i, e.from);
			tree.link(n + i, e.to);
		}
		if (tree.findroot(1) != tree.findroot(n)) continue;
		ans = ans == -1 ? a + tree.query() : std::min(ans, a + tree.query());
	}
	printOut(ans);
}

int main()
{
	run();
	return 0;
}