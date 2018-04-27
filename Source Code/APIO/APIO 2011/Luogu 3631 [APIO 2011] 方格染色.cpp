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

const int mod = int(1e9);
const int maxn = int(1e6) + 5;
int n, m, k;
int x[maxn];
int y[maxn];
int c[maxn];

struct DS
{
	int parent[maxn * 4];
	int color[maxn * 4];
	void clear(int size)
	{
		for (int i = 1; i <= size; i++)
			parent[i] = i;
		for (int i = 1; i <= size; i++)
			color[i] = -1;
	}
	int find(int x)
	{
		return x == parent[x] ? x : (x = find(parent[x]));
	}
	bool unite(int x, int y)
	{
		if (~color[find(x)] && ~color[find(y)] && color[find(x)] != color[find(y)])
			return false;
		color[find(x)] = std::max(color[find(x)], color[find(y)]);
		parent[find(y)] = find(x);
		return true;
	}
	bool judge(int x, int y)
	{
		return find(x) == find(y);
	}
} ds;

LL power(LL x, int y)
{
	LL ret = 1;
	while (y)
	{
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	bool bset[2] = {};
	for (int i = 1; i <= k; i++)
	{
		x[i] = readIn();
		y[i] = readIn();
		c[i] = readIn();
		if (x[i] == 1 && y[i] == 1)
			bset[c[i]] = true;
	}
	for (int i = 1; i <= k; i++)
	{
		x[i]--;
		y[i]--;
	}

	int ans = 0;
	int delta = n + m - 2;
#define THIS(x) (x)
#define ANTI(x) ((x) + delta)
	if (!bset[0])
	{
		bool bOk = true;
		ds.clear(delta << 1);
		for (int i = 1; i <= k; i++)
		{
			if (!x[i] && !y[i])
				continue;
			else if (!x[i])
			{
				if (~ds.color[ds.find(THIS(y[i]))] &&
					ds.find(THIS(y[i])) != c[i])
				{
					bOk = false;
					break;
				}
				ds.color[ds.find(THIS(y[i]))] = c[i];
				ds.color[ds.find(ANTI(y[i]))] = !c[i];
			}
			else if (!y[i])
			{
				if (~ds.color[ds.find(THIS(m - 1 + x[i]))] &&
					ds.find(THIS(m - 1 + x[i])) != c[i])
				{
					bOk = false;
					break;
				}
				ds.color[ds.find(THIS(m - 1 + x[i]))] = c[i];
				ds.color[ds.find(ANTI(m - 1 + x[i]))] = !c[i];
			}
			else
			{
				if ((x[i] & 1) && (y[i] & 1))
				{
					if (!ds.unite(THIS(m - 1 + x[i]), ANTI(y[i])) ||
						!ds.unite(ANTI(m - 1 + x[i]), THIS(y[i])) ||
						ds.judge(THIS(m - 1 + x[i]), ANTI(m - 1 + x[i])) ||
						ds.judge(THIS(y[i]), ANTI(y[i])))
					{
						bOk = false;
						break;
					}
				}
				else
				{
					if (!ds.unite(THIS(m - 1 + x[i]), THIS(y[i])) ||
						!ds.unite(ANTI(m - 1 + x[i]), ANTI(y[i])) ||
						ds.judge(THIS(m - 1 + x[i]), ANTI(m - 1 + x[i])) ||
						ds.judge(THIS(y[i]), ANTI(y[i])))
					{
						bOk = false;
						break;
					}
				}
			}
		}
		if (bOk)
		{
			int ex = 0;
			for (int i = 1; i <= (delta << 1); i++)
			{
				if (ds.parent[i] != i) continue;
				if (!~ds.color[i])
					ex++;
			}
			ex >>= 1;
			ans = (ans + power(2, ex)) % mod;
		}
	}
	if (!bset[1]) // copy and modify a !
	{
		bool bOk = true;
		ds.clear(delta << 1);
		for (int i = 1; i <= k; i++)
		{
			if (!x[i] && !y[i])
				continue;
			else if (!x[i])
			{
				if (~ds.color[ds.find(THIS(y[i]))] &&
					ds.find(THIS(y[i])) != c[i])
				{
					bOk = false;
					break;
				}
				ds.color[ds.find(THIS(y[i]))] = c[i];
				ds.color[ds.find(ANTI(y[i]))] = !c[i];
			}
			else if (!y[i])
			{
				if (~ds.color[ds.find(THIS(m - 1 + x[i]))] &&
					ds.find(THIS(m - 1 + x[i])) != c[i])
				{
					bOk = false;
					break;
				}
				ds.color[ds.find(THIS(m - 1 + x[i]))] = c[i];
				ds.color[ds.find(ANTI(m - 1 + x[i]))] = !c[i];
			}
			else
			{
				if (!((x[i] & 1) && (y[i] & 1)))
				{
					if (!ds.unite(THIS(m - 1 + x[i]), ANTI(y[i])) ||
						!ds.unite(ANTI(m - 1 + x[i]), THIS(y[i])) ||
						ds.judge(THIS(m - 1 + x[i]), ANTI(m - 1 + x[i])) ||
						ds.judge(THIS(y[i]), ANTI(y[i])))
					{
						bOk = false;
						break;
					}
				}
				else
				{
					if (!ds.unite(THIS(m - 1 + x[i]), THIS(y[i])) ||
						!ds.unite(ANTI(m - 1 + x[i]), ANTI(y[i])) ||
						ds.judge(THIS(m - 1 + x[i]), ANTI(m - 1 + x[i])) ||
						ds.judge(THIS(y[i]), ANTI(y[i])))
					{
						bOk = false;
						break;
					}
				}
			}
		}
		if (bOk)
		{
			int ex = 0;
			for (int i = 1; i <= (delta << 1); i++)
			{
				if (ds.parent[i] != i) continue;
				if (!~ds.color[i])
					ex++;
			}
			ex >>= 1;
			ans = (ans + power(2, ex)) % mod;
		}
	}
	printOut(ans);
}

int main()
{
	run();
	return 0;
}