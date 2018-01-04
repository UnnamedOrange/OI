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
	while (!(ch == '-' || (ch >= '0' && ch <= '9')))
		ch = getchar();
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
	if (minus)
		a = -a;
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
	putchar(' ');
}

const INT mod = INT(1e9) + 7;
const INT maxn = 100005;
INT n, a, b;
INT x[maxn];

INT power(INT x, INT y)
{
	INT ret = 1;
	while (y)
	{
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}

void run()
{
	n = readIn();
	a = readIn();
	b = readIn();
	for (int i = 1; i <= n; i++)
		x[i] = readIn() % (a + b);

	INT buf[4] = { 0 };
	INT ans[4] = { 0 };
	INT& a1 = a <= b ? ans[0] : ans[1];
	INT& a2 = a <= b ? ans[1] : ans[0];
	INT& a3 = ans[2];
	INT& a4 = ans[3];
	if (a > b) std::swap(a, b);

	for (int i = 1; i <= n; i++)
		buf[(x[i] >= a) + (x[i] >= b) + (x[i] >= b && x[i] >= a * 2)]++;

	a1 = (a1 + (power(2, buf[1]) + mod - 1) * power(2, buf[2] + buf[3]) % mod) % mod;
	a1 = (a1 + (power(2, buf[3]) + mod - buf[3] - 1) * power(2, buf[2]) % mod) % mod;
	a1 = (a1 + buf[3] * (buf[2] ? power(2, buf[2] - 1) : 0) % mod) % mod;
	a3 = (a3 + buf[3] * (buf[2] ? power(2, buf[2] - 1) : 1) % mod) % mod;
	a3 = (a3 + (buf[2] ? power(2, buf[2] - 1) : 0) % mod) % mod;
	a4 = (a4 + (buf[2] ? power(2, buf[2] - 1) : 1) % mod) % mod;
	for (int i = 0; i < 4; i++)
		printOut(ans[i] * power(2, buf[0]) % mod);
}

int main()
{
#ifndef LOCAL
	freopen("stone.in", "r", stdin);
	freopen("stone.out", "w", stdout);
#endif
	run();
	return 0;
}