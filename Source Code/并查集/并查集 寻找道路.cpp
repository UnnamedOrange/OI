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
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT maxn = 100005;
INT n, m;
struct Road
{
	INT x;
	INT y;
	INT t;
} roads[maxn];
INT roadIdx[maxn];

bool comp(INT a, INT b)
{
	return roads[a].t < roads[b].t;
}

struct DS
{
	INT parent[1005];

	void init()
	{
		for (int i = 1; i <= n; i++) parent[i] = i;
	}

	INT find(INT x)
	{
		if (parent[x] == x) return x;
		return parent[x] = find(parent[x]);
	}

	bool unite(INT x, INT y)
	{
		INT px = find(x);
		INT py = find(y);
		if (px == py) return false;
		parent[py] = px;
		return true;
	}
} ds;

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		roads[i].x = readIn();
		roads[i].y = readIn();
		roads[i].t = readIn();
		roadIdx[i] = i;
	}
	std::sort(roadIdx + 1, roadIdx + 1 + m, comp);

	ds.init();
	for (int i = 1; i <= m; i++)
	{
		Road& r = roads[roadIdx[i]];
		n -= ds.unite(r.x, r.y);
		if (n == 1)
		{
			cout << r.t << endl;
			return;
		}
	}
	cout << -1 << endl;
}

int main()
{
	run();
	return 0;
}
