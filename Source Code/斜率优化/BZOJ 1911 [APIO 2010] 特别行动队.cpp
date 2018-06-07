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

const LL INF = (~(LL(1) << (sizeof(LL) * 8 - 1))) >> 1;
const int maxn = int(1e6) + 5;
int n;

LL a, b, c;
LL x[maxn];
LL f[maxn];
inline LL DP(int i, int j)
{
	register LL X = x[i] - x[j];
	return f[j] + a * X * X + b * X + c;
}

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		f[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			LL& ans = f[i];
			ans = -INF;
			for (int j = 0; j < i; j++)
				ans = std::max(ans, DP(i, j));
		}
		printOut(f[n]);
	}
};
struct work
{
	inline static double slope(int j, int k)
	{
		return (double)((f[j] - f[k]) + a * (x[j] * x[j] - x[k] * x[k]) -
			b * (x[j] - x[k])) / (x[j] - x[k]);
	}
	int deque[maxn];
	int head, tail;

	work()
	{
		head = tail = 0;
		f[0] = 0;
		deque[tail++] = 0;
		for (int i = 1; i <= n; i++)
		{
			while (tail - head > 1 && slope(deque[head + 1], deque[head]) > 2 * a * x[i])
				head++;
			f[i] = DP(i, deque[head]);
			while (tail - head > 1 && slope(i, deque[tail - 1]) > slope(deque[tail - 1], deque[tail - 2]))
				tail--;
			deque[tail++] = i;
		}
		printOut(f[n]);
	}
};

void run()
{
	n = readIn();
	a = readIn();
	b = readIn();
	c = readIn();
	for (int i = 1; i <= n; i++)
		x[i] = x[i - 1] + readIn();

	RunInstance(work);
}

int main()
{
	run();
	return 0;
}