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

const int maxn = int(1e5) + 5;
int n, m;
using Graph = std::vector<std::vector<int> >;
Graph G;

int f[maxn], bit[maxn];

void DFS(int node, int parent)
{
	f[node] = bit[node] = 0;
	int temp = 0;
	for (int i = 0; i < G[node].size(); i++)
	{
		int to = G[node][i];
		if (to == parent) continue;
		DFS(to, node);
		temp |= (bit[node] & bit[to]);
		bit[node] |= bit[to];
	}
	if (!bit[node]) bit[node] = 1;
	else
	{
		while ((1 << f[node]) < temp || (1 << f[node]) & bit[node])
			f[node]++;
		bit[node] = (bit[node] >> f[node] << f[node]) | (1 << f[node]);
	}
}

void run()
{
	n = readIn();
	G.resize(n + 1);
	for (int i = 2; i <= n; i++)
	{
		int from = readIn();
		int to = readIn();
		G[from].push_back(to);
		G[to].push_back(from);
	}
	DFS(1, 0);
	printOut(*std::max_element(f + 1, f + 1 + n));
}

int main()
{
#ifndef LOCAL
	freopen("jas.in", "r", stdin);
	freopen("jas.out", "w", stdout);
#endif
	run();
	return 0;
}