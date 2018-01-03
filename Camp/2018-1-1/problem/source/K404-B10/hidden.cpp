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

const INT maxn = 15;
INT n;
INT a[maxn];

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
		a[i] |= 1 << (readIn() - 1);
	
	printOut(-1);
}

int main()
{
#ifndef LOCAL
	freopen("hidden.in", "r", stdin);
	freopen("hidden.out", "w", stdout);
#endif
	run();
	return 0;
}
