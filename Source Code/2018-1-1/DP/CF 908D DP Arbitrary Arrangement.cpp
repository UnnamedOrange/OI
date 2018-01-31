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
	putchar('\n');
}

const INT mod = INT(1e9) + 7;
const INT maxn = 1005;
INT n, a, b;

INT inv(INT x)
{
	if (x == 1) return 1;
	return (mod - mod / x) * inv(mod % x) % mod;
}

INT f[maxn][maxn];

void run()
{
	n = readIn();
	a = readIn();
	b = readIn();
	INT InvA = inv(a);
	INT InvB = inv(b);
	INT InvAB = inv(a + b);
	for (int i = 0; i < n; i++)
	{
		f[n][i] = (i + n + a * InvB % mod) % mod;
	}
	for (int i = n - 1; i >= 1; i--)
	{
		for (int j = n - 1; j >= 0; j--)
		{
			INT t = j + i >= n ? j + i : f[i][j + i];
			f[i][j] = (a * InvAB % mod * f[i + 1][j] % mod +
				b * InvAB % mod * t % mod) % mod;
		}
	}
	printOut(f[1][0]);
}

int main()
{
	run();
	return 0;
}