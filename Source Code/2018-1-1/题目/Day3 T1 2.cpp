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

const INT maxn = 100005;
INT n;
INT a[maxn];
char ans[maxn];

void run()
{
	n = readIn();

	a[1] = readIn();
	ans[1] = 'a';
	putchar(ans[1]);
	for (int i = 2; i <= n; i++)
	{
		a[i] = readIn();
		if (i != a[i])
		{
			ans[i] = ans[(i - 1) % a[i] + 1];
		}
		else
		{
			bool flag[26] = { true };
			INT pre = i - 1 - a[i - 1];
			while (pre)
			{
				flag[ans[pre + 1] - 'a'] = true;
				pre = pre - a[pre];
			}

			for (int j = 0; j < 26; j++)
				if (!flag[j])
				{
					ans[i] = j + 'a';
					break;
				}
		}
		putchar(ans[i]);
	}
}

int main()
{
	run();
	return 0;
}