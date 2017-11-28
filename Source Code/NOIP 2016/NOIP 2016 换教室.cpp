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
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1))) >> 1;
const INT maxn = 2005;
const INT maxv = 305;
INT n, m, v, e;
INT c[maxn];
INT d[maxn];
double p[maxn];
INT rect[maxv][maxv];

double f[maxn][maxn];
double g[maxn][maxn];

void run()
{
	n = readIn();
	m = readIn();
	v = readIn();
	e = readIn();

	for (int i = 1; i <= n; i++)
		c[i] = readIn();
	for (int i = 1; i <= n; i++)
		d[i] = readIn();
	for (int i = 1; i <= n; i++)
		scanf("%lf", &p[i]);

	memset(rect, 0x3f, sizeof(rect));
	for (int i = 1; i <= v; i++) rect[i][i] = 0;
	for (int i = 1; i <= e; i++)
	{
		INT u = readIn();
		INT v = readIn();
		INT cost = readIn();
		rect[v][u] = std::min(rect[v][u], cost);
		rect[u][v] = std::min(rect[u][v], cost);
	}
	for (int k = 1; k <= v; k++)
		for (int i = 1; i <= v; i++)
			for (int j = 1; j <= v; j++)
				if(i != j && j != k && k != i)
					rect[i][j] = std::min(rect[i][j], rect[i][k] + rect[k][j]);

	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= m; j++)
			f[i][j] = g[i][j] = 1e100;

	f[1][1] = g[1][0] = 0;
	for (int i = 2; i <= n; i++)
		for (int j = 0; j <= std::min(i, m); j++)
		{
			g[i][j] = g[i - 1][j] + rect[c[i - 1]][c[i]];
			if (j)
				g[i][j] = std::min(g[i][j],
					f[i - 1][j] + (rect[d[i - 1]][c[i]]) * p[i - 1] + rect[c[i - 1]][c[i]] * (1 - p[i - 1]));

			if (j)
			{
				f[i][j] = g[i - 1][j - 1] + rect[c[i - 1]][c[i]] * (1 - p[i]) + rect[c[i - 1]][d[i]] * p[i];
				if (j > 1)
					f[i][j] = std::min(f[i][j],
						f[i - 1][j - 1] + (rect[c[i - 1]][c[i]] * (1 - p[i - 1]) * (1 - p[i]) +
							rect[d[i - 1]][c[i]] * p[i - 1] * (1 - p[i]) +
							rect[c[i - 1]][d[i]] * (1 - p[i - 1]) * p[i] +
							rect[d[i - 1]][d[i]] * p[i - 1] * p[i]));
			}
		}

	double ans = 1e100;
	for (int i = 0; i <= std::min(n, m); i++)
		ans = std::min(ans, std::min(f[n][i], g[n][i]));

	printf("%.2f\n", ans);
}

int main()
{
	run();
	return 0;
}
