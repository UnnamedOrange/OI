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
typedef long long INT;
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
	putchar('\n');
}

const INT maxn = INT(3e5) + 5;
INT n, m, q;
class SegTree
{
	struct Node
	{
		INT size;
		INT val;
		Node* lc;
		Node* rc;
		Node() : size(), val(), lc(), rc() {}
	};
	Node* null;
	Node* root;

#define DEF INT mid = (l + r) >> 1
#define CNT node, l, r
#define LC node->lc, l, mid
#define RC node->rc, mid + 1, r
#define PARAM Node* &node, INT l, INT r

	void alloc(Node* &r)
	{
		if (r == null)
		{
			r = new Node;
			r->lc = r->rc = null;
		}
	}
	INT findKth(PARAM, INT k, INT& pos)
	{
		alloc(node);
		if (l == r)
		{
			node->size = 1;
			pos = l;
			return node->val;
		}
		DEF;
		INT s = mid - l + 1;
		s = s - node->lc->size;
		INT ret;
		if (k <= s) ret = findKth(LC, k, pos);
		else ret = findKth(RC, k - s, pos);
		node->size = node->lc->size + node->rc->size;
		return ret;
	}
	INT g_Pos, g_Val;
	void insert(PARAM)
	{
		alloc(node);
		if (l == r)
		{
			node->size = 0;
			node->val = g_Val;
			return;
		}
		DEF;
		if (g_Pos <= mid) insert(LC);
		else insert(RC);
		node->size = node->lc->size + node->rc->size;
	}

public:
	SegTree()
	{
		null = new Node;
		root = null->lc = null->rc = null;
	}
	INT kth(INT k, INT& pos)
	{
		return findKth(root, 1, std::max(n, m) + q, k, pos);
	}
	void insert(INT pos, INT val)
	{
		g_Pos = pos;
		g_Val = val;
		insert(root, 1, std::max(n, m) + q);
	}
} trees[maxn], colum;

INT size[maxn];

void run()
{
	n = readIn();
	m = readIn();
	q = readIn();
	for (int i = 1; i <= n; i++)
		size[i] = m - 1;
	size[n + 1] = n;

	for (int i = 1; i <= q; i++)
	{
		INT x = readIn();
		INT y = readIn();
		if (y == m)
		{
			INT pos;
			INT ans = colum.kth(x, pos);
			if (pos <= n)
				ans = m * pos;
			colum.insert(++size[n + 1], ans);

			printOut(ans);
		}
		else
		{
			INT pos1;
			INT ans = trees[x].kth(y, pos1);
			if (pos1 < m)
				ans = m * (x - 1) + pos1;
			INT pos2;
			INT ins = colum.kth(x, pos2);
			if (pos2 <= n)
				ins = m * pos2;
			trees[x].insert(++size[x], ins);
			colum.insert(++size[n + 1], ans);

			printOut(ans);
		}
	}
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