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
const char name[] = "gcd1";
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
		const int val[] =
		{
			4, 100, 200, 500, 1000,
			2000, 5000, 10000, 20000, 50000,
			100000, 200000, 500000, 1e6, 1e7,
		};
		const int size = sizeof(val) / sizeof(int);

		static int idx = -1;
		idx++;
		if (idx < size)
			printf("%d", val[idx]);
		else
			printf("%d", rand(8e6, 1e7));
	}
};

void run()
{
	GoCase(case1, 20);
}

int main()
{
	run();
	return 0;
}