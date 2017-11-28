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
typedef unsigned long long ULL;
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

const INT maxn = 10005;
INT n;
struct HashNode
{
	ULL val1;
	ULL val2;

	bool operator< (const HashNode& b) const
	{
		if (val1 != b.val1) return val1 < b.val1;
		return val2 < b.val2;
	}
	bool operator== (const HashNode& b) const
	{
		const HashNode& a = *this;
		return !(a < b) && !(b < a);
	}
	void next(char ch)
	{
		const INT p1 = 257;
		const INT mod1 = INT(1e9) + 7;
		const INT p2 = 263;
		const INT mod2 = INT(1e9) + 9;
		val1 = (p1 * val1 + ch) % mod1;
		val2 = (p2 * val2 + ch) % mod2;
	}
} hashVal[maxn];

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		char ch = getchar();
		while (!(ch > ' ' && ch < 127)) ch = getchar();
		while (ch > ' ' && ch < 127)
		{
			hashVal[i].next(ch);
			ch = getchar();
		}
	}
	std::sort(hashVal + 1, hashVal + 1 + n);
	printOut(std::unique(hashVal + 1, hashVal + 1 + n) - (hashVal + 1));
}

int main()
{
	run();
	return 0;
}
