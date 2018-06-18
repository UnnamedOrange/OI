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
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-'))
		ch = getchar();
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
	putchar('\n');
}

const int INF = (~(int(1) << (sizeof(int) * 8 - 1))) >> 1;
const int maxn = int(2e5) + 5;
int n, m;
struct Ins
{
	int type;
	int l, r, x;
	void read()
	{
		type = readIn();
		if (type == 1)
		{
			l = readIn();
			r = readIn();
			x = readIn();
		}
		else if (type == 2)
			x = readIn();
	}
} inss[maxn];

#define RunInstance(x) delete new x
struct brute
{
	std::vector<std::vector<int>> stack;

	brute()
	{
		stack.resize(n + 1);
		for (int i = 1; i <= m; i++)
		{
			const Ins &ins = inss[i];
			if (ins.type == 1)
			{
				for (int j = ins.l; j <= ins.r; j++)
				{
					while (stack[j].size() && stack[j].back() <= ins.x)
						stack[j].pop_back();
					stack[j].push_back(ins.x);
				}
			}
			else if (ins.type == 2)
			{
				LL ans = 0;
				for (int j = 0; j < stack[ins.x].size(); j++)
					ans += stack[ins.x][j];
				printOut(ans);
			}
		}
	}
};
struct work
{
	struct Query
	{
		int pos;
		int idx;
		Query() {}
		Query(int pos, int idx) : pos(pos), idx(idx) {}
		bool operator<(const Query& b) const
		{
			return pos < b.pos;
		}
	};
	int N;
	Query querys[maxn];
	int idx[maxn];
	int poss[maxn];

	class SegTree
	{
		static inline int code(int l, int r)
		{
			return (l + r) | (l != r);
		}
		struct Node
		{
			int major;
			int minor;
			LL sum;
			int lazy;
			void clear()
			{
				major = 0;
				minor = INF;
				sum = 0;
				lazy = 0;
			}
			Node() { clear(); }
		} nodes[maxn * 2];
		int bound;

		int g_L, g_R, g_Pos, g_Val;
		void cover(int l, int r, int val, LL val2)
		{
			Node& t = nodes[code(l, r)];
			if (val <= t.major) return; // note
			t.major = val;
			t.sum += val2;
			t.lazy = std::max(t.lazy, val);
		}
		void pushdown(int l, int r)
		{
			Node& t = nodes[code(l, r)];
			if (t.lazy || t.sum)
			{
				int mid = (l + r) >> 1;
				cover(l, mid, t.lazy, t.sum);
				cover(mid + 1, r, t.lazy, t.sum);
				t.lazy = 0;
				t.sum = 0;
			}
		}
		void update(int l, int r)
		{
			Node& t = nodes[code(l, r)];
			int mid = (l + r) >> 1;
			Node& lc = nodes[code(l, mid)];
			Node& rc = nodes[code(mid + 1, r)];
			if (lc.major == rc.major)
			{
				t.major = lc.major;
				t.minor = std::min(lc.minor, rc.minor);
			}
			else if (lc.major < rc.major)
			{
				t.major = lc.major;
				t.minor = std::min(lc.minor, rc.major);
			}
			else if (lc.major > rc.major)
			{
				t.major = rc.major;
				t.minor = std::min(lc.major, rc.minor);
			}
		}
		void checkmax_(int l, int r)
		{
			Node& t = nodes[code(l, r)];
			if (g_Val <= t.major)
				return;
			if (g_L <= l && r <= g_R && g_Val < t.minor)
			{
				cover(l, r, g_Val, g_Val);
				return;
			}
			pushdown(l, r);
			int mid = (l + r) >> 1;
			if (g_L <= mid) checkmax_(l, mid);
			if (g_R > mid) checkmax_(mid + 1, r);
			update(l, r);
		}
		void reset_(int l, int r)
		{
			if (l == r)
			{
				nodes[code(l, r)].clear();
				return;
			}
			pushdown(l, r);
			int mid = (l + r) >> 1;
			if (g_Pos <= mid) reset_(l, mid);
			else if (g_Pos > mid) reset_(mid + 1, r);
			update(l, r);
		}
		LL query_(int l, int r)
		{
			if (l == r)
			{
				return nodes[code(l, r)].sum;
			}
			pushdown(l, r);
			int mid = (l + r) >> 1;
			if (g_Pos <= mid) return query_(l, mid);
			else if (g_Pos > mid) return query_(mid + 1, r);
		}

	public:
		void SetBound(int b) { bound = b; }
		void checkmax(int l, int r, int val)
		{
			g_L = l;
			g_R = r;
			g_Val = val;
			checkmax_(1, bound);
		}
		void reset(int pos)
		{
			g_Pos = pos;
			reset_(1, bound);
		}
		LL query(int pos)
		{
			g_Pos = pos;
			return query_(1, bound);
		}
	} st;

	work() : N(), idx(), poss()
	{
		for (int i = 1; i <= m; i++)
		{
			if (inss[i].type == 2)
			{
				++N;
				querys[N] = Query(inss[i].x, i);
			}
		}
		st.SetBound(N);
		std::sort(querys + 1, querys + 1 + N);
		for (int i = 1; i <= N; i++)
			poss[i] = querys[i].pos;
		for (int i = 1; i <= N; i++)
			idx[querys[i].idx] = i;

		for (int i = 1; i <= m; i++)
		{
			if (inss[i].type == 1)
			{
				int newL = std::lower_bound(poss + 1, poss + 1 + N, inss[i].l) - poss;
				int newR = std::upper_bound(poss + 1, poss + 1 + N, inss[i].r) - poss - 1;
				if (newL > newR)
					inss[i].type = 0;
				else
				{
					inss[i].l = newL;
					inss[i].r = newR;
				}
			}
		}

		for (int i = m; i >= 1; i--)
		{
			if (inss[i].type == 1)
			{
				st.checkmax(inss[i].l, inss[i].r, inss[i].x);
			}
			else if (inss[i].type == 2)
			{
				st.reset(idx[i]);
			}
		}

		for (int i = 1; i <= m; i++)
		{
			if (inss[i].type == 2)
			{
				printOut(st.query(idx[i]));
			}
		}
	}
};

void run()
{
	n = readIn();
	m = readIn();
	bool appear = false;
	bool t1 = true;
	for (int i = 1; i <= m; i++)
	{
		inss[i].read();
		if (inss[i].type == 2)
			appear = true;
		if (appear && inss[i].type == 1)
			t1 = false;
	}

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("stack.in", "r", stdin);
	freopen("stack.out", "w", stdout);
#endif
	run();
	return 0;
}