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
const INT maxn = 10005;
const INT maxm = 1005;
INT n, m, k;
INT x[maxn];
INT y[maxn];
struct Pipe
{
	INT p;
	INT l;
	INT h;
	void read()
	{
		p = readIn();
		l = readIn();
		h = readIn();
	}
} pipes[maxn];
INT idxPipe[maxn];
INT pipeNum[maxn];

INT f[2][maxm];
void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	for (int i = 1; i <= n; i++)
	{
		x[i] = readIn();
		y[i] = readIn();
	}
	for (int i = 1; i <= k; i++)
	{
		pipes[i].read();
		idxPipe[pipes[i].p] = i;
		pipeNum[pipes[i].p] = 1;
	}
	for (int i = 1; i <= n; i++)
		pipeNum[i] += pipeNum[i - 1];

	for (int i = 1; i <= n; i++)
	{
		INT cnt = i & 1;
		INT pre = !cnt;
		memset(f[cnt], 0x3f, sizeof(f[cnt]));
		for (int j = 1; j <= m; j++)
		{
			f[cnt][std::min(m, j + x[i])] = std::min(f[cnt][std::min(m, j + x[i])], std::min(f[pre][j], f[cnt][j]) + 1);
		}
		for (int j = y[i] + 1; j <= m; j++)
		{
			f[cnt][j - y[i]] = std::min(f[cnt][j - y[i]], f[pre][j]);
		}
		INT idx = idxPipe[i];
		if (idx)
		{
			for (int j = 1; j <= pipes[idx].l; j++)
				f[cnt][j] = INF;
			for (int j = pipes[idx].h; j <= m; j++)
				f[cnt][j] = INF;
		}

		INT minVal = INF;
		for (int j = 1; j <= m; j++)
			minVal = std::min(minVal, f[cnt][j]);
		if (minVal >= INF)
		{
			printOut(0);
			printOut(pipeNum[i - 1]);
			return;
		}
	}
	INT ans = INF;
	for (int i = 1; i <= m; i++)
		ans = std::min(ans, f[n & 1][i]);
	printOut(1);
	printOut(ans);
}

int main()
{
	run();
	return 0;
}
