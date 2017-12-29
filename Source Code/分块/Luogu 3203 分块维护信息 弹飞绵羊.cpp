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
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = 200005;
const INT maxi = 455;
INT n, m;
INT sqrtN;
INT N;
INT a[maxn];
INT step[maxn];
INT next[maxn];

inline INT inB(INT x)
{
	if (x > n)
		return N;
	return (x - 1) / sqrtN;
}

void run()
{
	n = readIn();
	sqrtN = std::sqrt(n);
	N = (n + sqrtN - 1) / sqrtN;

	for (int i = 1; i <= n; i++)
		a[i] = readIn();

	for (int i = n; i >= 1; i--)
	{
		INT inBlock = inB(i);
		INT t;
		if (inB(t = i + a[i]) == inBlock)
		{
			step[i] = step[t] + 1;
			next[i] = next[t];
		}
		else
		{
			step[i] = 1;
			next[i] = t > n ? 0 : t;
		}
	}

	m = readIn();
	while (m--)
	{
		INT ins = readIn();
		if (ins == 1)
		{
			INT x = readIn() + 1;
			INT ans = 0;
			while (x)
			{
				ans += step[x];
				x = next[x];
			}
			printOut(ans);
		}
		else if (ins == 2)
		{
			INT x = readIn() + 1;
			a[x] = readIn();

			INT inBlock = inB(x);
			INT begin = inBlock * sqrtN + 1;
			for (int i = x; i >= begin; i--)
			{
				INT t;
				if (inB(t = i + a[i]) == inBlock)
				{
					step[i] = step[t] + 1;
					next[i] = next[t];
				}
				else
				{
					step[i] = 1;
					next[i] = t > n ? 0 : t;
				}
			}
		}
	}
}

int main()
{
	run();
	return 0;
}