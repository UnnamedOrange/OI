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
bool died[10000005];

void run()
{
	n = readIn();
	m = readIn();
	INT cnt = 1;
	for (int i = 1; i < n; i++)
	{
		for (int j = 2; j <= m; j++)
		{
			cnt = cnt % n + 1;
			while (died[cnt]) cnt = cnt % n + 1;
		}
		died[cnt] = true;
		cnt = cnt % n + 1;
		while (died[cnt]) cnt = cnt % n + 1;
	}
	printOut(cnt);
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