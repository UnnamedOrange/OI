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
	putchar('\n');
}

const LL INF = (~(LL(1) << (sizeof(LL) * 8 - 1))) >> 1;
const int maxn = 1005;
int sx, sy, tx, ty;
int n;
struct Rect
{
	int x1, y1, x2, y2;
	void read()
	{
		x1 = readIn();
		y1 = readIn();
		x2 = readIn();
		y2 = readIn();
		if (x1 > x2) std::swap(x1, x2);
		if (y1 > y2) std::swap(y1, y2);
	}
} r[maxn];

struct Edge
{
	int to;
	int cost;
	Edge() {};
	Edge(int to, int cost) : to(to), cost(cost) {}
};
std::vector<std::vector<Edge> > G;
void addEdge(int from, int to, int cost)
{
	G[from].push_back(Edge(to, cost));
	G[to].push_back(Edge(from, cost));
}
int cnt;
struct Vertex
{
	int idx;
	int val;
	Vertex() {}
	Vertex(int idx, int val) : idx(idx), val(val) {}
	bool operator<(const Vertex& b) const
	{
		return val < b.val;
	}
};
enum
{
	DOWN, UP, LEFT, RIGHT
};
std::vector<std::vector<Vertex> > V[4]; // down up left right

void rayup(int idxv, int x, int y)
{
	int idx = -1;
	for (int i = 1; i <= n; i++)
	{
		if (r[i].y1 < y || !(r[i].x1 <= x && x <= r[i].x2)) continue;
		if (!~idx || r[i].y1 < r[idx].y1)
		{
			idx = i;
		}
	}
	if (idx != -1)
	{
		++cnt;
		G.push_back(std::vector<Edge>());
		V[DOWN][idx].push_back(Vertex(cnt, x));
		int cost = r[idx].y1 - y;
		assert(cost >= 0);
		addEdge(idxv, cnt, cost);
	}
}
void raydown(int idxv, int x, int y)
{
	int idx = -1;
	for (int i = 1; i <= n; i++)
	{
		if (r[i].y2 > y || !(r[i].x1 <= x && x <= r[i].x2)) continue;
		if (!~idx || r[i].y2 > r[idx].y2)
		{
			idx = i;
		}
	}
	if (idx != -1)
	{
		++cnt;
		G.push_back(std::vector<Edge>());
		V[UP][idx].push_back(Vertex(cnt, x));
		int cost = y - r[idx].y2;
		assert(cost >= 0);
		addEdge(idxv, cnt, cost);
	}
}
void rayright(int idxv, int x, int y)
{
	int idx = -1;
	for (int i = 1; i <= n; i++)
	{
		if (r[i].x1 < x || !(r[i].y1 <= y && y <= r[i].y2)) continue;
		if (!~idx || r[i].x1 < r[idx].x1)
		{
			idx = i;
		}
	}
	if (idx != -1)
	{
		++cnt;
		G.push_back(std::vector<Edge>());
		V[LEFT][idx].push_back(Vertex(cnt, y));
		int cost = r[idx].x1 - x;
		assert(cost >= 0);
		addEdge(idxv, cnt, cost);
	}
}
void rayleft(int idxv, int x, int y)
{
	int idx = -1;
	for (int i = 1; i <= n; i++)
	{
		if (r[i].x2 > x || !(r[i].y1 <= y && y <= r[i].y2)) continue;
		if (!~idx || r[i].x2 > r[idx].x2)
		{
			idx = i;
		}
	}
	if (idx != -1)
	{
		++cnt;
		G.push_back(std::vector<Edge>());
		V[RIGHT][idx].push_back(Vertex(cnt, y));
		int cost = x - r[idx].x2;
		assert(cost >= 0);
		addEdge(idxv, cnt, cost);
	}
}
void buildGraph()
{
	for (int i = 0; i < 4; i++)
	{
		V[i].clear();
		V[i].resize(n + 1);
	}
	G.clear();
	G.resize((n << 2) + 2);
	cnt = G.size() - 1;

	int idxs = 0;
	int idxt = (n << 2) + 1;

#define PP1(x) (x)
#define PP2(x) ((x) + n)
#define PP3(x) ((x) + (n << 1))
#define PP4(x) ((x) + n * 3)
#define P1(x) PP1(x), r[(x)].x1, r[(x)].y2
#define P2(x) PP2(x), r[(x)].x2, r[(x)].y2
#define P3(x) PP3(x), r[(x)].x2, r[(x)].y1
#define P4(x) PP4(x), r[(x)].x1, r[(x)].y1

	rayup(idxs, sx, sy);
	rayup(idxt, tx, ty);
	for (int i = 1; i <= n; i++)
	{
		rayup(P1(i));
		rayup(P2(i));
	}

	raydown(idxs, sx, sy);
	raydown(idxt, tx, ty);
	for (int i = 1; i <= n; i++)
	{
		raydown(P3(i));
		raydown(P4(i));
	}

	rayright(idxs, sx, sy);
	rayright(idxt, tx, ty);
	for (int i = 1; i <= n; i++)
	{
		rayright(P2(i));
		rayright(P3(i));
	}

	rayleft(idxs, sx, sy);
	rayleft(idxt, tx, ty);
	for (int i = 1; i <= n; i++)
	{
		rayleft(P4(i));
		rayleft(P1(i));
	}

	for (int i = 1; i <= n; i++)
	{
		std::vector<Vertex>& down = V[DOWN][i];
		if (down.size())
		{
			std::sort(down.begin(), down.end());
			addEdge(PP4(i), down.front().idx, down.front().val - r[i].x1);
			addEdge(PP3(i), down.back().idx, r[i].x2 - down.back().val);
			for (int i = 1; i < down.size(); i++)
				addEdge(down[i - 1].idx, down[i].idx, down[i].val - down[i - 1].val);
		}
		else
		{
			int cost = r[i].x2 - r[i].x1;
			addEdge(PP3(i), PP4(i), cost);
		}

		std::vector<Vertex>& up = V[UP][i];
		if (up.size())
		{
			std::sort(up.begin(), up.end());
			addEdge(PP1(i), up.front().idx, up.front().val - r[i].x1);
			addEdge(PP2(i), up.back().idx, r[i].x2 - up.back().val);
			for (int i = 1; i < up.size(); i++)
				addEdge(up[i - 1].idx, up[i].idx, up[i].val - up[i - 1].val);
		}
		else
		{
			int cost = r[i].x2 - r[i].x1;
			addEdge(PP1(i), PP2(i), cost);
		}

		std::vector<Vertex>& right = V[RIGHT][i];
		if (right.size())
		{
			std::sort(right.begin(), right.end());
			addEdge(PP3(i), right.front().idx, right.front().val - r[i].y1);
			addEdge(PP2(i), right.back().idx, r[i].y2 - right.back().val);
			for (int i = 1; i < right.size(); i++)
				addEdge(right[i - 1].idx, right[i].idx, right[i].val - right[i - 1].val);
		}
		else
		{
			int cost = r[i].y2 - r[i].y1;
			addEdge(PP2(i), PP3(i), cost);
		}

		std::vector<Vertex>& left = V[LEFT][i];
		if (left.size())
		{
			std::sort(left.begin(), left.end());
			addEdge(PP4(i), left.front().idx, left.front().val - r[i].y1);
			addEdge(PP1(i), left.back().idx, r[i].y2 - left.back().val);
			for (int i = 1; i < left.size(); i++)
				addEdge(left[i - 1].idx, left[i].idx, left[i].val - left[i - 1].val);
		}
		else
		{
			int cost = r[i].y2 - r[i].y1;
			addEdge(PP1(i), PP4(i), cost);
		}
	}
}

