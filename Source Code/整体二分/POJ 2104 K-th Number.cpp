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

const int maxn = int(1e5) + 5;
const int maxm = 5005;
int n, m;
int a[maxn];
int disc[maxn];
void discretize()
{
	std::memcpy(disc, a, sizeof(disc));
	disc[0] = n;
	std::sort(disc + 1, disc + 1 + disc[0]);
	disc[0] = std::unique(disc + 1, disc + 1 + disc[0]) - (disc + 1);
	for (int i = 1; i <= n; i++)
		a[i] = std::lower_bound(disc + 1, disc + 1 + disc[0], a[i]) - disc;
}
int seq[maxn]; // 第 i 小是谁

struct Query
{
	int l, r, k;
	void read()
	{
		l = readIn();
		r = readIn();
		k = readIn();
	}
	bool operator<(const Query& b) const
	{
		if (l != b.l) return l < b.l;
		return r < b.r;
	}
} querys[maxm];
int idx[maxm];
int ans[maxm];

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
	int query(int l, int r)
	{
		return query(r) - query(l - 1);
	}
	void clear(int pos)
	{
		while (pos <= n)
		{
			if (c[pos]) c[pos] = 0;
			else break;
			pos += lowbit(pos);
		}
	}
} bit;

int temp[maxn];
void solve(int l, int r, int from, int to)
{
	if (l == r)
	{
		for (int i = from; i <= to; i++)
			ans[idx[i]] = l;
		return;
	}
	int mid = (l + r) >> 1;

	int lEnd = from - 1;
	int rBegin = to + 1;

	int num = 0; // 第一个大于等于 l 的 seq 下标
	int step = 1;
	while ((step << 1) < n) step <<= 1;
	for (; step; step >>= 1)
		if (num + step <= n && a[seq[num + step]] < l)
			num += step;
	num++;

	// 统计
	for (int i = num; i <= n && a[seq[i]] <= mid; i++)
		bit.add(seq[i], 1);
	for (int i = from; i <= to; i++)
	{
		Query& q = querys[idx[i]];
		int t = bit.query(q.l, q.r);
		if (t < q.k)
		{
			q.k -= t;
			temp[--rBegin] = idx[i];
		}
		else
			temp[++lEnd] = idx[i];
	}
	for (int i = num; i <= n && a[seq[i]] <= mid; i++)
		bit.clear(seq[i]);

	for (int i = from; i <= to; i++)
		idx[i] = temp[i];

	if (from <= lEnd)
		solve(l, mid, from, lEnd);
	if (rBegin <= to)
	{
		// std::reverse(idx + rBegin, idx + to + 1); // 可以不写
		solve(mid + 1, r, rBegin, to);
	}
}
bool comp(const int& x, const int& y)
{
	return a[x] < a[y];
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	discretize();
	for (int i = 1; i <= n; i++)
		seq[i] = i;
	std::sort(seq + 1, seq + 1 + n, comp);

	for (int i = 1; i <= m; i++)
		querys[i].read();
	for (int i = 1; i <= m; i++)
		idx[i] = i;

	solve(1, disc[0], 1, m);
	for (int i = 1; i <= m; i++)
		printOut(disc[ans[i]]);
}

int main()
{
	run();
	return 0;
}