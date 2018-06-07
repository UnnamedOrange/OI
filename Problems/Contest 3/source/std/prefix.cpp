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
	putchar('\n');
}

const int mod = int(1e5) + 3;
const int maxn = int(1e4) + 5;
int T;
struct Query
{
	LL n, m, a;
	void read()
	{
		n = readIn();
		m = readIn();
		a = readIn();
	}
} querys[maxn];
LL nt, mt, at;

#define RunInstance(x) delete new x
struct brute1
{
	int a[105];

	brute1()
	{
		for (int o = 1; o <= T; o++)
		{
			const Query& Q = querys[o];
			memset(a, 0, sizeof(a));
			a[0] = Q.a;
			for (int i = 0; i < Q.m; i++)
			{
				for (int j = 1; j <= Q.n; j++)
				{
					(a[j] += a[j - 1]) %= mod;
				}
			}
			printOut(a[Q.n]);
		}
	}
};
struct cheat
{
	cheat()
	{
		for (int o = 1; o <= T; o++)
		{
			const Query& Q = querys[o];
			printOut((Q.m % mod) * (Q.a % mod) % mod);
		}
	}
};
int fac[mod];
int inv[mod];
int invFac[mod];
void init()
{
	fac[0] = 1;
	for (int i = 1; i < mod; i++)
		fac[i] = (LL)fac[i - 1] * i % mod;
	inv[1] = 1;
	for (int i = 2; i < mod; i++)
		inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod;
	invFac[0] = 1;
	for (int i = 1; i < mod; i++)
		invFac[i] = (LL)invFac[i - 1] * inv[i] % mod;
}
inline int C(int down, int up)
{
	return down < up ? 0 : (LL)fac[down] * invFac[up] % mod *
		invFac[down - up] % mod;
}
struct brute2
{
	brute2()
	{
		init();
		for (int o = 1; o <= T; o++)
		{
			const Query& Q = querys[o];
			if (!Q.m)
				printOut(Q.n ? 0 : Q.a);
			else
				printOut(Q.a % mod * C(Q.m - 1 + Q.n, Q.m - 1) % mod);
		}
	}
};
struct work
{
	static LL Lucas(LL down, LL up)
	{
		if (down < up) return 0;
		if (!down) return 1;
		return C(down % mod, up % mod) * Lucas(down / mod, up / mod) % mod;
	}
	work()
	{
		init();
		for (int o = 1; o <= T; o++)
		{
			const Query& Q = querys[o];
			if (!Q.m)
				printOut(Q.n ? 0 : Q.a);
			else
				printOut(Q.a % mod * Lucas(Q.m - 1 + Q.n, Q.m - 1) % mod);
		}
	}
};

void run()
{
	T = readIn();
	for (int i = 1; i <= T; i++)
	{
		querys[i].read();
		nt = std::max(nt, querys[i].n);
		mt = std::max(mt, querys[i].m);
		at = std::max(at, querys[i].a);
	}

	if (nt <= 100 && mt <= 100)
		RunInstance(brute1);
	else if (nt == 1)
		RunInstance(cheat);
	else if (nt <= 50000 && mt <= 50000)
		RunInstance(brute2);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("prefix.in", "r", stdin);
	freopen("prefix.out", "w", stdout);
#endif
	run();
	return 0;
}