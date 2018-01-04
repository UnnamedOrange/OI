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
	while (!(ch == '-' || (ch >= '0' && ch <= '9')))
		ch = getchar();
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
	if (minus)
		a = -a;
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
	putchar('\n');
}

const INT maxm = 10005;
char a[maxm];
INT n;
char t[5][1005];

struct KMP
{
	INT f[1005];
	const char* str;
	INT length;
	void operator= (const char* s)
	{
		str = s;
		length = strlen(s);
		initFailure();
	}
	void initFailure()
	{
		f[0] = f[1] = 0;
		for (int i = 1; i < n; i++)
		{
			INT pre = f[i];
			while (pre && str[i] != str[pre]) pre = f[pre];
			f[i + 1] = str[pre] == str[i] ? f[pre] + 1 : 0;
		}
	}
} kmps[5];

void run()
{
	INT T = readIn();
	while (T--)
	{
		scanf("%s", a);
		n = readIn();
		for (int i = 1; i <= n; i++)
			scanf("%s", t[i]);

		for (int i = 1; i <= n; i++)
			kmps[i] = t[i];


	}
}

int main()
{
	run();
	return 0;
}
