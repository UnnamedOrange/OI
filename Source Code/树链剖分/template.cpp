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
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = INT(1e5) + 5;
INT n, m, r, mod;
INT origin[maxn];

struct Edge
{
	INT to;
	INT next;
} edges[maxn * 2];
INT head[maxn];
void addEdge(INT from, INT to)
{
	static INT i;
	i++;
	edges[i].to = to;
	edges[i].next = head[from];
	head[from] = i;
}

INT parent[maxn];
INT depth[maxn];
INT size[maxn];

//dissection of tree chain
INT heavy[maxn];
INT top[maxn];
INT Index[maxn];
INT IndexT[maxn];
void dfs1(INT node)
{
	size[node] = 1;
	depth[node] = depth[parent[node]] + 1;

	INT maxVal = 0;
	INT maxIdx = 0;
	for (int i = head[node]; i; i = edges[i].next)
	{
		Edge& e = edges[i];
		INT to = e.to;
		if (to == parent[node]) continue;
		parent[to] = node;
		dfs1(to);
		size[node] += size[to];
		if (size[to] > maxVal)
		{
			maxVal = size[to];
			maxIdx = to;
		}
	}
	heavy[node] = maxIdx;
}
void dfs2(INT node, INT topIdx)
{
	Index[node] = ++Index[0];
	IndexT[Index[node]] = node;
	top[node] = topIdx;
	if (heavy[node]) dfs2(heavy[node], topIdx);
	for (int i = head[node]; i; i = edges[i].next)
	{
		Edge& e = edges[i];
		INT to = e.to;
		if (to == parent[node] || to == heavy[node]) continue;
		dfs2(to, to);
	}
}
void goDissect()
{
	dfs1(r);
	dfs2(r, r);
}

class SegTree
{
	struct Node
	{
		INT val;
		INT add;
	} nodes[262200];

#define PARAM INT node, INT l, INT r
#define DEF INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1
#define CNT node, l, r
#define LC lc, l, mid
#define RC rc, mid + 1, r
	void cover(PARAM, INT val)
	{
		if (val)
		{
			nodes[node].val = (nodes[node].val + val * (r - l + 1)) % mod;
			nodes[node].add = (nodes[node].add + val) % mod;
		}
	}
	void pushdown(PARAM)
	{
		DEF;
		if (nodes[node].add)
		{
			cover(LC, nodes[node].add);
			cover(RC, nodes[node].add);
			nodes[node].add = 0;
		}
	}
	INT g_L, g_R, g_Val;
	INT handle_(PARAM)
	{
		if (g_L <= l && r <= g_R)
		{
			cover(CNT, g_Val);
			return nodes[node].val;
		}
		DEF;
		pushdown(CNT);
		INT ret = 0;
		if (g_L <= mid) ret = (ret + handle_(LC)) % mod;
		if (g_R > mid) ret = (ret + handle_(RC)) % mod;
		nodes[node].val = (nodes[lc].val + nodes[rc].val) % mod;
		return ret;
	}

public:
	INT handle(INT l, INT r, INT val)
	{
		g_L = l;
		g_R = r;
		g_Val = val;
		return handle_(1, 1, n);
	}
	INT query(INT l, INT r)
	{
		g_L = l;
		g_R = r;
		g_Val = 0;
		return handle_(1, 1, n);
	}
	typedef INT(*Access)(INT x);
	void build(PARAM, Access f)
	{
		if (l == r)
		{
			nodes[node].val = f(l);
			return;
		}
		DEF;
		build(LC, f);
		build(RC, f);
		nodes[node].val = (nodes[lc].val + nodes[rc].val) % mod;
	}
} st;
INT getOriginOnChain(INT x)
{
	return origin[IndexT[x]];
}

//go on chain
INT wander(INT x, INT y, INT val = 0)
{
	INT ret = 0;
	while (top[x] != top[y])
	{
		if (depth[top[x]] < depth[top[y]]) std::swap(x, y);
		ret = (ret + st.handle(Index[top[x]], Index[x], val)) % mod;
		x = parent[top[x]];
	}
	if (Index[x] > Index[y]) std::swap(x, y);
	ret = (ret + st.handle(Index[x], Index[y], val)) % mod;
	return ret;
}

void run()
{
	n = readIn();
	m = readIn();
	r = readIn();
	mod = readIn();
	for (int i = 1; i <= n; i++)
		origin[i] = readIn();
	for (int i = 2; i <= n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		addEdge(from, to);
		addEdge(to, from);
	}

	goDissect();
	st.build(1, 1, n, getOriginOnChain);
	while (m--)
	{
		INT ins = readIn();
		if (ins == 1)
		{
			INT x = readIn();
			INT y = readIn();
			INT z = readIn();
			wander(x, y, z);
		}
		else if (ins == 2)
		{
			INT x = readIn();
			INT y = readIn();
			printOut(wander(x, y));
		}
		else if (ins == 3)
		{
			INT x = readIn();
			INT z = readIn();
			st.handle(Index[x], Index[x] + size[x] - 1, z);
		}
		else if (ins == 4)
		{
			INT x = readIn();
			printOut(st.query(Index[x], Index[x] + size[x] - 1));
		}
	}

}

int main()
{
	run();
	return 0;
}