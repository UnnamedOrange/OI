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

LL l, r;

#define RunInstance(x) delete new x
struct brute
{
	bool bOk[int(1e6) + 5];

	brute() : bOk()
	{
		for (LL b = 2; b * b <= r; b++)
			for (LL a = 1; a < b && a * b * b <= r; a++)
				for (LL t = b * b; a * t <= r; t *= b)
					bOk[a * t] = true;
		int ans = 0;
		for (int i = l; i <= r; i++)
			ans += bOk[i];
		printOut(ans);
	}
};

void run()
{
	l = readIn();
	r = readIn();

	if (r <= 1000000)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("rinascimento.in", "r", stdin);
	freopen("rinascimento.out", "w", stdout);
#endif
	run();
	return 0;
}