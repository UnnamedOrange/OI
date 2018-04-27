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

const INT mod = 10007;
const INT maxn = 200005;
INT n;
struct Edge
{
	INT to;
	INT next;
} edges[maxn * 2];
INT head[maxn];
void addEdge(INT from, INT to)
{
	static INT i;
	i++;
	edges[i].to = to;
	edges[i].next = head[from];
	head[from] = i;
}
INT degree[maxn];
INT w[maxn];
INT temp[maxn];

void run()
{
	n = readIn();
	for (int i = 1; i < n; i++)
	{
		INT u = readIn();
		INT v = readIn();
		degree[u]++;
		degree[v]++;
		addEdge(u, v);
		addEdge(v, u);
	}
	for (int i = 1; i <= n; i++)
		w[i] = readIn();

	INT maxVal = 0, ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (degree[i] == 1) continue;
		INT sum = 0;
		INT major = 0;
		INT minor = 0;
		temp[0] = 0;
		for (int j = head[i]; j; j = edges[j].next)
		{
			INT to = edges[j].to;
			temp[++temp[0]] = to;
			sum = (sum + w[to]) % mod;
			if (w[to] > minor)
			{
				if (w[to] > major)
				{
					minor = major;
					major = w[to];
				}
				else
					minor = w[to];
			}
		}
		maxVal = std::max(maxVal, major * minor);
		for (int j = 1; j <= temp[0]; j++)
		{
			ans = ((ans + (sum - w[temp[j]]) * w[temp[j]]) % mod + mod) % mod;
		}
	}
	printOut(maxVal);
	putchar(' ');
	printOut(ans);
	putchar('\n');
}

int main()
{
	run();
	return 0;
}
