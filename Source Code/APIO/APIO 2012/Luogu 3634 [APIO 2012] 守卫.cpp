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
typedef int INT_PUT;
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
	putchar('\n');
}

const int maxn = int(1e5) + 5;
int n, m, k;
struct Area
{
	int l, r;
	Area() {}
	Area(int l, int r) :l(l), r(r) {}
};
int newIdx[maxn];
std::vector<Area> areas;

int ans[maxn];
void solve1() // n^2
{
	for (int i = 1; i <= n; i++)
	{
		bool bOk = false;
		int pre = -1;
		int cnt = 0;
		for (int j = 0; j < areas.size(); j++)
		{
			if (areas[j].l == i && areas[j].r == i)
			{
				bOk = true;
				break;
			}
			if (areas[j].l <= pre) continue;
			cnt++;
			if (areas[j].r == i)
				pre = areas[j].r - 1;
			else
				pre = areas[j].r;
		}
		if (bOk || cnt > k) ans[++ans[0]] = i;
	}
}
int f[maxn];
int left[maxn];
void solve2()
{
	for (int i = 0; i < areas.size(); i++)
		left[i] = areas[i].l;

	int pre, cnt;
	pre = n + 1;
	cnt = 0;
	for (int i = areas.size() - 1; ~i; i--)
	{
		if (pre > areas[i].r)
		{
			pre = areas[i].l;
			cnt++;
		}
		f[i] = cnt;
	}

	pre = -1;
	cnt = 0;
	for (int i = 0; i < areas.size(); i++)
	{
		const Area& a = areas[i];
		if (pre < a.l) // 只考虑已经选了的点
		{
			if (a.l == a.r)
				ans[++ans[0]] = a.l;
			else
			{
				int R = std::upper_bound(left, left + m, a.r - 1) - left; // 选了 r 左边那个点，即 r - 1
				if (cnt + 1 + f[R] > k)
					ans[++ans[0]] = a.r;
			}

			pre = a.r;
			cnt++;
		}
	}
}

int del[maxn];
void run()
{
	n = readIn();
	k = readIn();
	m = readIn();
	std::vector<Area> temp;
	for (int i = 1; i <= m; i++)
	{
		int l = readIn();
		int r = readIn();
		int c = readIn();
		if (!c)
		{
			del[l]++;
			del[r + 1]--;
		}
		else
		{
			temp.push_back(Area(l, r));
		}
	}
	for (int i = 2; i <= n; i++)
		del[i] += del[i - 1];
	for (int i = 1; i <= n; i++)
		if (!del[i])
			newIdx[++newIdx[0]] = i;
	for (int i = 0; i < temp.size(); i++)
	{
		Area& a = temp[i];
		a.l = std::lower_bound(newIdx + 1, newIdx + 1 + newIdx[0], a.l) - newIdx;
		a.r = std::upper_bound(newIdx + 1, newIdx + 1 + newIdx[0], a.r) - newIdx - 1;
		if (a.l <= a.r)
			areas.push_back(a);
	}
	temp = areas;
	areas.clear();
	std::sort(temp.begin(), temp.end(),
		[](const Area& a, const Area& b)
	{
		if (a.l != b.l) return a.l < b.l;
		return a.r > b.r;
	});
	for (int i = 0; i < temp.size(); i++)
	{
		const Area& a = temp[i];
		while (areas.size() && areas.back().r >= a.r)
			areas.pop_back();
		areas.push_back(a);
	}

	n = newIdx[0];
	m = areas.size();
	if (k == n) // 特判一下
	{
		for (int i = 1; i <= n; i++)
			printOut(newIdx[i]);
		return;
	}
	solve2();
	if (ans[0])
		for (int i = 1; i <= ans[0]; i++)
			printOut(newIdx[ans[i]]);
	else
		printOut(-1);
}

int main()
{
	run();
	return 0;
}