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

const int maxn = int(1e5) + 5;
int n, m, k;
std::pair<int, int> origin[maxn];
using Graph = std::vector<std::vector<int>>;
Graph G;

int inDegree[maxn];

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	for (int i = 1; i <= m; i++)
	{
		origin[i].first = readIn();
		origin[i].second = readIn();
	}
	std::sort(origin + 1, origin + 1 + m);
	m = std::unique(origin + 1, origin + 1 + m) - (origin + 1);

	G.resize(n + 1);
	for (int i = 1; i <= m; i++)
		G[origin[i].first].push_back(origin[i].second);

	for (int i = 1; i <= m; i++)
		inDegree[origin[i].second]++;

	std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
	for (int i = 1; i <= n; i++)
		if (!inDegree[i])
			pq.push(i);

	std::vector<std::pair<int, int>> ans;
	std::vector<int> topo;
	int t = 0;
	for (int i = 1; i <= n; i++)
	{
		while (k && pq.size() > 1)
		{
			int top = pq.top();
			pq.pop();
			G[pq.top()].push_back(top);
			inDegree[top]++;
			ans.push_back(std::make_pair(pq.top(), top));
			k--;
			t++;
		}
		int node = pq.top();
		pq.pop();
		topo.push_back(node);
		for (int to : G[node])
			if (!(--inDegree[to]))
				pq.push(to);
	}
	for (int v : topo)
	{
		printOut(v);
		putchar(' ');
	}
	putchar('\n');
	printOut(t);
	putchar('\n');
	for (auto e : ans)
	{
		printOut(e.first);
		putchar(' ');
		printOut(e.second);
		putchar('\n');
	}
}

int main()
{
#ifndef LOCAL
	freopen("topo.in", "r", stdin);
	freopen("topo.out", "w", stdout);
#endif
	run();
	return 0;
}