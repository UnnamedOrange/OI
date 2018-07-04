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
int n, m;
int a[maxn];
struct Ins
{
	int type;
	int l, r;
	int x;
	int idx;
	void read()
	{
		type = readIn();
		if (type == 1)
		{
			l = readIn();
			x = readIn();
		}
		else if (type == 2)
		{
			l = readIn();
			r = readIn();
			x = readIn();
		}
	}
} tempInss[maxn];
int bound;
int disc[maxn * 2];
void discretize()
{
	bound = 0;
	for (int i = 1; i <= n; i++)
		disc[++bound] = a[i];
	for (int i = 1; i <= m; i++)
		if (tempInss[i].type == 1)
			disc[++bound] = tempInss[i].x;
	std::sort(disc + 1, disc + 1 + bound);
	bound = std::unique(disc + 1, disc + 1 + bound) - (disc + 1);
	for (int i = 1; i <= n; i++)
		a[i] = std::lower_bound(disc + 1, disc + 1 + bound, a[i]) - disc;
	for (int i = 1; i <= m; i++)
		if (tempInss[i].type == 1)
			tempInss[i].x = std::lower_bound(disc + 1, disc + 1 + bound, tempInss[i].x) - disc;
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

int N, M;
Ins inss[maxn * 3];
int temp[maxn * 3];
int idx[maxn * 3];
int ans[maxn];
void solve(int l, int r, int from, int to)
{
	if (r - l <= 0)
	{
		for (int i = from; i <= to; i++)
			if (inss[idx[i]].type == 3)
				ans[inss[idx[i]].idx] = l;
		return;
	}
	int mid = (l + r) >> 1;
	int lEnd = from - 1;
	int rBegin = to + 1;

	for (int i = from; i <= to; i++)
	{
		Ins& ins = inss[idx[i]];
		if (ins.type == 1)
		{
			if (ins.x <= mid)
			{
				bit.add(ins.l, 1);
				temp[++lEnd] = idx[i];
			}
			else
				temp[--rBegin] = idx[i];
		}
		else if (ins.type == 2)
		{
			if (ins.x <= mid)
			{
				bit.add(ins.l, -1);
				temp[++lEnd] = idx[i];
			}
			else
				temp[--rBegin] = idx[i];
		}
		else if (ins.type == 3)
		{
			int t = bit.query(ins.l, ins.r);
			if (t < ins.x)
			{
				ins.x -= t;
				temp[--rBegin] = idx[i];
			}
			else
				temp[++lEnd] = idx[i];
		}
	}
	for (int i = from; i <= to; i++)
	{
		const Ins& ins = inss[idx[i]];
		if (ins.type != 3 && ins.x <= mid)
			bit.clear(ins.l);
	}

	for (int i = from; i <= to; i++)
		idx[i] = temp[i];
	if (from <= lEnd)
		solve(l, mid, from, lEnd);
	if (rBegin <= to)
	{
		std::reverse(idx + rBegin, idx + 1 + to);
		solve(mid + 1, r, rBegin, to);
	}
}

void run()
{
	while (~scanf("%d", &n))
	{
		for (int i = 1; i <= n; i++)
			a[i] = readIn();
		m = readIn();
		for (int i = 1; i <= m; i++)
			tempInss[i].read();
		discretize();

		N = M = 0;

		for (int i = 1; i <= n; i++)
		{
			inss[++N].type = 1;
			inss[N].l = i;
			inss[N].x = a[i];
		}
		for (int i = 1; i <= m; i++)
		{
			const Ins& ins = tempInss[i];
			if (ins.type == 1)
			{
				inss[++N].type = 2;
				inss[N].l = ins.l;
				inss[N].x = a[ins.l];

				a[ins.l] = ins.x;
				inss[++N].type = 1;
				inss[N].l = ins.l;
				inss[N].x = ins.x;
			}
			else if (ins.type == 2)
			{
				inss[++N] = ins;
				inss[N].type = 3;
				inss[N].idx = ++M;
			}
		}

		for (int i = 1; i <= N; i++)
			idx[i] = i;
		solve(1, bound, 1, N);
		for (int i = 1; i <= M; i++)
			printOut(disc[ans[i]]);
	}
}

int main()
{
	run();
	return 0;
}