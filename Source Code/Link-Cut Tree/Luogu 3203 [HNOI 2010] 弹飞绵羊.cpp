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

const int maxn = int(2e5) + 5;
int n, m;
int a[maxn];

class LCT
{
	struct Node
	{
		int size;
		bool flag;
		Node* parent;
		Node* ch[2];
		Node() : size() {}
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
			size = ch[0]->size + ch[1]->size + 1;
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
		null->parent = null->ch[0] = null->ch[1] = null;
		for (int i = 0; i < maxn; i++)
		{
			nodes[i].ch[0] = nodes[i].ch[1] = nodes[i].parent = null;
			nodes[i].size = 1;
		}
	}
	void access(int code)
	{
		Node* pre = null;
		Node* node = nodes + code;
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
		splay(nodes + code);
		(nodes + code)->reverse();
	}
	void link(int x, int y)
	{
		makeroot(x);
		(nodes + x)->parent = nodes + y;
	}
	void cut(int x, int y)
	{
		Node* node = nodes + y;
		makeroot(x);
		access(y);
		splay(node);
		(nodes + x)->parent = node->ch[0] = null;
		node->maintain();
	}
	int depth(int x)
	{
		makeroot(n);
		access(x);
		splay(nodes + x);
		return (nodes + x)->ch[0]->size;
	}
} tree;

void run()
{
	n = readIn();
	for (int i = 0; i < n; i++)
		a[i] = readIn();
	for (int i = 0; i < n; i++)
		tree.link(i, std::min(n, i + a[i]));
	m = readIn();
	while (m--)
	{
		int ins = readIn();
		int pos = readIn();
		if (ins == 1)
		{
			printOut(tree.depth(pos));
		}
		else if (ins == 2)
		{
			tree.cut(pos, std::min(n, pos + a[pos]));
			a[pos] = readIn();
			tree.link(pos, std::min(n, pos + a[pos]));
		}
	}
}

int main()
{
	run();
	return 0;
}