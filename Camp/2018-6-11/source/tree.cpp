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

const int mod = 323232323;
const int maxn = int(1e5) + 5;
int lastans;
int t1 = true;
int n, m;

struct Area
{
	int l, r;
	int idx, parent;
	Area() {}
	Area(int l, int r, int idx, int parent) : l(l), r(r), idx(idx), parent(parent) {}
	bool operator<(const Area& b) const
	{
		if (l != b.l) return l < b.l;
		return r < b.r;
	}
};
std::vector<Area> areas;
std::map<Area, int> mid;

struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxn * 2];
	int head[maxn];
	int i;
	Graph() : i() { std::memset(head, -1, sizeof(head)); }
	void addEdge(int from, int to)
	{
		edges[i].to = to;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
#define idx(G) idx_##G
#define wander(G, node) for (int idx(G) = G.head[node]; ~idx(G); idx(G) = G.edges[idx(G)].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx(G)]; int to = e.to
} G;

int build(int l, int r, int parent)
{
	int ret = areas.size() + 1;
	areas.push_back(Area(l, r, ret, parent));
	int divide = 0;
	if (l != r) divide = readIn();
	mid[areas.back()] = divide;
	if (l == r) return ret;

	if (((l + r) >> 1) ^ divide) t1 ^= t1;
	G.addEdge(ret, build(l, divide, ret));
	G.addEdge(ret, build(divide + 1, r, ret));
	return ret;
}

#define RunInstance(x) delete new x
struct brute
{
	int g_L, g_R, g_P, g_Val;
	int ans[maxn * 2];
	void add1(int l, int r, int sum)
	{
		auto it = mid.find(Area(l, r, 0, 0));
		int idx = it->first.idx;
		(sum += ans[idx]) %= mod;
		if (g_L <= l && r <= g_R)
		{
			ans[idx] = (ans[idx] + (LL)g_P * (g_Val + sum)) % mod;
			return;
		}
		int divide = it->second;
		if (g_L <= divide) add1(l, divide, sum);
		if (g_R > divide) add1(divide + 1, r, sum);
		ans[idx] = (LL)ans[idx] * (mod + 1 - g_P) % mod;
	}
	void add(int l, int r, int p, int val)
	{
		g_L = l;
		g_R = r;
		g_P = p;
		g_Val = val;
		add1(1, n, 0);
	}

	brute() : ans()
	{
		while (m--)
		{
			int type = readIn();
			if (type == 1)
			{
				int l = readIn() ^ lastans;
				int r = readIn() ^ lastans;
				int p = readIn() ^ lastans;
				int v = readIn() ^ lastans;
				add(l, r, p, v);
			}
			else if (type == 2)
			{
				int t = readIn() ^ lastans;
				printOut(lastans = ans[t]);
				// lastans = 0;
			}
		}
	}
};
class SegTree
{
	static inline int code(int l, int r)
	{
		return (l + r) | (l != r);
	}
	struct Node
	{
		int sum;
		int lazy;
		Node() : lazy(1) {}
	} nodes[maxn * 4];
	int bound;

	int g_Pos, g_Val, g_L, g_R;
	void cover(int l, int r, int val)
	{
		Node& t = nodes[code(l, r)];
		t.sum = (LL)t.sum * val % mod;
		t.lazy = (LL)t.lazy * val % mod;
	}
	void pushdown(int l, int r)
	{
		Node& t = nodes[code(l, r)];
		if (t.lazy != 1)
		{
			int mid = (l + r) >> 1;
			cover(l, mid, t.lazy);
			cover(mid + 1, r, t.lazy);
			t.lazy = 1;
		}
	}
	void update(int l, int r)
	{
		Node& t = nodes[code(l, r)];
		int mid = (l + r) >> 1;
		const Node& lc = nodes[code(l, mid)];
		const Node& rc = nodes[code(mid + 1, r)];
		t.sum = (lc.sum + rc.sum) % mod;
	}

