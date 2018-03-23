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
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;

const int maxn = int(3e6) + 5;
int n;
char str[maxn];

class SAM
{
	static const int alphabet = 26;
	struct Node
	{
		int len;
		int link;
		int next[alphabet];
	} nodes[maxn * 2];
	int size;
	int last;
	static int code(char ch) { return ch - 'a'; }

public:
	SAM() : size(), last(), buf()
	{
		nodes[last = size++].link = -1;
	}
	void extend(char ch)
	{
		int x = code(ch);
		int cur = size++;
		nodes[cur].len = nodes[last].len + 1;
		int p = last;
		last = cur;
		for (; ~p && !nodes[p].next[x]; p = nodes[p].link)
			nodes[p].next[x] = cur;
		if (!~p)
		{
			nodes[cur].link = 0;
			return;
		}
		int q = nodes[p].next[x];
		if (nodes[p].len + 1 == nodes[q].len)
		{
			nodes[cur].link = q;
			return;
		}
		int clone = size++;
		nodes[clone] = nodes[q];
		nodes[clone].len = nodes[p].len + 1;
		nodes[cur].link = nodes[q].link = clone;
		for (; ~p && nodes[p].next[x] == q; p = nodes[p].link)
			nodes[p].next[x] = clone;
	}

private:
	int buf[maxn * 2];
	int sort[maxn * 2];
	ULL f[maxn * 2];
	ULL sum[maxn * 2];

public:
	void radixSort()
	{
		for (int i = 0; i < size; i++) buf[nodes[i].len]++;
		for (int i = 1; i < size; i++) buf[i] += buf[i - 1];
		for (int i = size - 1; ~i; i--) sort[--buf[nodes[i].len]] = i;
	}
	ULL DP()
	{
		for (int i = size - 1; ~i; i--)
		{
			int node = sort[i];
			f[node] = 1;
			for (int j = 0; j < alphabet; j++)
			{
				if (int t = nodes[node].next[j])
				{
					f[node] += f[t];
					sum[node] += sum[t] + f[t];
				}
			}
		}
		return sum[0];
	}
} sam;

void run()
{
	scanf("%s", str);
	n = strlen(str);
	for (int i = 0; i < n; i++)
		sam.extend(str[i]);
	printf("%llu", (sam.radixSort(), sam.DP()));
}

int main()
{
#ifndef LOCAL
	freopen("prob3.in", "r", stdin);
	freopen("prob3.out", "w", stdout);
#endif
	run();
	return 0;
}