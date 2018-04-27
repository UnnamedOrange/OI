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
typedef int INT;
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

const INT INF = 0x3f3f3f3f;
const INT maxn = 15;
const INT maxm = 1005;
INT n, m;
INT rect[maxn][maxn];
INT f[maxn][1 << 12];
INT count1[1 << 12];

INT minVal[maxn][1 << 12];

void run()
{
	n = readIn();
	m = readIn();
	memset(rect, 0x3f, sizeof(rect));
	for (int i = 1; i <= m; i++)
	{
		INT u = readIn() - 1;
		INT v = readIn() - 1;
		INT c = readIn();
		rect[u][v] = rect[v][u] = std::min(rect[u][v], c);
	}
	memset(f, 0x3f, sizeof(f));

	INT U = 1 << n;
	for (int i = 1; i < U; i++)
		count1[i] = count1[i >> 1] + (i & 1);
	for (int i = 0; i < n; i++)
		f[0][1 << i] = 0;

	memset(minVal, 0x3f, sizeof(minVal));
	for (int S = 1; S < U; S++)
	{
		for (int i = 0; i < n; i++)
		{
			if (S & (1 << i)) continue;
			for (int j = 0; j < n; j++)
			{
				if (!(S & (1 << j))) continue;
				minVal[i][S] = std::min(minVal[i][S], rect[j][i]);
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int S = 1; S < U; S++)
		{
			if (count1[S] == 1) continue;
			for (int S0 = (S - 1) & S; S0; S0 = (S0 - 1) & S)
			{
				INT sum = 0;
				for (int j = 0; j < n; j++)
				{
					if (!((S ^ S0) & (1 << j))) continue;
					INT mv = minVal[j][S0];
					if (mv >= INF)
					{
						sum = -1;
						break;
					}
					sum += mv * (i + 1);
				}
				if (sum == -1) continue;
				f[i + 1][S] = std::min(f[i + 1][S], f[i][S0] + sum);
			}
		}
	}
	INT ans = INF;
	for (int i = 0; i <= n; i++)
		ans = std::min(ans, f[i][U - 1]);
	printOut(ans);
}

int main()
{
#ifndef LOCAL
	freopen("treasure.in", "r", stdin);
	freopen("treasure.out", "w", stdout);
#endif
	run();
	return 0;
}