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

const int mod = int(1e9) + 7;

struct Min_25
{
	static const int maxn = int(1e5);
	bool isntprime[maxn + 5];
	int prime[9593];
	int sum[9593];
	Min_25() : isntprime()
	{
		sum[0] = 0;
		prime[0] = 0;
		isntprime[1] = true;
		for (int i = 2; i <= maxn; i++)
		{
			if (!isntprime[i])
			{
				prime[++prime[0]] = i;
				sum[prime[0]] = (sum[prime[0] - 1] + i) % mod;
			}
			for (int j = 1, p = prime[j], s = i * p; j <= prime[0] && s <= maxn; j++, p = prime[j], s = i * p)
			{
				isntprime[s] = true;
				if (!(i % p))
					break;
			}
		}
	}

	LL n;
	int sqrtN;
	int k;
	int N;
	int id[2][maxn];
	LL appear[maxn * 2];
	void initBlocks()
	{
		N = 0;
		for (LL i = 1, t; n / i > 1; i = t + 1)
		{
			LL a = n / i;
			t = n / a;
			appear[++N] = a;
			if (a <= sqrtN) id[0][a] = N;
			else id[1][n / a] = N;
		}
	}
	int getId(LL x)
	{
		if (x <= sqrtN) return id[0][x];
		else return id[1][n / x];
	}
	int g[2][maxn * 2];
	int s[maxn * 2];
	void solveG()
	{
		for (int i = 1; i <= N; i++)
		{
			g[0][i] = (appear[i] - 1) % mod;
			if (appear[i] & 1)
				g[1][i] = (LL)(2 + appear[i]) % mod * (((appear[i] - 1) >> 1) % mod) % mod;
			else
				g[1][i] = (LL)((2 + appear[i]) >> 1) % mod * ((appear[i] - 1) % mod) % mod;
		}

		for (int j = 1, p = prime[j]; j <= k; j++, p = prime[j])
			for (int i = 1; i <= N && (LL)p * p <= appear[i]; i++)
			{
				g[0][i] = ((LL)g[0][i] - (g[0][getId(appear[i] / p)] - (j - 1))) % mod;
				g[1][i] = (g[1][i] - (LL)prime[j] *
					(g[1][getId(appear[i] / p)] - sum[j - 1])) % mod;
			}
	}
	void solveS()
	{
		for (int i = 1; i <= N; i++)
			s[i] = g[1][i] - g[0][i] + 2;

		for (int j = k, p = prime[j]; j; j--, p = prime[j])
			for (int i = 1; i <= N && (LL)p * p <= appear[i]; i++)
			{
				LL power = p;
				for (int e = 1; p <= appear[i] / power; e++, power *= p)
				{
					s[i] = (s[i] + (LL)(p ^ e) *
						((s[getId(appear[i] / power)] - (sum[j] - j + 2)) % mod) + (p ^ (e + 1))) % mod;
				}
			}
		s[1] = (s[1] + mod) % mod;
	}

	int operator()(LL param)
	{
		n = param;
		sqrtN = std::sqrt(n);
		k = std::upper_bound(prime + 1, prime + 1 + prime[0], sqrtN) - prime - 1;
		initBlocks();
		solveG();
		solveS();
		return s[1] + (n >= 1);
	}
} min_25;

void run()
{
	printOut(min_25(readIn()));
}

int main()
{
	run();
	return 0;
}