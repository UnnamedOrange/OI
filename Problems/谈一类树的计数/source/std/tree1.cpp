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
const INT maxn = 2005;
INT n;
INT d[maxn];

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
inline INT C(INT down, INT up)
{
	return (down < up) ? 0 : (fac[down] * invFac[up] % mod * invFac[down - up] % mod);
}

INT f[maxn][maxn];
void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		d[i] = readIn();
	init();

	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= n - 2; j++)
			for (int k = 0; k < d[i] && j - k >= 0; k++)
				f[i][j] = (f[i][j] + f[i - 1][j - k] * C(j, k) % mod) % mod;
	printOut(f[n][n - 2]);
}

int main()
{
#ifndef LOCAL
	freopen("tree1.in", "r", stdin);
	freopen("tree1.out", "w", stdout);
#endif
	run();
	return 0;
}