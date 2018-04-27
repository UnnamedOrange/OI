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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
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
inline void printOut(INT x)
{
	char buffer[15];
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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = 305;
INT n, s;
INT rect[maxn][maxn];

void run()
{
	n = readIn();
	s = readIn();
	memset(rect, 0x3f, sizeof(rect));
	for (int i = 1; i <= n; i++) rect[i][i] = 0;
	for (int i = 1; i < n; i++)
	{
		INT u = readIn();
		INT v = readIn();
		INT c = readIn();
		rect[u][v] = rect[v][u] = c;
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (i != j && j != k && k != i)
					rect[i][j] = std::min(rect[i][j], rect[i][k] + rect[k][j]);

	INT maxLen = 0;
	INT u, v;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
		{
			if (rect[i][j] > maxLen)
			{
				u = i;
				v = j;
				maxLen = rect[i][j];
			}
		}

	INT ans = INF;
	for (int i = 1; i <= n; i++)
		if (rect[u][i] + rect[i][v] == maxLen)
			for (int j = i; j <= n; j++)
				if (rect[i][j] <= s && rect[u][j] + rect[j][v] == maxLen)
				{
					if (i != u || j != v)
						ans = std::min(ans, std::max(std::min(rect[u][i], rect[u][j]), std::min(rect[v][i], rect[v][j])));
					else
					{
						INT ecc = 0;
						for (int a = 1; a <= n; a++)
						{
							INT temp = INF;
							if (rect[u][a] + rect[a][v] == maxLen) continue;
							for (int b = 1; b <= n; b++)
								if (rect[u][b] + rect[b][v] == maxLen)
									temp = std::min(temp, rect[a][b]);
							ecc = std::max(ecc, temp);
						}
						ans = std::min(ans, ecc);
					}
				}
	printOut(ans);
}

int main()
{
	run();
	return 0;
}
