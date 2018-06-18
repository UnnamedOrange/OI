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
using INT_PUT = LL;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-'))
		ch = getchar();
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
}

const int maxn = int(2.5e5) + 5;
int n;
int a[maxn], b[maxn];

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		int U = 1 << n;
		LL ans = 0;
		for (int S = 0; S < U; S++)
		{
			int t[10];
			for (int i = 0; i < n; i++)
				if (S & (1 << i))
					t[i] = a[i + 1];
				else
					t[i] = b[i + 1];
			std::sort(t, t + n);
			if (std::unique(t, t + n) != t + n)
				continue;
			LL sum = 0;
			for (int i = 0; i < n; i++)
				if (S & (1 << i))
					sum += b[i + 1];
				else
					sum += a[i + 1];
			ans = std::max(ans, sum);
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		a[i] = readIn();
		b[i] = readIn();
	}

	if (n <= 8)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("building.in", "r", stdin);
	freopen("building.out", "w", stdout);
#endif
	run();
	return 0;
}