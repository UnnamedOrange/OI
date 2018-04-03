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
typedef int INT;
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
}

const INT maxn = 262150;
INT n, m;
int a[maxn];
int b[maxn];
int c[maxn];

struct FNTT
{
	static const int mod = 998244353;
	static const int root = 3;
	static const int base = 119;
	static const int limit = 23;
	static inline int power(int x, int y)
	{
		int ret = 1;
		while (y)
		{
			if (y & 1) ret = (long long)ret * x % mod;
			x = (long long)x * x % mod;
			y >>= 1;
		}
		return ret;
	}
	int n, logn;
	inline int revbit(int x)
	{
		int ret = 0;
		for (int i = 0; i < logn; i++)
			ret = (ret << 1) | (bool)(x & (1 << i));
		return ret;
	}
	FNTT(int* a, int logn, int sig) : n(1 << logn), logn(logn)
	{
		for (int i = 0; i < n; i++)
		{
			int t = revbit(i);
			if (i < t) std::swap(a[i], a[t]);
		}
		for (int i = 1; i <= logn; i++)
		{
			int S = 1 << i;
			int half = S >> 1;
			int g1 = power(root, base * (1 << (23 - i)));
			if (sig == -1) g1 = power(g1, mod - 2);
			for (int j = 0; j < n; j += S)
			{
				int* A = a + j;
				int g = 1;
				for (int k = 0; k < half; k++)
				{
					int t = (long long)A[k + half] * g % mod;
					A[k + half] = ((A[k] - t) % mod + mod) % mod;
					A[k] = (A[k] + t) % mod;
					g = (long long)g * g1 % mod;
				}
			}
		}
	}
};
struct NTT : private FNTT
{
	NTT(int* a, int logn) : FNTT(a, logn, 1) {}
};
struct INTT : private FNTT
{
	INTT(int* a, int logn) : FNTT(a, logn, -1)
	{
		int n = 1 << logn;
		int inv = power(n, mod - 2);
		for (int i = 0; i < n; i++)
			a[i] = (long long)a[i] * inv % mod;
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 0; i <= n; i++)
		a[i] = readIn();
	for (int i = 0; i <= m; i++)
		b[i] = readIn();
	int logn = 0;
	while ((1 << logn) < std::max(n + 1, m + 1))
		logn++;
	logn++;
	NTT(a, logn);
	NTT(b, logn);
	int length = 1 << logn;
	for (int i = 0; i < length; i++)
		c[i] = (long long)a[i] * b[i] % FNTT::mod;
	INTT(c, logn);
	for (int i = 0, to = n + m; i <= to; i++)
	{
		printOut(c[i]);
		putchar(' ');
	}
}

int main()
{
	run();
	return 0;
}