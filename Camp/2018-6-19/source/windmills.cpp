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

const int maxn = int(1e4) + 5;
int n;
struct Flag
{
	int a, b;
	void read()
	{
		a = readIn();
		b = readIn();
	}
	bool operator<(const Flag& y) const
	{
		return a < y.a;
	}
} flags[maxn];
using Graph = std::vector<std::vector<int> >;

int stamp;
int dfn[maxn * 4];
int low[maxn * 4];
int N;
int belong[maxn * 4];
bool inStack[maxn * 4];
int stack[maxn * 4];
void Tarjan(const Graph& G, int node)
{
	dfn[node] = low[node] = ++stamp;
	inStack[node] = true;
	stack[++stack[0]] = node;
	for (int i = 0; i < G[node].size(); i++)
	{
		int to = G[node][i];
		if (!dfn[to])
		{
			Tarjan(G, to);
			low[node] = std::min(low[node], low[to]);
		}
		else if (inStack[to])
			low[node] = std::min(low[node], dfn[to]);
	}
	if (dfn[node] == low[node])
	{
		N++;
		int top;
		do
		{
			top = stack[stack[0]--];
			inStack[top] = false;
			belong[top] = N;
		} while (top != node);
	}
}
bool checkG(const Graph& G)
{
	stamp = N = 0;
	memset(dfn, 0, sizeof(int) * G.size());
	memset(low, 0, sizeof(int) * G.size());
	memset(belong, 0, sizeof(int) * G.size());
	memset(inStack, 0, sizeof(inStack[0]) * G.size());
	stack[0] = 0;
	for (int i = 1; i < G.size(); i++)
		if (!dfn[i])
			Tarjan(G, i);
	for (int i = 1; i <= n; i++)
		if (belong[i] == belong[i + n])
			return false;
	return true;
}

#define RunInstance(x) delete new x
struct brute
{
	int idx[maxn];

	Graph G;
	bool check(int ans)
	{
		G.clear();
		G.resize(2 * n + 1);
		int l, r;
		l = 1, r = 0;
		for (int i = 1; i <= n; i++)
		{
			while (r < n && flags[idx[r + 1]].b - flags[i].a < ans)
				r++;
			while (l <= n && flags[i].a - flags[idx[l]].b >= ans)
				l++;
			for (int j = l; j <= r; j++)
				G[i].push_back(idx[j]);
		}
		l = 1, r = 0;
		for (int i = 1; i <= n; i++)
		{
			while (r < n && flags[r + 1].a - flags[i].a < ans)
				r++;
			while (l <= n && flags[i].a - flags[l].a >= ans)
				l++;
			for (int j = l; j <= r; j++)
				if (i != j)
					G[i].push_back(n + j);
		}
		l = 1, r = 0;
		for (int i = 1; i <= n; i++)
		{
			while (r < n && flags[r + 1].a - flags[idx[i]].b < ans)
				r++;
			while (l <= n && flags[idx[i]].b - flags[l].a >= ans)
				l++;
			for (int j = l; j <= r; j++)
				G[n + idx[i]].push_back(n + j);
		}
		l = 1, r = 0;
		for (int i = 1; i <= n; i++)
		{
			while (r < n && flags[idx[r + 1]].b - flags[idx[i]].b < ans)
				r++;
			while (l <= n && flags[idx[i]].b - flags[idx[l]].b >= ans)
				l++;
			for (int j = l; j <= r; j++)
				if (i != j)
					G[n + idx[i]].push_back(idx[j]);
		}
		return checkG(G);
	}
	brute()
	{
		for (int i = 1; i <= n; i++)
			idx[i] = i;
		std::sort(idx + 1, idx + 1 + n,
			[](const int& x, const int& y)
		{
			return flags[x].b < flags[y].b;
		});

		int l = 0, r = int(1e9);
		while (r - l > 1)
		{
			int mid = (l + r) >> 1;
			if (check(mid))
				l = mid;
			else
				r = mid;
		}
		printOut(l);
	}
};
struct work
{
	int idx[maxn];

	Graph G;