	void add_(int l, int r)
	{
		if (l == r)
		{
			(nodes[code(l, r)].sum += g_Val) %= mod;
			return;
		}
		pushdown(l, r);
		int mid = (l + r) >> 1;
		if (g_Pos <= mid) add_(l, mid);
		if (g_Pos > mid) add_(mid + 1, r);
		update(l, r);
	}
	int mul_(int l, int r)
	{
		if (g_L <= l && r <= g_R)
		{
			int ret = nodes[code(l, r)].sum;
			cover(l, r, g_Val);
			return ret;
		}
		pushdown(l, r);
		int mid = (l + r) >> 1;
		LL ret = 0;
		if (g_L <= mid) ret += mul_(l, mid);
		if (g_R > mid) ret += mul_(mid + 1, r);
		update(l, r);
		return ret % mod;
	}
	int query_(int l, int r)
	{
		if (l == r)
			return nodes[code(l, r)].sum;
		pushdown(l, r);
		int mid = (l + r) >> 1;
		if (g_Pos <= mid) return query_(l, mid);
		else return query_(mid + 1, r);
	}

public:
	SegTree(int bound) : bound(bound) {}

	void add(int pos, int val)
	{
		g_Pos = pos;
		g_Val = val;
		add_(1, bound);
	}
	int mul(int l, int r, int val)
	{
		g_L = l;
		g_R = r;
		g_Val = val;
		return mul_(1, bound);
	}
	int query(int pos)
	{
		g_Pos = pos;
		return query_(1, bound);
	}
};
struct cheat
{
	SegTree st;

	int size[maxn * 2];
	int heavy[maxn * 2];
	int depth[maxn * 2];
	int parent[maxn * 2];
	void DFS1(int node)
	{
		heavy[node] = 0;
		size[node] = 1;
		wander(G, node)
		{
			DEF(G);
			depth[to] = depth[node] + 1;
			parent[to] = node;
			DFS1(to);
			if (!heavy[node] || size[to] > size[heavy[node]])
				heavy[node] = to;
			size[node] += size[to];
		}
	}
	int stamp;
	int dfn[maxn];
	int top[maxn];
	void DFS2(int node, int t)
	{
		dfn[node] = ++stamp;
		if (!t) t = node;
		top[node] = t;
		if (heavy[node])
			DFS2(heavy[node], t);
		wander(G, node)
		{
			DEF(G);
			if (to == heavy[node]) continue;
			DFS2(to, 0);
		}
	}

	int handle(int u, int v, int val)
	{
		int ret = 0;
		while (u)
		{
			if (depth[u] < depth[v])
				std::swap(u, v);
			ret = (ret + st.mul(dfn[top[u]], dfn[u], val)) % mod;
			u = parent[top[u]];
		}
		return ret;
	}

	cheat() : st(2 * n - 1)
	{
		parent[1] = 0;
		depth[1] = 1;
		DFS1(1);
		stamp = 0;
		DFS2(1, 0);

		while (m--)
		{
			int type = readIn();
			if (type == 1)
			{
				int l = readIn() ^ lastans;
				int r = readIn() ^ lastans;
				int p = readIn() ^ lastans;
				int v = readIn() ^ lastans;
				auto it = mid.find(Area(l, r, 0, 0));
				int sum = handle(1, it->first.parent, mod + 1 - p);
				st.add(dfn[it->first.idx], (LL)p * (v + sum) % mod);
			}
			else if (type == 2)
			{
				int t = readIn() ^ lastans;
				printOut(lastans = st.query(dfn[t]));
				// lastans = 0;
			}
		}
	}
};

void run()
{
	n = readIn();
	m = readIn();
	areas.reserve(2 * n - 1);
	build(1, n, 0);

	if (m <= 10 || t1)
		RunInstance(brute);
	else
		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	run();
	return 0;
}