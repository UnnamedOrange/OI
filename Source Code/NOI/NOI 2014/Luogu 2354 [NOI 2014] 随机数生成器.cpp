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
#define loop register int
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

const int maxn = int(5e3) + 5;
LL x, a, b, c, d;
int n, m, q;

int rect[maxn * maxn];

void exchange()
{
	for (loop i = 1, to = n * m; i <= to; i++)
	{
		x = (a * x % d * x + b * x + c) % d;
		std::swap(rect[i - 1], rect[x % i]);
	}
	while (q--)
	{
		std::swap(rect[readIn() - 1], rect[readIn() - 1]);
	}
}

int pos[maxn * maxn];
int minRange[maxn];
int maxRange[maxn];

void solve()
{
	for (loop i = 0, to = n * m; i < to; i++)
		pos[rect[i]] = i;
	std::vector<int> ans;
	ans.reserve(n + m - 1);

	for (loop i = 0; i < n; i++)
	{
		minRange[i] = 0;
		maxRange[i] = m - 1;
	}
	for (loop i = 1, to = n * m; i <= to; i++)
	{
		int r = pos[i] / m;
		int c = pos[i] % m;
		if (!(minRange[r] <= c && c <= maxRange[r]))
			continue;
		ans.push_back(rect[pos[i]]);
		for (int j = 0; j < r; j++)
			maxRange[j] = std::min(maxRange[j], c);
		for (int j = r + 1; j < n; j++)
			minRange[j] = std::max(minRange[j], c);
	}
	for (loop i = 0; i < ans.size(); i++)
	{
		printOut(ans[i]);
		putchar(' ');
	}
}

void run()
{
	x = readIn();
	a = readIn();
	b = readIn();
	c = readIn();
	d = readIn();
	n = readIn();
	m = readIn();
	q = readIn();
	for (loop i = 1, to = n * m; i <= to; i++)
		rect[i - 1] = i;
	exchange();

	solve();
}

int main()
{
	run();
	return 0;
}