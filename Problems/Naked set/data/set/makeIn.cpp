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
#include <windows.h>
typedef long long LL;
using std::cin;
using std::cout;
using std::endl;

#define redirect(x) freopen(x, "w", stdout);

LL rand(INT l, INT r)
{
#define r(x) (LL(rand()) << x)
	LL ret = r(45) | r(30) | r(15) | r(0);
	return l + ret % (r - l + 1);
#undef r
}

void make1()
{
	redirect("data1.in");
	INT n = 1000;
	printf("%d\n", n);
	for (int i = 1; i <= n / 2; i++)
	{
		printf("1 %d\n", i);
		printf("2 %d\n", i);
	}
}
void make2()
{
	redirect("data2.in");
	INT n = 1000;
	printf("%d\n", n);
	for (int i = 1; i <= n / 2; i++)
	{
		printf("1 %d\n", i);
		printf("3\n", i);
	}
}
void make3()
{
	redirect("data4.in");
	INT n = 300000;
	printf("%d\n", n);
	for (int i = 1; i <= n; i++)
	{
		printf("1 %d\n", i);
	}
}
void make(INT n, INT group)
{
	char buffer[260];
	sprintf(buffer, "data%d.in", group);
	redirect(buffer);

	printf("%d\n", n);
	std::set<INT> set;
	std::vector<INT> arr;
	for (int i = 1; i <= n; i++)
	{
		INT ins = rand(1, 10);
		if (ins == 5)
		{
			printf("3\n");
		}
		else if (3 <= ins && ins <= 7)
		{
			INT r = rand(1, 1e9);
			printf("1 %d\n", r);
			if (!set.count(r)) arr.push_back(r);
			set.insert(r);
		}
		else
		{
			INT p = rand(1, 10);
			INT r;
			if (!set.size() || (4 <= p && p <= 5))
			{
				do
				{
					r = rand(1, 1e9);
				}
				while (set.count(r));
			}
			else
			{
				do
				{
					r = arr[rand(0, arr.size() - 1)];
				}
				while(!set.count(r));
				set.erase(r);
			}
			printf("2 %d\n", r);
		}
	}
}

void run()
{
	srand(GetTickCount());

	make1();
	make2();
	make(1000, 3);
	make3();
	for (int i = 5; i <= 20; i++)
	{
		make(300000, i);
	}
}

int main()
{
	run();
	return 0;
}
