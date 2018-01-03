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
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = 55;
const INT maxm = 1005;
const INT U = 1 << 10;

INT count1[U];
INT next[10][U];
INT l, r, k;
INT f[25][U][10];

INT s[25];
INT dp(INT digit, INT S, const INT& v, INT top)
{
	if (!top && f[digit][S][v] != -1)
		return f[digit][S][v];
	INT to = top ? s[digit] : 9;
	INT ret;
	INT& ans = top ? ret : f[digit][S][v];
	ans = 0;
	if (digit == 1)
	{
		for (int i = 0; i <= to; i++)
			ans += count1[next[i][S]] == k;
		return ans;
	}

	for (int i = 0; i <= to; i++)
		ans += dp(digit - 1, next[i][S], v, top && i == to);
	return ans;
}
INT solve(INT x)
{
	s[0] = 0;
	do
	{
		s[++s[0]] = x % 10;
		x /= 10;
	} while (x);
	return dp(s[0], 0, k, true);
}

void run()
{
	for (int i = 1; i < U; i++)
		count1[i] = count1[i >> 1] + bool(i & 1);
	for (int i = 0; i <= 9; i++)
	{
		for (int S = 0; S < U; S++)
		{
			next[i][S] = S;
			for (int j = i; j <= 9; j++)
			{
				if (S & (1 << j))
				{
					next[i][S] ^= 1 << j;
					break;
				}
			}
			next[i][S] |= 1 << i;
		}
	}
	next[0][0] = 0;
	memset(f, -1, sizeof(f));

	INT T = readIn();
	for (int o = 1; o <= T; o++)
	{
		printf("Case #");
		printOut(o);
		printf(": ");
		l = readIn();
		r = readIn();
		k = readIn();
		printOut(solve(r) - solve(l - 1));
		putchar('\n');
	}
}

int main()
{
	run();
	return 0;
}