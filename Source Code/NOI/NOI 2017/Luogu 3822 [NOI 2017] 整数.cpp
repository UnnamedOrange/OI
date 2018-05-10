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

const int maxn = int(1e6) + 5;
int n;
int t1, t2, t3;

class SegTree
{
	struct Node
	{
		int s[2];
	} nodes[maxn * 2];
	static inline int code(int l, int r)
	{
		return (l + r) | (l != r);
	}

	static const int mask = (1 << 30) - 1;
	int g_Pos, g_Val, g_Type;

	void modify(int l, int r)
	{
		Node& cnt = nodes[code(l, r)];
		if (l == r)
		{
			cnt.s[g_Type] += g_Val;
			return;
		}
		int mid = (l + r) >> 1;
		if (g_Pos <= mid) modify(l, mid);
		else modify(mid + 1, r);
		Node& lc = nodes[code(l, mid)];
		Node& rc = nodes[code(mid + 1, r)];
		if (rc.s[0] == rc.s[1])
		{
			if (lc.s[0] == lc.s[1])
				cnt.s[0] = cnt.s[1] = 0;
			else if (lc.s[0] < lc.s[1])
				cnt.s[0] = 0, cnt.s[1] = 1;
			else
				cnt.s[0] = 1, cnt.s[1] = 0;
		}
		else if (rc.s[0] < rc.s[1])
			cnt.s[0] = 0, cnt.s[1] = 1;
		else
			cnt.s[0] = 1, cnt.s[1] = 0;
	}
	int g_L, g_R;
	int comp(int l, int r)
	{
		Node& cnt = nodes[code(l, r)];
		if (g_L <= l && r <= g_R)
		{
			if (cnt.s[0] == cnt.s[1])
				return 0;
			return cnt.s[0] < cnt.s[1] ? -1 : 1;
		}
		int mid = (l + r) >> 1;
		int ret = 0;
		if (g_R > mid)
			ret = comp(mid + 1, r);
		if (ret) return ret;
		if (g_L <= mid)
			ret = comp(l, mid);
		return ret;
	}

public:
	void modify(int digit, int val, int type)
	{
		g_Pos = digit;
		g_Val = val;
		g_Type = type;
		modify(0, n + 1);
	}
	void add(int bit, int val, int type)
	{
		int digit = bit / 30;
		int mod = bit - 30 * digit;
		LL t;
		if ((t = (LL(val) << mod)) > mask)
		{
			modify(digit, t & mask, type);
			if (nodes[digit << 1].s[type] > mask)
			{
				modify(digit, -(mask + 1), type);
				modify(digit + 1, 1, type);
			}
			digit++;
			t = (t >> 30) & mask;
		}
		modify(digit, t, type);
		while (nodes[digit << 1].s[type] > mask)
		{
			modify(digit, -(mask + 1), type);
			digit++;
			modify(digit, 1, type);
		}
	}
	int comp(int digit)
	{
		if (digit < 0) return 0;
		g_L = 0;
		g_R = digit;
		return comp(0, n + 1);
	}
	bool query(int bit)
	{
		int digit = bit / 30;
		int mod = bit - digit * 30;
		Node& t = nodes[digit << 1];
		int Mask = (1 << mod) - 1;
		if (mod && (t.s[0] & Mask) != (t.s[1] & Mask))
		{
			if ((t.s[0] & Mask) >= (t.s[1] & Mask))
				return (t.s[0] & (1 << mod)) ^ (t.s[1] & (1 << mod));
			else
				return !((t.s[0] & (1 << mod)) ^ (t.s[1] & (1 << mod)));
		}
		else
		{
			if (comp(digit - 1) >= 0)
				return (t.s[0] & (1 << mod)) ^ (t.s[1] & (1 << mod));
			else
				return !((t.s[0] & (1 << mod)) ^ (t.s[1] & (1 << mod)));
		}
	}
} st;

void run()
{
	n = readIn();
	t1 = readIn();
	t2 = readIn();
	t3 = readIn();
	for (int o = 1; o <= n; o++)
	{
		int type = readIn();
		if (type == 1)
		{
			int a = readIn();
			int b = readIn();
			if (a >= 0) st.add(b, a, 0);
			else st.add(b, -a, 1);
		}
		else if (type == 2)
		{
			int k = readIn();
			printOut(st.query(k));
		}
	}
}

int main()
{
	run();
	return 0;
}