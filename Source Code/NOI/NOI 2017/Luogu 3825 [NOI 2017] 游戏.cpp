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

const int maxn = int(5e4) + 5;
const int maxm = int(1e5) + 5;
int n, d;
char str[maxn];
int m;

struct Origin
{
	int idxa, idxb;
	int typea, typeb;
	void read()
	{
		char which[2][5];
		idxa = readIn();
		scanf("%s", which[0]);
		typea = which[0][0] - 'A';
		idxb = readIn();
		scanf("%s", which[1]);
		typeb = which[1][0] - 'A';
	}
} origins[maxm];

struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxm * 2];
	int head[maxn * 3];
	int i;
	void addEdge(int from, int to)
	{
		edges[i].to = to;
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
#define DEF(G) const Graph::Edge& e = G.edges[idx(G)]; int to = e.to
} G;

#define RunInstance(x) delete new x
struct work
{
	int pos[10];
	int prohibit[maxn];
	int code[3][maxn];

	bool inStack[maxn * 2];
	int stack[maxn * 2];
	int dfn[maxn * 2];
	int low[maxn * 2];
	int belong[maxn * 2];
	int N;
	int stamp;
	void initTarjan()
	{
		N = 0;
		stamp = 0;
		memset(inStack, 0, sizeof(inStack));
		memset(belong, 0, sizeof(belong));
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		stack[0] = 0;
	}
	void Tarjan(int node)
	{
		dfn[node] = low[node] = ++stamp;
		stack[++stack[0]] = node;
		inStack[node] = true;
		wander(G, node)
		{
			DEF(G);
			if (!dfn[to])
			{
				Tarjan(to);
				low[node] = std::min(low[node], low[to]);
			}
			else if (inStack[to])
			{
				low[node] = std::min(low[node], dfn[to]);
			}
		}
		if (dfn[node] == low[node])
		{
			N++;
			int top;
			do
			{
				top = stack[stack[0]--];
				inStack[top] = false;
				belong[top] = N;
			} while (top != node);
		}
	}

	work() : pos()
	{
		for (int i = 1; i <= n; i++)
			if (str[i] == 'x')
				pos[++pos[0]] = i;

		for (int i = 1; i <= n; i++)
		{
			if (str[i] == 'x')
				continue;
			prohibit[i] = str[i] - 'a';
			for (int j = 0, k = 0; j < 3; j++)
			{
				if (prohibit[i] == j) continue;
				code[j][i] = k++;
			}
		}

		bool flag = false;
		int U = 1 << d;
		for (int S = 0; S < U; S++)
		{
			for (int i = 0; i < d; i++)
			{
				prohibit[pos[i + 1]] = bool(S & (1 << i));
				for (int j = 0, k = 0; j < 3; j++)
				{
					if (prohibit[pos[i + 1]] == j) continue;
					code[j][pos[i + 1]] = k++;
				}
			}
			G.clear();
			for (int i = 1; i <= m; i++)
			{
				const Origin& t = origins[i];
				if (t.typea == prohibit[t.idxa])
					continue;
				if (t.typeb == prohibit[t.idxb])
				{
					int from = t.idxa + code[t.typea][t.idxa] * n;
					int to = t.idxa + !code[t.typea][t.idxa] * n;
					G.addEdge(from, to);
				}
				else
				{
					int from, to;
					from = t.idxa + code[t.typea][t.idxa] * n;
					to = t.idxb + code[t.typeb][t.idxb] * n;
					G.addEdge(from, to);
					from = t.idxb + !code[t.typeb][t.idxb] * n;
					to = t.idxa + !code[t.typea][t.idxa] * n;
					G.addEdge(from, to);
				}
			}

			initTarjan();
			for (int j = 1, to = n << 1; j <= to; j++)
				if (!dfn[j])
					Tarjan(j);

			bool bOk = true;
			for (int i = 1; i <= n; i++)
				if (belong[i] == belong[i + n])
				{
					bOk = false;
					break;
				}
			if (!bOk) continue;

			for (int i = 1; i <= n; i++)
			{
				if (belong[i] < belong[i + n])
				{
					if (prohibit[i]) putchar('A');
					else putchar('B');
				}
				else
				{
					if (prohibit[i] == 2) putchar('B');
					else putchar('C');
				}
			}
			return;
		}
		if (!flag)
			printOut(-1);
	}
};

void run()
{
	n = readIn();
	d = readIn();
	scanf("%s", str + 1);
	m = readIn();
	for (int i = 1; i <= m; i++)
		origins[i].read();

	RunInstance(work);
}

int main()
{
	run();
	return 0;
}