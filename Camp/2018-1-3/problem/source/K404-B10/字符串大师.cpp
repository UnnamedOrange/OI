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

INT f[maxn];
bool flag[27];
INT init(INT x)
{
	INT pre = f[x];
	while (pre && ans[pre] != ans[x]) pre = f[pre];
	f[x + 1] = (ans[pre] == ans[x]) ? pre + 1 : 0;
}

void run()
{
	n = readIn();

	a[0] = readIn();
	ans[0] = 'a';
	putchar(ans[0]);
	for (int i = 1; i < n; i++)
	{
		a[i] = readIn();
		INT pos = i % a[i];
		if (pos != i)
		{
			ans[i] = ans[pos];
			init(i);
		}
		else
		{
			memset(flag, 0, sizeof(flag));
			for (int j = 0; j < 26; j++)
			{
				ans[i] = j + 'a';
				init(i);
				if (f[i + 1])
					flag[j] = true;
			}
			for (int j = 0; j < 26; j++)
			{
				if (!flag[j])
				{
					ans[i] = j + 'a';
					break;
				}
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