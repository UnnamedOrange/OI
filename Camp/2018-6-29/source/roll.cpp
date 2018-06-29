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
	putchar('\n');
}

const int mod = 998244353;
const int maxn = int(1e5) + 5;
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
int fac[maxn];
int inv[maxn];
int invFac[maxn];
void init()
{
	int to = maxn - 1;
	inv[1] = 1;
	for (int i = 2; i <= to; i++)
		inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod;
	fac[0] = 1;
	for (int i = 1; i <= to; i++)
		fac[i] = (LL)fac[i - 1] * i % mod;
	invFac[0] = 1;
	for (int i = 1; i <= to; i++)
		invFac[i] = (LL)invFac[i - 1] * inv[i] % mod;
}
typedef std::vector<int> Base;
struct Poly : public Base
{
	Poly() : Base(1) {}
	Poly(int size) : Base(size) {}
	void clear() { clear(); resize(1); }
	void Mod(int size) { resize(size); }
	static void NTT(int* a, int logn, bool INTT)
	{
		static int pre;
		static int revbit[1 << 18];
		int n = 1 << logn;
		if (logn != pre)
		{
			revbit[0] = 0;
			int n = 1 << logn;
			for (int i = 1; i < n; i++)
				revbit[i] = (revbit[i >> 1] >> 1) | ((i & 1) << (logn - 1));
			pre = logn;
		}
		for (int i = 0; i < n; i++)
			if (i < revbit[i])
				std::swap(a[i], a[revbit[i]]);
		for (int i = 1; i <= logn; i++)
		{
			int S = 1 << i;
			int half = S >> 1;
			int g1 = power(3, 119 * (1 << (23 - i)));
			if (INTT) g1 = power(g1, mod - 2);
			for (int j = 0; j < n; j += S)
			{
				int* A = a + j;
				int g = 1;
				for (int k = 0; k < half; k++)
				{
					register int temp;
					int t = (LL)A[k + half] * g % mod;
					A[k + half] = (temp = A[k] - t) < 0 ? temp + mod : temp;
					A[k] = (temp = A[k] + t) >= mod ? temp - mod : temp;
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
		int logn = 0;
		while ((1 << logn) < ret.size()) logn++;
		int n = 1 << logn;
		static int a[1 << 18];
		static int b[1 << 18];
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
		return ret;
	}
};

int n, m;
int a[maxn];

#define RunInstance(x) delete new x
struct test
{
	long double sum = 0;
	LL count = 0;
	LL temp[10];
	static const int EPS = int(35);
	void search(int depth)
	{
		if (depth > n)
		{
			count++;
			long double t = 0;
			for (int i = 1; i <= n; i++)
				t += (long double)(a[i] * temp[i]) / EPS;
			sum += std::pow(t, m);
			return;
		}
		for (temp[depth] = 0; temp[depth] <= EPS; temp[depth]++)
			search(depth + 1);
	}
	test()
	{
		search(1);
		printf("%Lf\n", sum / count);
	}
};
struct real
{
	long double ans;
	long double E[6][6];
	int times[6];
	void search(int depth)
	{
		if (depth > m)
		{
			long double t = 1;
			for (int i = 1; i <= n; i++)
				t *= E[i][times[i]];
			ans += t;
			return;
		}
		for (int i = 1; i <= n; i++)
		{
			times[i]++;
			search(depth + 1);
			times[i]--;
		}
	}
	real() : ans(), times()
	{
		for (int i = 1; i <= n; i++)
		{
			E[i][0] = 1;
			for (int j = 1; j <= m; j++)
				E[i][j] = (double)std::pow(a[i], j) / (j + 1);
		}
		search(1);
		printf("%Lf\n", ans);
	}
};

struct brute1
{
	int ans;
	int E[6][6];
	int times[6];
	void search(int depth)
	{
		if (depth > m)
		{
			LL t = 1;
			for (int i = 1; i <= n; i++)
				t = t * E[i][times[i]] % mod;
			ans = (ans + t) % mod;
			return;
		}
		for (int i = 1; i <= n; i++)
		{
			times[i]++;
			search(depth + 1);
			times[i]--;
		}
	}
	brute1() : ans(), times()
	{
		for (int i = 1; i <= n; i++)
		{
			E[i][0] = 1;
			for (int j = 1; j <= m; j++)
				E[i][j] = (LL)power(a[i], j) * inv[j + 1] % mod;
		}
		search(1);
		printOut(ans);
	}
};
struct brute2
{
	Poly ans;
	Poly temp;

	brute2()
	{
		ans[0] = 1;
		for (int i = 1; i <= n; i++)
		{
			temp.Mod(m + 1);
			LL p = a[i];
			temp[0] = 1;
			for (int j = 1; j <= m; j++, p = (LL)p * a[i] % mod)
				temp[j] = (LL)p * inv[j + 1] % mod * invFac[j] % mod;
			ans = ans * temp;
			ans.Mod(m + 1);
		}
		printOut((LL)ans[m] * fac[m] % mod);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	init();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();

	if (n <= 5 && m <= 5)
		RunInstance(brute1);
	else if (n <= 1000 && m <= 1000)
		RunInstance(brute2);
}

int main()
{
#ifndef LOCAL
	freopen("roll.in", "r", stdin);
	freopen("roll.out", "w", stdout);
#endif
	run();
	return 0;
}