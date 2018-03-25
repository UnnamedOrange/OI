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

const int maxn = int(1e6) + 5;
int n;
char str[maxn];

int f[maxn];
void initFailure()
{
	f[0] = f[1] = 0;
	for (int i = 1; i < n; i++)
	{
		int pre = f[i];
		while (pre && str[i] != str[pre]) pre = f[pre];
		if (str[i] == str[pre]) pre++;
		f[i + 1] = pre;
	}
}

void run()
{
	scanf("%s", str);
	n = strlen(str);
	initFailure();
	int t = f[n];
	while (t)
	{
		if (!(n % (n - t)))
		{
			printOut(n / (n - t));
			return;
		}
		t = f[t];
	}
	printOut(1);
}

int main()
{
#ifndef LOCAL
	freopen("prob7.in", "r", stdin);
	freopen("prob7.out", "w", stdout);
#endif
	run();
	return 0;
}