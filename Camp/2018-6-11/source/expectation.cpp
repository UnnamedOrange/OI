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

const int mod = 323232323;
const int maxn = int(1e5) + 5;
int maxa;
int n;
int a[maxn];

int fac[maxn * 2];
int inv[maxn * 2];
int invFac[maxn * 2];
void init()
{
	loop to = std::max(maxa << 1, n);
	fac[0] = 1;
	for (loop i = 1; i <= to; i++)
		fac[i] = (LL)fac[i - 1] * i % mod;
	inv[1] = 1;
	for (loop i = 2; i <= to; i++)
		inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod;
	invFac[0] = 1;
	for (loop i = 1; i <= to; i++)
		invFac[i] = (LL)invFac[i - 1] * inv[i] % mod;
}
inline int C(int down, int up)
{
	return down < up ? 0 : (LL)fac[down] * invFac[up] % mod * invFac[down - up] % mod;
}

#define RunInstance(x) delete new x
struct cheat1
{
	cheat1()
	{
		int ans = 1;
		for (int i = 1, to = n - 1; i <= to; i++)
			ans = ((LL)ans * i % mod * inv[i + 1] + 1) % mod;
		printOut(ans);
	}
};
struct brute
{
	int f[10000];

	int code() const
	{
		int ret = 0;
		for (int i = n; i; i--)
			(ret *= 6) += a[i];
		return ret;
	}

	int DP()
	{
		if (!a[1])
			return 0;
		int& ans = f[code()];
		if (ans)
			return ans;

		int count = 0;
		for (int i = 1; i <= n; i++)
		{
			if (a[i])
			{
				count++;
				a[i]--;
				ans = (ans + DP()) % mod;
				a[i]++;
			}
		}
		ans = ((LL)ans * inv[count] + 1) % mod;
		return ans;
	}

	brute() : f()
	{
		printOut(DP());
	}
};
struct cheat2
{
	int f[1005][1005];

	cheat2()
	{
		for (int i = 0; i <= a[1]; i++)
			f[i][0] = i;
		for (int i = 0; i <= a[2]; i++)
			f[0][i] = 0;
		for (int i = 1; i <= a[1]; i++)
			for (int j = 1; j <= a[2]; j++)
			{
				f[i][j] = ((LL)(f[i - 1][j] + f[i][j - 1])
					* inv[2] + 1) % mod;
			}
		printOut(f[a[1]][a[2]]);
	}
};
struct cheat3
{
	int ans;
	cheat3() : ans()
	{
		int power2 = 1;
		for (int i = 1; i <= a[1]; i++)
			power2 = (LL)power2 * inv[2] % mod;
		for (int i = 0; i < a[2]; i++)
		{
			ans = (ans + (LL)power2 * C(a[1] - 1 + i, i)
				% mod * i) % mod;
			power2 = (LL)power2 * inv[2] % mod;
		}
		power2 = 1;
		for (int i = 1; i <= a[2]; i++)
			power2 = (LL)power2 * inv[2] % mod;
		for (int i = 0; i < a[1]; i++)
		{
			ans = (ans + (LL)power2 * C(a[2] - 1 + i, i)
				% mod * a[2]) % mod;
			power2 = (LL)power2 * inv[2] % mod;
		}
		ans = (ans + a[1]) % mod;
		printOut(ans);
	}
};
struct work
{
	int t[maxn];
	work() : t()
	{
		for (int i = 2; i <= n; i++)
			t[a[i] - 1]++;
		for (int i = maxa - 1; ~i; i--)
			t[i] += t[i + 1];

		int ans = 0;
		int power = 1;
		for (int i = 1; i <= a[1]; i++)
			power = (LL)power * inv[2] % mod;
		int base = power;
		for (int i = 0; i < maxa; i++)
		{
			ans = (ans + (LL)C(a[1] - 1 + i, i) * power % mod * i % mod * t[i]) % mod;
			power = (LL)power * inv[2] % mod;
		}

		memset(t, 0, sizeof(t));
		for (int i = 2; i <= n; i++)
			t[a[i] - 1] += a[i];
		for (int i = maxa - 1; ~i; i--)
			t[i] = (t[i] + t[i + 1]) % mod;
		int p = 0;
		power = base;
		for (int i = 0; i < maxa; i++)
		{
			p = (p + (LL)C(a[1] - 1 + i, i) * power % mod * t[i]) % mod;
			power = (LL)power * inv[2] % mod;
		}
		LL sum = 0;
		for (int i = 2; i <= n; i++)
			sum += a[i];
		sum %= mod;
		sum = sum - p + mod;
		ans = (ans + sum + a[1]) % mod;
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 1; i <= n; i++)
		maxa = std::max(maxa, a[i]);
	init();

	if (maxa <= 1)
		RunInstance(cheat1);
	else if (n <= 5 && maxa <= 5)
		RunInstance(brute);
	else if (n == 2)
		RunInstance(cheat3);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("expectation.in", "r", stdin);
	freopen("expectation.out", "w", stdout);
#endif
	run();
	return 0;
}