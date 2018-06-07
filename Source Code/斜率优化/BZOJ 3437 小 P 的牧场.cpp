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
LL a[maxn], b[maxn], c[maxn];

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = int(1e3) + 5;
	LL f[maxN];

	brute() : f()
	{
		for (int i = 1; i <= n; i++)
		{
			LL& ans = f[i];
			ans = INF;

			for (int j = 0; j < i; j++)
				ans = std::min(ans, f[j] + a[i] +
				(c[i] - c[j]) - (n - i) * (b[i] - b[j]));
		}

		printOut(f[n]);
	}
};
struct work
{
	int deque[maxn];
	int head, tail;
	LL f[maxn];

	inline LL DP(int i, int j)
	{
		return f[j] + a[i] + (c[i] - c[j]) - (n - i) * (b[i] - b[j]);
	}
	inline double slope(int j, int k)
	{
		return (double)((f[j] - f[k]) - (c[j] - c[k])) / (b[j] - b[k]);
	}

	work()
	{
		f[0] = 0;
		head = tail = 0;
		deque[tail++] = 0;
		for (int i = 1; i <= n; i++)
		{
			while (tail - head > 1 && slope(deque[head + 1], deque[head]) < -(n - i))
				head++;
			f[i] = DP(i, deque[head]);
			while (tail - head > 1 && slope(i, deque[tail - 1]) < slope(deque[tail - 1], deque[tail - 2]))
				tail--;
			deque[tail++] = i;
		}
		printOut(f[n]);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 1; i <= n; i++)
		b[i] = readIn();
	for (int i = 1; i <= n; i++)
		c[i] = (n - i) * b[i];
	for (int i = 2; i <= n; i++)
		b[i] += b[i - 1];
	for (int i = 2; i <= n; i++)
		c[i] += c[i - 1];

	RunInstance(work);
}

int main()
{
	run();
	return 0;
}