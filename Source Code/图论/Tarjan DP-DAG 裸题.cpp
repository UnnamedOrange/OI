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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
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
inline void printOut(INT x)
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
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1))) >> 1;
const INT maxn = 10005;
const INT maxm = 100005;
INT n, m;
std::vector<std::vector<INT> > edges, G;
INT w[maxn];
INT belong[maxn];
INT W[maxn];

INT scc;
INT dfn[maxn];
INT low[maxn];
INT s[maxn];
bool inStack[maxn];
void dfs(INT node)
{
	static INT clock;
	clock++;
	dfn[node] = low[node] = clock;
	s[++s[0]] = node;
	inStack[node] = true;
	for (int i = 0; i < edges[node].size(); i++)
	{
		INT to = edges[node][i];
		if (!dfn[to])
		{
			dfs(to);
			low[node] = std::min(low[node], low[to]);
		}
		else if (inStack[to])
		{
			low[node] = std::min(low[node], dfn[to]);
		}
	}
	if (dfn[node] == low[node])
	{
		scc++;
		INT top;
		do
		{
			top = s[s[0]--];
			inStack[top] = false;
			belong[top] = scc;
			W[scc] += w[top];
		} while (top != node);
	}
}

INT f[maxn];
INT dp(INT node)
{
	if (f[node]) return f[node];
	for (int i = 0; i < G[node].size(); i++)
	{
		f[node] = std::max(f[node], dp(G[node][i]));
	}
	f[node] += W[node];
	return f[node];
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		w[i] = readIn();
	edges.resize(n + 1);
	for (int i = 1; i <= m; i++)
	{
		INT u = readIn();
		INT v = readIn();
		edges[u].push_back(v);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			dfs(i);

	G.resize(scc + 1);
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < edges[i].size(); j++)
			if (belong[i] != belong[edges[i][j]])
				G[belong[i]].push_back(belong[edges[i][j]]);

	INT ans = -INF;
	for (int i = 1; i <= scc; i++)
		ans = std::max(ans, dp(i));
	printOut(ans);
}

int main()
{
	run();
	return 0;
}
