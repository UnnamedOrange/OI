#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <functional>
#include "datagen.h"
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int mod = 998244353;

struct case1 : CaseBase
{
	case1(int n, int delta)
	{
		n = rand_int(n - delta, n);
		cprintf("%d\n", n);
		for (int i = 1; i <= n; i++)
			cprintf("%d ", rand_int(1, mod - 1));
	}
};

struct case2 : CaseBase
{
	case2(int n)
	{
		cprintf("%d\n", n);
		for (int i = 1; i <= n; i++)
			cprintf("%d ", 1);
	}
};

void run()
{
	Initialize("subsubset");
	GoCase(case1, 4, 8, 0);
	GoCase(case1, 6, 15, 0);
	GoCase(case2, 5, 4995 + counter);
	GoCase(case1, 5, 5000, 200);
	GoCase(case1, 4, 100000, 15000);
}

int main()
{
	run();
	return 0;
}