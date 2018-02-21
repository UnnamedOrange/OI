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

const int mod = 998244353;
const int base = 119;
const int limit = 23;
const int root = 3;
const int maxn = 262150;

struct FNTT
{
	int n, logn;
	inline int revbit(int x)
	{
		int ret = 0;
		for (int i = 0; i < logn; i++)
			ret = (ret << 1) | (bool)(x & (1 << i));
		return ret;
	}
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
	FNTT(int* a, int logn, int sig) : n(1 << logn), logn(logn)
	{
		for (int i = 0; i < n; i++)
		{
			int t = revbit(i);
			if (i < t)
				std::swap(a[i], a[t]);
		}
		for (int i = 1; i <= logn; i++)
		{
			int S = 1 << i;
			int half = S >> 1;
			int g1 = power(root, base * (1 << (limit - i)));
			if (sig == -1) g1 = power(g1, mod - 2);
			for (int j = 0; j < n; j += S)
			{
				int g = 1;
				int* A = a + j;
				for (int k = 0; k < half; k++)
				{
					int t = (long long)A[k + half] * g % mod;
					A[k + half] = (A[k] - t) % mod;
					A[k] = (A[k] + t) % mod;
					g = (long long)g * g1 % mod;
				}
			}
		}
		for (int i = 0; i < n; i++)
			a[i] = (a[i] % mod + mod) % mod;
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
		int inv = FNTT::power(n, mod - 2);
		for (int i = 0; i < n; i++)
			a[i] = (long long)a[i] * inv % mod;
	}
};

int readNum(int* rec)
{
	static char buffer[maxn];
	std::cin.getline(buffer, maxn);
	int length = strlen(buffer);
	for (int i = 0; i < length; i++)
	{
		rec[i] = buffer[length - 1 - i] - '0';
	}
	return length;
}

int n, m;
int a[maxn], b[maxn];

void run()
{
	n = readNum(a);
	m = readNum(b);
	int logn = 0;
	while (1 << logn < std::max(n, m))
		logn++;
	logn++;
	NTT(a, logn);
	NTT(b, logn);
	int t = 1 << logn;
	for (int i = 0; i < t; i++)
		a[i] = (long long)a[i] * b[i] % mod;
	INTT(a, logn);

	t--;
	for (int i = 0; i < t; i++)
	{
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
	}
	while (t && !a[t])
		t--;
	for (int i = t; ~i; i--)
		printOut(a[i]);
}

int main()
{
	run();
	return 0;
}