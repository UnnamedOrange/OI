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
#define loop register int
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
	putchar('\n');
}

const int mod = 998244353;
const int maxn = int(1e5) + 5;
int n;
int a[maxn];

#define RunInstance(x) delete new x
struct brute1
{
	brute1()
	{
		int U = 1 << n;
		int ans = 0;
		for (loop S = 1; S < U; S++)
			for (loop S0 = S; S0; S0 = (S0 - 1) & S)
			{
				int mul = 1;
				for (loop i = 0; i < n; i++)
					if (S0 & (1 << i))
						mul = (LL)mul * a[i] % mod;
				ans = (ans + mul) % mod;
			}
		printOut(ans);
	}
};
struct brute2
{
	static const int maxN = 5005;
	int f[maxN];
	int power[maxN];

	brute2() : f()
	{
		power[0] = 1;
		for (int i = 1; i <= n; i++)
		{
			power[i] = power[i - 1] << 1;
			if (power[i] >= mod) power[i] -= mod;
		}
		f[0] = 1;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j; j--)
				f[j] = (f[j] + (LL)a[i] * f[j - 1]) % mod;

		int ans = 0;
		for (int i = 1; i <= n; i++)
			ans = (ans + (LL)f[i] * power[n - i]) % mod;
		printOut(ans);
	}
};
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
struct work
{
	typedef std::vector<int> __poly;
	struct Poly : __poly
	{
		Poly() : __poly(1) {}
		Poly(int x) : __poly(2) { __poly::operator[](0) = 1; __poly::operator[](1) = x; }
		static void DFT(int* a, int logn, bool IDFT)
		{
			static int revbit[1 << 19];
			int n = 1 << logn;
			for (int i = 1; i < n; i++)
				revbit[i] = (revbit[i >> 1] >> 1) | ((i & 1) << (logn - 1));

			for (int i = 0; i < n; i++)
				if (i < revbit[i])
					std::swap(a[i], a[revbit[i]]);

			const int limit = 23;
			const int base = 119;
			const int root = 3;
			for (int i = 1; i <= logn; i++)
			{
				int S = 1 << i;
				int half = S >> 1;
				int g1 = power(root, base * (1 << (limit - i)));
				if (IDFT) g1 = power(g1, mod - 2);
				for (int j = 0; j < n; j += S)
				{
					int* A = a + j;
					int g = 1;
					for (int k = 0; k < half; k++)
					{
						LL t = (LL)A[k + half] * g % mod;
						register int temp;
						A[k + half] = (temp = A[k] - t) < 0 ? temp + mod : temp;
						A[k] = (temp = A[k] + t) >= mod ? temp - mod : temp;
						g = (LL)g * g1 % mod;
					}
				}
			}

			if (IDFT)
			{
				int inv = power(n, mod - 2);
				for (int i = 0; i < n; i++)
					a[i] = (LL)a[i] * inv % mod;
			}
		}
		Poly operator*(const Poly& b) const
		{
			const Poly& a = *this;
			Poly c;
			c.resize(a.size() + b.size() - 1);
			int logn = 0;
			while ((1 << logn) < c.size())
				logn++;
			int n = 1 << logn;

			static int A[1 << 19];
			static int B[1 << 19];
			memcpy(A, a.data(), sizeof(int) * (a.size()));
			memset(A + a.size(), 0, sizeof(int) * (n - a.size()));
			memcpy(B, b.data(), sizeof(int) * (b.size()));
			memset(B + b.size(), 0, sizeof(int) * (n - b.size()));
			DFT(A, logn, false);
			DFT(B, logn, false);
			for (int i = 0; i < n; i++)
				A[i] = (LL)A[i] * B[i] % mod;
			DFT(A, logn, true);
			memcpy(c.data(), A, sizeof(int) * c.size());
			while (c.size() > 1 && !c.back()) c.pop_back();
			return c;
		}
	};

	Poly divide(int l, int r)
	{
		if (l == r)
			return Poly(a[l]);
		int mid = (l + r) >> 1;
		return divide(l, mid) * divide(mid + 1, r);
	}

	work()
	{
		Poly poly = divide(0, n - 1);
		int ans = 0;
		poly.resize(n + 1);
		int p = 1;
		for (int i = n; i; i--)
		{
			ans = (ans + (LL)p * poly[i]) % mod;
			p <<= 1;
			if (p >= mod)
				p -= mod;
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	for (int i = 0; i < n; i++)
		a[i] = readIn();

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("subsubset.in", "r", stdin);
	freopen("subsubset.out", "w", stdout);
#endif
	run();
	return 0;
}