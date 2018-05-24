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
	putchar('\n');
}

const int mod = int(1e9) + 7;
const int maxn = int(1e6) + 5;
int n;
char str[maxn];

int f[maxn];
int g[maxn];
void solve()
{
	f[0] = f[1] = 0;
	g[0] = -1;
	g[1] = 0;
	int pre = 0, t = 0;
	LL ans = 1;
	for (int i = 1; i < n; i++)
	{
		while (pre && str[pre] != str[i]) pre = f[pre];
		if (str[pre] == str[i]) pre++;
		while (t && str[t] != str[i]) t = f[t];
		if (str[t] == str[i]) t++;
		while ((t << 1) > i + 1) t = f[t]; // note

		f[i + 1] = pre;
		g[i + 1] = g[pre] + 1;
		ans = ans * (g[t] + 1 + 1) % mod;
	}
	printOut(ans);
}

void run()
{
	int T = readIn();
	while (T--)
	{
		scanf("%s", str);
		n = strlen(str);
		solve();
	}
}

int main()
{
	run();
	return 0;
}