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
typedef long long INT_PUT;

const int MAXS = 40 * 1024 * 1024;
char buf[MAXS], bufout[MAXS], *ch, *chout;
INT_PUT readIn() {
	INT_PUT x;
	for (++ch; *ch <= 32; ++ch);
	for (x = 0; *ch >= '0'; ++ch) x = x * 10 + *ch - '0';
	return x;
}
void printOut(INT_PUT x) {
	if (!x) *(++chout) = '0';
	else {
		char *ch0 = chout, *ch1 = chout + 1;
		while (x) {
			*(++ch0) = x % 10 + '0';
			x /= 10;
		}
		chout = ch0;
		while (ch1 <= ch0) std::swap(*(ch1++), *(ch0--));
	}
	*(++chout) = '\n';
}
void std_init() {
	ch = buf - 1;
	chout = bufout - 1;
	fread(buf, 1, MAXS, stdin);
}
void std_out() {
	fwrite(bufout, 1, chout - bufout + 1, stdout);
}

const int maxn = int(1e6) + 5;
int n, m;
int a[maxn];
class SegTree
{
	static const int code(int l, int r) { return (l + r) | (l != r); }
	struct Node
	{
		int major;
		int minor;
		int t;
		LL sum;
		int lazy;
	} nodes[maxn * 2];

#define PARAM int l, int r
#define DEF int mid = (l + r) >> 1
#define CNT l, r
#define LC l, mid
#define RC mid + 1, r
	int g_L, g_R, g_Val;

	void update(PARAM)
	{
		Node& t = nodes[code(CNT)];
		DEF;
		Node& lc = nodes[code(LC)];
		Node& rc = nodes[code(RC)];
		t.sum = lc.sum + rc.sum;
		if (lc.major == rc.major)
		{
			t.major = lc.major;
			t.t = lc.t + rc.t;
			t.minor = std::max(lc.minor, rc.minor);
		}
		else if (lc.major > rc.major)
		{
			t.major = lc.major;
			t.t = lc.t;
			t.minor = std::max(lc.minor, rc.major);
		}
		else if (lc.major < rc.major)
		{
			t.major = rc.major;
			t.t = rc.t;
			t.minor = std::max(lc.major, rc.minor);
		}
	}
	void cover(PARAM, int x)
	{
		Node& t = nodes[code(CNT)];
		if (x >= t.major) return;
		t.sum -= (LL)t.t * (t.major - x);
		t.major = x;
		t.lazy = ~t.lazy ? std::min(t.lazy, x) : x;
	}
	void pushdown(PARAM)
	{
		Node& t = nodes[code(CNT)];
		DEF;
		Node& lc = nodes[code(LC)];
		Node& rc = nodes[code(RC)];
		if (~t.lazy)
		{
			cover(LC, t.lazy);
			cover(RC, t.lazy);
			t.lazy = -1;
		}
	}
	void modify_(PARAM)
	{
		if (nodes[code(CNT)].major <= g_Val) return;
		if (g_L <= l && r <= g_R && g_Val > nodes[code(CNT)].minor)
		{
			cover(CNT, g_Val);
			return;
		}
		pushdown(CNT);
		DEF;
		if (g_L <= mid) modify_(LC);
		if (g_R > mid) modify_(RC);
		update(CNT);
	}
	LL sum_(PARAM)
	{
		if (g_L <= l && r <= g_R)
			return nodes[code(CNT)].sum;
		pushdown(CNT);
		DEF;
		LL ret = 0;
		if (g_L <= mid) ret += sum_(LC);
		if (g_R > mid) ret += sum_(RC);
		return ret;
	}
	int max_(PARAM)
	{
		if (g_L <= l && r <= g_R)
			return nodes[code(CNT)].major;
		pushdown(CNT);
		DEF;
		int ret = 0;
		if (g_L <= mid) ret = max_(LC);
		if (g_R > mid) ret = std::max(ret, max_(RC));
		return ret;
	}

public:
	SegTree() {}
	SegTree(int n)
	{
		for (int i = 0, to = code(n, n); i <= to; i++)
			nodes[i].lazy = -1;
		build(1, n);
	}
	void build(PARAM)
	{
		if (l == r)
		{
			Node& t = nodes[code(CNT)];
			t.sum = a[l];
			t.major = a[l];
			t.t = 1;
			t.minor = -1;
			return;
		}
		DEF;
		build(LC); build(RC);
		update(CNT);
	}
	LL querySum(int l, int r)
	{
		g_L = l;
		g_R = r;
		return sum_(1, n);
	}
	int queryMax(int l, int r)
	{
		g_L = l;
		g_R = r;
		return max_(1, n);
	}
	void modify(int l, int r, int x)
	{
		g_L = l;
		g_R = r;
		g_Val = x;
		modify_(1, n);
	}
} st;

void run()
{
	int T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();
		for (int i = 1; i <= n; i++)
			a[i] = readIn();
		new(&st) SegTree(n);
		while (m--)
		{
			int type = readIn();
			int l = readIn();
			int r = readIn();
			if (type == 0)
			{
				int x = readIn();
				st.modify(l, r, x);
			}
			else if (type == 1)
			{
				printOut(st.queryMax(l, r));
			}
			else if (type == 2)
			{
				printOut(st.querySum(l, r));
			}
		}
	}
}

int main()
{
	std_init();
	run();
	std_out();
	return 0;
}