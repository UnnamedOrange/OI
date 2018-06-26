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
using INT_PUT = LL;
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
	putchar('\n');
}

const int maxn = int(2e5) + 5;
int t1 = true;
int n;
LL h[maxn], c[maxn];
using Graph = std::vector<std::vector<int>>;
Graph G;

#define RunInstance(x) delete new x
struct cheat
{
	LL f[maxn];
	void brute()
	{
		for (int i = 1; i <= n; i++)
		{
			LL& ans = f[i];
			ans = LLONG_MAX;
			for (int j = 0; j < i; j++)
			{
				ans = std::min(ans,
					f[j] - h[i] + (LL)(i - j) * c[i] * c[i] + (((LL)i * i - (LL)2 * i * j + (LL)j * j - i + j) >> 1) * c[i]);
			}
		}
		for (int i = 1; i <= n; i++)
			printOut(f[i]);
	}

	cheat()
	{
		f[0] = 0;

	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		h[i] = readIn();
		c[i] = readIn();
	}
	G.resize(n + 1);
	for (int i = 1; i < n; i++)
	{
		int from = readIn();
		int to = readIn();
		if (from > to)
			std::swap(from, to);
		G[from].push_back(to);
		G[to].push_back(from);
		if (from + 1 != to)
			t1 = false;
	}

	if (t1)
		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	run();
	return 0;
}