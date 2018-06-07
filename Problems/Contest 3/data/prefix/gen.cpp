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

const int mod = 100003;

struct caseRandom : CaseBase
{
	caseRandom(LL lt, LL rt, LL mt, int tt, int occur = true)
	{
		int T = rand_int(1, tt);
		cprintf("%d\n", T);
		for (int i = 1; i <= T; i++)
		{
			bool happen = occur && !bool(rand_int(0, T - 1));
			LL n = happen ? 1 : rand_int(lt, rt);
			LL m = rand_int(0, mt) * !happen;
			cprintf("%lld %lld %lld\n", n, m, rand_int(0, mod - 1));
		}
	}
};
struct caseSpec1 : CaseBase
{
	caseSpec1()
	{
		cprintf("%d\n", 1);
		LL n, m;
		static int t = 0;
		switch (t++)
		{
		case 0:
			n = 0;
			m = 0;
			break;
		case 1:
			n = 1;
			m = 0;
			break;
		case 2:
			n = 49999;
			m = 49998;
			break;
		case 3:
			n = rand_int(0, 50000);
			m = 0;
			break;
		}
		cprintf("%lld %lld %lld\n", n, m, rand_int(1, mod - 1));
	}
};

void run()
{
	Initialize("prefix");
	// subtask 1
	GoCase(caseRandom, 2, 0, 100, 100, 1e4);

	// subtask 2
	GoCase(caseRandom, 2, 1, 1, 5e4, 1e4);

	// subtask 3
	GoCase(caseRandom, 6, 4e4, 5e4, 5e4, 1);
	GoCase(caseSpec1, 4);

	// subtask 4
	GoCase(caseRandom, 6, 0, 5e4, 5e4, 1e4, true);

	// subtask 5
	GoCase(caseRandom, 4, 0, 1e18, 1e18, 1e4);
}

int main()
{
	run();
	return 0;
}