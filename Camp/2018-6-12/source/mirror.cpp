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
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = std::getchar();
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

const int maxn = 10;
int T;
int n, m;
int can[maxn][maxn];

struct Query
{
	int n, m;
	int can[maxn][maxn];
	void read()
	{
		n = readIn();
		m = readIn();
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				char ch = std::getchar();
				while (!std::isdigit(ch))
					ch = getchar();
				can[i][j] = ch == '1';
			}
		}
	}
	void release()
	{
		::n = n;
		::m = m;
		std::memcpy(::can, can, sizeof(::can));
	}
} querys[105];

// 上下左右
const int vecx[] = { -1, 1, 0, 0 };
const int vecy[] = { 0, 0, -1, 1 };
const int func[][4] =
{ { 0, 1, 2, 3 },
{ 3, 2, 1, 0 },
{ 2, 3, 0, 1 } };

#define RunInstance(x) delete new x
struct brute // invalid
{
	int mirror[maxn][maxn]; // 1 - 左斜，2 - 右斜
	int ans[maxn * maxn];

	int go(int x, int y, int dir)
	{
		int ret = 0;
		while (1 <= x && x <= n && 1 <= y && y <= m)
		{
			ret++;
			dir = func[mirror[x][y]][dir];
			x += vecx[dir];
			y += vecy[dir];
		}
		return ret;
	}

	int calc()
	{
		int ret = 0;

		for (int i = 1; i <= m; i++)
			ret += go(n, i, 0); // 从下至上

		for (int i = 1; i <= m; i++)
			ret += go(1, i, 1); // 从上至下

		for (int i = 1; i <= n; i++)
			ret += go(i, m, 2); // 从右至左

		for (int i = 1; i <= n; i++)
			ret += go(i, 1, 3); // 从左至右

		return ret;
	}

	void search(int x, int y, int cnt)
	{
		if (x == n + 1)
		{
			int t = calc();
			if (t < ans[cnt])
			{
				ans[cnt] = t;
			}
			return;
		}
		int newx = x;
		int newy = y + 1;
		if (newy > m)
		{
			newx++;
			newy = 1;
		}
		mirror[x][y] = 0;
		search(newx, newy, cnt);
		if (can[x][y])
		{
			mirror[x][y] = 1;
			search(newx, newy, cnt + 1);
			mirror[x][y] = 2;
			search(newx, newy, cnt + 1);
		}
	}

	void solve()
	{
		memset(ans, 0x3f, sizeof(ans));
		search(1, 1, 0);
		for (int i = 1; i <= n * m; i++)
			ans[i] = std::min(ans[i], ans[i - 1]);

		for (int i = 0; i <= n * m; i++)
		{
			printOut(ans[i]);
			putchar(' ');
		}
		putchar('\n');
	}

	brute()
	{
		for (int i = 1; i <= T; i++)
		{
			querys[i].release();
			solve();
		}
	}
};
struct work
{
	int count1[1 << 5];
	int colum[8][1 << 5];

	int f[8][1 << 5][36];
	int ans[36];

	void solve()
	{
		int U = 1 << n;
		for (int i = 1; i <= m; i++)
		{
			for (int S = 0; S < U; S++)
			{
				bool bOk = true;
				if (count1[S] & 1) bOk = false;
				for (int j = 1; bOk && j <= n; j++)
					if ((S & (1 << (j - 1))) && !can[j][i])
					{
						bOk = false;
						break;
					}
				if (!bOk) continue;

				int t = 0;
				int sig = -1;
				for (int j = 1; j <= n; j++)
				{
					if (S & (1 << (j - 1)))
					{
						t += sig * j;
						sig = -sig;
					}
				}
				colum[i][S] = t;
			}
		}

		memset(f, 0xc0, sizeof(f));
		f[0][0][0] = 0;
		for (int i = 1; i <= m; i++)
		{
			for (int S = 0; S < U; S++)
			{
				bool bOk = true;
				if (count1[S] & 1) bOk = false;
				for (int j = 1; bOk && j <= n; j++)
					if ((S & (1 << (j - 1))) && !can[j][i])
					{
						bOk = false;
						break;
					}
				if (!bOk) continue;

				for (int S0 = 0; S0 < U; S0++)
				{
					int sum = colum[i][S];
					for (int j = 1; j <= n; j++)
						if (S & (1 << (j - 1)))
							sum += (S0 & (1 << (j - 1))) ? i : -i;
					for (int k = count1[S], to = n * m; k <= to; k++)
					{
						f[i][S0 ^ S][k] = std::max(f[i][S0 ^ S][k],
							f[i - 1][S0][k - count1[S]] + sum);
					}
				}
			}
		}
		ans[0] = 0;
		for (int i = 1, to = n * m; i <= to; i++)
			ans[i] = std::max(ans[i - 1], f[m][0][i]);
		int t = 4 * n * m;
		for (int i = 0, to = n * m; i <= to; i++)
		{
			printOut(t - (ans[i] << 1));
			putchar(' ');
		}
		putchar('\n');
	}

	work()
	{
		count1[0] = 0;
		int U = 1 << 5;
		for (int S = 1; S < U; S++)
			count1[S] = count1[S ^ (S & -S)] + 1;
		for (int i = 1; i <= T; i++)
		{
			querys[i].release();
			solve();
		}
	}
};

void run()
{
	T = readIn();
	for (int i = 1; i <= T; i++)
		querys[i].read();
	int maxt = 0;
	for (int i = 1; i <= T; i++)
		maxt = std::max(maxt, querys[i].n * querys[i].m);

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("mirror.in", "r", stdin);
	freopen("mirror.out", "w", stdout);
#endif
	run();
	return 0;
}