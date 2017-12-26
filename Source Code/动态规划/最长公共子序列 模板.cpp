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
}

const INT maxn = 100005;
INT n;
INT a[maxn];
INT b[maxn];
INT map[maxn];
INT s[maxn];

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 1; i <= n; i++)
		b[i] = readIn();
	for (int i = 1; i <= n; i++)
		map[a[i]] = i;
	for (int i = 1; i <= n; i++)
		b[i] = map[b[i]];

	for (int i = 1; i <= n; i++)
	{
		if (!s[0] || s[s[0]] < b[i])
		{
			s[++s[0]] = b[i];
		}
		else
		{
			*std::lower_bound(s + 1, s + 1 + s[0], b[i]) = b[i];
		}
	}
	printOut(s[0]);
}

int main()
{
	run();
	return 0;
}
