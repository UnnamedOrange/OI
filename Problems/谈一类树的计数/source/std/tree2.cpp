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
}

const int mod = 998244353;
const int maxn = 2005;
int n;

int f[maxn];

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

void run()
{
	n = readIn();

	f[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j < i; j++)
		{
			int s = 0;
			for (int k = 1; i - j * k > 0; k++)
				s = (s + f[i - j * k]) % mod;
			f[i] = (f[i] + (long long)j * f[j] % mod * s % mod) % mod;
		}
		f[i] = (long long)f[i] * power(i - 1, mod - 2) % mod;
	}
	printOut(f[n]);
}

int main()
{
#ifndef LOCAL
	freopen("tree2.in", "r", stdin);
	freopen("tree2.out", "w", stdout);
#endif
	run();
	return 0;
}