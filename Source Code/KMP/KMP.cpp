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

const INT maxn = INT(1e6) + 5;
INT n, m;
char str[maxn], t[maxn];

INT fMP[maxn];
void initFailureMP()
{
	fMP[0] = -1;
	for (int i = 0; i < m; i++)
	{
		INT pre = fMP[i]; //这个 pre 事实上可以通过维护得到
		while (~pre && t[i] != t[pre]) pre = fMP[pre];
		pre++; //从 -1 开始避免了判断
		fMP[i + 1] = pre;
	}
}
INT fKMP[maxn];
void initFailureKMP()
{
	INT pre = fKMP[0] = -1;
	for (int i = 0; i < m; i++)
	{
		while (~pre && t[i] != t[pre]) pre = fKMP[pre];
		pre++;
		if (t[i + 1] == t[pre]) fKMP[i + 1] = fKMP[pre];
		else fKMP[i + 1] = pre;
	}
}

void run()
{
	scanf("%s", str);
	scanf("%s", t);
	n = strlen(str);
	m = strlen(t);
	initFailureKMP();
	initFailureMP();
	INT cnt = 0;
	for (int i = 0; i < n; i++)
	{
		while (~cnt && str[i] != t[cnt]) cnt = fKMP[cnt];
		cnt++;
		if (cnt == m)
		{
			printOut(i - m + 2);
			putchar('\n');
		}
	}
	for (int i = 1; i <= m; i++)
	{
		printOut(fMP[i]);
		putchar(' ');
	}
	putchar('\n');
}

int main()
{
	run();
	return 0;
}