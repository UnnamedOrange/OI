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
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

const INT maxn = 4005;
INT n, m, k;
INT a[maxn], b[maxn];

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		
	}
};
struct work
{
	work()
	{
		
	}
};

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	for(int i = 1; i <= n; i++)
		a[i] = readIn();
	for(int i = 1; i <= n; i++)
		b[i] = readIn();
	
	if(n <= 18 && m <= 18 && k == 2)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("subsequence.in", "r", stdin);
	freopen("subsequence.out", "w", stdout);
#endif
	run();
	return 0;
}
