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
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = int;
INT_PUT readIn()
{
	register INT_PUT a = 0;
	register bool positive = true;
	register char ch = getchar();
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
	register int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int INF = (~(int(1) << (sizeof(int) * 8 - 1))) >> 1;
const int maxn = int(1e6 + 5);
int n;

#define RunInstance(x, ...) delete new x(__VA_ARGS__)
struct brute
{
	static const int maxN = 25;
	int h[maxN];
	int f[maxN];
	int ans;
	int buffer[maxN];

	brute()
	{
		int U = 1 << n;
		ans = 0;
		for (int S = 0; S < U; S++)
		{
			h[n] = 0;
			for (int i = 0; i < n; i++)
			{
				h[n - i - 1] = h[n - i] + bool(S & (1 << i));
			}

			for (int i = 0; i < n; i++)
			{
				int& t = f[i];
				t = i + 1;
				for (int j = i + 2; j <= n; j++)
				{
					if ((h[j] - h[i]) * (t - i) >=
						(h[t] - h[i]) * (j - i))
					{
						t = j;
					}
				}
			}
			f[n] = n;

			int temp = 0;
			int max = 0;
			for (int i = 0; i <= n; i++)
			{
				if (f[i] > max)
				{
					temp++;
					max = f[i];
				}
			}

			if (temp > ans)
			{
				ans = temp;
				std::memcpy(buffer, h, sizeof(buffer));
			}
		}
		printOut(ans);
		putchar('\n');
		for (int i = 0; i <= n; i++)
		{
			printOut(buffer[i]);
			putchar(' ');
		}
		putchar('\n');
	}
};
struct work
{
	static int gcd(register int a, register int b)
	{
		return b ? gcd(b, a % b) : a;
	}
	struct Frac
	{
		int up, down;
		Frac() {}
		Frac(int up, int down) : up(up), down(down) {}
		bool operator<(const Frac& b) const
		{
			return (LL)up * b.down < (LL)b.up * down;
		}
	};
	std::vector<Frac> fracs;

	int h[maxn];

	work()
	{
		h[0] = 0;
		int accum = 0;
		for (int i = 1; i <= n && accum + i <= n; i++)
		{
			for (int j = 1; j <= i && accum + i <= n; j++)
			{
				if (gcd(i, j) == 1)
				{
					accum += i;
					h[0] += j;
					fracs.push_back(Frac(j, i));
				}
			}
		}

		printOut(fracs.size() + (accum != n));
		putchar('\n');

		std::sort(fracs.begin(), fracs.end());
		for (int i = 1, to = n - accum; i <= to; i++)
			h[i] = h[0];
		int cnt = n - accum + 1;
		for (int i = 0; i < fracs.size(); i++)
		{
			for (int j = 0; j < fracs[i].up; j++, cnt++)
			{
				h[cnt] = h[cnt - 1] - 1;
			}
			for (int j = 0, to = fracs[i].down - fracs[i].up;
				j < to; j++, cnt++)
			{
				h[cnt] = h[cnt - 1];
			}
		}

		for (int i = 0; i <= n; i++)
		{
			printOut(h[i]);
			putchar(' ');
		}
		putchar('\n');
	}
};

void run()
{
	n = readIn();

	if (n <= 20)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("geometry.in", "r", stdin);
	freopen("geometry.out", "w", stdout);
#endif
	run();
	return 0;
}