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

const int mod = 998244353;
const int maxn = int(1e7);
int g[maxn + 5];
int prime[664580];
bool isntPrime[maxn + 5];
void init()
{
	g[1] = 1;
	isntPrime[1] = true;
	int& num = prime[0];
	for (int i = 2; i <= maxn; i++)
	{
		if (!isntPrime[i])
		{
			prime[++num] = i;
			g[i] = ((long long)-i * i % mod + mod) % mod;
		}
		for (int j = 1, p = prime[j], s = i * p; j <= num && s <= maxn; j++, p = prime[j], s = i * p)
		{
			isntPrime[s] = true;
			if (i % p)
			{
				g[s] = (long long)g[i] * g[p] % mod;
			}
			else
			{
				g[s] = 0;
				break;
			}
		}
	}
	for (int i = 2; i <= maxn; i++)
		g[i] = (g[i] + g[i - 1]) % mod;
}

int power(int x, int y)
{
	int ret = 1;
	while (y)
	{
		if (y & 1) ret = (long long)ret * x % mod;
		x = (long long)x * x % mod;
		y >>= 1;
	}
	return ret;
}

int n, m;

void run()
{
	init();
	int inv4 = power(4, mod - 2);
	int T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();
		if (n < m) std::swap(n, m);
		int ans = 0;
		for (int d = 1; d <= m; d++)
		{
			int a = n / d;
			int b = m / d;
			int sum = 0;
			for (int i = 1, t; i <= b; i = t + 1)
			{
				t = std::min(a / (a / i), b / (b / i));
				long long x = a / i;
				long long y = b / i;
				sum = (sum + x * (x + 1) % mod * y % mod * (y + 1) % mod * (g[t] - g[i - 1] + mod) % mod) % mod;
			}
			ans = (ans + (long long)d * sum) % mod;
		}
		printOut((long long)ans * inv4 % mod);
	}
}

int main()
{
#ifndef LOCAL
	freopen("gcd5.in", "r", stdin);
	freopen("gcd5.out", "w", stdout);
#endif
	run();
	return 0;
}