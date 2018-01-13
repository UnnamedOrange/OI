#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
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
#include <cassert>
typedef long long INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9')))
		ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus)
		a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

const INT mod = 1000000007;
const INT maxn = 1000005;
INT n;
INT c[maxn], d[maxn];

INT power(INT x, INT y = mod - 2)
{
	INT ret = 1;
	while (y)
	{
		if (y & 1)
			ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}

#define RunInstance(x) delete new x
struct brute
{
	static const INT maxN = 2005;
	INT f[maxN];
	INT w[maxN];
	INT rf[maxN];
	INT rw[maxN];

	brute()
	{
		memset(f, -1, sizeof(f));
		memset(rf, -1, sizeof(rf));
		memset(w, 0, sizeof(w));
		memset(rw, 0, sizeof(rw));
		f[0] = 0;
		w[0] = 1;
		rf[n + 1] = 0;
		rw[n + 1] = 1;
		for (int i = 1; i <= n; i++)
		{
			INT minVal = c[i];
			INT maxVal = d[i];
			for (int j = i, k = 1; j >= 1; j--, k++)
			{
				if (f[j - 1] == -1)
					continue;
				minVal = std::max(minVal, c[j]);
				maxVal = std::min(maxVal, d[j]);
				if (k > maxVal)
					break;
				else if (k < minVal)
					continue;
				if (f[j - 1] + 1 > f[i])
				{
					f[i] = f[j - 1] + 1;
					w[i] = w[j - 1];
				}
				else if (f[j - 1] + 1 == f[i])
				{
					w[i] = (w[i] + w[j - 1]) % mod;
				}
			}
		}
		for (int i = n; i >= 1; i--)
		{
			INT minVal = c[i];
			INT maxVal = d[i];
			for (int j = i, k = 1; j <= n; j++, k++)
			{
				if (rf[j + 1] == -1)
					continue;
				minVal = std::max(minVal, c[j]);
				maxVal = std::min(maxVal, d[j]);
				if (k > maxVal)
					break;
				else if (k < minVal)
					continue;
				if (rf[j + 1] + 1 > rf[i])
				{
					rf[i] = rf[j + 1] + 1;
					rw[i] = rw[j + 1];
				}
				else if (rf[j + 1] + 1 == rf[i])
				{
					rw[i] = (rw[i] + rw[j + 1]) % mod;
				}
			}
		}
		// assert(f[n] == rf[1]);

		if (f[n] == -1)
		{
			printOut(-1);
			return;
		}
		printOut(f[n]);
		putchar(' ');
		INT ans = 0;
		for (int i = 0; i <= n; i++)
		{
			if (f[i] + rf[i + 1] == f[n])
				ans = (ans + w[i] * rw[i + 1] % mod) % mod;
		}
		ans = ans * power(f[n] + 1) % mod;
		printOut(ans);
		putchar('\n');
	}
};
struct work
{
	// INT f[maxn];
	// INT w[maxn];
	// INT rf[maxn];
	// INT rw[maxn];

	// INT next[maxn];

	work()
	{
		// memset(f, -1, sizeof(f));
		// memset(rf, -1, sizeof(rf));
		// memset(w, 0, sizeof(w));
		// memset(rw, 0, sizeof(rw));
		// f[0] = 0;
		// w[0] = 1;
		// rf[n + 1] = 0;
		// rw[n + 1] = 1;

		// memset(next, -1, sizeof(next));
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		c[i] = readIn();
		d[i] = readIn();
	}

	if (n <= 2000)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("schooldays.in", "r", stdin);
	freopen("schooldays.out", "w", stdout);
#endif
	run();
	return 0;
}
