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

const INT maxn = 100005;
INT n, m;
class SegTree
{
	struct Node
	{
		INT sum;
		INT lazy;
	} nodes[262150];
#define PARAM INT node, INT l, INT r
#define DEF INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1
	void cover(PARAM, INT val)
	{
		nodes[node].sum += val * (r - l + 1);
		nodes[node].lazy += val;
	}
	void pushdown(PARAM)
	{
		DEF;
		if (nodes[node].lazy)
		{
			cover(lc, l, mid, nodes[node].lazy);
			cover(rc, mid + 1, r, nodes[node].lazy);
			nodes[node].lazy = 0;
		}
	}
	void update(PARAM)
	{
		DEF;
		nodes[node].sum = nodes[lc].sum + nodes[rc].sum;
	}

	INT g_L, g_R, g_Val;
	INT handle(PARAM)
	{
		if (g_L <= l && r <= g_R)
		{
			cover(node, l, r, g_Val);
			return nodes[node].sum;
		}
		pushdown(node, l, r);
		DEF;
		INT ans = 0;
		if (g_L <= mid) ans += handle(lc, l, mid);
		if (g_R > mid) ans += handle(rc, mid + 1, r);
		update(node, l, r);
		return ans;
	}

public:
	void add(INT l, INT r, INT val)
	{
		g_L = l;
		g_R = r;
		g_Val = val;
		handle(1, 1, n);
	}
	INT query(INT l, INT r)
	{
		g_L = l;
		g_R = r;
		g_Val = 0;
		return handle(1, 1, n);
	}
	void build(PARAM)
	{
		if (l == r)
		{
			nodes[node].sum = readIn();
			return;
		}
		DEF;
		build(lc, l, mid);
		build(rc, mid + 1, r);
		update(node, l, r);
	}
} st;

void run()
{
	n = readIn();
	m = readIn();
	st.build(1, 1, n);
	while (m--)
	{
		INT ins = readIn();
		if (ins == 1)
		{
			INT l = readIn();
			INT r = readIn();
			INT x = readIn();
			st.add(l, r, x);
		}
		else if (ins == 2)
		{
			INT l = readIn();
			INT r = readIn();
			printOut(st.query(l, r));
		}
	}
}

int main()
{
	run();
	return 0;
}
