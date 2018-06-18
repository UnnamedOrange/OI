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
	while (!(std::isdigit(ch) || ch == '-'))
		ch = getchar();
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
}

int phi(int x)
{
	int to = std::sqrt(x);
	int ret = x;
	for (int i = 2; i <= to; i++)
	{
		if (x % i) continue;
		(ret /= i) *= i - 1;
		while (!(x % i)) x /= i;
	}
	if (x > 1) (ret /= x) *= x - 1;
	return ret;
}
LL power(LL x, LL y, LL mod)
{
	bool bigger = false;
	bool biggerX = false;
	LL ret = 1;
	while (y)
	{
		if (y & 1)
		{
			if (biggerX || ret * x >= mod) bigger = true;
			ret = ret * x % mod;
		}
		if (x * x >= mod)
			biggerX = true;
		x = x * x % mod;
		y >>= 1;
	}
	return ret + (bigger ? mod : 0);
}
LL calc(LL n, LL m)
{
	if (m == 1)
		return 1;
	if (n == 1)
		return 1;
	return power(n, calc(n - 1, phi(m)), m);
}

int n, m;

void run()
{
	n = readIn();
	m = readIn();
	printOut(calc(n, m) % m);
}

int main()
{
#ifndef LOCAL
	freopen("efxapcotnoernatlial.in", "r", stdin);
	freopen("efxapcotnoernatlial.out", "w", stdout);
#endif
	run();
	return 0;
}