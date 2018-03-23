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

const int maxn = 105;
const int maxm = 505;
int n, x, y;
struct NetworkFlow
{
	int s, t;
	struct Edge
	{
		int from, to, flow, cap;
		double cost;
		Edge() {}
		Edge(int from, int to, int cap, double cost) : flow(), from(from), to(to), cap(cap), cost(cost) {}
	};
	std::vector<Edge> edges;
	std::vector<std::vector<int> > G;

	NetworkFlow() {}
	void addEdge(int from, int to, int cap, double cost)
	{
		edges.push_back(Edge(from, to, cap, cost));
		edges.push_back(Edge(to, from, 0, -cost));
		int i = edges.size();
		G[from].push_back(i - 2);
		G[to].push_back(i - 1);
	}

	std::vector<bool> inQ;
	std::queue<int> q;
	std::vector<double> dis;
	std::vector<int> pre;
	std::vector<int> opt;
	bool Bellman_Ford(double& cost)
	{
		inQ.clear();
		inQ.resize(n + 2);
		dis.clear();
		dis.resize(n + 2, 1e100);
		opt.clear();
		opt.resize(n + 2, 0);
		opt[s] = n * 100;
		q.push(s);
		inQ[s] = true;
		dis[s] = 0;
		pre.resize(n + 2);
		while (!q.empty())
		{
			int from = q.front();
			q.pop();
			inQ[from] = false;
			for (int i = 0; i < int(G[from].size()); i++)
			{
				const Edge& e = edges[G[from][i]];
				if (e.cap > e.flow && e.cost + dis[from] < dis[e.to])
				{
					dis[e.to] = dis[from] + e.cost;
					opt[e.to] = std::min(opt[from], e.cap - e.flow);
					pre[e.to] = G[from][i];
					if (!inQ[e.to])
					{
						q.push(e.to);
						inQ[e.to] = true;
					}
				}
			}
		}
		if (!opt[t]) return false;
		cost += opt[t] * dis[t];
		for (int u = t; u != s; u = edges[pre[u]].from)
		{
			edges[pre[u]].flow += opt[t];
			edges[pre[u] ^ 1].flow -= opt[t];
		}
		return true;
	}
	double MCMF()
	{
		double cost = 0;
		while (Bellman_Ford(cost));
		return cost;
	}
};
int pt[maxn][2];
std::vector<std::vector<int> > G;
int count_[maxn];

void run()
{
	while (n = readIn())
	{
		G.clear();
		G.resize(n + 1);
		x = readIn();
		y = readIn();
		for (int i = 1; i <= n; i++)
		{
			pt[i][0] = readIn();
			pt[i][1] = readIn();
			while (int to = readIn())
				G[i].push_back(to);
		}

		NetworkFlow nf;
		nf.s = 0;
		nf.t = n + 1;
		nf.G.resize(n + 2);

		double accum = 0;
		memset(count_, 0, sizeof(count_));
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j < G[i].size(); j++)
			{
				int to = G[i][j];
				double cost = std::sqrt(std::pow(pt[i][0] - pt[to][0], 2) + std::pow(pt[i][1] - pt[to][1], 2));
				cost = cost * x - y;
				cost = -cost;
				if (cost >= 0)
					nf.addEdge(i, to, 1, cost);
				else
				{
					count_[to]++;
					count_[i]--;
					accum += cost;
					nf.addEdge(to, i, 1, -cost);
				}
			}
		}
		for (int i = 1; i <= n; i++)
			if (count_[i] > 0)
				nf.addEdge(nf.s, i, count_[i], 0);
			else if (count_[i] < 0)
				nf.addEdge(i, nf.t, -count_[i], 0);
		double ans = -(accum + nf.MCMF());
		if (ans <= 0) ans = 0;
		static int T;
		printf("Case %d: %.2lf\n", ++T, ans);
	}
}

int main()
{
	run();
	return 0;
}