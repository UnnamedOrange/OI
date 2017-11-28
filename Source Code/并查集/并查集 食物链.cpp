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
typedef long long INT;
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
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[12];
		INT length = 0;
		bool minus = x < 0;
		if (minus) x = -x;
		while (x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		if (minus) buffer[length++] = '-';
		do
		{
			putchar(buffer[--length]);
		} while (length);
	}
	putchar('\n');
}

const INT maxn = INT(5e4) + 5;
INT n, m;
struct DS
{
	INT parent[maxn * 3];
	DS(INT size)
	{
		for (int i = 1; i <= size; i++)
			parent[i] = i;
	}
	INT find(INT x)
	{
		if (x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}
	void unite(INT x, INT y)
	{
		parent[find(y)] = find(x);
	}
	bool judge(INT x, INT y)
	{
		return find(x) == find(y);
	}
};
#define RunInstance(x) delete new x
#define EAT(x) ((x) + n)
#define ENEMY(x) ((x) + (n << 1))
struct work
{
	DS ds;

	work() : ds(n * 3)
	{
		INT ans = 0;
		while (m--)
		{
			INT ins = readIn();
			INT x = readIn();
			INT y = readIn();
			if (ins == 1)
			{
				if (x > n || y > n || ds.judge(x, EAT(y)) || ds.judge(x, ENEMY(y)))
				{
					ans++;
					continue;
				}
				ds.unite(x, y);
				ds.unite(EAT(x), EAT(y));
				ds.unite(ENEMY(x), ENEMY(y));
			}
			else if (ins == 2)
			{
				if (x == y || x > n || y > n || ds.judge(x, y) || ds.judge(x, EAT(y)))
				{
					ans++;
					continue;
				}
				ds.unite(x, ENEMY(y));
				ds.unite(EAT(x), y);
				ds.unite(ENEMY(x), EAT(y));
			}
		}
		cout << ans << endl;
	}
};

void run()
{
	n = readIn();
	m = readIn();
	RunInstance(work);
}

int main()
{
	run();
	return 0;
}
