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

const int mod = 998244353;
int power(LL x, int y)
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
int C(int down, int up)
{
	if (down < up) return 0;
	int mul = 1;
	int div = 1;
	up = std::min(up, down - up);
	for (int i = 2; i <= up; i++)
		div = (LL)div * i % mod;
	for (; up; up--, down--)
		mul = (LL)mul * down % mod;
	return (LL)mul * power(div, mod - 2) % mod;
}

const int limit = 23;
const int root = 3;
const int base = 119;
void DFT(int* a, int logn, bool IDFT)
{
	static int revbit[262144];
	int n = 1 << logn;
	for (int i = 0; i < n; i++)
		revbit[i] = (revbit[i >> 1] >> 1) | ((i & 1) << (logn - 1));
	for (int i = 0; i < n; i++)
		if (i < revbit[i])
			std::swap(a[i], a[revbit[i]]);

	for (int i = 1; i <= logn; i++)
	{
		int S = 1 << i;
		int half = S >> 1;
		int g1 = power(root, base * (1 << (limit - i)));
		if (IDFT) g1 = power(g1, mod - 2);
		for (int j = 0; j < n; j += S)
		{
			int g = 1;
			int* A = a + j;
			for (int k = 0; k < half; k++)
			{
				LL t = (LL)A[half + k] * g % mod;
				A[half + k] = (A[k] - t) % mod;
				A[k] = (A[k] + t) % mod;
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
typedef std::vector<int> _Poly;
struct Poly : public _Poly
{
	Poly() : _Poly(1) {}
	Poly(int x0) : _Poly(2) { (*this)[0] = x0; (*this)[1] = 1; }
	Poly operator*(const Poly& b) const
	{
		const Poly& a = *this;
		Poly ret;
		ret.resize(a.size() + b.size() - 1);
		if (a.size() <= 32 && b.size() <= 32)
			for (int i = 0; i < a.size(); i++)
				for (int j = 0; j < b.size(); j++)
					ret[i + j] = (ret[i + j] + (LL)a[i] * b[j]) % mod;
		else
		{
			static int A[262150];
			static int B[262150];
			int t = a.size() + b.size() - 1;
			int logn = 0;
			while (1 << logn < t) logn++;
			logn++;
			int n = 1 << logn;
			memcpy(A, a.data(), sizeof(int) * a.size());
			memcpy(B, b.data(), sizeof(int) * b.size());
			memset(A + a.size(), 0, sizeof(int) * (n - a.size()));
			memset(B + b.size(), 0, sizeof(int) * (n - b.size()));
			DFT(A, logn, false);
			DFT(B, logn, false);
			for (int i = 0; i < n; i++)
				A[i] = (LL)A[i] * B[i] % mod;
			DFT(A, logn, true);
			memcpy(ret.data(), A, sizeof(int) * ret.size());
		}
		while (ret.size() > 1 && !ret.back())
			ret.pop_back();
		return ret;
	}
};
const int maxn = int(1e5) + 5;
Poly polys[maxn];
void StirlingFirst(int l, int r)
{
	if (l == r) return;
	int mid = (l + r) >> 1;
	StirlingFirst(l, mid);
	StirlingFirst(mid + 1, r);
	if (l == mid && mid + 1 == r)
		polys[mid] = Poly(l) * Poly(r);
	else if (l == mid)
	{
		polys[mid] = Poly(l) * polys[(mid + 1 + r) >> 1];
		polys[(mid + 1 + r) >> 1].clear();
	}
	else if (mid + 1 == r)
	{
		polys[mid] = polys[(l + mid) >> 1] * Poly(r);
		polys[(l + mid) >> 1].clear();
	}
	else
	{
		polys[mid] = polys[(l + mid) >> 1] * polys[(mid + 1 + r) >> 1];
		polys[(l + mid) >> 1].clear();
		polys[(mid + 1 + r) >> 1].clear();
	}
}

int n, a, b;

void run()
{
	n = readIn();
	a = readIn();
	b = readIn();
	if (!a || !b || a + b - 2 < 0 || a + b - 2 > n - 1 || a + b - 2 == 0 && n - 1 != 0)
	{
		printOut(0);
		return;
	}
	int ans = C(a + b - 2, a - 1);
	if (n == 1)
	{
		printOut(1);
		return;
	}
	if (n - 2 == 0)
		polys[0] = Poly(0);
	else
		StirlingFirst(0, n - 2);
	printOut(((LL)polys[(0 + n - 2) >> 1][a + b - 2] * ans % mod + mod) % mod);
}

int main()
{
	run();
	return 0;
}