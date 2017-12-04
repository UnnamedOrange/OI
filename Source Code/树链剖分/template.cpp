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
typedef long long INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
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
inline void printOut(INT x)
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
}

const INT maxn = INT(1e5) + 5;
INT n, m, r, mod;
INT origin[maxn];
struct Edge
{
	INT to;
	INT next;
} edges[maxn * 2];
INT head[maxn];
void addEdge(INT from, INT to)
{
	static INT i;
	i++;
	edges[i].to = to;
	edges[i].next = head[from];
	head[from] = i;
}

void run()
{
	n = readIn();
	m = readIn();
	r = readIn();
	mod = readIn();
	for (int i = 1; i <= n; i++)
		origin[i] = readIn();

	for (int i = 2; i <= n; i++)
	{
		INT u = readIn();
		INT v = readIn();
		addEdge(u, v);
		addEdge(v, u);
	}

	while (m--)
	{
		INT ins = readIn();
		if (ins == 1)
		{

		}
		else if (ins == 2)
		{

		}
		else if (ins == 3)
		{

		}
		else if (ins == 4)
		{

		}
	}
}

int main()
{
	run();
	return 0;
}