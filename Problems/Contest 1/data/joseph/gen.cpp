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
typedef long long INT;
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

inline INT rand(INT l, INT r)
{
#define r(x) (INT(rand()) << (x))
	INT ret = r(30) | r(15) | r(0);
	return l + ret % (r - l + 1);
#undef r
}
const int buffer_size = 8192;
const char name[] = "joseph";

char buffer[buffer_size];
void redirect(int idx)
{
	sprintf(buffer, "%s%02d.in", name, idx);
	freopen(buffer, "w", stdout);
}
void release()
{
	fclose(stdout);
}
struct Instance
{
	static int g_nGroup;
	Instance()
	{
		g_nGroup++;
		redirect(g_nGroup);
		srand(time(NULL) + clock());
	}
	~Instance()
	{
		sprintf(buffer, "%s.exe < %s%02d.in > %s%02d.ans", name, name, g_nGroup, name, g_nGroup);
		release();
		system(buffer);
	}
};
int Instance::g_nGroup;

struct case1 : Instance
{
	case1()
	{
		int n = rand(80, 100);
		int m = rand(9e4, 1e5) / n;
		printOut(n);
		putchar(' ');
		printOut(m);
		putchar('\n');
	}
};
struct case2 : Instance
{
	case2()
	{
		int n = rand(8e5, 3e6);
		int m = rand(9.5e6, 1e7) / n;
		printOut(n);
		putchar(' ');
		printOut(m);
		putchar('\n');
	}
};
struct case3 : Instance
{
	case3()
	{
		int n = rand(2e6, 1e7);
		int m = rand(8e6, 1e9) / n;
		printOut(n);
		putchar(' ');
		printOut(m);
		putchar('\n');
	}
};
struct case4 : Instance
{
	case4()
	{
		int n = rand(6e8, 1e9);
		int m = 2;
		printOut(n);
		putchar(' ');
		printOut(m);
		putchar('\n');
	}
};

void run()
{
	for (int i = 1; i <= 3; i++)
		case1();
	for (int i = 1; i <= 3; i++)
		case2();
	for (int i = 1; i <= 2; i++)
		case3();
	for (int i = 1; i <= 2; i++)
		case4();
}

int main()
{
	run();
	return 0;
}