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
}

const int maxn = int(1e6) + 5;
int n;
int k;
char str[maxn];

int buf_size = 128;
int buf[maxn];
int SA[maxn];
int x[maxn];
int y[maxn];
void GetSA()
{
	int *rank = x, *SA_second = y;
	for (int i = 0; i < n; i++)
		rank[i] = str[i];

	for (int i = 0; i < buf_size; i++) buf[i] = 0;
	for (int i = 0; i < n; i++) buf[rank[i]]++;
	for (int i = 1; i < buf_size; i++) buf[i] += buf[i - 1];
	for (int i = n - 1; ~i; i--)
		SA[--buf[rank[i]]] = i;

	for (int k = 1; k <= n; k <<= 1)
	{
		int t = 0;
		for (int i = n - k; i < n; i++) SA_second[t++] = i;
		for (int i = 0; i < n; i++) if (SA[i] >= k) SA_second[t++] = SA[i] - k;

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
			rank[SA[i]] = (preRank[SA[i]] == preRank[SA[i - 1]] &&
				SA[i] + k < n && SA[i - 1] + k < n &&
				preRank[SA[i] + k] == preRank[SA[i - 1] + k]) ? t - 1 : t++;
		if (t >= n) break;
		buf_size = t;
	}
}
int rank[maxn];
int height[maxn];
void GetHeight()
{
	for (int i = 0; i < n; i++)
		rank[SA[i]] = i;
	int same = 0;
	for (int i = 0; i < n; i++)
	{
		if (rank[i] == 0)
			same = 0;
		else
		{
			if (same) same--;
			int pre = SA[rank[i] - 1];
			while (i + same < n && pre + same < n && str[i + same] == str[pre + same])
				same++;
		}
		height[rank[i]] = same;
	}
}

struct Rect
{
	int height;
	int width;
	Rect() {}
	Rect(int height, int width) : height(height), width(width) {}
};
std::stack<Rect> s;
void solve()
{
	LL ans = 0;
	height[n] = 0;
	for (int i = 0; i <= n; i++)
	{
		int w = 0;
		while (!s.empty() && height[i] < s.top().height)
		{
			Rect t = s.top();
			s.pop();
			w += t.width;
			if (w >= k - 1)
			{
				if (!s.empty())
					ans += t.height - s.top().height;
				else
					ans += t.height;
			}
		}
		if (!s.empty() && s.top().height == height[i])
			s.top().width += w + 1;
		else
			s.push(Rect(height[i], w + 1));
	}
	printOut(ans);
}

void run()
{
	scanf("%s", str);
	n = strlen(str);
	k = readIn();
	GetSA();
	GetHeight();

	solve();
}

int main()
{
	run();
	return 0;
}