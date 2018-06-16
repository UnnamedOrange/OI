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
	putchar('\n');
}

const int mod = 323232323;
const int maxn = 35;
int n;
LL a[maxn];
LL b[maxn];

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

	Poly operator*(const Poly& b) const
	{
		Poly ret;
		const Poly& a(*this);
		ret.resize(a.size() + b.size());
		for (int i = 0; i < a.size(); i++)
		{
			if (!a[i]) continue;
			for (int j = 0; j < b.size(); j++)
				ret[i + j] = (ret[i + j] + (LL)a[i] * b[j]) % mod;
		}
		ret.shrink();
		return ret;
	}
	Poly operator*(int b) const
	{
		Poly ret(size());
		for (int i = 0; i < size(); i++)
			ret[i] = (LL)(*this)[i] * b % mod;
		ret.shrink();
		return ret;
	}
	friend Poly operator*(int a, const Poly& b)
	{
		return b * a;
	}
	Poly operator-(const Poly& b) const
	{
		Poly ret(*this);
		ret.resize(std::max(size(), b.size()));
		for (int i = 0; i < b.size(); i++)
		{
			register int t;
			ret[i] = (t = ret[i] - b[i]) < 0 ? t + mod : t;
		}
		ret.shrink();
		return ret;
	}
	Poly operator+(const Poly& b) const
	{
		Poly ret(*this);
		ret.resize(std::max(size(), b.size()));
		for (int i = 0; i < b.size(); i++)
		{
			register int t;
			ret[i] = (t = ret[i] + b[i]) >= mod ? t - mod : t;
		}
		ret.shrink();
		return ret;
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

#define RunInstance(x) delete new x
struct work
{
	Poly S[maxn];
	LL C[maxn][maxn];

	void init()
	{
		memset(C, 0, sizeof(C));
		C[0][0] = 1;
		for (int i = 1; i <= n; i++)
		{
			C[i][0] = 1;
			for (int j = 1; j <= i; j++)
			{
				register LL t;
				C[i][j] = (t = C[i - 1][j - 1] + C[i - 1][j]) >= mod ? t - mod : t;
			}
		}

		S[0].resize(2);
		S[0][0] = 1;
		S[0][1] = 1;
		Poly temp(S[0]);
		for (int i = 1; i <= n; i++)
		{
			temp = temp * S[0];
			Poly& ans = S[i];
			LL inv = power(i + 1, mod - 2);
			for (int j = 0; j < i; j++)
				ans = ans + C[i + 1][j] * S[j];
			ans = (temp - ans) * inv;
		}
	}

	Poly f[maxn];

	work()
	{
		init();
		f[1][0] = 1;
		for (int i = 2; i <= n; i++)
		{
			Poly& ans = f[i];
			f[i - 1].resize(i - 1);
			for (int j = 0; j <= i - 2; j++)
			{
				LL g = 0;
				for (int k = 0; k <= i - 2 - j; k++)
				{
					g = (g + (LL)f[i - 1][j + k] * power(b[i - 1], k) % mod *
						power(a[i], j) % mod * C[j + k][k]) % mod;
				}
				ans = (ans + g * S[j]);
			}
		}

		LL ans = 0;
		LL p = 1;
		for (int i = 0; i < f[n].size(); i++)
		{
			ans = (ans + p * f[n][i]) % mod;
			p = p * b[n] % mod;
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 1; i <= n; i++)
		b[i] = readIn();

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
#endif
	run();
	return 0;
}