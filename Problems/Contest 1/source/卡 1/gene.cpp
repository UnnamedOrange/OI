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

const INT maxn = INT(1e4) + 5;
INT n;

struct Object
{
	std::vector<INT> a;
	INT idx;
	bool operator<(const Object& b) const
	{
		if(a.size() != b.a.size())
			return a.size() < b.a.size();
		if(a != b.a)
			return a > b.a;
		return idx < b.idx;
	}
} a[maxn];

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		a[i].idx = i;
		a[i].a.resize(readIn());
		for (int j = 0, to = a[i].a.size(); j < to; j++)
		{
			a[i].a[j] = readIn();
		}
	}

	std::sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++)
	{
		static bool printed;
		if (printed)
			putchar(' ');
		printed = true;
		printOut(a[i].idx);
	}
	putchar('\n');
}

int main()
{
#ifndef LOCAL
	freopen("gene.in", "r", stdin);
	freopen("gene.out", "w", stdout);
#endif
	run();
	return 0;
}
