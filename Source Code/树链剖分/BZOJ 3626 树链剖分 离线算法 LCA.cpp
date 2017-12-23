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

const INT mod = 201314;
const INT maxn = 50005;
INT n, q;
INT parent[maxn];
struct Graph
{
	INT count_;
	struct Edge
	{
		INT to;
		INT next;
	} edges[maxn];
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

class SegTree
{
	inline static INT area(INT l, INT r)
	{
		return l + r | l != r;
	}
	struct Node
	{
		INT sum;
		INT lazy;
	} nodes[maxn * 2];

#define PARAM INT l, INT r
#define DEF INT node = area(l, r); INT mid = (l + r) >> 1; INT lc = area(l, mid); INT rc = area(mid + 1, r)
#define LC l, mid
#define RC mid + 1, r
#define CNT l, r
	INT g_Val, g_L, g_R;
	void cover(PARAM, INT val)
	{
		if (val)
		{
			DEF;
			nodes[node].sum = (nodes[node].sum + val * (r - l + 1)) % mod;
			nodes[node].lazy = (nodes[node].lazy + val) % mod;
		}
	}
	void pushdown(PARAM)
	{
		DEF;
		INT& v = nodes[node].lazy;
		if (v)
		{
			cover(LC, v);
			cover(RC, v);
			v = 0;
		}
	}
	void update(PARAM)
	{
		DEF;
		nodes[node].sum = (nodes[lc].sum + nodes[rc].sum) % mod;
	}
	INT handle_(PARAM)
	{
		DEF;
		if (l == r)
		{
			cover(CNT, g_Val);
			return nodes[node].sum;
		}
		pushdown(CNT);
		INT ret = 0;
		if (g_L <= mid) ret = (ret + handle_(LC)) % mod;
		if (g_R > mid) ret = (ret + handle_(RC)) % mod;
		update(CNT);
		return ret;
	}

public:
	INT handle(INT l, INT r, INT val)
	{
		g_L = l;
		g_R = r;
		g_Val = val;
		return handle_(1, n);
	}
} st;
namespace DOC
{
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
			if (to == heavy[node])
				continue;
			DFS2(to, to);
		}
	}

	INT driver(INT u, INT v, INT val = 0)
	{
		INT ret = 0;
		while (top[u] != top[v])
		{
			if (depth[top[u]] < depth[top[v]])
				std::swap(u, v);
			ret = (ret + st.handle(dfn[top[u]], dfn[u], val)) % mod;
			u = parent[top[u]];
		}
		if (dfn[u] > dfn[v])
			std::swap(u, v);
		ret = (ret + st.handle(dfn[u], dfn[v], val)) % mod;
		return ret;
	}
}
using namespace DOC;

struct Query
{
	INT l, r, z;
	INT negative, positive;
	Query() : negative(-1) {}
	void read()
	{
		l = readIn() + 1;
		r = readIn() + 1;
		z = readIn() + 1;
	}
	void handle(INT x)
	{
		if (!~negative)
			negative = x;
		else
			positive = x;
	}
	void print()
	{
		printOut(((positive - negative) % mod + mod) % mod);
	}
} query[maxn];
std::vector<INT> offline[maxn];

void run()
{
	n = readIn();
	q = readIn();
	for (int i = 2; i <= n; i++)
	{
		INT from = parent[i] = readIn() + 1;
		G.addEdge(from, i);
	}
	DFS1(1);
	DFS2(1, 1);
	for (int i = 1; i <= q; i++)
	{
		query[i].read();
		offline[query[i].l - 1].push_back(i);
		offline[query[i].r].push_back(i);
	}
	for (int i = 0; i < offline[0].size(); i++)
		query[offline[0][i]].handle(0);
	for (int i = 1; i <= n; i++)
	{
		driver(1, i, 1);
		for (int j = 0; j < offline[i].size(); j++)
			query[offline[i][j]].handle(driver(1, query[offline[i][j]].z));
	}
	for (int i = 1; i <= q; i++)
		query[i].print();
}

int main()
{
	run();
	return 0;
}