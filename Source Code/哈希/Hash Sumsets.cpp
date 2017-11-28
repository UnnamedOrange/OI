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
typedef int INT;
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
	}
	while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	}
	while (length);
	putchar('\n');
}

const INT maxn = 1005;
INT n;
INT a[maxn];

struct unordered_map
{
	static const INT size = 1000007;
	struct hashNode
	{
		INT a;
		INT b;
		hashNode() : a(-1), b(-1) {}
		bool empty() const
		{
			return !~a;
		}
	} table[size];
	void insert(INT a, INT b)
	{
		INT sum = a + b;
		INT key = (sum % size + size) % size;
		while(~table[key].a)
		{
			if(table[key].a == a && table[key].b == b)
				return;
			key = (key + 1) % size;
		}
		table[key].a = a;
		table[key].b = b;
	}
	const hashNode query(INT c, INT d) const
	{
		INT sum = d - c;
		INT key = (sum % size + size) % size;
		while(~table[key].a)
		{
			if(table[key].a + table[key].b == sum && table[key].a != c && table[key].a != d && table[key].b != c && table[key].b != d)
				return table[key];

			key = (key + 1) % size;
		}
		return table[key];
	}
};

void run()
{
	while(n = readIn())
	{
		for(int i = 1; i <= n; i++)
			a[i] = readIn();
		std::sort(a + 1, a + 1 + n);
		unordered_map& map = *(new unordered_map);
		for(int i = 1; i <= n; i++)
			for(int j = i + 1; j <= n; j++)
				map.insert(a[i], a[j]);

		bool bOk = false;
		for(int i = n; i >= 1 && !bOk; i--)
			for(int j = 1; j <= n && !bOk; j++)
				if(i != j && !map.query(a[j], a[i]).empty())
				{
					printOut(a[i]);
					bOk = true;
				}

		if(!bOk) puts("no solution");

		delete &map;
	}
}

int main()
{
	run();
	return 0;
}
