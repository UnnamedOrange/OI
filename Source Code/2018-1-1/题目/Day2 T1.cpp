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

const INT maxn = INT(1e5) + 5;
INT n;
char str[maxn];

#define RunInstance(x) delete new x
struct brute
{
	static const INT maxN = 15;

	static bool isMirror(const char s[], INT from, INT to)
	{
		while (from < to)
		{
			if (s[from++] != s[to--])
				return false;
		}
		return true;
	}
	INT search(const char s[])
	{
		INT ret = -1;
		INT length = strlen(s);
		if (!length)
			return 0;
		if (length == 1)
			return -1;
		for (int i = 0; i < length; i++)
		{
			for (int j = i; j < length; j++)
			{
				if (!isMirror(s, i, j))
				{
					char temp[maxN] = {};
					strncpy(temp, s, i);
					strncpy(temp + i, s + j + 1, length - j - 1);
					INT t = search(temp);
					if (t != -1 && (ret == -1 || t + 1 < ret))
					{
						ret = t + 1;
					}
				}
			}
		}
		return ret;
	}

	brute()
	{
		printOut(search(str + 1));
	}
};
struct work
{
	work()
	{
		INT matched = 0;
		for (int i = 1, j = n; i < j; i++, j--)
		{
			if (str[i] != str[j])
			{
				printOut(1);
				return;
			}
			matched++;
		}

		INT times[128] = { 0 };
		INT timeCount = 0;
		INT diffCount = 0;
		INT minCount = n;
		for (int i = 1; i <= n; i++)
		{
			if (!times[str[i]]) timeCount++;
			times[str[i]]++;
			diffCount += str[i] != str[i - 1];
		}
		for (int i = 0; i < 128; i++)
		{
			if (times[i]) minCount = std::min(minCount, times[i]);
		}
		if (timeCount == 1 || timeCount == 2 && (diffCount == n || minCount == 1))
		{
			printOut(-1);
			return;
		}

		printOut(2);
	}
};

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		scanf("%s", str + 1);
		if (n <= 10)
			RunInstance(brute);
		else
			RunInstance(work);
	}
}

int main()
{
#ifndef LOCAL
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
#endif
	run();
	return 0;
}