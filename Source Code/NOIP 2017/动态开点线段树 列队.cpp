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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
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
inline void printOut(INT x)
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
}

const INT maxn = INT(3e5) + 5;
INT n, m, q;
INT size;
struct Query
{
	INT x;
	INT y;
	void read()
	{
		x = readIn();
		y = readIn();
	}
} querys[maxn];
class SegTree
{
	struct Node
	{
		INT sum;
		INT lazy;
		Node* ch[2];
		Node() : sum(), lazy() {}
	};
	Node* root;
	Node* null;

#define PARAM Node* &node, INT l, INT r
#define DEF INT mid = (l + r) >> 1;
#define CNT node, l, r
#define LC node->ch[0], l, mid
#define RC node->ch[1], mid + 1, r

	INT g_L, g_R, g_Val;

	Node* alloc(Node* &node)
	{
		if (node == null)
		{
			node = new Node;
			node->ch[0] = node->ch[1] = null;
		}
		return node;
	}
	void cover(PARAM, INT v)
	{
		alloc(node);
		node->sum += (r - l + 1) * v;
		node->lazy += v;
	}
	void pushdown(PARAM)
	{
		if (node->lazy)
		{
			DEF;
			cover(LC, node->lazy);
			cover(RC, node->lazy);
			node->lazy = 0;
		}
	}
	void update(PARAM)
	{
		node->sum = node->ch[0]->sum + node->ch[1]->sum;
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
		update(CNT);
	}

public:
	SegTree()
	{
		null = new Node;
		root = null->ch[0] = null->ch[1] = null;
	}



};

void run()
{
	n = readIn();
	m = readIn();
	q = readIn();
	size = n + q;
	for (int i = 1; i <= q; i++)
		querys[i].read();
}

int main()
{
#ifndef LOCAL
	freopen("phalanx.in", "r", stdin);
	freopen("phalanx.out", "w", stdout);
#endif
	run();
	return 0;
}