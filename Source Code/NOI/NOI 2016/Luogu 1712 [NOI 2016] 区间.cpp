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

const int INF = (~(int(1) << (sizeof(int) * 8 - 1)));
const int maxn = int(5e5) + 5;
int n, m;
struct Area
{
	int l, r;
	int length;
	void read()
	{
		l = readIn();
		r = readIn();
		length = r - l;
	}
	bool operator< (const Area& b) const
	{
		return length < b.length;
	}
} areas[maxn];

int bound;
int disc[maxn * 2];
void discretize()
{
	for (int i = 1; i <= n; i++)
	{
		disc[++bound] = areas[i].l;
		disc[++bound] = areas[i].r;
	}
	std::sort(disc + 1, disc + 1 + bound);
	bound = std::unique(disc + 1, disc + 1 + bound) - (disc + 1);
	for (int i = 1; i <= n; i++)
	{
		Area& t = areas[i];
		t.l = std::lower_bound(disc + 1, disc + 1 + bound, t.l) - disc;
		t.r = std::lower_bound(disc + 1, disc + 1 + bound, t.r) - disc;
	}
}

class SegTree
{
	static inline int code(int l, int r)
	{
		return (l + r) | (l != r);
	}
	struct Node
	{
		int max;
		int lazy;
	} nodes[maxn * 4];

	int g_L, g_R, g_Val;
	void cover(int l, int r, int val)
	{
		Node& t = nodes[code(l, r)];
		t.max += val;
		t.lazy += val;
	}
	void pushdown(int l, int r)
	{
		Node& t = nodes[code(l, r)];
		if (t.lazy)
		{
			int mid = (l + r) >> 1;
			cover(l, mid, t.lazy);
			cover(mid + 1, r, t.lazy);
			t.lazy = 0;
		}
	}
	void add(int l, int r)
	{
		if (g_L <= l && r <= g_R)
		{
			cover(l, r, g_Val);
			return;
		}
		pushdown(l, r);
		int mid = (l + r) >> 1;
		if (g_L <= mid) add(l, mid);
		if (g_R > mid) add(mid + 1, r);
		nodes[code(l, r)].max = std::max(
			nodes[code(l, mid)].max,
			nodes[code(mid + 1, r)].max);
	}

public:
	void add(int l, int r, int val)
	{
		g_L = l;
		g_R = r;
		g_Val = val;
		add(1, bound);
	}
	int max()
	{
		return nodes[code(1, bound)].max;
	}
} st;

void run()
{
	n = readIn();
	m = readIn();
	if (!m)
	{
		printOut(0);
		return;
	}
	for (int i = 1; i <= n; i++)
		areas[i].read();
	std::sort(areas + 1, areas + 1 + n);
	discretize();

	int ans = INF;

	int r = 0;
	for (int l = 1; l <= n; l++)
	{
		while (r < n && st.max() < m)
		{
			r++;
			st.add(areas[r].l, areas[r].r, 1);
		}
		if (st.max() < m) break;
		ans = std::min(ans, areas[r].length - areas[l].length);
		st.add(areas[l].l, areas[l].r, -1);
	}
	if (ans >= INF)
		printOut(-1);
	else
		printOut(ans);
}

int main()
{
	run();
	return 0;
}