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
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = int;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

int n, m, mod;

#define RunInstance(x) delete new x
struct cheat1
{
	int f[10005][2];

	cheat1()
	{
		f[1][0] = 1;
		f[1][1] = 2 % mod;
		for (int i = 2; i <= m; i++)
		{
			f[i][0] = (f[i - 1][0] + f[i - 1][1]) % mod;
			f[i][1] = (f[i - 1][0] << 1) % mod;
		}
		printOut((f[m][0] + f[m][1]) % mod);
	}
};
struct brute
{
	static const int maxn = 25;
	int rect[maxn][maxn];
	bool vis[maxn][maxn];
	int ans{};
	void DFS(int x, int y)
	{
		vis[x][y] = true;
		const int vecx[] = { 1, -1, 0, 0 };
		const int vecy[] = { 0, 0, 1, -1 };
		for (int i = 0; i < 4; i++)
		{
			int newx = x + vecx[i];
			int newy = y + vecy[i];
			if (1 <= newx && newx <= n && 1 <= newy && newy <= m &&
				rect[newx][newy] && !vis[newx][newy])
				DFS(newx, newy);
		}
	}
	bool check()
	{
		memset(vis, 0, sizeof(vis));
		bool started = false;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (rect[i][j] && !vis[i][j])
				{
					if (started)
						return false;
					else
					{
						started = true;
						DFS(i, j);
					}
				}
			}
		}
		return true;
	}

	int f[1 << 10]{};

	void search(int x, int y)
	{
		if (y == m + 1)
		{
			bool t = check();
			ans = (ans + t) % mod;
			int S = 0;
			for (int i = 1; i <= n; i++)
				S |= (rect[i][m] << (i - 1));
			f[S] = (f[S] + t) % mod;
			return;
		}
		int newx = x + 1;
		int newy = y;
		if (newx > n)
		{
			newx = 1;
			newy++;
		}
		rect[x][y] = 1;
		search(newx, newy);
		if ((x == 1 || rect[x - 1][y]) && (y == 1 || rect[x][y - 1]))
		{
			rect[x][y] = 0;
			search(newx, newy);
		}
	}

	brute()
	{
		search(1, 1);
		printOut(ans);
		putchar('\n');
		for (int i = 0; i < (1 << n); i++)
		{
			printOut(f[i]);
			putchar(' ');
		}
		putchar('\n');
	}
};

void run()
{
	n = readIn();
	m = readIn();
	mod = readIn();

	if (n == 2)
		RunInstance(cheat1);
}

int main()
{
#ifndef LOCAL
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
#endif
	run();
	return 0;
}