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

const INT maxn = 10;
INT n, m, k;
INT rect[maxn][maxn];

const INT vecx[] = { 1, -1, 0, 0 };
const INT vecy[] = { 0, 0, 1, -1 };
INT INF;
INT U;
typedef std::pair<INT, INT> Point;
INT f[maxn][maxn][1 << maxn];
INT pre[maxn][maxn][1 << maxn][3];
void SPFA(INT S)
{
	bool inQ[maxn][maxn] = { false };
	std::queue<Point> q;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (f[i][j][S] < INF)
			{
				q.push(Point(i, j));
				inQ[i][j] = true;
			}
		}
	}
	while (!q.empty())
	{
		Point from = q.front();
		q.pop();
		inQ[from.first][from.second] = false;
		for (int i = 0; i < 4; i++)
		{
			INT newx = from.first + vecx[i];
			INT newy = from.second + vecy[i];
			if (!(newx >= 0 && newx < n && newy >= 0 && newy < m))
				continue;
			if (f[newx][newy][S] > f[from.first][from.second][S] + rect[newx][newy])
			{
				f[newx][newy][S] = f[from.first][from.second][S] + rect[newx][newy];
				pre[newx][newy][S][0] = from.first;
				pre[newx][newy][S][1] = from.second;
				pre[newx][newy][S][2] = S;
				if (!inQ[newx][newy])
				{
					q.push(std::make_pair(newx, newy));
					inQ[newx][newy] = true;
				}
			}
		}
	}
}
void SteinerTree()
{
	memset(f, 0x3f, sizeof(f));
	memset(&INF, 0x3f, sizeof(INF));
	Point s[maxn];
	k = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (!rect[i][j])
			{
				s[k].first = i;
				s[k].second = j;
				k++;
			}

	U = 1 << k;
	for (int i = 0; i < k; i++)
		f[s[i].first][s[i].second][1 << i] = 0;

	for (int S = 0; S < U; S++)
	{
		for (int x = 0; x < n; x++)
		{
			for (int y = 0; y < m; y++)
			{
				for (int S0 = (S - 1) & S; S0; S0 = (S0 - 1) & S)
				{
					int S1 = S ^ S0;
					if (f[x][y][S0] + f[x][y][S1] - rect[x][y] < f[x][y][S])
					{
						f[x][y][S] = f[x][y][S0] + f[x][y][S1] - rect[x][y];
						pre[x][y][S][0] = x;
						pre[x][y][S][1] = y;
						pre[x][y][S][2] = S0;
					}
				}
			}
		}
		SPFA(S);
	}
}
INT vis[maxn][maxn];
void Track(INT x, INT y, INT S)
{
	if (!pre[x][y][S][2])
		return;
	vis[x][y] = true;
	Track(pre[x][y][S][0], pre[x][y][S][1], pre[x][y][S][2]);
	if (pre[x][y][S][0] == x && pre[x][y][S][1] == y)
		Track(pre[x][y][S][0], pre[x][y][S][1], S ^ pre[x][y][S][2]);
}
void run()
{
	n = readIn();
	m = readIn();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			rect[i][j] = readIn();

	SteinerTree();

	INT ans = INF;
	INT ansX;
	INT ansY;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (f[i][j][U - 1] < ans)
			{
				ans = f[i][j][U - 1];
				ansX = i;
				ansY = j;
			}
		}
	Track(ansX, ansY, U - 1);
	printOut(ans);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (!rect[i][j])
				putchar('x');
			else if (vis[i][j])
				putchar('o');
			else
				putchar('_');
		}
		putchar('\n');
	}
}

int main()
{
	run();
	return 0;
}