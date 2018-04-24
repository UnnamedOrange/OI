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

const int maxn = 255;
const int mod = 10007;
int n, m;

int rect[maxn][maxn];
LL power(LL x, int y = mod - 2)
{
	LL ret = 1;
	while (y)
	{
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
int det()
{
	int changed = 1;
	n--;
	for (int i = 0; i < n; i++)
	{
		int maxIdx = i;
		for (int j = i + 1; j < n; j++)
		{
			if (rect[j][i] > rect[maxIdx][i])
				maxIdx = j;
		}
		if (i != maxIdx)
		{
			changed = -changed;
			for (int j = 0; j < n; j++)
				std::swap(rect[i][j], rect[maxIdx][j]);
		}
		if (!rect[i][i])
			return 0;

		int ratio = power(rect[i][i]);
		for (int j = i + 1; j < n; j++)
		{
			int temp = (LL)ratio * rect[j][i] % mod;
			if (rect[j][i])
			{
				for (int k = 0; k < n; k++)
				{
					rect[j][k] = (rect[j][k] - (LL)temp * rect[i][k]) % mod;
					if (rect[j][k] < 0)
						rect[j][k] += mod;
				}
			}
		}
	}
	int ret = 1;
	for (int i = 0; i < n; i++)
		ret = (LL)ret * rect[i][i] % mod;
	ret = (ret * changed + mod) % mod;
	return ret;
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		int to = readIn() - 2;
		int from = readIn() - 2;
		if (to >= 0)
		{
			rect[to][to]++;
			if (from >= 0) rect[from][to]--;
		}
	}

	printOut(det());
}

int main()
{
	run();
	return 0;
}