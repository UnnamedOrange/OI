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
using INT_PUT = LL;
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

const int maxn = int(5e4) + 5;
int n, m;
struct Ins
{
	int type;
	int l, r;
	LL x;
	void read()
	{
		type = readIn();
		l = readIn();
		r = readIn();
		x = readIn();
	}
} inss[maxn];
int Q;
int idxInQuery[maxn];
int bound;
LL disc[maxn];
void discretize()
{
	for (int i = 1; i <= m; i++)
		if (inss[i].type == 1)
			disc[++bound] = inss[i].x;
	std::sort(disc + 1, disc + 1 + bound);
	bound = std::unique(disc + 1, disc + 1 + bound) - (disc + 1);
	for (int i = 1; i <= m; i++)
		if (inss[i].type == 1)
			inss[i].x = std::lower_bound(disc + 1, disc + 1 + bound, inss[i].x) - disc;
}

#define RunInstance(x) delete new x
struct work
{
	class SegTree
	{
		struct Node
		{
			LL sum, lazy;
			int lc, rc;
			void clear()
			{
				sum = lazy = NULL;
				lc = rc = NULL;
			}
		};
		Node nodes[maxn * 2];
		int size;
		int root;
		int g_L, g_R, g_Val;
		void newNode(int& node)
		{
			if (!node)
			{
				node = ++size;
				nodes[node].clear();
			}
		}
		void cover(int& node, int l, int r, LL val)
		{
			newNode(node);
			Node& t = nodes[node];
			t.sum += (r - l + 1) * val;
			t.lazy += val;
		}
		void pushdown(int& node, int l, int r)
		{
			Node& t = nodes[node];
			if (t.lazy)
			{
				int mid = (l + r) >> 1;
				cover(t.lc, l, mid, t.lazy);
				cover(t.rc, mid + 1, r, t.lazy);
				t.lazy = 0;
			}
		}
		void add_(int& node, int l, int r)
		{
			newNode(node);
			Node& t = nodes[node];
			if (g_L <= l && r <= g_R)
			{
				cover(node, l, r, g_Val);
				return;
			}
			pushdown(node, l, r);
			int mid = (l + r) >> 1;
			if (g_L <= mid) add_(t.lc, l, mid);
			if (g_R > mid) add_(t.rc, mid + 1, r);
			t.sum = nodes[t.lc].sum + nodes[t.rc].sum;
		}
		LL query_(int& node, int l, int r)
		{
			if (!node) return 0;
			Node& t = nodes[node];
			if (g_L <= l && r <= g_R)
			{
				return t.sum;
			}
			pushdown(node, l, r);
			int mid = (l + r) >> 1;
			LL ret = 0;
			if (g_L <= mid) ret += query_(t.lc, l, mid);
			if (g_R > mid) ret += query_(t.rc, mid + 1, r);
			return ret;
		}

	public:
		SegTree() { clear(); }
		void clear()
		{
			root = 0;
			nodes[0].clear();
			size = 0;
		}
		void add(int l, int r, int val)
		{
			g_L = l;
			g_R = r;
			g_Val = val;
			add_(root, 1, n);
		}
		LL query(int l, int r)
		{
			g_L = l;
			g_R = r;
			return query_(root, 1, n);
		}
	} st;

	int ans[maxn];
	int idx[maxn];
	int temp[maxn];
	void solve(int l, int r, int from, int to)
	{
		if (r - l <= 1)
		{
			for (int i = from; i <= to; i++)
				if (inss[idx[i]].type == 2)
					ans[idxInQuery[idx[i]]] = l;
			return;
		}
		int mid = (l + r) >> 1;

		st.clear();
		int lEnd = from - 1;
		int rBegin = to + 1;
		for (int i = from; i <= to; i++)
		{
			Ins& ins = inss[idx[i]];
			if (ins.type == 1)
			{
				if (ins.x >= mid)
				{
					temp[--rBegin] = idx[i];
					st.add(ins.l, ins.r, 1);
				}
				else
				{
					temp[++lEnd] = idx[i];
				}
			}
			else if (ins.type == 2)
			{
				LL t = st.query(ins.l, ins.r);
				if (t < ins.x)
				{
					ins.x -= t;
					temp[++lEnd] = idx[i];
				}
				else
				{
					temp[--rBegin] = idx[i];
				}
			}
		}

		for (int i = from; i <= to; i++)
			idx[i] = temp[i];
		if (from <= lEnd)
			solve(l, mid, from, lEnd);
		if (rBegin <= to)
		{
			std::reverse(idx + rBegin, idx + 1 + to);
			solve(mid, r, rBegin, to);
		}
	}

	work()
	{
		for (int i = 1; i <= m; i++)
			idx[i] = i;
		solve(1, bound + 1, 1, m);
		for (int i = 1; i <= Q; i++)
			printOut(disc[ans[i]]);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
		inss[i].read();
	discretize();
	for (int i = 1; i <= m; i++)
		if (inss[i].type == 2)
			idxInQuery[i] = ++Q;

	RunInstance(work);
}

int main()
{
	run();
	return 0;
}