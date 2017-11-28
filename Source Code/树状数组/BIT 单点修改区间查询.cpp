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
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[12];
		INT length = 0;
		bool minus = x < 0;
		if (minus) x = -x;
		while (x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		if (minus) buffer[length++] = '-';
		do
		{
			putchar(buffer[--length]);
		} while (length);
	}
	putchar('\n');
}

const INT maxn = 500005;
INT n, m;
struct BIT
{
#define lowbit(x) ((x) & -(x))
	INT bit[maxn];
	BIT() : bit() {}

	void add(INT x, INT val)
	{
		while (x <= n)
		{
			bit[x] += val;
			x += lowbit(x);
		}
	}
	INT query(INT x)
	{
		INT ret = 0;
		while (x > 0)
		{
			ret += bit[x];
			x -= lowbit(x);
		}
		return ret;
	}
	INT query(INT l, INT r)
	{
		return query(r) - query(l - 1);
	}
} bit;

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++) bit.add(i, readIn());
	while (m--)
	{
		INT ins = readIn();
		if (ins == 1)
		{
			INT x = readIn();
			INT val = readIn();
			bit.add(x, val);
		}
		else
		{
			INT x = readIn();
			INT y = readIn();
			printOut(bit.query(x, y));
		}
	}
}

int main()
{
	run();
	return 0;
}
