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
char read()
{
	char ch = getchar();
	while (!(ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')) ch = getchar();
	return ch;
}

const INT maxn = 60;
INT n, m;
INT rect[maxn][maxn];
inline INT code(char ch)
{
	if (ch >= 'A' && ch <= 'Z') return ch - 'A';
	return ch - 'a' + 26;
}
inline char decode(INT c)
{
	if (0 <= c && c < 26) return 'A' + c;
	return 'a' + (c - 26);
}
INT degree[maxn];
bool appear[maxn];

std::vector<char> buf;

void dfs(INT node)
{
	for (int i = 0; i < n; i++)
	{
		if (rect[node][i])
		{
			rect[node][i] = rect[i][node] = false;
			dfs(i);
		}
	}
	buf.push_back(decode(node));
}

void run()
{
	n = 52;
	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		INT u = code(read());
		INT v = code(read());

		rect[u][v] = rect[v][u] = true;
		degree[u]++;
		degree[v]++;
		appear[u] = appear[v] = true;
	}

	INT u = -1;
	INT v = -1;
	INT count_ = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		if (degree[i] & 1)
		{
			count_++;
			u = i;
		}
		else if (!(degree[i] & 1) && appear[i])
			v = i;
	}
	if (count_ && count_ != 2)
	{
		puts("No Solution");
		return;
	}
	if (u != -1) dfs(u);
	else dfs(v);

	while (buf.size())
	{
		putchar(buf.back());
		buf.pop_back();
	}
}

int main()
{
	run();
	return 0;
}
