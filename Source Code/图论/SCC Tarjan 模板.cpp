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
using std::cin;
using std::cout;
using std::endl;
typedef int INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT maxn = 100005;
INT n, m;
std::vector<std::vector<INT> > edges;

INT count_;
INT dfn[maxn];
INT low[maxn];
bool inStack[maxn];
std::stack<INT> s;
std::vector<std::vector<INT> > scc;

void Tarjan(INT node)
{
	dfn[node] = low[node] = ++count_;
	s.push(node);
	inStack[node] = true;
	for (int i = 0; i < edges[node].size(); i++)
	{
		INT to = edges[node][i];
		if (!dfn[to])
		{
			Tarjan(to);
			low[node] = std::min(low[node], low[to]);
		}
		else
		{
			if (inStack[to])
				low[node] = std::min(low[node], dfn[to]);
		}
	}

	if (dfn[node] == low[node])
	{
		scc.push_back(std::vector<INT>());
		INT popped;
		do
		{
			popped = s.top();
			s.pop();
			inStack[popped] = false;
			scc.back().push_back(popped);
		} while (!s.empty() && popped != node);
	}
}

void run()
{
	n = readIn();
	m = readIn();
	edges.resize(n + 1);
	for (int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		edges[from].push_back(to);
	}

	for (int i = 1; i <= n; i++)
	{
		if (!dfn[i]) Tarjan(i);
	}
	for (int i = 0; i < scc.size(); i++)
	{
		for (int j = 0; j < scc[i].size(); j++)
		{
			printf("%d ", scc[i][j]);
		}
		puts("");
	}
}

int main()
{
	run();
	return 0;
}
