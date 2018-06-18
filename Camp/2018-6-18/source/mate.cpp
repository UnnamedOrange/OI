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
	while (!(std::isdigit(ch) || ch == '-'))
		ch = getchar();
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
	putchar('\n');
}

const int mod = 998244353;
const int maxn = int(1e5) + 5;
int n, t1 = true, t2;
int a[maxn], b[maxn];

int fac[maxn];
int inv[maxn];
int invFac[maxn];
void init()
{
	int to = int(1e5);
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
inline LL A(int down, int up)
{
	return down < up ? 0 : (LL)fac[down] * invFac[down - up] % mod;
}

#define RunInstance(x) delete new x
struct cheat1
{
	int f[maxn];
	cheat1() : f()
	{
		f[0] = 1;
		f[1] = 0;
		f[2] = 1;
		for (int i = 3; i <= n; i++)
			f[i] = ((LL)(i - 1) * (f[i - 2] + f[i - 1])) % mod;
		printOut(f[n]);
	}
};
struct cheat2
{
	cheat2()
	{
		int sum = 0;
		bool bOk = true;
		int b1 = 0, b2 = 0;
		for (int i = 1; i <= n; i++)
		{
			if (!b[i])
				sum += a[i];
			else
			{
				if (!b1)
					b1 = i;
				else
					b2 = i;
			}
		}

		LL ans = A(b[b2], a[b1]) * A(b[b1], a[b2]) % mod * fac[sum] % mod;
		printOut(ans);
	}
};
LL power(LL x, int y)
{
	LL ret = 1;
	while (y)
	{
		if (y & 1)
			ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
using Base = std::vector<int>;
struct Poly : public Base
{
	Poly() : Base(1, 1) {}
	Poly(int size) : Base(size) {}
	void shrink()
	{
		while (size() > 1 && !back())
			pop_back();
	}

	static void NTT(int *a, int logn, bool INTT)
	{
		static int revbit[1 << 18];
		int n = 1 << logn;
		revbit[0] = 0;
		for (int i = 1; i < n; i++)
			revbit[i] = (revbit[i >> 1] >> 1) | ((i & 1) << (logn - 1));
		for (int i = 0; i < n; i++)
			if (i < revbit[i])
				std::swap(a[i], a[revbit[i]]);

		for (int i = 1; i <= logn; i++)
		{
			int S = 1 << i;
			int half = S >> 1;
			int g1 = power(3, 119 * (1 << (23 - i)));
			if (INTT)
				g1 = power(g1, mod - 2);
			for (int j = 0; j < n; j += S)
			{
				int *B = a + j;
				int g = 1;
				for (int k = 0; k < half; k++)
				{
					int t = (LL)g * B[k + half] % mod;
					B[k + half] = (B[k] - t + mod) % mod;
					B[k] = (B[k] + t) % mod;
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
	Poly operator*(const Poly &c) const
	{
		static int a[1 << 18];
		static int b[1 << 18];
		Poly ret(size() + c.size() - 1);
		int logn = 0;
		while (1 << logn < ret.size())
			logn++;
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
		memcpy(ret.data(), a, sizeof(int) * ret.size());
		ret.shrink();
		return ret;
	}
};
struct work
{
	Poly divide(int l, int r)
	{
		Poly ret;
		if (l == r)
		{
			int to = std::min(a[l], b[l]);
			ret.resize(to + 1);
			for (int i = 0; i <= to; i++)
				ret[i] = (LL)A(a[l], i) * C(b[l], i) % mod;
			return ret;
		}
		int mid = (l + r) >> 1;
		return divide(l, mid) * divide(mid + 1, r);
	}

	work()
	{
		int m = 0;
		for (int i = 1; i <= n; i++)
			m += a[i];
		Poly poly = divide(1, n);
		int ans = 0;
		for (int i = 0, t = 1; i < poly.size(); i++, t = -t)
			ans = (ans + (LL)poly[i] * fac[m - i] % mod * t) % mod;
		printOut((ans + mod) % mod);
	}
};

void run()
{
	init();
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		a[i] = readIn();
		b[i] = readIn();
		if (a[i] != 1 || b[i] != 1)
			t1 = false;
		if (b[i])
			t2++;
	}

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("mate.in", "r", stdin);
	freopen("mate.out", "w", stdout);
#endif
	run();
	return 0;
}