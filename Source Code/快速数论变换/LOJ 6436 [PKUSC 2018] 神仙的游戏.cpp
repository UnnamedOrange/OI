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
typedef LL INT_PUT;
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

static const int mod = 998244353;
static const int limit = 23;
static const int g = 3;
static const int base = 119;

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

using Vec = std::vector<int>;
struct Poly : public Vec
{
	Poly() : Vec(1) {}

	static void NTT(int* a, int logn, bool INTT)
	{
		static int preLogn;
		static int revbit[1 << 20];
		int n = 1 << logn;
		if (logn != preLogn)
		{
			preLogn = logn;
			for (int i = 1; i < n; i++)
			{
				revbit[i] = (revbit[i >> 1] >> 1) | ((i & 1) << (logn - 1));
			}
		}
		for (int i = 1; i < n; i++)
			if (i < revbit[i])
				std::swap(a[i], a[revbit[i]]);

		for (int i = 1; i <= logn; i++)
		{
			int S = 1 << i;
			int half = S >> 1;
			int g1 = power(g, base * (1 << (limit - i)));
			if (INTT) g1 = power(g1, mod - 2);
			for (int j = 0; j < n; j += S)
			{
				int* A = a + j;
				int w = 1;
				for (int k = 0; k < half; k++)
				{
					register LL t = (LL)A[k + half] * w % mod;
					A[k + half] = (A[k] - t + mod) % mod;
					A[k] = (A[k] + t) % mod;
					w = (LL)w * g1 % mod;
				}
			}
		}

		if (INTT)
		{
			register LL inv = power(n, mod - 2);
			for (int i = 0; i < n; i++)
				a[i] = (LL)a[i] * inv % mod;
		}
	}
	Poly operator*(const Poly& c)
	{
		static int a[1 << 20];
		static int b[1 << 20];
		int logn = 0;
		while ((1 << logn) < size() + c.size() - 1) logn++;
		int n = 1 << logn;
		std::memcpy(a, data(), sizeof(int) * size());
		std::memcpy(b, c.data(), sizeof(int) * c.size());
		std::memset(a + size(), 0, sizeof(int) * (n - size()));
		std::memset(b + c.size(), 0, sizeof(int) * (n - c.size()));
		NTT(a, logn, false);
		NTT(b, logn, false);
		for (int i = 0; i < n; i++)
			a[i] = (LL)a[i] * b[i] % mod;
		NTT(a, logn, true);

		Poly ret;
		ret.resize(n);
		std::memcpy(ret.data(), a, sizeof(int) * n);
		while (ret.size() > 1 && !ret.back())
			ret.pop_back();
		return ret;
	}
} A, B;

const int maxn = int(5e5) + 5;
int n;
char str[maxn];

bool pos[maxn];

void run()
{
	scanf("%s", str);
	n = strlen(str);

	A.resize(n + 1);
	B.resize(n + 1);
	for (int i = 1; i <= n; i++)
		if (str[i - 1] == '0')
			B[n - i] = 1;
		else if (str[i - 1] == '1')
			A[i] = 1;

	Poly C = A * B;
	C.resize(2 * n);

	for (int i = 1; i < n; i++)
		pos[i] = C[n + i] || C[n - i];

	LL ans = (LL)n * n;
	for (int i = 1; i < n; i++)
	{
		bool bOk = true;
		for (int j = i; j <= n; j += i)
		{
			if (pos[j])
			{
				bOk = false;
				break;
			}
		}
		if (bOk) ans ^= (LL)(n - i) * (n - i);
	}
	printOut(ans);
}

int main()
{
	run();
	return 0;
}