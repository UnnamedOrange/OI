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

const INT maxn = INT(1e7) + 5;
INT n, m;
INT left[maxn];
INT right[maxn];

void run()
{
	n = readIn();
	m = readIn();
	for(int i = 1; i < n; i++)
	{
		left[i + 1] = i;
		right[i] = i + 1;
	}
	left[1] = n;
	right[n] = 1;
	
	INT cnt = 1;
	for(int i = 1; i < n; i++)
	{
		for(int j = 1; j < m; j++)
			cnt = right[cnt];
		INT temp = cnt;
		cnt = right[cnt];
		right[left[temp]] = right[temp];
		left[right[temp]] = left[temp];
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
