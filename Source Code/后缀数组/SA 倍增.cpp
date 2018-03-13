#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <cassert>
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
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT_PUT x)
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
	putchar(' ');
}

const int maxn = int(1e6) + 5;

int n;
char str[maxn];
int buf_size = 128;
int buf[maxn];
int SA[maxn]; // SA: 第 i 大的是谁，rank: i 是第几大；rank 的 rank 是 SA
int x[maxn], y[maxn];
void GetSA()
{
	int *rank = x, *SA_second = y;

	for (int i = 0; i < n; i++)
		rank[i] = str[i];

	for (int i = 0; i < buf_size; i++) buf[i] = 0;
	for (int i = 0; i < n; i++) buf[rank[i]]++;
	for (int i = 1; i < buf_size; i++) buf[i] += buf[i - 1];
	for (int i = n - 1; ~i; i--)
		SA[--buf[rank[i]]] = i; // 离散：(SA[--buf[rank[i]]] = rank[i])：rank[i]->i

	for (int k = 1; k <= n; k <<= 1)
	{
		int t = 0;
		for (int i = n - k; i < n; i++) // 尾部“没有”第二关键字的元素，它们的排名设为最小
			SA_second[t++] = i;
		for (int i = 0; i < n; i++)
			if (SA[i] >= k) SA_second[t++] = SA[i] - k;
		// 从小到大枚举第二关键字对应的字符串的右端点 SA[i]

		// 对 rank 排序，按照第二关键字从小到大放入 buf，保证出来时第一关键字相同的第二关键字有序
		for (int i = 0; i < buf_size; i++) buf[i] = 0;
		for (int i = 0; i < n; i++) buf[rank[SA_second[i]]]++;
		for (int i = 1; i < buf_size; i++) buf[i] += buf[i - 1];
		for (int i = n - 1; ~i; i--)
			SA[--buf[rank[SA_second[i]]]] = SA_second[i];

		int* preRank = rank;
		std::swap(rank, SA_second);
		t = 1;
		rank[SA[0]] = 0;
		for (int i = 1; i < n; i++)
			rank[SA[i]] = (preRank[SA[i - 1]] == preRank[SA[i]] &&
				SA[i - 1] + k < n && SA[i] + k < n && // note
				preRank[SA[i - 1] + k] == preRank[SA[i] + k]) ? t - 1 : t++;
		if (t >= n) break;
		buf_size = t;
	}
}

void run()
{
	scanf("%s", str);
	n = strlen(str);

	GetSA();
	for (int i = 0; i < n; i++)
		printOut(SA[i] + 1);
}

int main()
{
	run();
	return 0;
}