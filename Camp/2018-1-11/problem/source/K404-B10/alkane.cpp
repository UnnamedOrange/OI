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

const INT mod = 998244353;
const INT maxn = INT(1e5) + 5;
INT n;

INT f[2005][5];
void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();

		memset(f, 0, sizeof(f));
		f[1][0] = 1;
		for (int i = 2; i <= n; i++)
		{
			for (int j = 1; j <= 4; j++)
			{
				for (int size = 1; size <= i / 2; size++)
				{

				}
			}
		}


	}
}

int main()
{
#ifndef LOCAL
	freopen("alkane.in", "r", stdin);
	freopen("alkane.out", "w", stdout);
#endif
	run();
	return 0;
}