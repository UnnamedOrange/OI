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

const LL INF = (~(int(1) << (sizeof(int) * 8 - 1))) >> 1;
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
		for (loop i = n - 1; ~i; i--)
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
	int size[maxn];
	LL majorP[maxn];
	LL minorP[maxn];
	LL miniP[maxn];
	LL majorN[maxn];
	LL minorN[maxn];
	LL miniN[maxn];
	void init()
	{
		for (int i = 0; i < n; i++)
		{
			parent[i] = i;
			size[i] = 1;
			majorP[i] = -INF;
			minorP[i] = -INF;
			miniP[i] = INF;
			majorN[i] = INF;
			minorN[i] = INF;
			miniN[i] = -INF;

			if (a[SA[i]] >= 0)
				majorP[i] = miniP[i] = w[i];
			else
				majorN[i] = miniN[i] = w[i];
		}
	}
	int find(int x)
	{
		return x == parent[x] ? x : parent[x] = find(parent[x]);
	}
	template <typename C>
	static void update(LL& major, LL& minor, LL val)
	{
		if (C()(minor, val))
		{
			if (C()(major, val))
			{
				minor = major;
				major = val;
			}
			else
				minor = val;
		}
	}
	void unite(int x, int y)
	{
		int px = find(x);
		int py = find(y);
		if (px == py) return;
		if (size[px] < size[py])
			std::swap(px, py);
		parent[py] = px;
		size[px] += size[py];
		update<std::less<LL> >(majorP[px], minorP[px], majorP[py]);
		update<std::less<LL> >(majorP[px], minorP[px], minorP[py]);
		update<std::greater<LL> >(majorN[px], minorN[px], majorN[py]);
		update<std::greater<LL> >(majorN[px], minorN[px], minorN[py]);
		miniP[px] = std::min(miniP[px], miniP[py]);
		miniN[px] = std::min(miniN[px], miniN[py], std::greater<LL>());
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
	for (loop i = n - 1; i; i--)
		offline[height[i]].push_back(i);

	ds.init();
	LL cnt1 = 0, cnt2 = -INF * INF;
	for (int i = n - 1; ~i; i--)
	{
		for (int j = 0; j < offline[i].size(); j++)
		{
			int pos = offline[i][j];
			register LL t;

			t = ds.size[ds.find(pos)];
			cnt1 -= t * (t - 1) >> 1;
			t = ds.size[ds.find(pos - 1)];
			cnt1 -= t * (t - 1) >> 1;
			ds.unite(pos, pos - 1);
			t = ds.size[ds.find(pos)];
			cnt1 += t * (t - 1) >> 1;

			t = ds.find(pos);
			if (ds.majorP[t] >= 0 && ds.minorP[t] >= 0)
				cnt2 = std::max(cnt2, (LL)ds.majorP[t] * ds.minorP[t]);
			if (ds.majorN[t] < 0 && ds.minorN[t] < 0)
				cnt2 = std::max(cnt2, (LL)ds.majorN[t] * ds.minorN[t]);
			if (ds.miniP[t] >= 0 && ds.miniN[t] < 0)
				cnt2 = std::max(cnt2, ds.miniP[t] * ds.miniN[t]);
		}
		ans1[i] = cnt1;
		ans2[i] = cnt1 ? cnt2 : 0;
	}

	for (int i = 0; i < n; i++)
	{
		printOut(ans1[i]);
		putchar(' ');
		printOut(ans2[i]);
		putchar('\n');
	}
}

int main()
{
	run();
	return 0;
}