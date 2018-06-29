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
}

const int mod = 998244353;
const int maxn = 4005;
int n, k;
std::vector<std::pair<int, int> > edges;

#define RunInstance(x) delete new x
struct cheat
{
	int f[maxn];
	cheat() : f()
	{
		f[0] = 1;
		for (int i = 1; i <= (n >> 1); i++)
			for (int j = 0; j < i; j++)
				f[i] = (f[i] + (LL)f[j] * f[i - 1 - j]) % mod;
		printOut(f[n >> 1]);
	}
};

void run()
{
	n = readIn();
	k = readIn();
	for (int i = 1; i <= k; i++)
	{
		int from = readIn();
		int to = readIn();
		edges.push_back(std::make_pair(from, to));
	}

	if (!k)
		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("line.in", "r", stdin);
	freopen("line.out", "w", stdout);
#endif
	run();
	return 0;
}