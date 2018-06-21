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
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = int;
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

const int maxn = 25;
int n, m;
double money;
double cost[maxn];
double limit[maxn];
double rect[maxn][maxn];
double weight[maxn];

double temp[maxn];
double max;
double ans[maxn];
int idx[maxn];

void run()
{
	n = readIn();
	m = readIn();
	scanf("%lf", &money);
	for (int i = 1; i <= n; i++)
		scanf("%lf", &cost[i]);
	for (int i = 1; i <= n; i++)
		scanf("%lf", &limit[i]);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			scanf("%lf", &rect[i][j]);

	int U = 1 << m;
	for (int S = 0; S < U; S++)
	{
		for (int i = 1; i <= n; i++)
			weight[i] = 0;
		for (int i = 1; i <= m; i++)
		{
			int sig = (S & (1 << (i - 1))) ? -1 : 1;
			for (int j = 1; j <= n; j++)
				weight[j] += rect[i][j] * sig;
		}

		if (weight[1] >= 0 && weight[2] >= 0)
			int a = 0;

		for (int i = 1; i <= n; i++)
			idx[i] = i;
		std::sort(idx + 1, idx + 1 + n,
			[](const int& a, const int& b)
		{
			return weight[a] / cost[a] > weight[b] / cost[b];
		});

		double val = 0;
		double t = money;
		std::memset(temp, 0, sizeof(temp));
		for (int i = 1; i <= n && weight[idx[i]] > 0; i++)
		{
			if (t >= cost[idx[i]] * limit[idx[i]])
			{
				t -= cost[idx[i]] * limit[idx[i]];
				val += weight[idx[i]] * limit[idx[i]];
				temp[idx[i]] = limit[idx[i]];
			}
			else
			{
				temp[idx[i]] = t / cost[idx[i]];
				val += weight[idx[i]] * t / cost[idx[i]];
				t = 0;
				break;
			}
		}
		if (val > max)
		{
			max = val;
			std::memcpy(ans, temp, sizeof(ans));
		}
	}

	for (int i = 1; i <= n; i++)
		printf("%.12f ", ans[i]);
}

int main()
{
	for (int i = 1; i <= 10; i++)
	{
		char buffer[20];
		sprintf(buffer, "element%d.in", i);
		freopen(buffer, "r", stdin);
		sprintf(buffer, "element%d.out", i);
		freopen(buffer, "w", stdout);

		max = 0;
		std::memset(ans, 0, sizeof(ans));
		run();
	}
	return 0;
}