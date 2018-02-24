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
}

const int maxn = int(1e7) + 5;
int n;

long long phi[maxn];
bool isntPrime[maxn];
int prime[maxn];
void init()
{
	isntPrime[1] = true;
	phi[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (!isntPrime[i])
		{
			phi[i] = i - 1;
			prime[++prime[0]] += i;
		}
		for (int j = 1, s = i * prime[j]; j <= prime[0] && s <= n; j++, s = i * prime[j])
		{
			isntPrime[s] = true;
			if (i % prime[j])
				phi[s] = phi[i] * (prime[j] - 1);
			else
			{
				phi[s] = phi[i] * prime[j];
				break;
			}
		}
	}

	for (int i = 1; i <= n; i++)
		phi[i] += phi[i - 1];
}

void run()
{
	n = readIn();
	init();

	long long ans = 0;
	for (int i = 1; i <= prime[0]; i++)
		ans += 2 * phi[n / prime[i]] - 1;
	printOut(ans);
}

int main()
{
#ifndef LOCAL
	freopen("gcd1.in", "r", stdin);
	freopen("gcd1.out", "w", stdout);
#endif
	run();
	return 0;
}