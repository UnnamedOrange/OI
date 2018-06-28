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
#include <random>
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = int;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

std::default_random_engine e;
using Rand = std::uniform_int_distribution<int>;
int rand(int l, int r)
{
	return Rand(l, r)(e);
}

const int maxn = 10005;
int n, R, C;
std::pair<int, int> points[maxn];

LL getAns()
{
	LL ret = 0;
	static int num[maxn];
	for (int i = 1; i <= n; i++)
		num[i] = points[i].first;
	std::nth_element(num + 1, num + (n + 1) / 2, num + 1 + n);
	for (int i = 1; i <= n; i++)
		ret += std::abs(num[i] - num[(n + 1) / 2]);

	for (int i = 1; i <= n; i++)
		num[i] = points[i].second;
	std::nth_element(num + 1, num + (n + 1) / 2, num + 1 + n);
	for (int i = 1; i <= n; i++)
		ret += std::abs(num[i] - num[(n + 1) / 2]);

	return ret;
}

void run()
{
	int ret;
	int maxVal = 0;
	do
	{
		FILE* file = fopen("diff.in", "w");

		n = 997;
		R = 1e7;
		C = 1e7;
		fprintf(file, "%d %d %d\n", n, R, C);
		for (int i = 1; i <= n; i++)
		{
			if (i > 1 && !rand(0, 50))
				points[i] = points[rand(1, i - 1)];
			else
			{
				points[i].first = rand(1, R);
				points[i].second = rand(1, C);
			}
		}
		for (int i = 1; i <= n; i++)
			fprintf(file, "%d %d\n", points[i].first, points[i].second);
		fprintf(file, "%lld\n", getAns());
		fclose(file);

		ret = std::system("./diff < diff.in");
		// getchar();
	} while (!ret);
}

int main()
{
#ifndef LOCAL

#endif
	run();
	return 0;
}