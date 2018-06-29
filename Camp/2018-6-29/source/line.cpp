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
	putchar('\n');
}

const int mod = 998244353;
const int maxn = 4005;
int n, m;
int Catalan[maxn];
std::vector<std::pair<int, int> > edges;

#define RunInstance(x) delete new x
struct cheat
{
	cheat()
	{
		printOut(Catalan[n >> 1]);
	}
};
struct brute
{
	static const int maxN = 405;
	bool red[maxN][maxN];
	int f[maxN][maxN];
	int g[maxN][maxN];

	brute() : red(), f(), g()
	{
		for (int i = 0; i < edges.size(); i++)
			red[edges[i].first][edges[i].second] = true;

		for (int i = 1; i + 1 <= n; i += 1)
			f[i][i + 1] = g[i][i + 1] = 1 + red[i][i + 1];
		for (int len = 4; len <= n; len += 2)
			for (int l = 1; l + len - 1 <= n; l++)
			{
				int r = l + len - 1;
				f[l][r] = g[l][r] = (f[l + 1][r - 1] * (1 + red[l][r])) % mod;
				for (int k = l + 1; k + 1 < r; k += 2)
					f[l][r] = (f[l][r] + (LL)g[l][k] * f[k + 1][r]) % mod;
			}
		printOut(f[1][n]);
	}
};
struct work
{
	int seq[maxn];
	typedef std::vector<std::vector<int> > Graph;
	Graph G;
	int stack[maxn];

	int g[maxn][maxn];
	int temp[maxn];
	void DFS(int node)
	{
		for (int i = 0; i < G[node].size(); i++)
		{
			int to = G[node][i];
			DFS(to);
		}
		int size = 1;
		g[node][0] = 1;
		for (int i = 0; i < G[node].size(); i++)
		{
			int to = G[node][i];
			int sizeto = edges[to - 1].second - edges[to - 1].first + 1;
			sizeto >>= 1;
			LL sum = 0;
			for (int i = 0; i < sizeto; i++)
				sum = (sum + (LL)g[to][i] * Catalan[sizeto - 1 - i]) % mod;
			g[to][sizeto] = sum; // Ì×ÉÏ×îÍâ²ã

			sizeto++;
			int newsize = size + sizeto - 1;
			for (int j = 0; j < newsize; j++)
				temp[j] = 0;
			for (int j = 0; j < size; j++)
				for (int k = 0; k < sizeto; k++)
					temp[j + k] = (temp[j + k] + (LL)g[node][j] * g[to][k]) % mod;
			for (int j = 0; j < newsize; j++)
				g[node][j] = temp[j];
			size = newsize;
		}
	}

	work() : g()
	{
		std::memset(seq, -1, sizeof(seq));
		seq[0] = 0;
		seq[n + 1] = 0;
		for (int i = 0; i < edges.size(); i++)
		{
			seq[edges[i].first] = i + 1;
			seq[edges[i].second] = i + 1;
		}
		G.resize(edges.size() + 1);

		stack[0] = 0;
		stack[++stack[0]] = 0;
		for (int i = 1; i <= n; i++) if (~seq[i])
		{
			if (seq[i] == stack[stack[0]])
				stack[0]--;
			else
			{
				G[stack[stack[0]]].push_back(seq[i]);
				stack[++stack[0]] = seq[i];
			}
		}

		DFS(0);
		int ans = 0;
		for (int i = 0; i <= (n >> 1); i++)
			ans = (ans + (LL)g[0][i] * Catalan[(n >> 1) - i]) % mod;
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		int from = readIn();
		int to = readIn();
		if ((to - from + 1) & 1) continue;
		edges.push_back(std::make_pair(from, to));
	}
	Catalan[0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < i; j++)
			Catalan[i] = (Catalan[i] + (LL)Catalan[j] * Catalan[i - 1 - j]) % mod;

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("line.in", "r", stdin);
	freopen("line.out", "w", stdout);
#endif
	run();
	return 0;
}