struct HeapNode
{
	int idx;
	LL dis;
	HeapNode() {}
	HeapNode(int idx, LL dis) : idx(idx), dis(dis) {}
	bool operator<(const HeapNode& b) const
	{
		return dis > b.dis;
	}
};
LL Dijkstra()
{
	std::priority_queue<HeapNode> pq;
	std::vector<LL> dis(cnt + 1, INF);
	dis[0] = 0;
	pq.push(HeapNode(0, 0));
	while (!pq.empty())
	{
		HeapNode from = pq.top();
		pq.pop();
		if (from.dis > dis[from.idx]) continue;
		for (int i = 0; i < G[from.idx].size(); i++)
		{
			const Edge& e = G[from.idx][i];
			if (from.dis + e.cost < dis[e.to])
			{
				dis[e.to] = from.dis + e.cost;
				pq.push(HeapNode(e.to, dis[e.to]));
			}
		}
	}
	return dis[(n << 2) + 1] >= INF ? -1 : dis[(n << 2) + 1];
}

void run()
{
	int T = readIn();
	while (T--)
	{
		sx = readIn();
		sy = readIn();
		tx = readIn();
		ty = readIn();
		n = readIn();

		for (int i = 1; i <= n; i++)
			r[i].read();

		if (sx == tx)
		{
			bool bOk = true;
			int d1 = std::min(sy, ty); // об
			int d2 = std::max(sy, ty); // ио
			for (int i = 1; i <= n; i++)
			{
				if (r[i].x1 < sx && r[i].x2 > sx && !(r[i].y2 <= d1 || r[i].y1 >= d2))
				{
					bOk = false;
					break;
				}
			}
			if (bOk)
			{
				printOut(std::abs(sy - ty));
				continue;
			}
		}
		else if (sy == ty)
		{
			bool bOk = true;
			int d1 = std::min(sy, ty); // вС
			int d2 = std::max(sy, ty); // ср
			for (int i = 1; i <= n; i++)
			{
				if (r[i].y1 < sy && r[i].y2 > sy && !(r[i].x2 <= d1 || r[i].x1 >= d2))
				{
					bOk = false;
					break;
				}
			}
			if (bOk)
			{
				printOut(std::abs(sx - tx));
				continue;
			}
		}

		buildGraph();
		LL ans = Dijkstra();
		if (ans >= 0) printOut(ans);
		else puts("No Path");
	}
}

int main()
{
	run();
	return 0;
}