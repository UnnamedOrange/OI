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

const int maxn = int(5e4);
int mu[maxn + 5];
int prime[5134];
bool isntPrime[maxn + 5];
long long f[maxn + 5];
void init()
{
	isntPrime[1] = true;
	mu[1] = 1;
	int& num = prime[0];
	for (int i = 2; i <= maxn; i++)
	{
		if (!isntPrime[i])
		{
			prime[++num] = i;
			mu[i] = -1;
		}
		for (int j = 1, p = prime[j], s = i * p; j <= num && s <= maxn; j++, p = prime[j], s = i * p)
		{
			isntPrime[s] = true;
			if (i % p)
			{
				mu[s] = -mu[i];
			}
			else
			{
				mu[s] = 0;
				break;
			}
		}
	}
	for (int i = 2; i <= maxn; i++)
		mu[i] += mu[i - 1];

	for (int i = 1; i <= maxn; i++)
	{
		for (int j = 1, t; j <= i; j = t + 1)
		{
			t = i / (i / j);
			f[i] += (long long)(t - j + 1) * (i / j);
		}
	}
}

int n, m;

void run()
{
	init();
	int T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();
		if (n < m) std::swap(n, m);
		long long ans = 0;
		for (int i = 1, t; i <= m; i = t + 1)
		{
			t = std::min(n / (n / i), m / (m / i));
			ans += (long long)(mu[t] - mu[i - 1]) * f[n / i] * f[m / i];
		}
		printOut(ans);
	}
}

int main()
{
#ifndef LOCAL
	freopen("gcd7.in", "r", stdin);
	freopen("gcd7.out", "w", stdout);
#endif
	run();
	return 0;
}