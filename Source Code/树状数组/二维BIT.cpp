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

const INT maxn = 2005;
INT n, m;
struct BIT
{
#define lowbit(x) ((x) & -(x))
	INT bit[maxn][maxn];

	void add(INT x, INT y)
	{
		for(int i = x; i <= n; i += lowbit(i))
		{
			for(int j = y; j <= m; j += lowbit(j))
			{
				bit[i][j]++;
			}
		}
	}
	INT query(INT x, INT y)
	{
		INT ret = 0;
		for(int i = x; i > 0; i -= lowbit(i))
		{
			for(int j = y; j > 0; j -= lowbit(j))
			{
				ret += bit[i][j];
			}
		}
		return ret;
	}
} bit;

void run()
{
	
}

int main()
{
	run();
	return 0;
}
