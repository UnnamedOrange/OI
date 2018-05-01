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
#define loop register int
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
}
template<typename T>
inline void checkmin(T& x, const T& v) { x = std::min(x, v); }

int INF;
const int maxn = int(1e5) + 5;
const int maxm = int(3e5) + 5;
int n, m, k;
struct DS
{
	int size;
	int parent[maxn];
	DS() {}
	void clear(int s)
	{
		size = s;
		for (int i = 1; i <= s; i++)
			parent[i] = i;
	}
	int find(int x) { return x == parent[x] ? x : parent[x] = find(parent[x]); }
	bool judge(int x, int y) { return find(x) == find(y); }
	bool unite(int x, int y)
	{
		int px = find(x);
		int py = find(y);
		if (px == py) return false;
		size--;
		parent[py] = px;
		return true;
	}
} ds;
struct __Edge
{
	int from, to, cost;
	__Edge() {}
	__Edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
	void readWithoutCost()
	{
		from = readIn();
		to = readIn();
	}
	void read()
	{
		readWithoutCost();
		cost = readIn();
	}
	bool operator<(const __Edge& b) const
	{
		return cost < b.cost;
	}
} edges[maxm];
__Edge key[25];
int nSel, nGiveup;
__Edge sel[maxn], giveup[maxm];
int weight[maxn];

struct Edge
{
	int to;
	int cost;
	int next;
};
template <int N, int M>
struct Graph
{
	Edge edges[M];
	int i;
	int head[N];
	Graph() { clear(); }
	void addEdge(int from, int to, int cost)
	{
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
	void clear()
	{
		i = 0;
		memset(head, -1, sizeof(head));
	}
#define idx(G) idx_##G
#define wander(G, node) for (int idx(G) = G.head[node]; ~idx(G); idx(G) = G.edges[idx(G)].next)
#define DEF(G) const Edge& e = G.edges[idx(G)]; int to = e.to; int cost = e.cost
};
Graph<maxn, maxm * 2> O;

LL Weight[25];
int belong[maxn];
int rect[25][25];
int N;
void DFS1(int node, int block = 0)
{
	if (!block) block = ++N;
	Weight[block] += weight[node];
	belong[node] = block;
	wander(O, node)
	{
		DEF(O);
		if (!belong[to])
			DFS1(to, block);
	}
}

int M;
__Edge compressedEdges[25 * 25];
Graph<22, 22 * 2> G;
LL ans;
LL t;
LL size[25];

void solve()
{
	int U = 1 << k;
	for (loop S = 1; S < U; S++)
	{
		ds.clear(N);
		G.clear();
		bool bOk = true;
		for (int i = 0; i < k; i++)
		{
			if (S & (1 << i))
			{
				const __Edge& e = key[i + 1];
				if (!ds.unite(e.from, e.to))
				{
					bOk = false;
					break;
				}
			}
		}
		if (!bOk) continue;

		for (int i = 1; i <= M && ds.size > 1; i++)
		{
			const __Edge& e = compressedEdges[i];
			if (ds.unite(e.from, e.to))
			{
				G.addEdge(e.from, e.to, 0);
				G.addEdge(e.to, e.from, 0);
			}
		}

		t = 0;
		// TODO
		ans = std::max(ans, t);
	}
	printOut(ans);
}

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	for (int i = 1; i <= m; i++)
		edges[i].read();
	std::sort(edges + 1, edges + 1 + m);
	for (int i = 1; i <= k; i++)
		key[i].readWithoutCost();
	for (int i = 1; i <= n; i++)
		weight[i] = readIn();

	// DS
	ds.clear(n);
	for (int i = 1; i <= k; i++)
		ds.unite(key[i].from, key[i].to);

	// Kruskal
	for (int i = 1; i <= m; i++)
	{
		const __Edge& e = edges[i];
		if (ds.unite(e.from, e.to))
			sel[++nSel] = e;
		else
			giveup[++nGiveup] = e;
	}

	// compress
	for (int i = 1; i <= nSel; i++)
	{
		const __Edge& e = sel[i];
		O.addEdge(e.from, e.to, e.cost);
		O.addEdge(e.to, e.from, e.cost);
	}
	for (int i = 1; i <= n; i++)
		if (!belong[i])
			DFS1(i);

	// rebuild
	memset(&INF, 0x3f, sizeof(INF));
	memset(rect, 0x3f, sizeof(rect));
	for (int i = 1; i <= nGiveup; i++)
	{
		const __Edge& e = giveup[i];
		int from = belong[e.from];
		int to = belong[e.to];
		checkmin(rect[from][to], e.cost);
		checkmin(rect[to][from], e.cost);
	}
	for (int i = 1; i <= N; i++)
		for (int j = i + 1; j <= N; j++)
		{
			if (rect[i][j] >= INF) continue;
			compressedEdges[++M] = __Edge(i, j, rect[i][j]);
		}
	for (int i = 1; i <= k; i++)
	{
		key[i].from = belong[key[i].from];
		key[i].to = belong[key[i].to];
	}
	std::sort(compressedEdges + 1, compressedEdges + 1 + M);

	solve();
}

int main()
{
	run();
	return 0;
}