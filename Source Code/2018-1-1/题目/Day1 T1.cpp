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
	while (!(ch == '-' || (ch >= '0' && ch <= '9')))
		ch = getchar();
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
	if (minus)
		a = -a;
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
	putchar(' ');
}

const INT mod = 1004535809;
const INT maxn = 105;
INT n;
INT a[maxn];

INT f[maxn][maxn][maxn];

INT fac[maxn];
INT inv[maxn];
INT invFac[maxn];
void init()
{
	fac[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[1] = 1;
	for (int i = 2; i <= n; i++)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	invFac[0] = 1;
	for (int i = 1; i <= n; i++)
		invFac[i] = invFac[i - 1] * inv[i] % mod;
}

void run()
{
	n = readIn();
	init();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();

	f[0][0][0] = 1;
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			for (int k = 0; k <= n - 2; k++)
			{
				if (f[i][j][k])
				{
					f[i + 1][j][k] = (f[i + 1][j][k] + f[i][j][k]) % mod;
					for (int c = 0, to = std::min(n - 2 - k, a[i + 1] - 1); c <= to; c++)
						f[i + 1][j + 1][k + c] = (f[i + 1][j + 1][k + c] + f[i][j][k] * invFac[c] % mod) % mod;
				}
			}
		}
	}
	printOut(n);
	for (int i = 2; i <= n; i++)
		printOut(f[n][i][i - 2] * fac[i - 2] % mod);
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