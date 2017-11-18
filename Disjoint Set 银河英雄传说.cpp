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
void printOut(INT x)
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
		}
		while(length);
	}
	putchar('\n');
}

const INT n = 30000;
struct DS
{
	std::vector<INT> parent;
	std::vector<INT> size;
	std::vector<INT> pos;
	
	DS() : parent(n + 1), size(n + 1), pos(n + 1)
	{
		for(int i = 1; i <= n; i++)
		{
			parent[i] = i;
			size[i] = 1;
			pos[i] = 0;
		}
	}
	
	INT find(INT x)
	{
		if(x == parent[x]) return x;
		INT anc = find(parent[x]);
		pos[x] += pos[parent[x]];
		return parent[x] = anc;
	}
	INT judge(INT x, INT y)
	{
		if(find(x) != find(y)) return -1;
		return std::abs(pos[x] - pos[y]) - 1;
	}
	void unite(INT x, INT y)
	{
		INT px = find(x);
		INT py = find(y);
		parent[px] = parent[py];
		pos[px] = size[py];
		size[py] += size[px];
	}
};

void run()
{
	DS ds;
	INT T = readIn();
	while (T--)
	{
		char ins;
		scanf(" %c ", &ins);
		INT x = readIn();
		INT y = readIn();
		if (ins == 'M')
		{
			ds.unite(x, y);
		}
		else if (ins == 'C')
		{
			printOut(ds.judge(x, y));
		}
	}
}

int main()
{
	run();
	return 0;
}
