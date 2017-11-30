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
using std::cin;
using std::cout;
using std::endl;
typedef int INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT maxn = 1000005;
const INT maxm = 1005;
char s1[maxn], s2[maxm];
INT l1, l2;
INT f[maxm];

void KMP()
{
	INT matched = 0;
	for (int i = 0; i < l1; i++)
	{
		while (matched && s1[i] != s2[matched]) matched = f[matched];
		if (s1[i] == s2[matched]) matched++;
		if (matched == l2)
		{
			printf("%d\n", i - l2 + 1 + 1);
		}
	}
}

void initFailure()
{
	f[0] = f[1] = 0;
	for (int i = 1; i < l2; i++)
	{
		INT pre = f[i];
		while (pre && s2[i] != s2[pre]) pre = f[pre]; //s[i]代表的是第i + 1个字符
		f[i + 1] = s2[i] == s2[pre] ? pre + 1 : 0;
	}
}

void run()
{
	scanf("%s%s", s1, s2);
	l1 = strlen(s1);
	l2 = strlen(s2);
	initFailure();
	KMP();
	for (int i = 1; i <= l2; i++)
	{
		printf("%d ", f[i]);
	}
}

int main()
{
	run();
	return 0;
}