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
typedef int INT;
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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = 30005;
struct Graph
{
	INT count_;
	struct Edge
	{
		INT to;
		INT next;
	} edges[maxn * 2];
	INT head[maxn];
	Graph() : count_(), head() {}
	void addEdge(INT from, INT to)
	{
		count_++;
		edges[count_].to = to;
		edges[count_].next = head[from];
		head[from] = count_;
	}
#define wander(G, v) for(int i = G.head[v]; i; i = G.edges[i].next)
} G;
typedef Graph::Edge Edge;
INT n;
INT weight[maxn];

class SegTree
{
	inline static INT area(INT l, INT r)
	{
		return l + r | l != r;
	}
	struct Node
	{
		INT sum;
		INT max;
	} nodes[maxn * 2];

#define PARAM INT l, INT r
#define DEF INT node = area(l, r); INT mid = (l + r) >> 1; INT lc = area(l, mid); INT rc = area(mid + 1, r)
#define LC l, mid
#define RC mid + 1, r
#define CNT l, r
	INT g_Val, g_L, g_R, g_Pos;
	void update(PARAM)
	{
		DEF;
		nodes[node].sum = nodes[lc].sum + nodes[rc].sum;
		nodes[node].max = std::max(nodes[lc].max, nodes[rc].max);
	}
	void cover(PARAM, INT val)
	{
		DEF;
		nodes[node].sum = val * (r - l + 1);
		nodes[node].max = val;
	}
	void set_(PARAM)
	{
		DEF;
		if (l == r)
		{
			cover(CNT, g_Val);
			return;
		}
		if (g_Pos <= mid) set_(LC);
		else if (g_Pos > mid) set_(RC);
		update(CNT);
	}
	void query_(PARAM)
	{
		DEF;
		if (g_L <= l && r <= g_R)
		{
			g_Sum += nodes[node].sum;
			g_Max = std::max(g_Max, nodes[node].max);
			return;
		}
		if (g_L <= mid) query_(LC);
		if (g_R > mid) query_(RC);
	}

public:
	INT g_Sum, g_Max;
	void set(INT pos, INT val)
	{
		g_Pos = pos;
		g_Val = val;
		set_(1, n);
	}
	void query(INT l, INT r)
	{
		g_Sum = 0;
		g_Max = -INF;
		g_L = l;
		g_R = r;
		query_(1, n);
	}

	typedef INT(*F)(INT x);
	void build(INT l, INT r, F f)
	{
		DEF;
		if (l == r)
		{
			cover(l, r, f(l));
			return;
		}
		build(LC, f); build(RC, f);
		update(CNT);
	}
} st;
namespace DOC
{
	INT parent[maxn];
	INT depth[maxn];
	INT size[maxn];
	INT heavy[maxn];
	void DFS1(INT node)
	{
		INT maxSize = 0;
		size[node] = 1;
		depth[node] = depth[parent[node]] + 1;
		wander(G, node)
		{
			const Edge& e = G.edges[i];
			INT to = e.to;
			if (to == parent[node])
				continue;
			parent[to] = node;
			DFS1(to);
			size[node] += size[to];
			if (size[to] > maxSize)
			{
				maxSize = size[to];
				heavy[node] = to;
			}
		}
	}

	INT seq[maxn];
	INT dfn[maxn];
	INT top[maxn];
	void DFS2(INT node, INT cntTop)
	{
		static INT clock = 0;
		clock++;
		dfn[node] = clock;
		seq[clock] = node;
		top[node] = cntTop;
		if (heavy[node])
			DFS2(heavy[node], cntTop);
		wander(G, node)
		{
			const Edge& e = G.edges[i];
			INT to = e.to;
			if (to == parent[node] || to == heavy[node])
				continue;
			DFS2(to, to);
		}
	}

	INT g_Sum, g_Max;
	void driver(INT u, INT v)
	{
		g_Sum = 0;
		g_Max = -INF;
		while (top[u] != top[v])
		{
			if (depth[top[u]] < depth[top[v]])
				std::swap(u, v);
			st.query(dfn[top[u]], dfn[u]);
			g_Sum += st.g_Sum;
			g_Max = std::max(g_Max, st.g_Max);
			u = parent[top[u]];
		}
		if (dfn[u] > dfn[v])
			std::swap(u, v);
		st.query(dfn[u], dfn[v]);
		g_Sum += st.g_Sum;
		g_Max = std::max(g_Max, st.g_Max);
	}
}
using namespace DOC;

void run()
{
	n = readIn();
	for (int i = 2; i <= n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		G.addEdge(from, to);
		G.addEdge(to, from);
	}
	for (int i = 1; i <= n; i++)
		weight[i] = readIn();
	DFS1(1);
	DFS2(1, 1);
	st.build(1, n, [](INT x) { return weight[seq[x]]; });

	INT m = readIn();
	while (m--)
	{
		char str[10];
		scanf("%s", str);
		if (str[1] == 'H') //change
		{
			INT u = readIn();
			INT t = readIn();
			st.set(dfn[u], t);
		}
		else if (str[1] == 'M') //qmax
		{
			driver(readIn(), readIn());
			printOut(g_Max);
		}
		else if (str[1] == 'S') //qsum
		{
			driver(readIn(), readIn());
			printOut(g_Sum);
		}
	}
}

int main()
{
	run();
	return 0;
}