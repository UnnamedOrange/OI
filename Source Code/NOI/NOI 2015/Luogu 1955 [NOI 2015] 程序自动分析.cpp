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

const int maxn = int(1e5) + 5;
int n;
struct Instruction
{
	int x, y, e;
	void read()
	{
		x = readIn();
		y = readIn();
		e = readIn();
	}
} ins[maxn];

int disc[maxn * 2];
void discretize()
{
	std::sort(disc + 1, disc + 1 + disc[0]);
	disc[0] = std::unique(disc + 1, disc + 1 + disc[0]) - (disc + 1);
	for (int i = 1; i <= n; i++)
	{
		ins[i].x = std::lower_bound(disc + 1, disc + 1 + disc[0], ins[i].x) - disc;
		ins[i].y = std::lower_bound(disc + 1, disc + 1 + disc[0], ins[i].y) - disc;
	}
}

struct DS
{
	int parent[maxn * 2];
	void clear(int n)
	{
		for (int i = 1; i <= n; i++)
			parent[i] = i;
	}
	int find(int x)
	{
		if (x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}
	void unite(int x, int y)
	{
		parent[find(y)] = parent[find(x)];
	}
	bool judge(int x, int y)
	{
		return find(x) == find(y);
	}
} ds;

void run()
{
	int T = readIn();
	while (T--)
	{
		n = readIn();
		for (register int i = 1; i <= n; i++)
			ins[i].read();
		disc[0] = 0;
		for (register int i = 1; i <= n; i++)
		{
			disc[++disc[0]] = ins[i].x;
			disc[++disc[0]] = ins[i].y;
		}
		discretize();

		ds.clear(disc[0]);
		for (register int i = 1; i <= n; i++) if (ins[i].e)
			ds.unite(ins[i].x, ins[i].y);
		bool bOk = true;
		for (register int i = 1; i <= n; i++) if (!ins[i].e)
		{
			if (ds.judge(ins[i].x, ins[i].y))
			{
				bOk = false;
				break;
			}
		}
		if (!bOk) puts("NO");
		else puts("YES");
	}
}

int main()
{
	run();
	return 0;
}