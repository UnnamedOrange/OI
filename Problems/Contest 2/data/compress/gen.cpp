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
#include <ctime>
#include <climits>
typedef long long LL;
using std::cin;
using std::cout;
using std::endl;
LL readIn()
{
	LL a = 0;
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
void printOut(LL x)
{
	char buffer[20];
	int length = 0;
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

const int buffer_size = 8192;
char buffer[buffer_size];
const char name[] = "compress";
int g_idx;
LL rand(LL from, LL to)
{
#define r(x) ((LL)rand() << x)
	LL ret = r(45) | r(30) | r(15) | r(0);
#undef r
	return from + ret % (to - from + 1);
}
struct CaseBase
{
	CaseBase()
	{
		g_idx++;
		sprintf(buffer, "%s%d.in", name, g_idx);
		freopen(buffer, "w", stdout);

		srand(time(NULL) + clock());
	}
	~CaseBase()
	{
		fclose(stdout);

		sprintf(buffer, "%s.exe < %s%d.in > %s%d.ans", name, name, g_idx, name, g_idx);
		system(buffer);
	}
};
#define GoCase(x, t) for (int o = 0; o < t; o++) x()

struct case1 : private CaseBase
{
	case1()
	{
		printf("%lld\n%lld\n", rand(SHRT_MAX / 10, SHRT_MAX), rand(SHRT_MAX / 10, SHRT_MAX));
	}
};
struct case2 : private CaseBase
{
	case2()
	{
		printf("%lld\n%lld\n", rand(INT_MAX / 10, INT_MAX), rand(INT_MAX / 10, INT_MAX));
	}
};
struct case3 : private CaseBase
{
	case3()
	{
		printf("%lld\n%lld\n", rand(LLONG_MAX / 10, LLONG_MAX), rand(LLONG_MAX / 10, LLONG_MAX));
	}
};
struct case4 : private CaseBase
{
	void print(int digit)
	{
		putchar(rand(1, 9) + '0');
		while (--digit) putchar(rand(0, 9) + '0');
		putchar('\n');
	}
	case4(int limit = 5000)
	{
		int n = rand(limit - 1000, limit);
		int m = rand(limit - 1000, limit);
		print(n);
		print(m);
	}
};
struct case5 : private case4
{
	case5() : case4(80000) {}
};

void run()
{
	GoCase(case1, 1);
	GoCase(case2, 1);
	GoCase(case3, 2);
	GoCase(case4, 6);
	GoCase(case5, 10);
}

int main()
{
	run();
	return 0;
}