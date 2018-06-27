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
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = int;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

struct Point
{
	LL x, y;
	int idx;
	Point() = default;
	Point(LL x, LL y) : x(x), y(y) {}
	void read()
	{
		x = readIn();
		y = readIn();
	}
	bool operator<(const Point& b) const
	{
		if (x != b.x) return x < b.x;
		return y < b.y;
	}
};

const int maxn = int(2e5) + 5;
int n;
Point p[2];
Point lamps[maxn];
int K[maxn];
LL Cross(const Point& a, const Point& b)
{
	return a.x * b.y - a.y * b.x;
}
bool comp(const int& a, const int& b)
{
	return lamps[a] < lamps[b];
}

void discretize()
{
	static LL disc[maxn];
	int bound;

	bound = 0;
	for (int i = 1; i <= n; i++)
		disc[++bound] = lamps[i].x;
	std::sort(disc + 1, disc + 1 + bound);
	bound = std::unique(disc + 1, disc + 1 + bound) - (disc + 1);
	for (int i = 1; i <= n; i++)
		lamps[i].x = std::lower_bound(disc + 1, disc + 1 + bound, lamps[i].x) - disc;

	bound = 0;
	for (int i = 1; i <= n; i++)
		disc[++bound] = lamps[i].y;
	std::sort(disc + 1, disc + 1 + bound);
	bound = std::unique(disc + 1, disc + 1 + bound) - (disc + 1);
	for (int i = 1; i <= n; i++)
		lamps[i].y = std::lower_bound(disc + 1, disc + 1 + bound, lamps[i].y) - disc;
}

struct BIT
{
	int c[maxn];
	static inline int lowbit(int x) { return x & -x; }
	void add(int pos, int val)
	{
		while (pos <= n)
		{
			c[pos] += val;
			pos += lowbit(pos);
		}
	}
	int query(int pos)
	{
		int ret = 0;
		while (pos)
		{
			ret += c[pos];
			pos ^= lowbit(pos);
		}
		return ret;
	}
} bit;

int idx[maxn];
int d[maxn];
int ans[maxn];
void solve(int l, int r, int from, int to)
{
	if (l == r)
	{
		for (int i = from; i <= to; i++)
			ans[idx[i]] = l;
		return;
	}
	int mid = (l + r) >> 1;
	int nr = from - 1;
	int nl = to + 1;
	for (int i = from; i <= to; i++)
	{
		int temp2 = bit.query(lamps[idx[i]].y);
		int temp = (idx[i] <= mid) || (temp2 >= K[idx[i]]);
		if (temp)
		{
			d[++nr] = idx[i];
			bit.add(lamps[idx[i]].y, 1);
		}
		else
		{
			d[--nl] = idx[i];
			K[idx[i]] -= temp2;
		}
	}
	for (int i = from; i <= nr; i++)
		bit.add(lamps[d[i]].y, -1);
	for (int i = from; i <= to; i++)
		idx[i] = d[i];
	if (from <= nr)
		solve(l, mid, from, nr);
	if (nl <= to)
	{
		std::reverse(idx + nl, idx + to + 1);
		solve(mid + 1, r, nl, to);
	}
}

void run()
{
	n = readIn();
	p[0].read();
	p[1].read();
	for (int i = 1; i <= n; i++)
		lamps[i].read();
	for (int i = 1; i <= n; i++)
		K[i] = readIn();

	if (!Cross(p[0], p[1]))
	{
		LL ratio = (INT_MAX >> 1) / std::max(p[0].x, p[0].y);
		p[0].x *= ratio;
		p[0].y *= ratio;
		p[1] = p[0];
		p[1].x--;
	}
	if (Cross(p[0], p[1]) < 0)
		std::swap(p[0], p[1]);

	for (int i = 1; i <= n; i++)
	{
		lamps[i] = Point(Cross(lamps[i], p[1]), Cross(p[0], lamps[i]));
		lamps[i].idx = i;
	}
	discretize();

	for (int i = 1; i <= n; i++)
		idx[i] = i;
	std::sort(idx + 1, idx + 1 + n, comp);
	solve(1, n, 1, n);
	for (int i = 1; i <= n; i++)
	{
		printOut(ans[i]);
		putchar(' ');
	}
}

int main()
{
#ifndef LOCAL
	freopen("lamp.in", "r", stdin);
	freopen("lamp.out", "w", stdout);
#endif
	run();
	return 0;
}