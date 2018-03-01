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
int power(int x, int y)
{
	int ret = 1;
	while (y)
	{
		if (y & 1) ret = (long long)ret * x %mod;
		x = (long long)x * x % mod;
		y >>= 1;
	}
	return ret;
}
const int maxn = int(1e7);
int h[maxn + 5];
int prime[664580];
bool isntPrime[maxn + 5];
int times[maxn + 5];
int mul[maxn + 5];
void init()
{
	h[1] = 1;
	isntPrime[1] = true;
	int& num = prime[0];
	for (int i = 2; i <= maxn; i++)
	{
		if (!isntPrime[i])
		{
			prime[++num] = i;
			h[i] = ((long long)i * (i - 1) + 1) % mod;
			times[i] = 1;
			mul[i] = i;
		}
		for (int j = 1, p = prime[j], s = i * p; j <= num && s <= maxn; j++, p = prime[j], s = i * p)
		{
			isntPrime[s] = true;
			if (i % p)
			{
				times[s] = 1;
				mul[s] = p;
				h[s] = (long long)h[i] * h[p] % mod;
			}
			else
			{
				times[s] = times[i] + 1;
				mul[s] = mul[i] * p;
				h[s] = (long long)h[s / mul[s]] * ((long long)h[mul[i]] * p % mod * p % mod - p + 1 + mod) % mod;
				break;
			}
		}
	}
	for (int i = 1; i <= maxn; i++)
		h[i] = (long long)h[i] * i % mod;
	for (int i = 2; i <= maxn; i++)
		h[i] = (h[i] + h[i - 1]) % mod;
}

int n;

void run()
{
	init();
	int T = readIn();
	while (T--)
	{
		n = readIn();
		printOut(h[n]);
	}
}

int main()
{
#ifndef LOCAL
	freopen("gcd6.in", "r", stdin);
	freopen("gcd6.out", "w", stdout);
#endif
	run();
	return 0;
}