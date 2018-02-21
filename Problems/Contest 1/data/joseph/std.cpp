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
typedef long long INT;
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
	putchar('\n');
}

INT n, m;

void run()
{
	n = readIn();
	m = readIn();
	if (m == 2)
	{
		INT t = 1;
		while ((t << 1) <= n) t <<= 1;
		printOut((n - t) * 2 + 1);
		return;
	}
	int f = 0;
	for (int i = 2; i <= n; i++)
	{
		int g = f;
		f = (g + m) % i;
	}
	printOut(f + 1);
}

int main()
{
#ifndef LOCAL
	freopen("joseph.in", "r", stdin);
	freopen("joseph.out", "w", stdout);
#endif
	run();
	return 0;
}