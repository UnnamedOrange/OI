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
	}
	while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	}
	while (length);
	putchar('\n');
}

const INT maxn = 50005;
INT n;
INT a[2][maxn];
INT in[maxn];
INT seq[maxn];
bool vis[maxn];

INT ans;
INT sub[maxn];
void calc()
{
	memset(sub, 0, sizeof(sub));
	for(int i = 1; i <= n; i++)
	{
		INT x = seq[i] - i;
		if(x <= 0) x += n;
		sub[x]++;
		ans = std::min(ans, n - sub[x]);
	}
}

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		in[a[0][i] = readIn()]++;
		in[a[1][i] = readIn()]++;
		if(a[0][i] == i || a[1][i] == i || in[a[0][i]] > 2 || in[a[1][i]] > 2)
		{
			printOut(-1);
			return;
		}
	}
	INT person = 1;
	while(seq[0] < n)
	{
		seq[++seq[0]] = person;
		vis[person] = true;
		if(!vis[a[0][person]]) person = a[0][person];
		else if (!vis[a[1][person]]) person = a[1][person];
		else if(seq[0] < n)
		{
			printOut(-1);
			return;
		}
	}
	
	ans = n;
	calc();
	std::reverse(seq + 1, seq + 1 + n);
	calc();
	printOut(ans);
}

int main()
{
	run();
	return 0;
}
