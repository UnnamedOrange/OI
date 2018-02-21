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
const char name[] = "wander";

int nE;
const int maxn = 200005;
struct Edge
{
	INT from, to, cost;
	void print()
	{
		printf("%d %d %d\n", from, to, cost);
	}
} edges[maxn];
void addEdge(INT from, INT to, INT cost)
{
	edges[nE].from = from;
	edges[nE].to = to;
	edges[nE].cost = cost;
	nE++;
}

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
		nE = 0;
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
		printf("1 0\n");
	}
};
struct case2 : Instance
{
	case2()
	{
		int n = 6;
		int m = 10;
		printf("%d %d\n", n, m);
		for (int i = 1; i < n; i++)
			addEdge(i, i + 1, rand(1, 10));
		while (nE < m)
			addEdge(rand(1, n), rand(1, n), rand(1, 10));

		std::random_shuffle(edges, edges + nE);
		for (int i = 0; i < nE; i++)
			edges[i].print();
	}
};
struct case3 : Instance
{
	case3()
	{
		int n = rand(350, 400);
		int m = rand(550, 600);
		printf("%d %d\n", n, m);
		for (int i = 1; i < n; i++)
			addEdge(i, i + 1, rand(1e6, 1e9));
		while (nE < m)
			addEdge(rand(1, n), rand(1, n), rand(1, 1e8));

		std::random_shuffle(edges, edges + nE);
		for (int i = 0; i < nE; i++)
			edges[i].print();
	}
};
struct case4 : Instance
{
	case4()
	{
		int n = rand(50000, 80000);
		int m = rand(195000, 200000);
		printf("%d %d\n", n, m);
		for (int i = 1; i < n; i++)
			addEdge(i, i + 1, rand(1, 1e9));
		while (nE < m)
			addEdge(rand(1, n), rand(1, n), rand(1, 1e9));

		std::random_shuffle(edges, edges + nE);
		for (int i = 0; i < nE; i++)
			edges[i].print();
	}
};
struct case5 : Instance
{
	case5()
	{
		int n = rand(50000, 80000);
		int m = rand(195000, 200000);
		n = n / 10 * 10;
		int base = rand(1e3, 1e4);
		for (int i = 1; i <= n; i++)
		{
			addEdge(1, i, (2 * (n - i + 1) + 1) * base);
			addEdge(i, i - 1, base);
		}
		for (int i = 1; i <= 1e3 && nE < m; i++)
			addEdge(rand(1, n), rand(1, n), rand(1, 1e9));

		printf("%d %d\n", n, nE);
		std::random_shuffle(edges, edges + nE);
		for (int i = 0; i < nE; i++)
			edges[i].print();
	}
};

void run()
{
	case1();
	case2();
	for (int i = 1; i <= 4; i++)
		case3();
	for (int i = 1; i <= 4; i++)
		case4();
	for (int i = 1; i <= 10; i++)
		case5();
}

int main()
{
	run();
	return 0;
}
