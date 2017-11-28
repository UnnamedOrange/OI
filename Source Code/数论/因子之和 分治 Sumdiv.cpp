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
typedef long long INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
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
inline void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

const INT mod = 9901;
INT a, b;
INT ans = 1;

INT power(INT x, INT y)
{
	INT ret = 1;
	x = x % mod;
	while (y)
	{
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}

INT calc(INT x, INT y)
{
	if (!y) return 1;
	INT mid = y >> 1;
	if (y & 1)
	{
		INT t = calc(x, mid);
		return (t + power(x, mid + 1) * t) % mod;
	}
	else
	{
		INT t = calc(x, mid - 1);
		return (((t + power(x, mid) * t) % mod) * (x % mod) + 1) % mod;
	}
}

void divide()
{
	INT to = std::sqrt(a);
	for (int i = 2; i <= to; i++)
	{
		if (a % i) continue;
		INT k = 0;
		while (!(a % i))
		{
			a /= i;
			k++;
		}
		ans = ans * calc(i, k * b) % mod;
	}
	if (a != 1) ans = ans * calc(a, b) % mod;
}

void run()
{
	a = readIn();
	b = readIn();
	divide();
	printOut(ans);
}

int main()
{
	run();
	return 0;
}
