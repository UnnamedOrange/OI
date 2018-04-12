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
typedef LL INT_PUT;
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
int n, m;

class LCT
{
	struct Node
	{
		bool flag;
		Node* parent;
		Node* ch[2];

		int virt;
		int size;

		Node() : flag() {}
		void reverse()
		{
			flag ^= 1;
		}
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
			size = virt + ch[0]->size + ch[1]->size;
		}
	};

	Node* null;
	Node nodes[maxn];

	bool isRoot(Node* node)
	{
		return node->parent->ch[0] != node && node->parent->ch[1] != node;
	}
	int trace(Node* node)
	{
		return node->parent->ch[1] == node;
	}
	void rotate(Node* node)
	{
		Node* parent = node->parent;
		Node* grand = parent->parent;
		int d = trace(node);
		if (!isRoot(parent)) grand->ch[trace(parent)] = node;
		node->parent = grand;

		parent->ch[d] = node->ch[d ^ 1];
		node->ch[d ^ 1]->parent = parent;
		parent->maintain();

		node->ch[d ^ 1] = parent;
		parent->parent = node;
		node->maintain();
	}
	void pushdown(Node* node)
	{
		if (isRoot(node)) return void(node->pushdown());
		pushdown(node->parent);
		node->pushdown();
	}
	void splay(Node* node)
	{
		pushdown(node);
		while (!isRoot(node))
		{
			Node* parent = node->parent;
			if (!isRoot(parent)) rotate(trace(node) == trace(parent) ? parent : node);
			rotate(node);
		}
	}

public:
	LCT()
	{
		null = nodes;
		null->ch[0] = null->ch[1] = null->parent = null;
		null->size = null->virt = 0;
	}
	void init()
	{
		for (int i = 1; i <= n; i++)
		{
			Node* t = nodes + i;
			t->parent = t->ch[0] = t->ch[1] = null;
			t->size = t->virt = 1;
		}
	}

	void access(int code)
	{
		Node* node = nodes + code;
		Node* pre = null;
		while (node != null)
		{
			splay(node);
			node->virt += node->ch[1]->size;
			node->ch[1] = pre;
			node->virt -= node->ch[1]->size;
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
	void link(int x, int y)
	{
		makeroot(x);
		Node* X = nodes + x;
		Node* Y = nodes + y;
		X->parent = Y;
		makeroot(y);
		Y->virt += X->size;
		Y->maintain();
	}
	LL query(int x, int y)
	{
		Node* X = nodes + x;
		Node* Y = nodes + y;
		makeroot(x);
		access(y);
		splay(X);
		LL a = Y->size;
		makeroot(y);
		access(x);
		splay(Y);
		LL b = X->size;
		return a * b;
	}
} lct;

void run()
{
	n = readIn();
	m = readIn();
	lct.init();
	while (m--)
	{
		char str[10];
		scanf("%s", str);
		int u = readIn();
		int v = readIn();
		if (str[0] == 'A')
			lct.link(u, v);
		else if (str[0] == 'Q')
			printOut(lct.query(u, v));
	}
}

int main()
{
	run();
	return 0;
}