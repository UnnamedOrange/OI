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
#include <list>
typedef long long INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
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
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT mod = 1000000009;
const INT maxn = 500005;
INT n, m;
struct Area
{
	INT l;
	INT r;
	void read()
	{
		l = readIn();
		r = readIn();
	}
	bool operator< (const Area& b) const
	{
		//if (l != b.l)
		return l < b.l;
		//return r > b.r;
	}
} areas[maxn];
INT points[maxn];
INT V;

#define RunInstance(x) delete new x
struct brute
{
	INT events[3][65];

	brute() : events()
	{
		INT ans = 0;
		INT U = 1 << n;
		for (int i = 1; i <= V; i++)
			events[1][i]++;

		for (int S = 0; S < U; S++)
		{
			for (int i = 0; i < n; i++)
				if (S & (1 << i))
				{
					events[0][areas[i + 1].l]++;
					events[2][areas[i + 1].r]++;
				}

			INT cnt = 0;
			INT covered = 0;
			for (int i = 1; i <= V; i++)
			{
				cnt += events[0][i];
				if (cnt) covered += events[1][i];
				cnt -= events[2][i];
			}
			if (covered == m) ans++;

			for (int i = 0; i < n; i++)
				if (S & (1 << i))
				{
					events[0][areas[i + 1].l]--;
					events[2][areas[i + 1].r]--;
				}
		}
		printOut(ans);
	}
};
class SegTree
{
	struct Node
	{
		INT sum;
		INT add;
		INT mul;
		Node() : sum(0), add(0), mul(1) {}
	} nodes[maxn * 2];
	inline static INT code(INT l, INT r)
	{
		return l + r | l != r;
	}

#define PARAM INT l, INT r
#define DEF INT node = code(l, r); INT mid = (l + r) >> 1
#define CNT l, r
#define LC l, mid
#define RC mid + 1, r

	void cover(PARAM, INT ad, INT mu)
	{
		DEF;
		Node& t = nodes[node];
		if (mu != 1)
		{
			t.sum = t.sum * mu % mod;
			t.mul = t.mul * mu % mod;
			t.add = t.add * mu % mod;
		}
		if (ad)
		{
			t.sum = (t.sum + ad * (r - l + 1)) % mod;
			t.add = (t.add + ad) % mod;
		}
	}
	void pushdown(PARAM)
	{
		DEF;
		INT& ad = nodes[node].add;
		INT& mu = nodes[node].mul;
		if (mu != 1 || ad)
		{
			cover(LC, ad, mu);
			cover(RC, ad, mu);
			ad = 0;
			mu = 1;
		}
	}
	INT g_L, g_R, g_Mul, g_Add;
	INT handle_(PARAM)
	{
		DEF;
		if (g_L <= l && r <= g_R)
		{
			if (g_Add || g_Mul != 1)
				cover(CNT, g_Add, g_Mul);
			return nodes[node].sum;
		}
		pushdown(CNT);
		INT ret = 0;
		if (g_L <= mid) ret = (ret + handle_(LC)) % mod;
		if (g_R > mid) ret = (ret + handle_(RC)) % mod;
		nodes[node].sum = (nodes[code(l, mid)].sum + nodes[code(mid + 1, r)].sum) % mod;
		return ret;
	}

public:
	void mul(INT l, INT r, INT v)
	{
		g_L = l;
		g_R = r;
		g_Mul = v;
		g_Add = 0;
		handle_(0, V);
	}
	void add(INT l, INT r, INT v)
	{
		g_L = l;
		g_R = r;
		g_Mul = 1;
		g_Add = v;
		handle_(0, V);
	}
	INT query(INT l, INT r)
	{
		g_L = l;
		g_R = r;
		g_Mul = 1;
		g_Add = 0;
		return handle_(0, V);
	}
};
struct work
{
	SegTree st;

	work()
	{
		INT power2 = 0;
		st.add(0, 0, 1);
		for (int i = 1; i <= n; i++)
		{
			INT l = areas[i].l;
			INT r = areas[i].r;
			if (l > r)
			{
				power2++;
				continue;
			}
			st.mul(r, V, 2);
			st.add(r, r, st.query(l - 1, r - 1));
		}
		printOut(st.query(V, V) * ((1ll << power2) % mod) % mod);
	}
};

void discretize()
{
	std::sort(points + 1, points + 1 + m);
	V = std::unique(points + 1, points + 1 + m) - (points + 1);
	for (int i = 1; i <= n; i++)
	{
		areas[i].l = std::lower_bound(points + 1, points + 1 + V, areas[i].l) - points;
		areas[i].r = std::upper_bound(points + 1, points + 1 + V, areas[i].r) - points - 1;
	}
}
void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		areas[i].read();
	for (int i = 1; i <= m; i++)
		points[i] = readIn();
	discretize();
	std::sort(areas + 1, areas + 1 + n);

	if (n <= 20 && m <= 20)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("xmasinterval.in", "r", stdin);
	freopen("xmasinterval.out", "w", stdout);
#endif
	run();
	return 0;
}