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
	putchar('\n');
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = 505;
INT n;
INT W;
INT p, q;
const INT maxp = 25;
struct P
{
	INT x, y, z, a, b, c, d, e, f;
	void read()
	{
		x = readIn();
		y = readIn();
		z = readIn();
		a = readIn();
		b = readIn();
		c = readIn();
		d = readIn();
		e = readIn();
		f = readIn();
	}
	INT calc(INT set)
	{
		INT wx = (set & (1 << (x - 1))) ? W : -W;
		INT wy = (set & (1 << (y - 1))) ? W : -W;
		INT wz = (set & (1 << (z - 1))) ? W : -W;
		return a * std::abs(wx - wy) +
			b * std::abs(wy - wz) +
			c * std::abs(wz - wx) +
			d * (wx - wy) + e * (wy - wz) + f * (wz - wx);
	}
} ps[maxp];
struct Q
{
	INT x, y, r;
	void read()
	{
		x = readIn();
		y = readIn();
		r = readIn();
	}
	bool check(INT set)
	{
		INT wx = (set & (1 << (x - 1))) ? W : -W;
		INT wy = (set & (1 << (y - 1))) ? W : -W;
		if (r == 0)
			return wx <= wy;
		else if (r == 1)
			return wx == wy;
		else if (r == 2)
			return wx < wy;
	}
} qs[maxp];

#define RunInstance(x) delete new x
struct brute
{
	static INT sigmaW(INT set)
	{
		INT ret = 0;
		for (int i = 0; i < n; i++)
			ret += ((set & (1 << i)) ? W : -W);
		return ret;
	}
	brute()
	{
		INT ans = INF;
		INT U = 1 << n;
		for (int S = 0; S < U; S++)
		{
			bool bOk = true;
			for (int i = 1; i <= q; i++)
			{
				if (!qs[i].check(S))
				{
					bOk = false;
					break;
				}
			}
			if (!bOk) continue;
			INT sum = sigmaW(S);
			for (int i = 1; i <= p; i++)
				sum += ps[i].calc(S);
			ans = std::min(ans, sum);
		}
		printOut(ans);
	}
};
struct work
{
	work()
	{

	}
};

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		W = readIn();
		p = readIn();
		q = readIn();
		for (int i = 1; i <= p; i++)
			ps[i].read();
		for (int i = 1; i <= q; i++)
			qs[i].read();

		if (n <= 15)
			RunInstance(brute);
		else
			RunInstance(work);
	}
}

int main()
{
#ifndef LOCAL
	freopen("variable.in", "r", stdin);
	freopen("variable.out", "w", stdout);
#endif
	run();
	return 0;
}