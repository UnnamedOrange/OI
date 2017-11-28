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
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[12];
		INT length = 0;
		while (x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		do
		{
			putchar(buffer[--length]);
		} while (length);
	}
	putchar('\n');
}

const INT maxn = 400005;
const INT maxm = maxn * 2;
INT n, m, k;
struct Edge
{
	INT to;
	INT next;
} edges[maxm * 2];
INT head[maxn];
void addEdge(INT from, INT to)
{
	static INT i;
	i++;
	edges[i].to = to;
	edges[i].next = head[from];
	head[from] = i;
}

INT destroy[maxn];

struct DS
{
	INT parent[maxn];
	DS()
	{
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}
	INT find(INT x)
	{
		if (x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}
	bool unite(INT x, INT y)
	{
		INT px = find(x);
		INT py = find(y);
		if (px == py) return false;
		parent[py] = px;
		return true;
	}
};

#define RunInstance(x) delete new x
struct work
{
	DS ds;

	bool vis[maxn];
	INT ans[maxn];

	work() : vis(), ans()
	{
		for (int i = 1; i <= k; i++)
			vis[destroy[i]] = true;

		ans[k + 1] = n - k;
		for (int i = 1; i <= n; i++)
		{
			if (vis[i]) continue;
			for (int j = head[i]; j; j = edges[j].next)
			{
				INT to = edges[j].to;
				if (vis[to]) continue;
				ans[k + 1] -= ds.unite(i, to);
			}
		}

		for (int i = k; i >= 1; i--)
		{
			ans[i] = ans[i + 1] + 1;
			for (int j = head[destroy[i]]; j; j = edges[j].next)
			{
				INT to = edges[j].to;
				if (vis[to]) continue;
				ans[i] -= ds.unite(destroy[i], to);
			}
			vis[destroy[i]] = false;
		}

		for (int i = 1; i <= k + 1; i++)
			printOut(ans[i]);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		addEdge(from, to);
		addEdge(to, from);
	}
	k = readIn();
	for (int i = 1; i <= k; i++)
		destroy[i] = readIn();

	RunInstance(work);
}

int main()
{
	run();
	return 0;
}
