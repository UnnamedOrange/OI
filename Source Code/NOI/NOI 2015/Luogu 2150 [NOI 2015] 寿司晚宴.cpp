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

const int prime[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
LL mod;
int n;

#define RunInstance(x) delete new x
struct brute
{
	int mask[35];
	LL f[1 << 10][1 << 10];

	brute() : mask(), f()
	{
		for (int i = 2; i <= n; i++)
			for (int j = 0; j < 10; j++)
				if (i % prime[j] == 0)
					mask[i] |= 1 << j;

		int U = 1 << 10;
		f[0][0] = 1;
		for (loop i = 2; i <= n; i++)
		{
			loop m = mask[i];
			for (loop S1 = U - 1; ~S1; S1--)
				for (loop S2 = U - 1; ~S2; S2--) if (f[S1][S2])
				{
					if (!(S2 & m))
						(f[S1 | m][S2] += f[S1][S2]) %= mod;
					if (!(S1 & m))
						(f[S1][S2 | m] += f[S1][S2]) %= mod;
					// 唯一会出错的情况是: (!(S2 & mask[i + 1])) && (!(S1 & mask[i + 1])) && ((S1 | mask[i + 1]) == S1)，
					// 即 f[S1][S2] 在自增后再去更新其它的
					// 显然第二个条件和第三个条件矛盾，因此不会出错
				}
		}

		LL ans = 0;
		for (loop S1 = 0; S1 < U; S1++)
			for (loop S2 = 0; S2 < U; S2++)
				(ans += f[S1][S2]) %= mod;
		printOut(ans);
	}
};
struct work
{
	struct Number
	{
		int num;
		int mask;
		int big;
		Number() {}
		Number(int num, int mask, int big) : num(num), mask(mask), big(big) {}
		bool operator<(const Number& b) const { return big < b.big; }
	};
	std::vector<Number> number[505];

	LL f[1 << 8][1 << 8];
	LL g[2][1 << 8][1 << 8];

	work() : f()
	{
		for (int i = 2; i <= n; i++)
		{
			int t = i;
			int mask = 0;
			for (int j = 0; j < 8; j++)
			{
				if (t % prime[j]) continue;
				mask |= 1 << j;
				while (!(t % prime[j]))
					t /= prime[j];
			}
			number[t].push_back(Number(i, mask, t));
		}

		int U = 1 << 8;
		f[0][0] = 1;
		for (int i = 0; i < number[1].size(); i++)
		{
			loop m = number[1][i].mask;
			for (loop S1 = U - 1; ~S1; S1--)
				for (loop S2 = U - 1; ~S2; S2--) if (f[S1][S2])
				{
					if (!(S2 & m))
						(f[S1 | m][S2] += f[S1][S2]) %= mod;
					if (!(S1 & m))
						(f[S1][S2 | m] += f[S1][S2]) %= mod;
				}
		}

		for (int i = 2; i <= n; i++) if (number[i].size())
		{
			memcpy(g[0], f, sizeof(g[0]));
			memcpy(g[1], g, sizeof(g[1]));
			for (int j = 0; j < number[i].size(); j++)
			{
				loop m = number[i][j].mask;
				for (loop S1 = U - 1; ~S1; S1--)
					for (loop S2 = U - 1; ~S2; S2--) if (g[0][S1][S2])
					{
						if (!(S2 & m))
							(g[0][S1 | m][S2] += g[0][S1][S2]) %= mod;
						if (!(S1 & m))
							(g[1][S1][S2 | m] += g[1][S1][S2]) %= mod;
					}
			}
			for (loop S1 = U - 1; ~S1; S1--)
				for (loop S2 = U - 1; ~S2; S2--)
					f[S1][S2] = ((g[0][S1][S2] + g[1][S1][S2] - f[S1][S2]) % mod + mod) % mod;
		}

		LL ans = 0;
		for (loop S1 = 0; S1 < U; S1++)
			for (loop S2 = 0; S2 < U; S2++)
				(ans += f[S1][S2]) %= mod;
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	mod = readIn();
	if (n <= 30)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
	run();
	return 0;
}