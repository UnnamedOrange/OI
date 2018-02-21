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
#include <random> 
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
const char name[] = "gene";

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
		int n = rand(7, 10);
		printf("%d\n", n);
		for (int i = 1; i <= n; i++)
		{
			int c = rand(1, 5);
			printf("%d", c);
			for (int j = 1; j <= c; j++)
				printf(" %d", rand(1, 10));
			printf("\n");
		}
	}
};
struct case2 : Instance
{
	case2()
	{
		int n = rand(9e2, 1e3);
		printf("%d\n", n);
		int c = rand(90, 100);
		for (int i = 1; i <= n; i++)
		{
			printf("%d", c);
			for (int j = 1; j <= c; j++)
				printf(" %d", rand(80, 100));
			printf("\n");
		}
	}
};
struct case3 : Instance
{
	case3()
	{
		int n = rand(9e2, 1e3);
		printf("%d\n", n);
		int sum = rand(9.5e4, 1e5);

		std::default_random_engine e(clock() + time(NULL));
		std::normal_distribution<> nd(sum / n, 50);
		std::vector<int> c(n);
		for (int i = 0; i < c.size(); i++)
			c[i] = std::max(2, std::abs((int)nd(e)));
		std::random_shuffle(c.begin(), c.end());
		for (int i = 0; i < n; i++)
		{
			printf("%d", c[i]);
			for (int j = 1; j <= c[i]; j++)
				printf(" %d", rand(1, 1e3));
			printf("\n");
		}
	}
};
struct case4 : Instance
{
	case4()
	{
		int n = rand(9e3, 1e4);
		printf("%d\n", n);
		int sum = rand(9.5e5, 1e6);

		std::default_random_engine e(clock() + time(NULL));
		std::normal_distribution<> nd(sum / n, 50);
		std::vector<int> c(n);
		for (int i = 0; i < c.size(); i++)
			c[i] = std::max(2, std::abs((int)nd(e)));
		std::random_shuffle(c.begin(), c.end());
		for (int i = 0; i < n; i++)
		{
			printf("%d", c[i]);
			for (int j = 1; j <= c[i]; j++)
				printf(" %d", rand(1, 1e3));
			printf("\n");
		}
	}
};
struct case5 : Instance
{
	case5()
	{
		int n = rand(9e3, 1e4);
		printf("%d\n", n);
		int sum = rand(9.5e5, 1e6);

		std::default_random_engine e(clock() + time(NULL));
		std::normal_distribution<> nd(sum / n, 50);
		std::vector<std::vector<int> > c(n / 2);
		for (int i = 0; i < c.size(); i++)
		{
			c[i].resize(std::max(1, std::abs((int)nd(e))));
			for (int j = 0; j < c[i].size(); j++)
				c[i][j] = rand(1, 5e2);
		}
		while (c.size() < n)
			c.push_back(c[rand(0, c.size() - 1)]);

		std::vector<int> idx(n);
		for (int i = 0; i < n; i++)
			idx[i] = i;
		std::random_shuffle(idx.begin(), idx.end());
		for (int i = 0; i < n; i++)
		{
			printf("%d", c[idx[i]].size());
			for (int j = 0; j < c[idx[i]].size(); j++)
				printf(" %d", c[idx[i]][j]);
			printf("\n");
		}
	}
};

void run()
{
	for (int i = 1; i <= 1; i++)
		case1();
	for (int i = 1; i <= 2; i++)
		case2();
	for (int i = 1; i <= 2; i++)
		case3();
	for (int i = 1; i <= 3; i++)
		case4();
	for (int i = 1; i <= 2; i++)
		case5();
}

int main()
{
	run();
	return 0;
}
