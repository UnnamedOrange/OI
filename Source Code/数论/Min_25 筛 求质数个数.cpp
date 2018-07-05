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

LL n;
LL sqrtN;
int k;

struct Min_25
{
	static const int maxn = int(1e6);
	int isntprime[maxn + 5];
	int prime[78499];
	void init()
	{
		std::memset(isntprime, 0, sizeof(isntprime));
		prime[0] = 0;
		isntprime[1] = true;
		for (int i = 2; i <= maxn; i++)
		{
			if (!isntprime[i])
				prime[++prime[0]] = i;
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
	LL g[maxn * 2 + 5];
	void initBlocks()
	{
		N = 0;
		for (LL i = 1, t; n / i > 1; i = t + 1) // 不需要用到 g(1)
		{
			t = n / (n / i);
			appear[++N] = n / i;
			if (appear[N] <= sqrtN) id[0][appear[N]] = N;
			else id[1][n / appear[N]] = N;
		}
	}
	inline LL& get(LL x)
	{
		if (x <= sqrtN) return g[id[0][x]];
		else return g[id[1][n / x]];
	}
	void solveG()
	{
		for (int i = 1; i <= N; i++)
			g[i] = appear[i] - 1;

		for (int j = 1; j <= k; j++)
			for (int i = 1; i <= N && (LL)prime[j] * prime[j] <= appear[i]; i++) // 从大到小计算
				g[i] = g[i] - (get(appear[i] / prime[j]) - (j - 1));
	}
} min_25;

void run()
{
	n = readIn();
	sqrtN = std::sqrt(n);
	min_25.init();
	min_25.initBlocks();
	min_25.solveG();
	printOut(min_25.get(n));
}

int main()
{
	run();
	return 0;
}