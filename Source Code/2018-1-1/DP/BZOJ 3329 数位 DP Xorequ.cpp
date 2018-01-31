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
}

INT n;
INT f[100][2];
INT dp(INT digit, INT pre, INT top)
{
	if (!top && f[digit][pre] != -1)
		return f[digit][pre];
	if (digit == 0)
		return 1 + (!pre && (!top || (n & 1)));
	INT ans = 0;
	if (pre)
		ans = dp(digit - 1, 0, top && !(n & (1ll << digit)));
	else
	{
		ans += dp(digit - 1, 0, top && !(n & (1ll << digit)));
		if (!top || (n & (1ll << digit)))
			ans += dp(digit - 1, 1, top);
	}
	if (!top)
		f[digit][pre] = ans;
	return ans;
}

const INT mod = INT(1e9) + 7;
struct Matrix
{
	INT c[2][2];
	Matrix() : c() {}
	Matrix(bool unit) : c()
	{
		for (int i = 0; i < 2; i++)
			c[i][i] = 1;
	}
	INT* operator[] (INT x)
	{
		return c[x];
	}
	const INT* operator[] (INT x) const
	{
		return c[x];
	}
	Matrix operator* (const Matrix& b) const
	{
		Matrix ret;
		const Matrix& a = *this;
		for (int i = 0; i < 2; i++)
		{
			for (int k = 0; k < 2; k++)
			{
				if (!a[i][k]) continue;
				for (int j = 0; j < 2; j++)
				{
					ret[i][j] = (ret[i][j] + a[i][k] * b[k][j] % mod) % mod;
				}
			}
		}
		return ret;
	}
	Matrix operator^ (INT y) const
	{
		Matrix ret(true);
		Matrix a = *this;
		while (y)
		{
			if (y & 1) ret = ret * a;
			a = a * a;
			y >>= 1;
		}
		return ret;
	}
};
void solve()
{
	Matrix base;
	base[0][1] = base[1][0] = base[1][1] = 1;
	base = base ^ (n - 1);
	printOut((2 * base[0][0] + 3 * base[1][0]) % mod);
}

void run()
{
	memset(f, -1, sizeof(f));
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		printOut(dp(63, 0, true) - 1);
		putchar('\n');
		solve();
		putchar('\n');
	}
}

int main()
{
	run();
	return 0;
}