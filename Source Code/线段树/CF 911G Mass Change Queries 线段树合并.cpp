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

const int maxn = int(2e5) + 5;
int n, m;
int a[maxn];

class SegTree
{
	struct Node
	{
		Node *lc, *rc;
		Node() {}
	};
	static Node* null;
	static struct Initializer
	{
		Initializer()
		{
			null = new Node;
			null->lc = null->rc = null;
		}
	} initializer;
	static int g_Pos, g_Val, g_L, g_R;
	static void alloc(Node* &node)
	{
		if (node == null)
		{
			node = new Node;
			node->lc = node->rc = null;
		}
	}
	Node* root;

	void modify(Node* &node, int l, int r)
	{
		alloc(node);
		if (l == r)
		{
			return;
		}
		int mid = (l + r) >> 1;
		if (g_Pos <= mid) modify(node->lc, l, mid);
		else modify(node->rc, mid + 1, r);
	}
	void query(Node* node, int l, int r, int* ans)
	{
		if (node == null) return; // note: 保证时间复杂度
		if (l == r)
		{
			ans[l] = g_Val;
			return;
		}
		int mid = (l + r) >> 1;
		query(node->lc, l, mid, ans);
		query(node->rc, mid + 1, r, ans);
	}
	static void merge(Node* &src, Node* &des)
	{
		if (src == null) return;
		if (des == null)
		{
			des = src;
			src = null;
			return;
		}
		merge(src->lc, des->lc);
		merge(src->rc, des->rc);
		delete src;
		src = null;
	}
	static void merge(Node* &src, Node* &des, int l, int r) // 不是真正的线段树合并
	{
		if (src == null) return; // note: 从 src 合并到 des，src 没有，无需继续
		if (g_L <= l && r <= g_R)
		{
			merge(src, des);
			return;
		}
		alloc(des); // note: 要合并到 des，必须把 des 的结点分配好
		int mid = (l + r) >> 1;
		if (g_L <= mid) merge(src->lc, des->lc, l, mid);
		if (g_R > mid) merge(src->rc, des->rc, mid + 1, r);
	}

public:
	SegTree() : root(null) {}
	void modify(int pos, int val)
	{
		g_Pos = pos;
		g_Val = val;
		modify(root, 1, n);
	}
	void query(int* ans, int val)
	{
		g_Val = val;
		query(root, 1, n, ans);
	}
	static void merge(SegTree& src, SegTree& des, int l, int r)
	{
		g_L = l;
		g_R = r;
		merge(src.root, des.root, 1, n);
	}
};
SegTree::Node* SegTree::null;
SegTree::Initializer SegTree::initializer;
int SegTree::g_Pos, SegTree::g_Val, SegTree::g_L, SegTree::g_R;

int ans[maxn];

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++) a[i] = readIn();
	SegTree st[105];
	for (int i = 1; i <= n; i++)
		st[a[i]].modify(i, 1);

	m = readIn();
	while (m--)
	{
		int l = readIn();
		int r = readIn();
		int x = readIn();
		int y = readIn();
		if (x == y) continue;
		SegTree::merge(st[x], st[y], l, r);
	}
	for (int i = 1; i <= 100; i++)
		st[i].query(ans, i);
	for (int i = 1; i <= n; i++)
	{
		printOut(ans[i]);
		putchar(' ');
	}
}

int main()
{
	run();
	return 0;
}