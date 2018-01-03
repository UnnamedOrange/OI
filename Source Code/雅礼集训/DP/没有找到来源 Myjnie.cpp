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
	while(!(ch == '-' || (ch >= '0' && ch <= '9')))
		ch = getchar();
	if(ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if(minus)
		a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	if(x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	}
	while(x);
	do
	{
		putchar(buffer[--length]);
	}
	while(length);
	putchar('\n');
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = 55;
const INT maxm = 1005;
INT n, m, t;
struct People
{
	INT a, b, c;
	void read()
	{
		a = readIn();
		b = readIn();
		c = readIn();
	}
} people[maxm];
INT disc[maxm];

void discretize()
{
	for(int i = 1; i <= m; i++)
		disc[i] = people[i].c;
	std::sort(disc + 1, disc + 1 + n);
	t = std::unique(disc + 1, disc + 1 + n) - (disc + 1);
	for(int i = 1; i <= m; i++)
		people[i].c = std::lower_bound(disc + 1, disc + 1 + t, people[i].c) - disc;
}

INT f[maxn][maxn][maxm];
INT dp(INT l, INT r, INT minCost)
{
	INT& ans = f[l][r][minCost];
	if(ans != -1)
		return ans;
	ans = -INF;
	for(int i = l; i <= r; i++)
	{
		INT maxLeft = 0;
		INT maxRight = 0;
		for(int j = minCost; j <= t; j++)
		{
			maxLeft = std::max(maxLeft, dp(l, i - 1, j));
			maxRight = std::max(maxRight, dp(i + 1, r, j));
		}
		INT cost = 0;
		for(int j = 1; j <= m; j++)
			if(l <= people[j].a && people[j].b <= r)
				if(people[j].a <= i && i <= people[j].b && minCost <= people[i].c)
					cost += disc[minCost];
		ans = std::max(ans, maxLeft + maxRight + cost);
	}
	return ans;
}

void run()
{
	n = readIn();
	m = readIn();
	for(int i = 1; i <= m; i++)
		people[i].read();
	discretize();
	
	INT ans = 0;
	for(int i = 1; i <= t; i++)
		ans = std::max(ans, dp(1, n, i));
	printOut(ans);
}

int main()
{
	run();
	return 0;
}
