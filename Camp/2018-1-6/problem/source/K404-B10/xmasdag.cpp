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
#include <list>
typedef long long INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while(!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if(ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if(minus) a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	if(x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
	}
	while(x /= 10);
	do
	{
		putchar(buffer[--length]);
	}
	while(length);
	putchar('\n');
}

const INT mod = 998244353;
const INT maxn = 100005;
const INT maxm = 200005;
const INT maxk = 505;
INT n, m, k;
struct Graph
{
	INT i;
	struct Edge
	{
		INT to;
		INT next;
	} edges[maxm];
	INT head[maxn];
	Graph() : i(), head() {}
	void addEdge(INT from, INT to)
	{
		i++;
		edges[i].to = to;
		edges[i].next = head[from];
		head[from] = i;
	}
#define wander(G, node) for(int i = G.head[node]; i; i = G.edges[i].next)
#define DEF(G) const Graph::Edge& e = G.edges[i]; INT to = e.to
} G;

INT topo[maxn];
INT inDegree[maxn];
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
		c[tail++] = x;
	}
	INT front()
	{
		return c[head];
	}
	void pop()
	{
		head++;
	}
} q;
void topoSort()
{
	topo[0] = 0;
	for(int i = 1; i <= n; i++)
		if(!inDegree[i])
			q.push(i);
	while(!q.empty())
	{
		INT from = q.front();
		q.pop();
		topo[++topo[0]] = from;
		wander(G, from)
		{
			DEF(G);
			inDegree[to]--;
			if(!inDegree[to])
				q.push(to);
		}
	}
}
INT power(INT x, INT y)
{
	INT ret = 1;
	while(y)
	{
		if(y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
INT C[maxk][maxk];

#define RunInstance(x) delete new x
struct cheat
{
	INT c[maxn];
	INT f[maxn];

	cheat() : c(), f()
	{
		c[1] = 1;
		for(int i = 1; i <= topo[0]; i++)
		{
			INT from = topo[i];
			wander(G, from)
			{
				DEF(G);
				f[to] = (f[to] + f[from] + c[from]) % mod;
				c[to] = (c[to] + c[from]) % mod;
			}
		}
		for(int i = 1; i <= n; i++)
			printOut(f[i]);
	}
};
struct brute
{
	static const INT maxN = 2005;
	INT f[maxN][maxN];
	INT ans[maxN];
	INT buf[maxN];

	brute() : f(), ans()
	{
		f[1][0] = 1;
		for(int i = 1; i <= topo[0]; i++)
		{
			INT from = topo[i];
			wander(G, from)
			{
				DEF(G);
				for(int j = 0; j < n; j++)
					if(const INT& t = f[from][j])
						f[to][j + 1] = (f[to][j + 1] + t) % mod;
			}
		}
		for(int i = 1; i <= n; i++)
			buf[i] = power(i, k);
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				ans[i] = (ans[i] + f[i][j] * buf[j] % mod) % mod;
		for(int i = 1; i <= n; i++)
			printOut(ans[i]);
	}
};
struct brute2
{
	static const INT maxK = 35;
	INT f[maxn][maxK];

	brute2() : f()
	{
		f[1][0] = 1;
		for(int i = 1; i <= topo[0]; i++)
		{
			INT from = topo[i];
			wander(G, from)
			{
				DEF(G);
				for(int j = 0; j <= k; j++)
					for(int l = 0; l <= j; l++)
						f[to][j] = (f[to][j] + C[j][l] * f[from][j - l] % mod) % mod;
			}
		}
		for(int i = 1; i <= n; i++)
			printOut(f[i][k]);
	}
};
struct work
{
	work()
	{

	}
};

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	for(int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		inDegree[to]++;
		G.addEdge(from, to);
	}
	topoSort();
	C[0][0] = 1;
	for(int i = 1; i <= k; i++)
	{
		C[i][0] = 1;
		for(int j = 1; j <= k; j++)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	}

	if(k == 1)
		RunInstance(cheat);
	else if(n <= 2000 && m <= 5000)
		RunInstance(brute);
	else if(k <= 30)
		RunInstance(brute2);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("xmasdag.in", "r", stdin);
	freopen("xmasdag.out", "w", stdout);
#endif
	run();
	return 0;
}
