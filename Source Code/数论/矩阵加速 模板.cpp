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
	putchar('\n');
}

const INT mod = INT(1e9) + 7;
INT n;

struct Matrix
{
	static const INT size = 3;
	INT c[size][size];
	INT* operator[] (INT x)
	{
		return c[x];
	}
	const INT* operator[] (INT x) const
	{
		return c[x];
	}
	Matrix() : c() {}
	Matrix(INT unit) : c()
	{
		for (int i = 0; i < size; i++)
			c[i][i] = unit;
	}

	Matrix operator* (const Matrix& b) const
	{
		Matrix ret;
		const Matrix& a = *this;
		for (int i = 0; i < size; i++)
			for (int k = 0; k < size; k++)
			{
				if (!a[i][k]) continue;
				for (int j = 0; j < size; j++)
				{
					ret[i][j] = (ret[i][j] + a[i][k] * b[k][j] % mod) % mod;
				}
			}
		return ret;
	}
	Matrix operator^ (INT y) const
	{
		Matrix ret(1);
		Matrix x = *this;
		while (y)
		{
			if (y & 1) ret = ret * x;
			x = x * x;
			y >>= 1;
		}
		return ret;
	}
} base;

void run()
{
	INT T = readIn();
	base[1][0] = 1;
	base[2][1] = 1;
	base[0][2] = 1;
	base[2][2] = 1;
	while (T--)
	{
		n = readIn();
		Matrix ans = base ^ (n - 1);
		printOut((ans[0][0] + ans[1][0] + ans[2][0]) % mod);
	}
}

int main()
{
	run();
	return 0;
}
