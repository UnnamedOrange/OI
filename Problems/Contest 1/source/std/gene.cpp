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

const INT maxn = INT(1e4) + 5;
INT n;

std::vector<INT> a[maxn];
INT idx[maxn];

bool comp(const INT& x, const INT& y)
{
	if (a[x].size() != a[y].size())
		return a[x].size() < a[y].size();
	for (int i = 0, to = a[x].size(); i < to; i++)
	{
		if (a[x][i] != a[y][i])
			return a[x][i] > a[y][i];
	}
	return false;
}

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		a[i].resize(readIn());
		for (int j = 0, to = a[i].size(); j < to; j++)
		{
			a[i][j] = readIn();
		}
	}

	for (int i = 1; i <= n; i++)
		idx[i] = i;
	std::stable_sort(idx + 1, idx + 1 + n, comp);
	for (int i = 1; i <= n; i++)
	{
		static bool printed;
		if (printed)
			putchar(' ');
		printed = true;
		printOut(idx[i]);
	}
	putchar('\n');
}

int main()
{
#ifndef LOCAL
	freopen("gene.in", "r", stdin);
	freopen("gene.out", "w", stdout);
#endif
	run();
	return 0;
}