	int build1(int l, int r)
	{
		if (l == r)
		{
			return idx[l];
		}
		int mid = (l + r) >> 1;
		int cnt = (n << 1) + mid;
		G[cnt].push_back(build1(l, mid));
		G[cnt].push_back(build1(mid + 1, r));
		return cnt;
	}
	int build2(int l, int r)
	{
		if (l == r)
		{
			return n + l;
		}
		int mid = (l + r) >> 1;
		int cnt = (n * 3 - 1) + mid;
		G[cnt].push_back(build2(l, mid));
		G[cnt].push_back(build2(mid + 1, r));
		return cnt;
	}
	int g_L, g_R, g_Pos;
	void link1(int l, int r)
	{
		int mid = (l + r) >> 1;
		if (g_L <= l && r <= g_R)
		{
			if (l == r)
				G[g_Pos].push_back(idx[l]);
			else
				G[g_Pos].push_back((n << 1) + mid);
			return;
		}
		if (g_L <= mid) link1(l, mid);
		if (g_R > mid) link1(mid + 1, r);
	}
	void link2(int l, int r)
	{
		int mid = (l + r) >> 1;
		if (g_L <= l && r <= g_R)
		{
			if (l == r)
				G[g_Pos].push_back(n + l);
			else
				G[g_Pos].push_back((n * 3 - 1) + mid);
			return;
		}
		if (g_L <= mid) link2(l, mid);
		if (g_R > mid) link2(mid + 1, r);
	}
	void link1(int l, int r, int pos)
	{
		g_L = l;
		g_R = r;
		g_Pos = pos;
		link1(1, n);
	}
	void link2(int l, int r, int pos)
	{
		g_L = l;
		g_R = r;
		g_Pos = pos;
		link2(1, n);
	}
	bool check(int ans)
	{
		G.clear();
		G.resize(4 * n - 1);
		build1(1, n);
		build2(1, n);
		int l, r;
		l = 1, r = 0;
		for (int i = 1; i <= n; i++)
		{
			while (r < n && flags[idx[r + 1]].b - flags[i].a < ans)
				r++;
			while (l <= n && flags[i].a - flags[idx[l]].b >= ans)
				l++;
			if (l <= r)
				link1(l, r, i);
		}
		l = 1, r = 0;
		for (int i = 1; i <= n; i++)
		{
			while (r < n && flags[r + 1].a - flags[i].a < ans)
				r++;
			while (l <= n && flags[i].a - flags[l].a >= ans)
				l++;
			if (l <= i && i <= r)
			{
				if (l <= i - 1)
					link2(l, i - 1, i);
				if (i + 1 <= r)
					link2(i + 1, r, i);
			}
			else if (l <= r)
				link2(l, r, i);
		}
		l = 1, r = 0;
		for (int i = 1; i <= n; i++)
		{
			while (r < n && flags[r + 1].a - flags[idx[i]].b < ans)
				r++;
			while (l <= n && flags[idx[i]].b - flags[l].a >= ans)
				l++;
			if (l <= r)
				link2(l, r, n + idx[i]);
		}
		l = 1, r = 0;
		for (int i = 1; i <= n; i++)
		{
			while (r < n && flags[idx[r + 1]].b - flags[idx[i]].b < ans)
				r++;
			while (l <= n && flags[idx[i]].b - flags[idx[l]].b >= ans)
				l++;
			if (l <= i && i <= r)
			{
				if (l <= i - 1)
					link1(l, i - 1, n + idx[i]);
				if (i + 1 <= r)
					link1(i + 1, r, n + idx[i]);
			}
			else if (l <= r)
				link1(l, r, n + idx[i]);
		}
		return checkG(G);
	}
	work()
	{
		for (int i = 1; i <= n; i++)
			idx[i] = i;
		std::sort(idx + 1, idx + 1 + n,
			[](const int& x, const int& y)
		{
			return flags[x].b < flags[y].b;
		});

		int l = 0, r = int(1e9);
		while (r - l > 1)
		{
			int mid = (l + r) >> 1;
			if (check(mid))
				l = mid;
			else
				r = mid;
		}
		printOut(l);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		flags[i].read();
	std::sort(flags + 1, flags + 1 + n);

	if (n <= 1000)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("windmills.in", "r", stdin);
	freopen("windmills.out", "w", stdout);
#endif
	run();
	return 0;
}