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
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int maxn = 205;
const int mod = int(1e9) + 7;
char str[maxn];
int m;
int m2;

#define RunInstance(x) delete new x
struct case1
{
	int n;
	int f[2][1 << 11];
	std::vector<int> transfer[1 << 11];
	void MakeTransfer(int colum, int from, int to)
	{
		if (colum == m)
		{
			transfer[from].push_back(to);
			return;
		}
		else if (colum > m) return;
		MakeTransfer(colum + 1, from << 1 | 1, to << 1); // 不放
		MakeTransfer(colum + 1, from << 1, to << 1 | 1); // 竖放
		MakeTransfer(colum + 2, from << 2 | 3, to << 2 | 3); // 横放
	}

	case1() : f()
	{
		sscanf(str, "%d", &n);
		int U = 1 << m;
		f[0][U - 1] = 1;
		MakeTransfer(0, 0, 0);
		for (int i = 1; i <= n; i++)
		{
			int* cnt = f[i & 1];
			int* pre = f[!(i & 1)];
			memset(cnt, 0, sizeof(int) * U);
			int* trans;
			for (int S = 0; S < U; S++) // 上一个状态
			{
				trans = transfer[S].data();
				for (int j = 0, to = transfer[S].size(); j < to; j++)
					(cnt[trans[j]] += pre[S]) %= mod;
			}
		}
		printOut(f[n & 1][U - 1]);
	}
};
struct case2
{
	struct BigInt
	{
		static const int compress = 15;
		static const LL digit = LL(1e15);
		int size;
		LL num[15];
		BigInt(const char* str)
		{
			int length = strlen(str);
			size = -1;
			int j = compress;
			LL exp10;
			for (int i = length - 1; ~i; i--)
			{
				if (j == compress)
				{
					size++;
					j = 0;
					exp10 = 1;
					num[size] = 0;
				}
				num[size] += exp10 * (str[i] - '0');
				j++;
				exp10 *= 10;
			}
		}
		void div()
		{
			LL mod = 0;
			for (int i = size; ~i; i--)
			{
				num[i] += mod * digit;
				mod = num[i] & 1;
				num[i] >>= 1;
			}
			if (!num[size]) size--;
		}
	} n;
	struct Matrix
	{
		int c[32][32];
		Matrix() : c() {}
		Matrix(bool unit) : c()
		{
			for (int i = 0; i < m2; i++)
				c[i][i] = 1;
		}
		Matrix operator*(const Matrix& b) const
		{
			Matrix ret;
			for (int i = 0; i < m2; i++)
				for (int k = 0; k < m2; k++)
					if (c[i][k])
						for (int j = 0; j < m2; j++)
							(ret.c[i][j] += (LL)c[i][k] * b.c[k][j] % mod) %= mod;

			return ret;
		}
		Matrix operator^(BigInt y) const
		{
			Matrix ret(true);
			Matrix x(*this);
			while (~y.size)
			{
				if (y.num[0] & 1) ret = ret * x;
				x = x * x;
				y.div();
			}
			return ret;
		}
	};
	Matrix base;

	void MakeMatrix(Matrix& r, int colum, int from, int to)
	{
		if (colum == m)
		{
			r.c[from][to] = 1;
			return;
		}
		else if (colum > m) return;
		MakeMatrix(r, colum + 1, from << 1 | 1, to << 1); // 不放
		MakeMatrix(r, colum + 1, from << 1, to << 1 | 1); // 竖放
		MakeMatrix(r, colum + 2, from << 2 | 3, to << 2 | 3); // 横放
	}

	Matrix ans;
	case2() : n(str)
	{
		MakeMatrix(base, 0, 0, 0);
		ans = base ^ n;
		// 用转移矩阵乘以列向量
		printOut(ans.c[m2 - 1][m2 - 1]);
	}
};

void run()
{
	scanf("%s", str);
	m = readIn();
	m2 = 1 << m;

	if (m <= 5)
		RunInstance(case2);
	else
		RunInstance(case1);
}

int main()
{
	run();
	return 0;
}