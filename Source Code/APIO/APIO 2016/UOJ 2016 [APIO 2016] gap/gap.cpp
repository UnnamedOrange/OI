#include "gap.h"
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

const int maxn = int(1e5) + 5;
int n;
long long a[maxn];

LL solve1()
{
	LL min = 0, max = LL(1e18);
	int cntL = 1, cntR = n;
	while (cntL <= cntR)
	{
		MinMax(min, max, a + cntL, a + cntR);
		min = a[cntL] + 1;
		max = a[cntR] - 1;
		cntL++;
		cntR--;
	}
	LL ans = 0;
	for (int i = 2; i <= n; i++)
		ans = std::max(ans, a[i] - a[i - 1]);
	return ans;
}

LL minVal[maxn], maxVal[maxn];

LL solve2()
{
	LL min = 0, max = LL(1e18);
	MinMax(min, max, &min, &max);
	if (n == 2) return max - min;
	LL step = (max - min - 1) / (n - 2);
	LL cnt = min + 1;
	for (int i = 1; i < n - 2; i++)
	{
		MinMax(cnt, cnt + step - 1, &minVal[i], &maxVal[i]);
		cnt += step;
	}
	MinMax(cnt, max - 1, &minVal[n - 2], &maxVal[n - 2]);

	LL ans = 0;
	cnt = min;
	for (int i = 1; i <= n - 2; i++)
	{
		if (minVal[i] == -1) continue;
		ans = std::max(ans, minVal[i] - cnt);
		cnt = maxVal[i];
	}
	ans = std::max(ans, max - cnt);
	return ans;
}

LL findGap(int type, int N)
{
	n = N;
	if (type == 1) return solve1();
	else return solve2();
}