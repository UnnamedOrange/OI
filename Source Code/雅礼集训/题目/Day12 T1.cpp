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
typedef int INT;
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

const INT maxn = INT(1e6) + 5;
INT n;
INT w[maxn];

#define RunInstance(x) delete new x
struct work
{
	INT idx[maxn];
	static inline bool comp(const INT &a, const INT &b)
	{
		return w[a] < w[b];
	}
	INT left[maxn];
	INT right[maxn];

	work() : left(), right()
	{
		for (int i = 1; i <= n; i++)
			idx[i] = i;
		std::sort(idx + 1, idx + 1 + n, comp);

		for (int i = 1; i < n; i++)
		{
			right[i] = i + 1;
			left[i + 1] = i;
		}

		const INT T = 35;
		double ans = 0;
		for (int i = 1; i <= n; i++)
		{
			INT l = idx[i];
			double lCont = 0;
			double power2 = 0.5;
			for (int j = 1; l && j <= T; j++, power2 /= 2, l = left[l])
			{
				INT nxt = left[l];
				lCont += (l - nxt) * power2;
			}

			INT r = idx[i];
			double rCont = 0;
			power2 = 0.5;
			for (int j = 1; r && j <= T; j++, power2 /= 2, r = right[r])
			{
				INT nxt = right[r];
				if (!nxt)
					nxt = n + 1;
				rCont += (nxt - r) * power2;
			}

			ans += 2 * w[idx[i]] * lCont * rCont;
			if (INT &t = right[left[idx[i]]])
				t = right[idx[i]];
			if (INT &t = left[right[idx[i]]])
				t = left[idx[i]];
		}
		printf("%.5f", ans / n / n);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		w[i] = readIn();

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("drink.in", "r", stdin);
	freopen("drink.out", "w", stdout);
#endif
	run();
	return 0;
}