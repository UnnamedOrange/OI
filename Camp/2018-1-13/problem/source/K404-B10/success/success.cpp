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
	putchar('\n');
}

const INT mod = 1000000007;
INT s, t, n, m;

#define RunInstance(x) delete new x
struct brute
{
	static const INT maxN = 105;
	INT f[maxN][maxN];

	brute() : f()
	{
		f[0][0] = 1;
		for (int i = 1; i <= m; i++)
			if (i <= n)
				for (int j = 0; j <= s; j++)
					for (int k = 1; k <= t && j + k <= s; k++)
						f[i][j + k] = (f[i][j + k] + f[i - 1][j]) % mod;
			else
				for (int j = 0; j <= s; j++)
					for (int k = 1; j + k <= s; k++)
						f[i][j + k] = (f[i][j + k] + f[i - 1][j]) % mod;
		INT ans = 0;
		for (int i = 0; i <= s; i++)
			ans = (ans + f[m][i]) % mod;
		printOut(ans);
	}
};
struct work
{
	work()
	{
	}
};

void run()
{
	s = readIn(); //all
	t = readIn(); //each time
	n = readIn(); //the former
	m = readIn(); //the whole

	if (s <= 100 && t <= 100 && n <= 100 && m <= 100)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("success.in", "r", stdin);
	freopen("success.out", "w", stdout);
#endif
	run();
	return 0;
}
