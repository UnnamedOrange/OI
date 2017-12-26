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

const INT maxn = 100005;
INT n, m;
INT prefixSum[maxn];
class SegTree
{
	static inline INT code(INT l, INT r)
	{
		return l + r | l != r;
	}
	struct Node
	{
		INT sum;
		INT lazy;
	} nodes[maxn * 2];
#define PARAM INT l, INT r
#define DEF INT node = code(l, r); INT mid = (l + r) >> 1
#define LC l, mid
#define RC mid + 1, r
#define CNT l, r
	void cover(PARAM, INT val)
	{
		if (val)
		{
			DEF;
			nodes[node].sum += val * (prefixSum[r] - prefixSum[l - 1]);
			nodes[node].lazy += val;
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
		nodes[node].sum = nodes[code(l, mid)].sum + nodes[code(mid + 1, r)].sum;
	}
	INT g_L, g_R, g_Val;
	INT handle_(PARAM)
	{
		DEF;
		if (g_L <= l && r <= g_R)
		{
			cover(CNT, g_Val);
			return nodes[node].sum;
		}
		pushdown(CNT);
		INT ret = 0;
		if (g_L <= mid) ret += handle_(LC);
		if (g_R > mid) ret += handle_(RC);
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
#undef DEF
} st;
struct Graph
{
	INT i;
	struct Edge
	{
		INT to;
		INT cost;
		INT next;
	} edges[maxn];
	INT head[maxn];
	Graph() : i(), head() {}
	void addEdge(INT from, INT to)
	{
		i++;
		edges[i].to = to;
		edges[i].next = head[from];
		head[from] = i;
	}
#define wander(G, node) for(int i = G.head[node]; i; i = G.edges[i].next)
#define DEF(G) const Graph::Edge& e = G.edges[i]; INT to = e.to; INT cost = e.cost
} G;
namespace DOC
{
	INT parent[maxn];
	INT depth[maxn];
	INT costs[maxn];
	INT dis[maxn];
	INT size[maxn];
	INT heavy[maxn];
	void DFS1(INT node)
	{
		INT maxSize = 0;
		size[node] = 1;
		depth[node] = depth[parent[node]] + 1;
		wander(G, node)
		{
			DEF(G);
			parent[to] = node;
			costs[to] = cost;
			dis[to] = dis[node] + cost;
			DFS1(to);
			size[node] += size[to];
			if (size[to] > maxSize)
			{
				maxSize = size[to];
				heavy[node] = to;
			}
		}
	}
	INT top[maxn];
	INT dfn[maxn];
	INT seq[maxn];
	void DFS2(INT node, INT cntTop)
	{
		static INT clock;
		clock++;
		dfn[node] = clock;
		seq[clock] = node;
		top[node] = cntTop;
		if (heavy[node])
		{
			DFS2(heavy[node], cntTop);
		}
		wander(G, node)
		{
			DEF(G);
			if (to == heavy[node])
				continue;
			DFS2(to, to);
		}
	}
	void initDOC()
	{
		DFS1(1);
		DFS2(1, 1);
		for (int i = 1; i <= n; i++)
			prefixSum[i] = prefixSum[i - 1] + costs[seq[i]];
	}
	INT driver(INT u, INT v, INT val = 0)
	{
		INT ret = 0;
		while (top[u] != top[v])
		{
			if (depth[top[u]] < depth[top[v]])
				std::swap(u, v);
			ret += st.handle(dfn[top[u]], dfn[u], val);
			u = parent[top[u]];
		}
		if (dfn[u] > dfn[v])
			std::swap(u, v);
		ret += st.handle(dfn[u], dfn[v], val);
		return ret;
	}
}
using namespace DOC;

bool isBlack[maxn];
INT nBlack;
INT disBlack;
void run()
{
	n = readIn();
	m = readIn();
	for (int i = 2; i <= n; i++)
	{
		INT from = readIn() + 1;
		G.addEdge(from, i);
	}
	for (int i = 1; i < n; i++)
		G.edges[i].cost = readIn();
	initDOC();

	while (m--)
	{
		INT ins = readIn();
		INT x = readIn() + 1;
		if (ins == 1)
		{
			if (!isBlack[x])
			{
				isBlack[x] = true;
				nBlack++;
				disBlack += dis[x];
				driver(1, x, 2);
			}
		}
		else if (ins == 2)
		{
			printOut(nBlack * dis[x] + disBlack - driver(1, x));
		}
	}
}

int main()
{
	run();
	return 0;
}