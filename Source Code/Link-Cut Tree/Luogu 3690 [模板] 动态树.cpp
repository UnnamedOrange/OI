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

const int maxn = int(3e5) + 5;
int n, m;
int a[maxn];

class LCT
{
	struct Node
	{
		Node* ch[2];
		Node* parent;
		int weight;
		int sum;
		int flag;
		Node() : weight(), sum() {}
		void pushdown()
		{
			if (flag)
			{
				ch[0]->flag ^= 1;
				ch[1]->flag ^= 1;
				std::swap(ch[0], ch[1]);
				flag = false;
			}
		}
		void maintain()
		{
			sum = weight ^ ch[0]->sum ^ ch[1]->sum;
		}
		void reverse()
		{
			flag ^= 1;
		}
	};
	Node* null;
	Node nodes[maxn];

	bool isRoot(Node* r) { return r->parent->ch[0] != r && r->parent->ch[1] != r; }
	int trace(Node* r) { return r->parent->ch[1] == r; }
	void rotate(Node* r)
	{
		Node* parent = r->parent;
		Node* grand = parent->parent;
		int d = trace(r);
		if (!isRoot(parent)) grand->ch[trace(parent)] = r;
		r->parent = grand;

		parent->ch[d] = r->ch[d ^ 1];
		r->ch[d ^ 1]->parent = parent;
		parent->maintain();

		r->ch[d ^ 1] = parent;
		parent->parent = r;
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
		null->ch[0] = null->ch[1] = null->parent = null;
		for (int i = 0; i < maxn; i++)
		{
			nodes[i].ch[0] = nodes[i].ch[1] = nodes[i].parent = null;
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
		access(code);
		Node* node = nodes + code;
		splay(node);
		node->reverse();
	}
	int findroot(int code)
	{
		access(code);
		Node* node = nodes + code;
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
		if (node->ch[0] != nodes + x || (nodes + x)->ch[1] != null) return; // note
		(nodes + x)->parent = node->ch[0] = null; // note
		node->maintain();
	}
	void change(int pos, int val)
	{
		access(pos);
		Node* node = nodes + pos;
		splay(node);
		node->weight = val;
		node->maintain();
	}
	int query(int x, int y)
	{
		makeroot(x);
		access(y);
		Node* node = nodes + y;
		splay(node);
		return node->sum;
	}
} tree;

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 1; i <= n; i++)
		tree.change(i, a[i]);

	while (m--)
	{
		int ins = readIn();
		int x = readIn();
		int y = readIn();
		if (ins == 0)
			printOut(tree.query(x, y));
		else if (ins == 1)
			tree.link(x, y);
		else if (ins == 2)
			tree.cut(x, y);
		else if (ins == 3)
			tree.change(x, y);
	}
}

int main()
{
	run();
	return 0;
}