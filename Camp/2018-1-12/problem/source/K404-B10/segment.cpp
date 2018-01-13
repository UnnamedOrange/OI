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

const INT mod = 998244353;
const INT maxn = 100005;
const INT maxm = 325;
INT n, m, up;
INT power(INT x, INT y = up)
{
	INT ret = 1;
	while (y)
	{
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}

INT f[2][maxm][maxm];
INT w[2][maxm][maxm];
INT pwr[maxm];
void clear(INT t[maxm][maxm])
{
	for (register int i = 0; i <= m; i++)
		for (register int j = 0; j <= m; j++)
			t[i][j] = 0;
}

void run()
{
	m = readIn();
	n = readIn();
	up = readIn();

	if (m > n)
	{
		printOut(0);
		return;
	}
	for (int i = 0; i <= m; i++)
		pwr[i] = power(i);

	w[0][0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		INT cnt = i & 1;
		INT pre = !cnt;
		clear(w[cnt]);
		clear(f[cnt]);
		for (int j = 0; j <= std::min(i, int(m)); j++)
		{
			for (int k = 0; k <= j; k++)
			{
				INT& ans = w[cnt][j][k];
				INT& F = f[cnt][j][k];
				ans = (ans + w[pre][j][k]) % mod;
				F = (F + f[pre][j][k]) % mod;
				if (j && j > k)
				{
					ans = (ans + w[pre][j - 1][k]) % mod;
					F = (F + f[pre][j - 1][k]) % mod;
				}
				if (k)
				{
					ans = (ans + w[pre][j][k - 1]) % mod;
					F = (F + f[pre][j][k - 1]) % mod;
				}
				if (j && k)
				{
					ans = (ans + w[pre][j - 1][k - 1]) % mod;
					F = (F + f[pre][j - 1][k - 1]) % mod;
				}
				F = (F + ans * pwr[j - k] % mod) % mod;
			}
		}
	}
	printOut(f[n & 1][m][m]);
}

int main()
{
#ifndef LOCAL
	freopen("segment.in", "r", stdin);
	freopen("segment.out", "w", stdout);
#endif
	run();
	return 0;
}