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
INT n, m, mod;

class SegTree
{
	struct Node
	{
		INT val;
		INT add;
		INT mul;
		Node() : val(), add(), mul(1) {}
	} nodes[262200];
	INT g_L, g_R, g_Add, g_Mul;

#define PARAM INT node, INT l, INT r
#define DEF INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1
#define LC lc, l, mid
#define RC rc, mid + 1, r
#define CNT node, l, r

	void cover(PARAM, INT add, INT mul)
	{
		DEF;
		nodes[node].val = (nodes[node].val * mul % mod + add * (r - l + 1) % mod) % mod;
		nodes[node].add = (nodes[node].add * mul % mod + add) % mod;
		nodes[node].mul = nodes[node].mul * mul % mod;
	}
	void pushdown(PARAM)
	{
		DEF;
		cover(LC, nodes[node].add, nodes[node].mul);
		cover(RC, nodes[node].add, nodes[node].mul);
		nodes[node].add = 0;
		nodes[node].mul = 1;
	}
	void update(PARAM)
	{
		DEF;
		nodes[node].val = (nodes[lc].val + nodes[rc].val) % mod;
	}
	void modify_(PARAM)
	{
		if (g_L <= l && r <= g_R)
		{
			cover(CNT, g_Add, g_Mul);
			return;
		}
		DEF;
		pushdown(CNT);
		if (g_L <= mid) modify_(LC);
		if (g_R > mid) modify_(RC);
		update(CNT);
	}
	INT query_(PARAM)
	{
		if (g_L <= l && r <= g_R)
		{
			return nodes[node].val;
		}
		DEF;
		pushdown(CNT);
		INT ans = 0;
		if (g_L <= mid) ans = (ans + query_(LC)) % mod;
		if (g_R > mid) ans = (ans + query_(RC)) % mod;
		return ans;
	}

public:
	void build(PARAM)
	{
		if (l == r)
		{
			nodes[node].val = readIn();
			return;
		}
		DEF;
		build(LC);
		build(RC);
		update(CNT);
	}
	void add(INT l, INT r, INT val)
	{
		g_L = l;
		g_R = r;
		g_Add = val;
		g_Mul = 1;
		modify_(1, 1, n);
	}
	void mul(INT l, INT r, INT val)
	{
		g_L = l;
		g_R = r;
		g_Add = 0;
		g_Mul = val;
		modify_(1, 1, n);
	}
	INT query(INT l, INT r)
	{
		g_L = l;
		g_R = r;
		return query_(1, 1, n);
	}
} st;

void run()
{
	n = readIn();
	m = readIn();
	mod = readIn();
	st.build(1, 1, n);
	while (m--)
	{
		INT ins = readIn();
		switch (ins)
		{
		case 1:
		case 2:
		{
			INT x = readIn();
			INT y = readIn();
			INT k = readIn();
			if (ins == 1) st.mul(x, y, k);
			else if (ins == 2) st.add(x, y, k);
			break;
		}
		case 3:
		{
			INT x = readIn();
			INT y = readIn();
			printOut(st.query(x, y));
			break;
		}
		};
	}
}

int main()
{
	run();
	return 0;
}
