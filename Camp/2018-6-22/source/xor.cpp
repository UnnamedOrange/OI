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
const int maxn = int(1e5) + 5;
int n;
int a[maxn];

int fac[maxn];
int inv[maxn];
int invFac[maxn];
void init()
{
	const int to = int(1e5);
	fac[0] = 1;
	for (int i = 1; i <= to; i++)
		fac[i] = (LL)fac[i - 1] * i % mod;
	inv[1] = 1;
	for (int i = 2; i <= to; i++)
		inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod;
	invFac[0] = 1;
	for (int i = 1; i <= to; i++)
		invFac[i] = (LL)invFac[i - 1] * inv[i] % mod;
}
inline LL C(int down, int up)
{
	return down < up ? 0 : (LL)fac[down] * invFac[up] % mod * invFac[down - up] % mod;
}
inline LL invC(int down, int up)
{
	return down < up ? 0 : (LL)invFac[down] * fac[up] % mod * fac[down - up] % mod;
}
LL power(LL x, int y)
{
	LL ret = 1;
	while (y)
	{
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}

#define RunInstance(x) delete new x
struct brute
{
	int ans[maxn];

	brute() : ans()
	{
		for (int i = 0; i < 20; i++)
		{
			int c[2] = {};
			for (int j = 1; j <= n; j++)
				c[bool(a[j] & (1 << i))]++;

			for (int j = 1; j <= c[1]; j += 2)
			{
				for (int k = 0; k <= c[0]; k++)
				{
					ans[j + k] = (ans[j + k] +
						(LL)(1 << i) * C(c[1], j) % mod *
						C(c[0], k) % mod * invC(n, j + k)) % mod;
				}
			}
		}
		for (int i = n; i; i--)
		{
			printOut(ans[i]);
			putchar(' ');
		}
	}
};
struct work
{
	using Base = std::vector<int>;
	struct Poly : public Base
	{
		Poly() : Base(1) {}
		Poly(int size) : Base(size) {}
		void shrink()
		{
			while (size() > 1 && !back())
				pop_back();
		}

		static const int base = 119;
		static const int root = 3;
		static const int limit = 23;
		static void NTT(int* a, int logn, bool INTT)
		{
			static int revbit[1 << 17];
			int n = 1 << logn;
			revbit[0] = 0;
			for (int i = 1; i < n; i++)
				revbit[i] = (revbit[i >> 1] >> 1) | ((i & 1) << (logn - 1));
			for (int i = 1; i < n; i++)
				if (i < revbit[i])
					std::swap(a[i], a[revbit[i]]);

			for (int i = 1; i <= logn; i++)
			{
				int S = 1 << i;
				int half = S >> 1;
				int g1 = power(root, base * (1 << (limit - i)));
				if (INTT) g1 = power(g1, mod - 2);
				for (int j = 0; j < n; j += S)
				{
					int* A = a + j;
					int g = 1;
					for (int k = 0; k < half; k++)
					{
						int t = (LL)A[k + half] * g % mod;
						A[k + half] = (A[k] - t + mod) % mod;
						A[k] = (A[k] + t) % mod;
						g = (LL)g * g1 % mod;
					}
				}
			}
			if (INTT)
			{
				int inv = power(n, mod - 2);
				for (int i = 0; i < n; i++)
					a[i] = (LL)a[i] * inv % mod;
			}
		}
		Poly operator*(const Poly& c) const
		{
			Poly ret(size() + c.size() - 1);
			static int a[1 << 17];
			static int b[1 << 17];
			int logn = 0;
			while (1 << logn < ret.size()) logn++;
			int n = 1 << logn;
			std::memcpy(a, data(), sizeof(int) * size());
			std::memset(a + size(), 0, sizeof(int) * (n - size()));
			std::memcpy(b, c.data(), sizeof(int) * c.size());
			std::memset(b + c.size(), 0, sizeof(int) * (n - c.size()));
			NTT(a, logn, false);
			NTT(b, logn, false);
			for (int i = 0; i < n; i++)
				a[i] = (LL)a[i] * b[i] % mod;
			NTT(a, logn, true);
			std::memcpy(ret.data(), a, sizeof(int) * ret.size());
			ret.shrink();
			return ret;
		}
	};

	int ans[maxn];
	work() : ans()
	{
		int logn = 0;
		int t = *std::max_element(a + 1, a + 1 + n);
		while (1 << logn <= t) logn++;

		for (int i = 0; i < logn; i++)
		{
			int c[2] = {};
			for (int j = 1; j <= n; j++)
				c[bool(a[j] & (1 << i))]++;

			Poly A(c[1] + 1);
			for (int j = 1; j <= c[1]; j += 2)
				A[j] = C(c[1], j);
			Poly B(c[0] + 1);
			for (int j = 0; j <= c[0]; j++)
				B[j] = C(c[0], j);
			Poly temp = A * B;

			for (int j = 0; j < temp.size(); j++)
				ans[j] = (ans[j] + (LL)(1 << i) * invC(n, j) % mod * temp[j]) % mod;
		}
		for (int i = n; i; i--)
		{
			printOut(ans[i]);
			putchar(' ');
		}
	}
};

void run()
{
	init();
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();

	if (n <= 2000)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
#endif
	run();
	return 0;
}