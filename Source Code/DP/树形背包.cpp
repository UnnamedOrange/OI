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
INT n, m;
INT value[maxn];
std::vector<std::vector<INT> > edges;
std::bitset<maxn> sets[maxn][maxn];

INT seq[maxn];
INT size[maxn];
void dfs(INT node = 0)
{
	static INT count_ = 0;
	seq[count_++] = node;
	for (int i = 0; i < edges[node].size(); i++)
	{
		INT to = edges[node][i];
		dfs(to);
		size[node] += size[to];
	}
	size[node]++;
}

INT f[maxn][maxn];
void run()
{
	n = readIn();
	m = readIn();
	edges.resize(n + 1);
	for (int i = 1; i <= n; i++)
	{
		INT from = readIn();
		value[i] = readIn();
		edges[from].push_back(i);
	}
	dfs();

	for (int i = n; i >= 0; i--)
	{
		INT c = i ? 1 : 0;
		INT v = value[seq[i]];
		INT s = size[seq[i]];
		for (int j = 0; j <= m; j++)
		{
			if (j < c)
			{
				f[i][j] = f[i + s][j];
				if (n <= 100) sets[i][j] = sets[i + s][j];
			}
			else
			{
				if (f[i + s][j] < f[i + 1][j - c] + v)
				{
					f[i][j] = f[i + 1][j - c] + v;
					if (n <= 100)
					{
						sets[i][j] = sets[i + 1][j - c];
						sets[i][j][seq[i]] = true;
					}
				}
				else
				{
					f[i][j] = f[i + s][j];
					if (n <= 100)
					{
						sets[i][j] = sets[i + s][j];
					}
				}
			}
		}
	}
	cout << f[0][m] << endl;
	if (n <= 100)
	{
		for (int i = 1; i <= n; i++)
		{
			if (sets[0][m].test(i))
			{
				cout << i << endl;
			}
		}
	}
}

int main()
{
	run();
	return 0;
}
