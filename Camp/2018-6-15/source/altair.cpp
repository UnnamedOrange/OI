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
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
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
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int mod = 998244353;
const int maxn = 105;
int n;
int power(LL x, int y)
{
	LL ret = 1;
	while (y)
	{
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
int a[5];
int sum;
int p[5];

#define RunInstance(x) delete new x
struct brute
{
	int rect[maxn * 2][maxn * 2];
	int nDot;
	int E, D;
	void search1(int depth, int x, int y, int P)
	{
		if (!(rect[x + n][y + n]++))
			nDot++;
		if (depth == n)
		{
			E = (E + (LL)nDot * P) % mod;
		}
		else
		{
			search1(depth + 1, x, y + 1, (LL)P * p[1] % mod);
			search1(depth + 1, x, y - 1, (LL)P * p[2] % mod);
			search1(depth + 1, x - 1, y, (LL)P * p[3] % mod);
			search1(depth + 1, x + 1, y, (LL)P * p[4] % mod);
		}
		if (!(--rect[x + n][y + n]))
			nDot--;
	}
	void search2(int depth, int x, int y, int P)
	{
		if (!(rect[x + n][y + n]++))
			nDot++;
		if (depth == n)
		{
			D = (D + (LL)(nDot - E) * (nDot - E) % mod * P) % mod;
		}
		else
		{
			search2(depth + 1, x, y + 1, (LL)P * p[1] % mod);
			search2(depth + 1, x, y - 1, (LL)P * p[2] % mod);
			search2(depth + 1, x - 1, y, (LL)P * p[3] % mod);
			search2(depth + 1, x + 1, y, (LL)P * p[4] % mod);
		}
		if (!(--rect[x + n][y + n]))
			nDot--;
	}

	brute() : rect(), E(), D(), nDot()
	{
		search1(0, 0, 0, 1);
		search2(0, 0, 0, 1);
		printOut((LL)D * power(sum, n * 2) % mod);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= 4; i++)
		a[i] = readIn();
	sum = ((LL)a[1] + a[2] + a[3] + a[4]) % mod;
	int inv = power(sum, mod - 2);
	for (int i = 1; i <= 4; i++)
		p[i] = (LL)a[i] * inv % mod;

	if (n <= 10)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("altair.in", "r", stdin);
	freopen("altair.out", "w", stdout);
#endif
	run();
	return 0;
}