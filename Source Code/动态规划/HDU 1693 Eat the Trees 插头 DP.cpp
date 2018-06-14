#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <functional>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef LL INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = 12;
int n, m;
int rect[maxn + 1][maxn + 1];
LL f[maxn][maxn][1 << maxn];

void run()
{
	int T = readIn();
	for (int o = 1; o <= T; o++)
	{
		n = readIn();
		m = readIn();
		memset(rect, 0, sizeof(rect));
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				rect[i][j] = readIn();

		memset(f, 0, sizeof(f));
		f[1][0][0] = 1;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (rect[i][j])
				{
					for (int S = 0, to = 1 << (m + 1); S < to; S++)
					{
						if ((S & (1 << (j - 1))) && (S & (1 << j)))
						{
							f[i][j][S ^ (1 << (j - 1)) ^ (1 << j)] +=
								f[i][j - 1][S];
						}
						else if (!(S & (1 << (j - 1))) && (S & (1 << j)))
						{
							if (rect[i][j + 1])
								f[i][j][S] += f[i][j - 1][S];
							if (rect[i + 1][j])
								f[i][j][S ^ (1 << (j - 1)) ^ (1 << j)] +=
								f[i][j - 1][S];
						}
						else if ((S & (1 << (j - 1))) && !(S & (1 << j)))
						{
							if (rect[i + 1][j])
								f[i][j][S] += f[i][j - 1][S];
							if (rect[i][j + 1])
								f[i][j][S ^ (1 << (j - 1)) ^ (1 << j)] +=
								f[i][j - 1][S];
						}
						else if (!(S & (1 << (j - 1))) && !(S & (1 << j)))
						{
							if (rect[i][j + 1] && rect[i + 1][j])
								f[i][j][S ^ (1 << (j - 1)) ^ (1 << j)] +=
								f[i][j - 1][S];
						}
					}
				}
				else
				{
					for (int S = 0, to = 1 << (m + 1); S < to; S++)
					{
						f[i][j][S] = (!(S & (1 << (j - 1)))
							&& !(S & (1 << j))) ? f[i][j - 1][S] : 0;
					}
				}
			}

			if (i != n)
				for (int S = 0; S < (1 << m); S++)
					f[i + 1][0][S << 1] = f[i][m][S];
		}
		printf("Case %d: There are %lld ways to eat the trees.\n", o, f[n][m][0]);
	}
}

int main()
{
	run();
	return 0;
}