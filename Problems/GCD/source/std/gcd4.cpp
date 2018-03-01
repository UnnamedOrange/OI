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
	putchar('\n');
}

const int mod = 998244353;
const int maxn = int(1e7);

int phi[maxn + 5];
int prime[664580];
bool isntPrime[maxn + 5];
void init()
{
	phi[1] = 1;
	isntPrime[1] = true;
	int& num = prime[0];
	for (int i = 2; i <= maxn; i++)
	{
		if (!isntPrime[i])
		{
			prime[++num] = i;
			phi[i] = i - 1;
		}
		for (int j = 1, p = prime[j], s = i * p; j <= num && s <= maxn; j++, p = prime[j], s = i * p)
		{
			isntPrime[s] = true;
			if (i % p)
				phi[s] = phi[i] * (p - 1);
			else
			{
				phi[s] = phi[i] * p;
				break;
			}
		}
	}
	for (int i = 2; i <= maxn; i++)
		phi[i] = (phi[i] + phi[i - 1]) % mod;
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
		int ans = 0;
		for (int i = 1, t; i <= m; i = t + 1)
		{
			t = std::min(n / (n / i), m / (m / i));
			ans = (ans + (long long)(phi[t] - phi[i - 1] + mod) * (n / i) % mod * (m / i) % mod) % mod;
		}
		printOut(ans);
	}
}

int main()
{
#ifndef LOCAL
	freopen("gcd4.in", "r", stdin);
	freopen("gcd4.out", "w", stdout);
#endif
	run();
	return 0;
}