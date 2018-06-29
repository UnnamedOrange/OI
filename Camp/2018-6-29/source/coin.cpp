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
struct brute
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

	brute() : ans()
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

void run()
{
	std::cin.getline(str, maxn);
	n = strlen(str);

	if (n <= 10)
		RunInstance(brute);
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