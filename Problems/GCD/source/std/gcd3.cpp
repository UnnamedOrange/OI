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

const int maxn = int(1e7);
int mu[maxn + 5];
int prime[664580];
bool isntPrime[maxn + 5];
void init()
{
	mu[1] = 1;
	isntPrime[1] = true;
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
}

int n, m, k;

long long solve(int a, int b)
{
	long long ans = 0;
	a /= k;
	b /= k;
	if (a < b) std::swap(a, b);
	for (int i = 1, t; i <= b; i = t + 1)
	{
		t = std::min(a / (a / i), b / (b / i));
		ans += (long long)(mu[t] - mu[i - 1]) * (a / i) * (b / i);
	}
	long long sub = 0;
	for (int i = 1, t; i <= b; i = t + 1)
	{
		t = b / (b / i);
		sub += (long long)(mu[t] - mu[i - 1]) * (b / i) * (b / i);
	}
	return ans - (sub >> 1);
}

void run()
{
	init();
	int T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();
		k = readIn();
		printOut(solve(n, m));
	}
}

int main()
{
#ifndef LOCAL
	freopen("gcd3.in", "r", stdin);
	freopen("gcd3.out", "w", stdout);
#endif
	run();
	return 0;
}