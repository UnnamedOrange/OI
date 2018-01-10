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

typedef unsigned long long ULL;
ULL mul(ULL x, ULL y, ULL mod)
{
	ULL ret = 0;
	while (y)
	{
		if (y & 1) ret = (ret + x) % mod;
		x = (x << 1) % mod;
		y >>= 1;
	}
	return ret;
}
ULL power(ULL x, ULL y, ULL mod)
{
	ULL ret = 1;
	while (y)
	{
		if (y & 1) ret = mul(ret, x, mod);
		x = mul(x, x, mod);
		y >>= 1;
	}
	return ret;
}
ULL rand(ULL l, ULL r)
{
#define randMov(n) (ULL(rand()) << (n))
	ULL ret = randMov(45) | randMov(30) | randMov(15) | randMov(0);
	return ret % (r - l + 1) + l;
}

bool check(ULL n, ULL a)
{
	ULL r = n - 1;
	ULL c2 = 0;
	while (!(r & 1))
	{
		c2++;
		r >>= 1;
	}

	ULL x = power(a, r, n);
	if (x == 1 || x == n - 1) return true;
	while (c2--)
	{
		x = mul(x, x, n);
		if (x == n - 1 && c2) return true;
	}
	return false;
}
bool Miller_Rabin(ULL n)
{
	if (n < 2) return false;
	else if (n == 2) return true;

	const ULL a[] = { 2, 7, 61 };
	ULL size = sizeof(a) / sizeof(ULL);
	for (int i = 0; i < size; i++)
	{
		if (n == a[i]) return true;
		else if (n % a[i] == 0) return false;
	}
	for (int i = 0; i < size; i++)
		if (!check(n, a[i])) return false;
	return true;
}

void run()
{
	readIn();
	INT T = readIn();
	while (T--)
	{
		puts(Miller_Rabin(readIn()) ? "Yes" : "No");
	}
}

int main()
{
	run();
	return 0;
}