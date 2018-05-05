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
#define loop register int
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef LL INT_PUT;
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

const int maxn = int(3e5) + 5;
int n;
char str[maxn];
int a[maxn];

int SA[maxn];
int buf_size = 26;
int buf[maxn];
int x[maxn], y[maxn];
void GetSA()
{
	int *rank = x, *SA_second = y;
	for (loop i = 0; i < n; i++)
		rank[i] = str[i] - 'a';

	for (loop i = 0; i < n; i++) buf[rank[i]]++;
	for (loop i = 1; i < buf_size; i++) buf[i] += buf[i - 1];
	for (loop i = n - 1; ~i; i--) SA[--buf[rank[i]]] = i;

	for (int k = 1; k <= n; k <<= 1)
	{
		int t = 0;
		for (loop i = n - k; i < n; i++)
			SA_second[t++] = i;
		for (loop i = 0; i < n; i++)
			if (SA[i] >= k) SA_second[t++] = SA[i] - k;

		for (loop i = 0; i < buf_size; i++) buf[i] = 0;
		for (loop i = 0; i < n; i++) buf[rank[SA_second[i]]]++;
		for (loop i = 1; i < buf_size; i++) buf[i] += buf[i - 1];
		for (loop i = n; ~i; i--)
			SA[--buf[rank[SA_second[i]]]] = SA_second[i];

		int* oldRank = rank;
		std::swap(rank, SA_second);
		rank[SA[0]] = 0;
		t = 1;
		for (loop i = 1; i < n; i++)
			rank[SA[i]] = (oldRank[SA[i]] == oldRank[SA[i - 1]] &&
				SA[i] + k < n && SA[i - 1] + k < n &&
				oldRank[SA[i] + k] == oldRank[SA[i - 1] + k])
			? t - 1 : t++;
		if (t == n) break;
		buf_size = t;
	}
}

int rank[maxn];
int height[maxn];
void GetHeight()
{
	int same = 0;
	for (int i = 0; i < n; i++)
		rank[SA[i]] = i;

	for (int i = 0; i < n; i++)
	{
		if (same) same--;
		if (rank[i])
		{
			int pre = SA[rank[i] - 1];
			while (i + same < n && pre + same < n &&
				str[i + same] == str[pre + same])
				same++;
		}
		else
			same = 0;
		height[rank[i]] = same;
	}
}

int w[maxn];
std::vector<int> offline[maxn];

struct DS
{
	int parent[maxn];
	void init()
	{
		for (int i = 0; i < n; i++)
		{
			parent[i] = i;
		}
	}
} ds;

LL ans1[maxn], ans2[maxn];

void run()
{
	n = readIn();
	scanf("%s", str);
	for (int i = 0; i < n; i++)
		a[i] = readIn();

	GetSA();
	GetHeight();
	for (loop i = 0; i < n; i++)
		w[i] = a[SA[i]];
	for (loop i = n; i; i--)
		offline[height[i]].push_back(i);

	ds.init();

}

int main()
{
	run();
	return 0;
}