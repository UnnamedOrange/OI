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

const INT maxn = 200005;
INT n, m;
INT count_;
struct Edge
{
	INT to;
	INT cost;
	INT next;
} edges[maxn * 2];
INT head[maxn];
void addEdge(INT from, INT to, INT cost)
{
	count_++;
	edges[count_].to = to;
	edges[count_].cost = cost;
	edges[count_].next = head[from];
	head[from] = count_;
}

bool inStack[maxn];
INT dis[maxn];

bool bFound;
void dfs(INT node)
{
	inStack[node] = true;
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		INT cost = edges[i].cost;
		if (dis[node] + cost < dis[to])
		{
			if (inStack[to])
			{
				bFound = true;
				return;
			}
			dis[to] = dis[node] + cost;
			dfs(to);
			if (bFound)
				return;
		}
	}
	inStack[node] = false;
}

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();
		count_ = 0;
		memset(head, 0, sizeof(head));
		memset(inStack, 0, sizeof(inStack));
		memset(dis, 0, sizeof(dis));
		for (int i = 1; i <= m; i++)
		{
			INT u = readIn();
			INT v = readIn();
			INT c = readIn();
			addEdge(u, v, c);
			if (c > 0) addEdge(v, u, c);
		}

		bFound = false;
		for (int i = 1; i <= n; i++)
		{
			dfs(i);
			if (bFound) break;
		}
		if (bFound)
			puts("YE5");
		else
			puts("N0");

	}
}

int main()
{
	run();
	return 0;
}
