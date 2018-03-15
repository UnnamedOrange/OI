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

const int maxn = 105;
int n;
struct Rect
{
	double x1, y1;
	double x2, y2;
	void read()
	{
		scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
	}
} rects[maxn];

int bound;
double disc[maxn * 2];
void discretize()
{
	bound = 0;
	for (int i = 1; i <= n; i++)
	{
		disc[++bound] = rects[i].y1;
		disc[++bound] = rects[i].y2;
	}
	std::sort(disc + 1, disc + 1 + bound);
	bound = std::unique(disc + 1, disc + 1 + bound) - (disc + 1);
	for (int i = 1; i <= n; i++)
	{
		rects[i].y1 = std::lower_bound(disc + 1, disc + 1 + bound, rects[i].y1) - disc;
		rects[i].y2 = std::lower_bound(disc + 1, disc + 1 + bound, rects[i].y2) - disc;
	}
}

class SegTree
{
	struct Node
	{
		double sum;
		double qsum;
		int tag;
	} nodes[maxn * 4];
	static inline int code(int l, int r)
	{
		return (l + r) | (l != r);
	}

#define PARAM int l, int r
#define DEF int mid = (l + r) >> 1
#define CNT l, r
#define LC l, mid
#define RC mid + 1, r

	int g_L, g_R, g_Val;
	void add_(PARAM)
	{
		Node& t = nodes[code(CNT)];
		if (g_L <= l && r <= g_R)
		{
			t.tag += g_Val;
			if (t.tag) t.qsum = t.sum;
			else
			{
				if (l != r)
				{
					DEF;
					t.qsum = nodes[code(LC)].qsum + nodes[code(RC)].qsum;
				}
				else
				{
					t.qsum = 0;
				}
			}
			return;
		}
		DEF;
		if (g_L <= mid) add_(LC);
		if (g_R > mid) add_(RC);
		if (t.tag) t.qsum = t.sum;
		else t.qsum = nodes[code(LC)].qsum + nodes[code(RC)].qsum;
	}

public:
	double query()
	{
		return nodes[code(1, bound - 1)].qsum;
	}
	void add(int l, int r, int val)
	{
		g_L = l;
		g_R = r;
		g_Val = val;
		add_(1, bound - 1);
	}
	void init()
	{
		build(1, bound - 1);
	}
	void build(PARAM)
	{
		Node& t = nodes[code(CNT)];
		if (l == r)
		{
			t.sum = disc[l + 1] - disc[l];
			t.qsum = 0;
			t.tag = 0;
			return;
		}
		DEF;
		build(LC);
		build(RC);
		t.sum = nodes[code(LC)].sum + nodes[code(RC)].sum;
		t.qsum = 0;
		t.tag = 0;
	}
} st;

int nEvent;
struct Event
{
	double x;
	int idx;
	bool in;
	Event() {}
	Event(double x, int idx, bool in) : x(x), idx(idx), in(in) {}
	bool operator<(const Event& b) const
	{
		if (x != b.x) return x < b.x;
		return in > b.in;
	}
} events[maxn * 2];

void run()
{
	int T = 0;
	while (n = readIn())
	{
		T++;
		static bool printed;
		if (printed) putchar('\n');
		printed = true;
		printf("Test case #%d\n" "Total explored area: ", T);

		for (int i = 1; i <= n; i++)
			rects[i].read();
		discretize();

		nEvent = 0;
		for (int i = 1; i <= n; i++)
		{
			events[++nEvent] = Event(rects[i].x1, i, true);
			events[++nEvent] = Event(rects[i].x2, i, false);
		}
		std::sort(events + 1, events + 1 + nEvent);
		st.init();

		double ans = 0;
		double pre = 0;
		for (int i = 1; i <= nEvent; i++)
		{
			const Event& e = events[i];
			ans += (e.x - pre) * st.query();
			st.add(rects[e.idx].y1, rects[e.idx].y2 - 1, e.in ? 1 : -1);
			pre = e.x;
		}
		printf("%.2f\n", ans);
	}
}

int main()
{
	run();
	return 0;
}