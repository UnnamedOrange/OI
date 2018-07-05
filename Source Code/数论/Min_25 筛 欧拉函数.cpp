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

const int mod = int(1e9) + 7;
LL n;
LL sqrtN;
int k;

struct Min_25
{
	static const int maxn = int(1e5);
	int isntprime[maxn + 5];
	int prime[9593];
	LL sum[9593];
	void init()
	{
		std::memset(isntprime, 0, sizeof(isntprime));
		prime[0] = 0;
		sum[0] = 0;
		isntprime[1] = true;
		for (int i = 2; i <= maxn; i++)
		{
			if (!isntprime[i])
			{
				prime[++prime[0]] = i;
				sum[prime[0]] = (sum[prime[0] - 1] + i) % mod;
			}
			for (int j = 1, p = prime[j], s = p * i; j <= prime[0] && s <= maxn; j++, p = prime[j], s = p * i)
			{
				isntprime[s] = true;
				if (!(i % p)) break;
			}
		}
		k = std::upper_bound(prime + 1, prime + 1 + prime[0], sqrtN) - prime - 1;
	}

	int N;
	LL appear[maxn * 2 + 5];
	int id[2][maxn + 5];
	LL g1[maxn * 2 + 5];
	LL g2[maxn * 2 + 5];
	LL s[maxn * 2 + 5];
	void initBlocks()
	{
		N = 0;
		for (LL i = 1, t; n / i > 1; i = t + 1)
		{
			t = n / (n / i);
			appear[++N] = n / i;
			if (appear[N] <= sqrtN) id[0][appear[N]] = N;
			else id[1][n / appear[N]] = N;
		}
	}
	inline LL& get1(LL x)
	{
		if (x <= sqrtN) return g1[id[0][x]];
		else return g1[id[1][n / x]];
	}
	inline LL& get2(LL x)
	{
		if (x <= sqrtN) return g2[id[0][x]];
		else return g2[id[1][n / x]];
	}
	inline LL& gets(LL x)
	{
		if (x <= sqrtN) return s[id[0][x]];
		else return s[id[1][n / x]];
	}
	void solveG()
	{
		for (int i = 1; i <= N; i++)
		{
			if ((2 + appear[i]) & 1) // note：注意数据范围，小心溢出
				g1[i] = (LL)(2 + appear[i]) % mod * (((appear[i] - 1) / 2) % mod) % mod;
			else
				g1[i] = (LL)((2 + appear[i]) / 2) % mod * ((appear[i] - 1) % mod) % mod;
			g2[i] = appear[i] - 1;
		}

		for (int j = 1; j <= k; j++)
			for (int i = 1; i <= N && (LL)prime[j] * prime[j] <= appear[i]; i++)
			{
				g1[i] = g1[i] - (LL)prime[j] * (get1(appear[i] / prime[j]) - sum[j - 1]);
				g1[i] %= mod;
				g2[i] = g2[i] - (get2(appear[i] / prime[j]) - (j - 1));
				g2[i] %= mod;
			}

		for (int i = 1; i <= N; i++)
			(g1[i] -= g2[i]) %= mod; // note：g2 不能等于 -1
	}
	void solveS()
	{
		for (int i = 1; i <= N; i++)
			s[i] = g1[i];

		for (int j = k; j; j--)
			for (int i = 1; i <= N && (LL)prime[j] * prime[j] <= appear[i]; i++)
			{
				LL power = prime[j];
				LL f = prime[j] - 1;
				for (int e = 1; appear[i] / power >= prime[j]; // note：这里是要保证满足的条件的本质。为了防止溢出（不过好像不可能溢出……），这里用了除法
					e++, power *= prime[j], // note：别忘了 power 不能取模
					f = f * prime[j] % mod)
				{
					s[i] += f * (gets(appear[i] / power) - gets(prime[j]) + prime[j]); // note：这里把最后那个写进来了
					s[i] %= mod;
				}
			}
		(s[1] += mod) %= mod;
	}
} min_25;

void run()
{
	n = readIn();
	sqrtN = std::sqrt(n);
	min_25.init();
	min_25.initBlocks();
	min_25.solveG();
	min_25.solveS();
	printOut(min_25.s[1] + (n >= 1)); // note：s[1] 保存的是 n 的值；记住加上 1
}

int main()
{
	run();
	return 0;
}