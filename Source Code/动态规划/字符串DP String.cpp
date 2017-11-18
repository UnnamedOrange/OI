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

const INT maxn = 1005;
INT n, m, K;
char s[maxn];
char t[maxn];

INT f[maxn][maxn][11];
INT g[maxn][maxn][11];
void DP()
{
	INT ans = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			for (int k = 1; k <= K; k++)
			{
				g[i][j][k] = std::max(g[i - 1][j][k], g[i][j - 1][k]);
				if (s[i] == t[j])
				{
					f[i][j][k] = std::max(g[i - 1][j - 1][k - 1] + 1,
						f[i - 1][j - 1][k] + 1);
				}
				g[i][j][k] = std::max(g[i][j][k], f[i][j][k]);
				if (k == K) ans = std::max(ans, f[i][j][k]);
			}
		}
	}

	cout << ans << endl;
}

void run()
{
	n = readIn();
	m = readIn();
	K = readIn();
	scanf("%s", s + 1);
	scanf("%s", t + 1);

	DP();
}

int main()
{
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
	run();
	return 0;
}