#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
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
using std::cin;
using std::cout;
using std::endl;
typedef int INT;
INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxk = 55;
const INT maxn = 100005;
const INT maxm = 200005;
INT n, m, K, mod;
struct Edge
{
	INT to;
	INT cost;
	INT next;
} edges[maxm], edgesT[maxm];
INT head[maxn], headT[maxm]; //G and GT
INT count_;
void addEdge(INT from, INT to, INT cost)
{
	count_++;
	edges[count_].to = to;
	edges[count_].cost = cost;
	edges[count_].next = head[from];
	head[from] = count_;

	edgesT[count_].to = from;
	edgesT[count_].cost = cost;
	edgesT[count_].next = headT[to];
	headT[to] = count_;
}
INT d; //no use
INT minC; //for cheat

		  //a mess, so comment is needed

		  //shortest path, dis means 1 to others, disT means n to others
namespace SP
{
	INT dis[maxn];
	INT disT[maxn];
	bool vis[maxn];
	struct Queue
	{
		INT c[maxn];
		INT head, tail;
		Queue() : head(), tail() {}
		void clear()
		{
			head = tail = 0;
		}
		bool empty()
		{
			return head == tail;
		}
		void push(INT x)
		{
			c[tail] = x;
			tail = (tail + 1) % maxn;
		}
		INT front()
		{
			return c[head];
		}
		void pop()
		{
			head = (head + 1) % maxn;
		}
	} q;
	INT s;
	//bad code
	void SPFA()
	{
		memset(vis, 0, sizeof(vis));
		q.clear();
		q.push(1);
		dis[1] = 0;
		vis[1] = true;
		while (!q.empty())
		{
			INT from = q.front();
			q.pop();
			vis[from] = false;
			for (int i = head[from]; i; i = edges[i].next)
			{
				Edge& e = edges[i];
				INT to = e.to;
				INT c = e.cost;
				if (dis[from] + c < dis[to])
				{
					dis[to] = dis[from] + c;
					if (!vis[to])
					{
						q.push(to);
						vis[to] = true;
					}
				}
			}
		}

		memset(vis, 0, sizeof(vis));
		q.clear();
		q.push(n);
		disT[n] = 0;
		vis[n] = true;
		while (!q.empty())
		{
			INT from = q.front();
			q.pop();
			vis[from] = false;
			for (int i = headT[from]; i; i = edgesT[i].next)
			{
				Edge& e = edgesT[i];
				INT to = e.to;
				INT c = e.cost;
				if (disT[from] + c < disT[to])
				{
					disT[to] = disT[from] + c;
					if (!vis[to])
					{
						q.push(to);
						vis[to] = true;
					}
				}
			}
		}
	}
	INT goSP()
	{
		memset(dis, 0x3f, sizeof(dis));
		memset(disT, 0x3f, sizeof(disT));
		SPFA();
		return dis[n];
	}
};

#define RunInstance(x) delete new x
struct work
{
	INT topo[maxn];
	INT inDegree[maxn];
	bool vis[maxn];
	INT found;
	//if a vertex on a "0 ring" is valid (dis[i] + disT[i] <= dis[1] + K), print -1
	//use topo sort to find vertexes on "0 ring"
	void BFS() //topo sort
	{
		using namespace SP;
		for (int i = 1; i <= n; i++)
		{
			for (int j = head[i]; j; j = edges[j].next)
			{
				Edge& e = edges[j];
				INT to = e.to;
				INT cost = e.cost;
				if (dis[i] + cost == dis[to])
					inDegree[to]++;
			}
		}

		q.clear();
		for (int i = n; i >= 1; i--)
			if (!inDegree[i])
				q.push(i);

		while (!q.empty())
		{
			INT from = q.front();
			vis[from] = true;
			topo[++topo[0]] = from;
			found++;
			q.pop();
			for (int j = head[from]; j; j = edges[j].next)
			{
				Edge& e = edges[j];
				INT to = e.to;
				INT cost = e.cost;
				if (dis[from] + cost == dis[to])
				{
					inDegree[to]--;
					if (!inDegree[to])
						q.push(to);
				}
			}
		}
		if (found != n)
			for (int i = 1; i <= n; i++)
				if (!vis[i] && dis[i] + disT[i] <= dis[n] + K)
				{
					found = -1;
					return;
				}
	}

	INT f[maxk][maxn];
	work() : f(), vis(), found(), inDegree()
	{
		using namespace SP;
		topo[0] = 0;
		BFS();
		if (found == -1)
		{
			printOut(-1);
			return;
		}

		//otherwise, this is a DAG
		f[0][1] = 1;
		for (int k = 0; k <= K; k++)
		{
			for (int i = 1; i <= topo[0]; i++)
			{
				INT node = topo[i];
				for (int j = head[node]; j; j = edges[j].next)
				{
					Edge& e = edges[j];
					INT to = e.to;
					INT c = e.cost;
					INT s2 = k + dis[node] + c - dis[to];
					if (s2 <= K)
					{
						f[s2][to] = (f[s2][to] + f[k][node]) % mod;
					}
				}
			}
		}

		INT ans = 0;
		for (int i = 0; i <= K; i++)
			ans = (ans + f[i][n]) % mod;
		printOut(ans);
	}
};

void run()
{
	INT T = readIn();
	while (T--)
	{
		count_ = 0;
		memset(head, 0, sizeof(head));
		memset(headT, 0, sizeof(headT));
		n = readIn();
		m = readIn();
		K = readIn();
		mod = readIn();
		minC = INF;
		for (int i = 1; i <= m; i++)
		{
			INT u = readIn();
			INT v = readIn();
			INT c = readIn();
			minC = std::min(minC, c);
			addEdge(u, v, c);
		}
		d = SP::goSP();

		RunInstance(work);
	}
}

int main()
{
#ifndef LOCAL
	freopen("park.in", "r", stdin);
	freopen("park.out", "w", stdout);
#endif
	run();
	return 0;
}