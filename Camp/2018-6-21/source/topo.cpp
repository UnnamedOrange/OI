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
int from[maxn];

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

	std::set<int> set;
	for (int i = 1; i <= n; i++)
		if (!inDegree[i])
			set.insert(i);

	int t = k;
	std::vector<std::pair<int, int>> ans;
	std::vector<int> topo;
	while (set.size())
	{
		int vertex = *set.begin();
		int c = 0;
		for (auto it = set.begin(); it != set.end(); it++)
		{
			vertex = *it;
			if (c == t && !from[*it])
				break;
			if (!from[*it]) c++;
		}
		for (auto it = set.begin(); *it != vertex; it = set.begin())
		{
			auto next = it;
			next++;
			G[*next].push_back(*it);
			if (!from[*it]) t--;
			from[*it] = *next;
			inDegree[*it]++;
			set.erase(it);
		}
		set.erase(set.begin());
		if (from[vertex])
			ans.push_back(std::make_pair(from[vertex], vertex));
		topo.push_back(vertex);
		for (int i = 0; i < G[vertex].size(); i++)
		{
			int to = G[vertex][i];
			if (!(--inDegree[to]))
				set.insert(to);
		}
	}
	for (int v : topo)
	{
		printOut(v);
		putchar(' ');
	}
	putchar('\n');
	printOut(k - t);
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