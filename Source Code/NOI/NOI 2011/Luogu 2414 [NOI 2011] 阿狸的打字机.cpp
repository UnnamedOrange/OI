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

const int maxn = int(1e5) + 5;
char origin[maxn];
int n, m, q;
int querys[maxn][2];
int pos[maxn];

int idx[maxn];
bool comp(const int& a, const int& b)
{
	return querys[a][1] < querys[b][1];
}
int ans[maxn];

struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxn];
	int i;
	int head[maxn];
	Graph() : i() { memset(head, -1, sizeof(head)); }
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
};
struct BIT
{
	int bit[maxn];
	static inline int lowbit(int x) { return x & -x; }
	BIT() : bit() {}

	void add(int pos, int val, int size)
	{
		while (pos <= size)
		{
			bit[pos] += val;
			pos += lowbit(pos);
		}
	}
	int query(int pos)
	{
		int ret = 0;
		while (pos)
		{
			ret += bit[pos];
			pos ^= lowbit(pos);
		}
		return ret;
	}
	int query(int l, int r)
	{
		return query(r) - query(l - 1);
	}
};

struct ACAutomaton
{
	static const int alphabet = 26;
	static inline int code(char ch)
	{
		return ch - 'a';
	}
	struct Node
	{
		int parent;
		int ch[alphabet];
		int fail;
		int suffix;
		bool at;
		Node() {}
	} nodes[maxn];
	int size;

	void build()
	{
		size = 1;
		int cnt = 0;
		for (char* ch = origin; *ch; ch++)
		{
			if (*ch == 'B')
				cnt = nodes[cnt].parent;
			else if (*ch == 'P')
			{
				nodes[cnt].at = true;
				pos[++n] = cnt;
			}
			else
			{
				int x = code(*ch);
				if (!nodes[cnt].ch[x])
				{
					nodes[cnt].ch[x] = size;
					nodes[size++].parent = cnt;
				}
				cnt = nodes[cnt].ch[x];
			}
		}
	}
	void initACAutomaton()
	{
		static int queue[maxn];
		int head = 0, tail = 0;
		queue[tail++] = 0;
		while (head != tail)
		{
			int from = queue[head++];
			for (int i = 0; i < alphabet; i++)
			{
				if (int t = nodes[from].ch[i])
				{
					int temp = nodes[from].fail;
					while (temp && !nodes[temp].ch[i])
						temp = nodes[temp].fail;
					nodes[t].fail = temp = from ? nodes[temp].ch[i] : 0;
					nodes[t].suffix = nodes[temp].at ? temp : nodes[temp].suffix;
					queue[tail++] = t;
				}
			}
		}
	}

	Graph G;
	void buildGraph()
	{
		for (int i = 1; i < size; i++)
			G.addEdge(nodes[i].suffix, i);
	}

	int stamp;
	void DFS()
	{
		stamp = 0;
		DFS(0);
	}
	int dfn[maxn];
	int end[maxn];
	void DFS(int node)
	{
		dfn[node] = ++stamp;
		wander(G, node)
		{
			DEF(G);
			DFS(to);
		}
		end[node] = stamp;
	}

	BIT bit;
	void query()
	{
		int cntq = 1;
		int cnt = 0;
		for (char* ch = origin; *ch; ch++)
		{
			if (*ch == 'B')
			{
				bit.add(dfn[cnt], -1, size);
				cnt = nodes[cnt].parent;
			}
			else if (*ch == 'P')
			{
				while (cntq <= q && pos[querys[idx[cntq]][1]] == cnt)
				{
					register int t = querys[idx[cntq]][0];
					ans[idx[cntq]] = bit.query(dfn[pos[t]], end[pos[t]]);
					cntq++;
				}
			}
			else
			{
				int x = code(*ch);
				cnt = nodes[cnt].ch[x];
				bit.add(dfn[cnt], 1, size);
			}
		}
	}
} ac;

void run()
{
	scanf("%s", origin);
	m = strlen(origin);
	ac.build();

	q = readIn();
	for (int i = 1; i <= q; i++)
	{
		querys[i][0] = readIn();
		querys[i][1] = readIn();
	}

	for (int i = 1; i <= q; i++)
		idx[i] = i;
	std::sort(idx + 1, idx + 1 + q, comp);

	ac.initACAutomaton();
	ac.buildGraph();
	ac.DFS();
	ac.query();
	for (int i = 1; i <= q; i++)
		printOut(ans[i]);
}

int main()
{
	run();
	return 0;
}