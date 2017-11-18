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

const INT mod = INT(1e9) + 7;
const INT maxn = 1005;
INT n, m;
char x[maxn], y[maxn];
INT readStr(char* buffer)
{
	char ch = getchar();
	while (!(ch >= 'a' && ch <= 'z')) ch = getchar();
	INT length = 0;
	while (ch >= 'a' && ch <= 'z')
	{
		buffer[++length] = ch;
		ch = getchar();
	}
	return length;
}

INT lcs[maxn][maxn];
INT f[maxn][maxn];

void LCS()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (x[i] == y[j])
			{
				lcs[i][j] = lcs[i - 1][j - 1] + 1;
			}
			else
			{
				lcs[i][j] = std::max(lcs[i - 1][j], lcs[i][j - 1]);
			}
		}
	}
}

void DP()
{
	for (int i = 1; i <= n; i++) f[i][0] = 1;
	for (int i = 1; i <= m; i++) f[0][i] = 1;
	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		INT nearest = 0;
		for (int j = 1; j <= m; j++)
		{
			if (x[i] == y[j]) nearest = j;
			//don't match i
			if (lcs[i][j] == lcs[i - 1][j]) f[i][j] = f[i - 1][j];
			//match i
			if (nearest && lcs[i][j] == lcs[i - 1][nearest - 1] + 1)
				f[i][j] = (f[i][j] + f[i - 1][nearest - 1]) % mod;
		}
	}
	cout << f[n][m] << endl;
}

void run()
{
	n = readStr(x);
	m = readStr(y);
	LCS();
	DP();
}

int main()
{
	run();
	return 0;
}
