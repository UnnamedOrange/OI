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
	putchar(' ');
}

const int maxn = int(1e5) + 5;
int T, F;

int mex[maxn];
int SG[maxn];
int DP(int x)
{
	int& ans = SG[x];
	if (~ans) return ans;
	for (register int i = 2, t; i <= x; i = t + 1)
	{
		t = x / (x / i);

		int Div = x / i;
		int Mod = x - Div * i;
		DP(Div);
		if (t != i) DP(Div + 1);
	}
	for (register int i = 2, t; i <= x; i = t + 1)
	{
		t = x / (x / i);

		int Div = x / i;
		int Mod = x - Div * i;
		mex[(((i - Mod) & 1) ? DP(Div) : 0) ^ ((Mod & 1) ? DP(Div + 1) : 0)] = x;

		if (t != i)
		{
			i++;
			Mod -= Div;
			mex[(((i - Mod) & 1) ? DP(Div) : 0) ^ ((Mod & 1) ? DP(Div + 1) : 0)] = x;
		}
	}
	ans = 0;
	while (mex[ans] == x) ans++;
	return ans;
}

void init()
{
	memset(SG, -1, sizeof(SG));
	for (int i = 0; i < F; i++)
		SG[i] = 0;
}

int n;
int a[maxn];
void run()
{
	T = readIn();
	F = readIn();
	init();
	while (T--)
	{
		n = readIn();
		for (int i = 1; i <= n; i++)
			a[i] = readIn();
		int xorsum = 0;
		for (int i = 1; i <= n; i++)
			xorsum ^= DP(a[i]);
		printOut(bool(xorsum));
	}
}

int main()
{
	run();
	return 0;
}