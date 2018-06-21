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
}

const int mod = 998244353;
int n, m;

template<int size>
struct Matrix
{
	int c[size][size];
	Matrix() : c() {};
	explicit Matrix(bool) : Matrix()
	{
		for (int i = 0; i < size; i++)
			c[i][i] = 1;
	}
	int* operator[](int x) { return c[x]; }
	const int* operator[](int x) const { return c[x]; }
	Matrix operator*(const Matrix& b) const
	{
		Matrix ret;
		for (int i = 0; i < size; i++)
			for (int k = 0; k < size; k++) if (c[i][k])
				for (int j = 0; j < size; j++)
					ret.c[i][j] = (ret.c[i][j] +
					(LL)c[i][k] * b.c[k][j]) % mod;
		return ret;
	}
	Matrix operator^(int y) const
	{
		Matrix ret(true);
		Matrix x = *this;
		while (y)
		{
			if (y & 1) ret = ret * x;
			x = x * x;
			y >>= 1;
		}
		return ret;
	}
};

#define RunInstance(x) delete new x
struct cheat
{
	using Matrix = Matrix<2>;
	Matrix base;
	cheat()
	{
		if (n == 1)
		{
			printOut(m % mod);
			return;
		}
		base[0][0] = 0;
		base[0][1] = m - 1;
		base[1][0] = 1;
		base[1][1] = m - 2;
		Matrix ans = base ^ (n - 1);
		printOut((LL)m * (m - 1) % mod * ans[1][0] % mod);
	}
};
struct work
{
	using Matrix = Matrix<7>;

	work()
	{
		Matrix base;
		/*
		* 0: None
		* 1: Self
		* 2: Opposite
		* 0 - 0 0
		* 1 - 0 1
		* 2 - 0 2
		* 3 - 1 0
		* 4 - 1 1
		* 5 - 2 0
		* 6 - 2 2
		*/

		base[0][0] = (std::max(LL(0), (LL)(m - 3) * (m - 3) - (m - 4))) % mod;
		base[0][1] = m - 3;
		base[0][2] = m - 3;
		base[0][3] = m - 3;
		base[0][4] = 1;
		base[0][5] = m - 3;
		base[0][6] = 1;

		base[1][0] = (std::max(LL(0), (LL)(m - 2) * (m - 3) - (m - 3))) % mod;
		base[1][1] = 0;
		base[1][2] = m - 3;
		base[1][3] = m - 2;
		base[1][4] = 0;
		base[1][5] = m - 2;
		base[1][6] = 1;

		base[2][0] = (std::max(LL(0), (LL)(m - 2) * (m - 3) - (m - 3))) % mod;
		base[2][1] = m - 3;
		base[2][2] = 0;
		base[2][3] = m - 2;
		base[2][4] = 1;
		base[2][5] = m - 2;
		base[2][6] = 0;

		base[3][0] = (std::max(LL(0), (LL)(m - 2) * (m - 3) - (m - 3))) % mod;
		base[3][1] = m - 2;
		base[3][2] = m - 2;
		base[3][3] = 0;
		base[3][4] = 0;
		base[3][5] = m - 3;
		base[3][6] = 1;

		base[4][0] = (std::max(LL(0), (LL)(m - 2) * (m - 2) - (m - 2))) % mod;
		base[4][1] = 0;
		base[4][2] = m - 2;
		base[4][3] = 0;
		base[4][4] = 0;
		base[4][5] = m - 2;
		base[4][6] = 1;

		base[5][0] = (std::max(LL(0), (LL)(m - 2) * (m - 3) - (m - 3))) % mod;
		base[5][1] = m - 2;
		base[5][2] = m - 2;
		base[5][3] = m - 3;
		base[5][4] = 1;
		base[5][5] = 0;
		base[5][6] = 0;

		base[6][0] = (std::max(LL(0), (LL)(m - 2) * (m - 2) - (m - 2))) % mod;
		base[6][1] = m - 2;
		base[6][2] = 0;
		base[6][3] = m - 2;
		base[6][4] = 1;
		base[6][5] = 0;
		base[6][6] = 0;

		base = base ^ ((n >> 1) - 1);
		LL ans = ((LL)base[4][0] + base[4][1] + base[4][3] + base[4][4]) % mod;
		printOut(ans * m % mod * (m - 1) % mod);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	if (n & 1)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("LiaPo.in", "r", stdin);
	freopen("LiaPo.out", "w", stdout);
#endif
	run();
	return 0;
}