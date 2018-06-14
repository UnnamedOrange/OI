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
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = int;
INT_PUT readIn()
{
	register INT_PUT a = 0;
	register bool positive = true;
	register char ch = getchar();
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
	register int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = int(2e5) + 5;
int n, q;
char str[maxn];
struct Query
{
	int l, r;
	void read()
	{
		l = readIn();
		r = readIn();
	}
} querys[maxn];

#define RunInstance(x) delete new x
struct brute
{
	int idx[maxn];
	int ans[maxn];
	int f[maxn];

	int initFailure(const char* s, int n)
	{
		f[0] = f[1] = 0;
		int pre = 0;
		for (int i = 1; i < n; i++)
		{
			while (pre && s[i] != s[pre]) pre = f[pre];
			if (s[i] == s[pre]) pre++;
			f[i + 1] = pre;
		}
	}

	brute()
	{
		for (int i = 1; i <= q; i++)
			idx[i] = i;
		std::sort(idx + 1, idx + 1 + q,
			[](const int& a, const int& b)
		{
			return querys[a].l < querys[b].l;
		});

		int cnt = 0;
		for (int i = 1; i <= q; i++)
		{
			const Query& Q = querys[idx[i]];
			if (cnt != Q.l)
			{
				initFailure(str + Q.l, n - Q.l + 1);
				cnt = Q.l;
			}
			ans[idx[i]] = f[Q.r - Q.l + 1];
		}

		for (int i = 1; i <= q; i++)
			printOut(ans[i]);
	}
};

void run()
{
	n = readIn();
	q = readIn();
	for (int i = 1; i <= n; i++)
	{
		register char ch = getchar();
		while (!std::isalpha(ch)) ch = getchar();
		str[i] = ch;
	}
	for (int i = 1; i <= q; i++)
		querys[i].read();

	if (n <= 10000)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("str.in", "r", stdin);
	freopen("str.out", "w", stdout);
#endif
	run();
	return 0;
}