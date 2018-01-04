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
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
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
	if (minus) a = -a;
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

const INT maxn = 30;
INT n;
INT a[maxn];

INT geth()
{
	INT ret = 0;
	for (int i = 2; i <= n; i++)
		ret += std::abs(a[i - 1] - a[i]) != 1;
	return ret;
}
bool search(INT depth, INT h, INT pre, const INT& maxd)
{
	if (depth + h > maxd)
		return false;

	if (!h && a[1] == 1)
		return true;

	for (int i = n; i >= 2; i--)
	{
		if (i == pre)
			continue;
		INT preH = h;

		if (i != n) h -= (std::abs(a[i] - a[i + 1]) != 1);
		std::reverse(a + 1, a + 1 + i);
		if (i != n) h += (std::abs(a[i] - a[i + 1]) != 1);

		if (search(depth + 1, h, i, maxd))
			return true;

		h = preH;
		std::reverse(a + 1, a + 1 + i);
	}
	return false;
}

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		for (int i = 1; i <= n; i++)
			a[i] = readIn();

		INT maxd;
		for (maxd = geth(); ; maxd++)
		{
			if (search(0, geth(), 0, maxd))
				break;
		}
		printOut(maxd);
	}
}

int main()
{
#ifndef LOCAL
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif
	run();
	return 0;
}