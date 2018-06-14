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
using INT_PUT = int;
INT_PUT readIn()
{
	register INT_PUT a = 0;
	register bool positive = true;
	register char ch = getchar();
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
	register int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int mod = 998244353;
const int maxn = 50005;
int n, m;
int a[maxn];
int c[maxn];

int fac[maxn];
int inv[maxn];
int invFac[maxn];
void init()
{
	int to = int(5e4);
	fac[0] = 1;
	for (int i = 1; i <= to; i++)
		fac[i] = (LL)fac[i - 1] * i % mod;
	inv[1] = 1;
	for (int i = 2; i <= to; i++)
		inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod;
	invFac[0] = 1;
	for (int i = 1; i <= to; i++)
		invFac[i] = (LL)invFac[i - 1] * inv[i] % mod;
}
inline int C(int down, int up)
{
	return down < up ? 0 : (LL)fac[down] * invFac[up] % mod * invFac[down - up] % mod;
}

#define RunInstance(x) delete new x
struct brute0
{
	static const int maxN = 55;
	int f[maxN];
	int g[maxN][maxN][maxN];

	brute0() : g()
	{
		for (int i = 1; i <= n; i++)
			f[i] = a[i];
		for (int i = n + 1; i <= m; i++)
		{
			int& t = f[i];
			t = 0;
			for (int j = 1; j <= n; j++)
				t = (t + (LL)c[j] * f[i - j]) % mod;
		}

		g[0][0][0] = 1;
		for (int i = 1; i <= m; i++)
		{
			for (int j = 0; j <= m; j++)
			{
				for (int k = 0; k <= m; k++)
				{
					int t = 1;
					for (int l = 0; l <= j && k - i * l >= 0; l++, t = (LL)t * f[i] % mod)
					{
						g[i][j][k] = (g[i][j][k] +
							(LL)g[i - 1][j - l][k - i * l] *
							t % mod * C(j, l)) % mod;
					}
				}
			}
		}
		int ans = 0;
		for (int i = 0; i <= m; i++)
			ans = (ans + g[m][i][m]) % mod;
		printOut(ans);
	}
};

void run()
{
	init();
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 1; i <= n; i++)
		c[i] = readIn();

	if (n <= 1000 && m <= 1000)
		RunInstance(brute0);
}

int main()
{
#ifndef LOCAL
	freopen("candy.in", "r", stdin);
	freopen("candy.out", "w", stdout);
#endif
	run();
	return 0;
}