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

struct Min_25
{
	static const int maxn = int(1e5);
	int isntprime[maxn + 5];
	int prime[maxn];
	Min_25() : isntprime()
	{
		prime[0] = 0;
		isntprime[1] = true;
		for (int i = 2; i <= maxn; i++)
		{
			if (!isntprime[i])
				prime[++prime[0]] = i;
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
	LL appear[maxn * 2 + 5];
	int id[2][maxn + 5];
	void initBlocks()
	{
		N = 0;
		for (LL i = 1, t; n / i > 1; i = t + 1)
		{
			t = n / (n / i);
			LL a = appear[++N] = n / i;
			if (a <= sqrtN) id[0][a] = N;
			else id[1][n / a] = N;
		}
	}
	int getId(LL x)
	{
		if (x <= sqrtN) return id[0][x];
		else return id[1][n / x];
	}
	LL g[maxn * 2 + 5];
	LL s[maxn * 2 + 5];
	void solveG()
	{
		for (int i = 1; i <= N; i++)
			g[i] = appear[i] - 1;
		for (int j = 1, p = prime[j]; j <= k; j++, p = prime[j])
			for (int i = 1; i <= N && (LL)p * p <= appear[i]; i++)
				g[i] -= g[getId(appear[i] / p)] - (j - 1);
	}
	void solveS()
	{
		for (int i = 1; i <= N; i++)
			s[i] = -g[i];
		for (int j = k, p = prime[j]; j; j--, p = prime[j])
			for (int i = 1; i <= N && (LL)p * p <= appear[i]; i++)
				s[i] += -(s[getId(appear[i] / p)] - s[getId(p)]); // note：mu 就不用枚举了，上面全是 0
	}

	LL operator()(LL param)
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
	LL from = readIn();
	LL to = readIn();
	printOut(min_25(to) - min_25(from - 1));
}

int main()
{
	run();
	return 0;
}