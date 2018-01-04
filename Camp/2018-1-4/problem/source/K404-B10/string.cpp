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

const INT mod = 998244353;
const INT maxn = 10;
const INT maxm = 505;
INT n, m;
char str[maxn][105];

#define RunInstance(x) delete new x
struct brute
{
	static INT reverse(INT x)
	{
		INT ret = 0;
		for (int i = 0, j = m - 1; i < m; i++, j--)
			ret |= (x & (1 << i) ? 0 : (1 << j));
		return ret;
	}
	brute()
	{
		INT U = 1 << m;
		INT num[maxn] = { 0 };
		INT mask[maxn] = { 0 };
		INT length[maxn] = { 0 };
		for (int i = 1; i <= n; i++)
		{
			length[i] = strlen(str[i]);
			for (int j = 0; j < length[i]; j++)
			{
				num[i] <<= 1;
				num[i] |= (str[i][j] == '1');
				mask[i] <<= 1;
				mask[i] |= 1;
			}
		}
		INT ans = 0;
		for (int i = 0; i < U; i++)
		{
			bool bOk = true;
			INT s = (reverse(i) << m) | i;
			for (int j = 1; j <= n; j++)
			{
				bool flag = false;
				for (int k = 0; k <= m * 2 - length[j]; k++)
				{
					if (!((s ^ (num[j] << k)) & (mask[j] << k)))
					{
						flag = true;
						break;
					}
				}
				if (!flag)
				{
					bOk = false;
					break;
				}
			}
			if (bOk)
				ans++;
		}
		printOut(ans);
	}
};
struct cheat
{
	static INT power(INT x, INT y)
	{
		INT ret = 1;
		while (y)
		{
			if (y & 1) ret = ret * x % mod;
			x = x * x % mod;
			y >>= 1;
		}
		return ret;
	}

	cheat()
	{
		INT ans = 0;
		INT length = strlen(str[1]);
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
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		scanf("%s", str[i]);

	if (m <= 15)
		RunInstance(brute);
	else if (n == 1)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
#endif
	run();
	return 0;
}