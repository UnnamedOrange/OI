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
typedef LL INT_PUT;
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

const int maxn = int(2e5) + 5;
int n;
int logn;
int parent[19][maxn];
LL cost[maxn];
LL p[maxn], q[maxn], l[maxn];

struct Graph
{
	struct Edge
	{
		int to;
		LL cost;
		int next;
	} edges[maxn];
	int i;
	int head[maxn];
	Graph() : i() { memset(head, -1, sizeof(head)); }
	void addEdge(int from, int to, LL cost)
	{
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
#define idx(G) idx_##G
#define wander(G, node) for (int idx(G) = G.head[node]; ~idx(G); idx(G) = G.edges[idx(G)].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx(G)]; int to = e.to; LL cost = e.cost
} G;

LL f[maxn];
int depth[maxn];
LL dis[19][maxn];
LL Depth[maxn];

int stack[maxn];
int tail;
double slope(int j, int k)
{
	return (double)(f[j] - f[k]) / (Depth[j] - Depth[k]);
}
LL DP(int i, int j)
{
	return f[j] + (Depth[i] - Depth[j]) * p[i] + q[i];
}
class SegTree
{
	int stack[maxn * 19];
	static inline int code(int l, int r)
	{
		return (l + r) | (l != r);
	}
	int size;
	int head[maxn * 2];
	int tail[maxn * 2];
	void build(int l, int r)
	{
		head[code(l, r)] = tail[code(l, r)] = size;
		size += r - l + 1;
		if (l == r)
			return;
		int mid = (l + r) >> 1;
		build(l, mid);
		build(mid + 1, r);
	}

	int g_Pos, g_Val;
	int g_L, g_R;

	struct RestoreRecord
	{
		int stackCode;
		int preTail;
		int prePos;
		int preVal;
		RestoreRecord() {}
		RestoreRecord(int sc, int pt, int pp, int pv) :
			stackCode(sc), preTail(pt), prePos(pp), preVal(pv) {}
	};
	std::vector<std::vector<RestoreRecord> > rr;
	std::vector<RestoreRecord> curRecord;

	void modify(int l, int r)
	{
		const int& h = head[code(l, r)];
		int& t = tail[code(l, r)];
		int step = 1;
		int cnt = t;
		if (t - h > 1)
		{
			while (step < t - h) step <<= 1;
			for (; step; step >>= 1) if (h + step < cnt)
			{
				if (slope(g_Val, stack[cnt - step]) <
					slope(stack[cnt - step], stack[cnt - step - 1]))
				{
					cnt -= step;
				}
			}
		}
		curRecord.push_back(RestoreRecord(code(l, r), t, cnt, stack[cnt]));
		t = cnt;
		stack[t++] = g_Val;

		if (l == r)
			return;
		int mid = (l + r) >> 1;
		if (g_Pos <= mid) modify(l, mid);
		if (g_Pos > mid) modify(mid + 1, r);
	}
	LL query_(int l, int r) const
	{
		if (g_L <= l && r <= g_R)
		{
			const int& h = head[code(l, r)];
			const int& t = tail[code(l, r)];
			int step = 1;
			while (step < t - h) step <<= 1;
			int cnt = h;
			if (t - h > 1)
			{
				for (; step; step >>= 1) if (cnt + step < t)
				{
					if (slope(stack[cnt + step], stack[cnt + step - 1]) < p[g_Val])
					{
						cnt += step;
					}
				}
			}
			return DP(g_Val, stack[cnt]);
		}
		int mid = (l + r) >> 1;
		LL ret = LLONG_MAX;
		if (g_L <= mid) ret = std::min(ret, query_(l, mid));
		if (g_R > mid) ret = std::min(ret, query_(mid + 1, r));
		return ret;
	}

public:
	void build()
	{
		build(1, n);
	}
	void push(int pos, int val)
	{
		g_Pos = pos;
		g_Val = val;
		modify(1, n);
		rr.push_back(std::move(curRecord));
	}
	void restore()
	{
		std::vector<RestoreRecord> r(std::move(rr.back()));
		rr.pop_back();
		for (const RestoreRecord& t : r)
		{
			stack[t.prePos] = t.preVal;
			tail[t.stackCode] = t.preTail;
		}
	}
	LL query(int l, int r, int val)
	{
		g_L = l;
		g_R = r;
		g_Val = val;
		return query_(1, n);
	}
} st;

void DFS(int node)
{
	wander(G, node)
	{
		DEF(G);
		depth[to] = depth[node] + 1;
		Depth[to] = Depth[node] + cost;
		dis[0][to] = cost;
		for (int i = 1; i <= logn; i++)
		{
			parent[i][to] = parent[i - 1][parent[i - 1][to]];
			dis[i][to] = dis[i - 1][to] + dis[i - 1][parent[i - 1][to]];
		}
		int cnt = to;
		LL remain = l[to];
		for (int i = logn; ~i; i--) if (parent[i][cnt])
		{
			if (remain < dis[i][cnt]) continue;
			remain -= dis[i][cnt];
			cnt = parent[i][cnt];
		}
		f[to] = st.query(depth[cnt], depth[node], to);

		st.push(depth[to], to);
		DFS(to);
		st.restore();
	}
}

void run()
{
	n = readIn();
	while (1 << logn < n) logn++;
	readIn();
	for (int i = 2; i <= n; i++)
	{
		parent[0][i] = readIn();
		cost[i] = readIn();
		p[i] = readIn();
		q[i] = readIn();
		l[i] = readIn();
		G.addEdge(parent[0][i], i, cost[i]);
	}
	st.build();
	st.push(1, 1);
	depth[1] = 1;
	Depth[1] = 0;
	DFS(1);
	for (int i = 2; i <= n; i++)
		printOut(f[i]);
}

int main()
{
	run();
	return 0;
}