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
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int mod = 998244353;
const int maxn = int(3e5) + 5;
int n;
char str[maxn];

#define RunInstance(x) delete new x
struct brute1
{
	static inline void DebugPrint(int S)
	{
#ifdef LOCAL
		static int stamp;
		++stamp;
		printf("#%d: ", stamp);
		for (int i = n - 1; ~i; i--)
			putchar('0' + bool(S & (1 << i)));
		putchar(' ');
		printOut(S);
#endif
	}
	static inline int set(int S, int bit)
	{
		return S | (1 << bit);
	}
	static inline int reset(int S, int bit)
	{
		return S & ~(1 << bit);
	}
	static inline int flip(int S, int bit)
	{
		return S ^ (1 << bit);
	}

	int ans;
	int f[1 << 10];
	bool check(int S)
	{
		int& ans = f[S];
		if (~ans) return ans;
		ans = false;
		for (int i = n - 1; ~i; i--) if (S & (1 << i))
			for (int j = i - 1; ~j && j + j - i >= 0; j--)
			{
				int t = S;
				t = flip(t, i);
				t = flip(t, j);
				t = flip(t, j + j - i);
				if (!check(t))
					return (ans = true);
			}
		return ans;
	}
	void search(int depth)
	{
		static int S;
		if (depth == n)
		{
			ans += check(S);
			return;
		}
		if (str[depth] == '0' || str[depth] == '?')
		{
			S = reset(S, depth);
			search(depth + 1);
		}
		if (str[depth] == '1' || str[depth] == '?')
		{
			S = set(S, depth);
			search(depth + 1);
		}
	}

	brute1() : ans()
	{
		std::memset(f, -1, sizeof(f));
#ifdef LOCAL
		int U = 1 << n;
		for (int S = 0; S < U; S++)
			if (check(S))
				DebugPrint(S);
#endif
		search(0);
		printOut(ans);
	}
};
struct brute2
{
	static const int maxN = 505;
	int SG[maxN];
	int temp[maxN];
	int f[maxN][100];
	brute2() : f()
	{
		SG[0] = 0;
		for (int i = 1; i < n; i++)
		{
			temp[0] = 0;
			for (int j = i - 1; j + j - i >= 0; j--)
				temp[++temp[0]] = SG[j] ^ SG[j + j - i];
			std::sort(temp + 1, temp + 1 + temp[0]);
			temp[0] = std::unique(temp + 1, temp + 1 + temp[0]) - (temp + 1);

			int& ans = SG[i];
			for (ans = 0; ans + 1 <= temp[0]; ans++)
				if (temp[ans + 1] != ans)
					break;
			if (ans)
				ans = temp[ans] + 1;
		}

		f[0][0] = 1 + (str[0] == '?');
		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if (str[i] == '0')
					f[i][j] = f[i - 1][j];
				else if (str[i] == '1')
					f[i][j] = f[i - 1][j ^ SG[i]];
				else if (str[i] == '?')
					f[i][j] = (f[i - 1][j] + f[i - 1][j ^ SG[i]]) % mod;
			}
		}
		int ans = 0;
		for (int i = 1; i < 32; i++)
			ans = (ans + f[n - 1][i]) % mod;
		printOut(ans);
	}
};
const int table[] = { 1, 2, 4, 7, 8, 11, 13, 14, 16, 19, 21 };
struct work
{
	int SG[maxn];
	int f[maxn][100];

	work() : f()
	{
		SG[0] = 0;
		for (int r = 1, cnt = 0; r <= n; r *= 3, cnt++)
		{
			for (int i = r; i < std::min(n, r + r); i++)
				SG[i] = SG[i - r];
			for (int i = r + r; i < std::min(n, r * 3); i++)
				SG[i] = SG[i - r] ? SG[i - r] : table[cnt];
		}

		f[0][0] = 1 + (str[0] == '?');
		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if (str[i] == '0')
					f[i][j] = f[i - 1][j];
				else if (str[i] == '1')
					f[i][j] = f[i - 1][j ^ SG[i]];
				else if (str[i] == '?')
					f[i][j] = (f[i - 1][j] + f[i - 1][j ^ SG[i]]) % mod;
			}
		}
		int ans = 0;
		for (int i = 1; i < 32; i++)
			ans = (ans + f[n - 1][i]) % mod;
		printOut(ans);
	}
};

void run()
{
	std::cin.getline(str, maxn);
	n = strlen(str);

	if (n <= 10)
		RunInstance(brute1);
	else if (n <= 500)
		RunInstance(brute2);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("coin.in", "r", stdin);
	freopen("coin.out", "w", stdout);
#endif
	run();
	return 0;
}