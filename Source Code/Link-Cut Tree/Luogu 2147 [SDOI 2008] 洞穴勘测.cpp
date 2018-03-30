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

const int maxn = 10005;
int n, m;

typedef class LinkCutTree
{
	typedef struct SplayNode
	{
		bool flag; // reverse
		SplayNode* ch[2];
		SplayNode* parent;
		SplayNode() : flag() {}
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
	} Node;
	Node* null;
	Node nodes[maxn];

	int isRoot(Node* node)
	{
		return node->parent->ch[0] != node && node->parent->ch[1] != node;
	}
	int trace(Node* node)
	{
		return node->parent->ch[1] == node; // 左 0 右 1
	}
	void rotate(Node* r) // 旋转至 r 的父结点的位置
	{
		Node* father = r->parent; // 父结点
		Node* grand = father->parent; // 爷结点
		int d = trace(r);
		if (!isRoot(father)) grand->ch[grand->ch[1] == father] = r; // 爷结点的儿子变成了 r
		father->ch[d] = r->ch[d ^ 1];
		father->ch[d]->parent = father; // r 的子结点的 parent 发生了变化
		father->parent = r; // r 的父结点的 parent 发生了变化
		r->ch[d ^ 1] = father;
		r->parent = grand; // r 的父结点发生了变化
	}
	void pushdown(Node* r) // 下传根到 r 这条链上的标记
	{
		if (isRoot(r)) return void(r->pushdown());
		pushdown(r->parent);
		r->pushdown();
	}
	void splay(Node* r) // 旋转 r 至根 
	{
		pushdown(r);
		while (!isRoot(r)) // 从下往上旋转
		{
			Node* father = r->parent;
			// 如果是一字型，先旋转上面；如果是之字形，先旋转下面
			if (!isRoot(father)) rotate(trace(r) == trace(father) ? father : r);
			rotate(r);
		}
	}
	void reverse(Node* r)
	{
		r->flag ^= 1;
	}

public:
	LinkCutTree()
	{
		null = new Node;
		null->parent = null->ch[0] = null->ch[1] = null;
	}
	void init()
	{
		for (int i = 1; i <= n; i++)
			nodes[i].ch[0] = nodes[i].ch[1] = nodes[i].parent = null;
	}
	void access(int code) // 之前的 node->ch[1] 的 parent 没变
	{
		Node* pre = null;
		Node* node = nodes + code;
		while (node != null)
		{
			splay(node);
			node->ch[1] = pre;
			pre = node;
			node = node->parent;
		}
	}
	void makeroot(int code) // 指定结点成为对应连通块在 LCT 中的根
	{
		Node* node = nodes + code;
		access(code);
		splay(node); // 注意这个点也是 Splay 的根
		reverse(node);
	}
	int findroot(int code) // 寻找某个结点对应连通块在 LCT 中的根
	{
		Node* node = nodes + code;
		access(code);
		splay(node);
		while (node->ch[0] != null)
			node = node->ch[0];
		return node - nodes;
	}
	void link(int x, int y)
	{
		makeroot(x); // x 已是 Splay 的根结点
		(nodes + x)->parent = nodes + y;
	}
	void cut(int x, int y)
	{
		Node* node = nodes + y;
		makeroot(x);
		access(y);
		splay(node);
		(nodes + x)->parent = node->ch[0] = null;
	}
} LCT;

LCT tree;

void run()
{
	n = readIn();
	m = readIn();
	tree.init();
	while (m--)
	{
		char ins[10];
		scanf("%s", ins);
		int x = readIn();
		int y = readIn();
		if (ins[0] == 'Q')
			puts(tree.findroot(x) == tree.findroot(y) ? "Yes" : "No");
		else if (ins[0] == 'D')
			tree.cut(x, y);
		else if (ins[0] == 'C')
			tree.link(x, y);
	}
}

int main()
{
	run();
	return 0;
}