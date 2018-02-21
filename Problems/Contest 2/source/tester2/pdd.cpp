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
#include <list>
#include <functional>
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
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
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

const int maxn = int(1e6) + 5;
int n;
int a[maxn];
int f[maxn];
int g[maxn];

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();

	for (int i = n; i >= 1; i--)
	{
		f[i] = std::upper_bound(g + 1, g + 1 + g[0], a[i], std::greater<int>()) - g;

		if (!g[0] || a[i] <= g[g[0]])
			g[++g[0]] = a[i];
		else
			*std::upper_bound(g + 1, g + 1 + g[0], a[i], std::greater<int>()) = a[i];
	}
	printOut(*std::max_element(f + 1, f + 1 + n));
	putchar('\n');
	printOut(f[1]);
	for (int i = 2; i <= n; i++)
	{
		putchar(' ');
		printOut(f[i]);
	}
}

int main()
{
#ifndef LOCAL
	freopen("pdd.in", "r", stdin);
	freopen("pdd.out", "w", stdout);
#endif
	run();
	return 0;
}