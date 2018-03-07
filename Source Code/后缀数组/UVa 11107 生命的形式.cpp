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
	putchar('\n');
}

const int maxn = 105;
int len;
int str[maxn * 1000];
int belong[maxn * 1000];
int buf_size;
int buf[maxn * 1000];
int SA[maxn * 1000];
int x[maxn * 1000];
int y[maxn * 1000];
void GetSA()
{
	int *rank = x, *SA_second = y;
	for (int i = 0; i < len; i++)
		rank[i] = str[i];

	for (int i = 0; i < buf_size; i++) buf[i] = 0;
	for (int i = 0; i < len; i++) buf[rank[i]]++;
	for (int i = 1; i < buf_size; i++) buf[i] += buf[i - 1];
	for (int i = len - 1; ~i; i--)
		SA[--buf[rank[i]]] = i;

	for (int k = 1; k <= len; k <<= 1)
	{
		int t = 0;
		for (int i = len - k; i < len; i++)
			SA_second[t++] = i;
		for (int i = 0; i < len; i++)
			if (SA[i] >= k) SA_second[t++] = SA[i] - k;

		for (int i = 0; i < buf_size; i++) buf[i] = 0;
		for (int i = 0; i < len; i++) buf[rank[SA_second[i]]]++;
		for (int i = 1; i < buf_size; i++) buf[i] += buf[i - 1];
		for (int i = len - 1; ~i; i--) SA[--buf[rank[SA_second[i]]]] = SA_second[i];

		int* preRank = rank;
		std::swap(rank, SA_second);
		t = 1;
		rank[SA[0]] = 0;
		for (int i = 1; i < len; i++)
			rank[SA[i]] = (preRank[SA[i]] == preRank[SA[i - 1]] && preRank[SA[i] + k] == preRank[SA[i - 1] + k]) ? t - 1 : t++;
		if (t >= len) break;
		buf_size = t;
	}
}
int rank[maxn];
int height[maxn];
void GetHeight()
{
	for (int i = 0; i < len; i++) rank[SA[i]] = i;
	int same = 0;
	for (int i = 0; i < len; i++)
	{
		if (rank[i] == 0)
			same = 0;
		else
		{
			if (same) same--;
			int pre = SA[rank[i] - 1];
			while (i + same < len && pre + same < len && str[i + same] == str[pre + same])
				same++;
		}
		height[rank[i]] = same;
	}
}
int n;
bool check(int s)
{
	static int used[101];
	memset(used, 0, sizeof(used));
	int state = 0;
	int cnt = 0;
	for (int i = 0; i < len; i++)
	{
		if (height[i] < s)
		{
			state++;
			cnt = 1;
			used[belong[SA[i]]] = state;
		}
		else
		{
			if (used[belong[SA[i]]] != state)
			{
				cnt++;
				used[belong[SA[i]]] = state;
			}
		}
		if (cnt > n / 2) return true;
	}
	return false;
}
void statistic(int s)
{
	static int used[101];
	memset(used, 0, sizeof(used));
	int state = 0;
	int cnt = 0;
	for (int i = 0; i < len; i++)
	{
		if (height[i] < s)
		{
			if (cnt > n / 2)
			{
				for (int j = 0, k = SA[i - 1]; j < s; j++, k++)
					putchar(str[k] + 'a');
				putchar('\n');
			}
			state++;
			cnt = 1;
			used[belong[SA[i]]] = state;
		}
		else
		{
			if (used[belong[SA[i]]] != state)
			{
				cnt++;
				used[belong[SA[i]]] = state;
			}
		}
	}
	if (cnt > n / 2)
	{
		for (int j = 0, k = SA[len - 1]; j < s; j++, k++)
			putchar(str[k] + 'a');
		putchar('\n');
	}
}

void run()
{
	while (n = readIn())
	{
		static bool printed;
		if (printed)
			putchar('\n');
		printed = true;
		len = 0;
		int l = 0, r = 0;
		for (int i = 1; i <= n; i++)
		{
			char ch = getchar();
			while (!('a' <= ch && ch <= 'z')) ch = getchar();
			int t = 0;
			while ('a' <= ch && ch <= 'z')
			{
				t++;
				belong[len] = i;
				str[len++] = ch - 'a';
				ch = getchar();
			}
			r = std::max(r, t);
			str[len++] = buf_size = 26 + i - 1;
		}
		buf_size++;
		GetSA();
		GetHeight();

		r++;
		while (r - l > 1)
		{
			int mid = (l + r) >> 1;
			if (check(mid))
				l = mid;
			else
				r = mid;
		}
		if (l)
			statistic(l);
		else
			puts("?");
	}
}

int main()
{
	run();
	return 0;
}