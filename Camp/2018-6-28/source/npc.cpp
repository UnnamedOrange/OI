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
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = int;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

int t1, n, m;
using Graph = std::vector<std::vector<int>>;
Graph G;

#define RunInstance(x) delete new x
struct brute
{
	int S;
	int ans{};
	int count1[1 << 18]{};

	bool bOk;
	bool vis[20];
	void DFS(int node, int parent)
	{
		vis[node] = true;
		for (auto to : G[node]) if (to != parent)
		{
			if (S & (1 << (to - 1)))
			{
				if (vis[to])
				{
					bOk = false;
					return;
				}
				else
					DFS(to, node);
			}
		}
	}
	bool check()
	{
		bOk = true;
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= n && bOk; i++)
			if ((S & (1 << (i - 1))) && !vis[i])
				DFS(i, 0);
		return bOk;
	}

	brute()
	{
		int U = 1 << n;
		count1[0] = 0;
		for (S = 1; S < U; S++)
			count1[S] = count1[S ^ (S & -S)] + 1;

		for (S = 0; S < U; S++)
			if (check())
				if (count1[S] > count1[ans])
					ans = S;
		printOut(count1[ans]);
		putchar('\n');
		for (int i = 1; i <= n; i++)
			if (ans & (1 << (i - 1)))
			{
				printOut(i);
				putchar(' ');
			}
	}
};

void run()
{
	t1 = readIn();
	n = readIn();
	m = readIn();
	G.resize(n + 1);
	for (int i = 1; i <= m; i++)
	{
		int from = readIn();
		int to = readIn();
		G[from].push_back(to);
		G[to].push_back(from);
	}

	if (n <= 18)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("npc.in", "r", stdin);
	freopen("npc.out", "w", stdout);
#endif
	run();
	return 0;
}