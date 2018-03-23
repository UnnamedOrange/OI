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
	int link[maxn * 2];
	int next[maxn * 2][alphabet];
	int len[maxn * 2];
	int size;
	int last;
	static int code(char ch) { return ch - 'a'; }

public:
	SAM()
	{
		link[last = size++] = -1;
	}
	void extend(char ch)
	{
		int x = code(ch);
		int cur = size++;
		int p = last;
		last = cur;

		len[cur] = len[p] + 1;
		for (; ~p && !next[p][x]; p = link[p])
			next[p][x] = cur;
		if (!~p) return void(link[cur] = 0);
		int q = next[p][x];
		if (len[p] + 1 == len[q]) return void(link[cur] = q);
		int clone = size++;
		memcpy(next[clone], next[q], sizeof(next[clone]));
		link[clone] = link[q];
		len[clone] = len[p] + 1;
		link[cur] = link[q] = clone;
		for (; ~p && next[p][x] == q; p = link[p])
			next[p][x] = clone;
	}

private:
	int buf[maxn * 2];
	int sort[maxn * 2];
	ULL f[maxn * 2];
	ULL sum[maxn * 2];

public:
	ULL calc()
	{
		ULL ret = 0;
		for (int i = 1; i < size; i++)
		{
			ULL end = len[i];
			ULL begin = len[link[i]] + 1;
			ret += (begin + end) * (end - begin + 1) / 2;
		}
		return ret;
	}
} sam;

void run()
{
	scanf("%s", str);
	n = strlen(str);
	for (int i = 0; i < n; i++)
		sam.extend(str[i]);
	printf("%llu", sam.calc());
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