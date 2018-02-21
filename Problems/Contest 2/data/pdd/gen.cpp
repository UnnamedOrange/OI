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
const char name[] = "pdd";
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
	case1(int limit = 20)
	{
		int n = rand(limit - 5, limit);
		printf("%d\n", n);
		for (int i = 1; i <= n; i++)
			printf("%d ", rand(1, limit / rand(1, 4)));
	}
};
struct case2 : private case1
{
	case2() : case1(5000) {}
};
struct case3 : private case1
{
	case3() : case1(1000000) {}
};

void run()
{
	GoCase(case1, 4);
	GoCase(case2, 6);
	GoCase(case3, 10);
}

int main()
{
	run();
	return 0;
}