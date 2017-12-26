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
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = INT(1e5) + 5;
INT n, m;
INT size;
INT rmq[17][maxn];

void goRMQ()
{
	while (1 << (size + 1) < n) size++;
	for (int i = 1; i <= size; i++)
		for (int j = 1; j + (1 << i) - 1 <= n; j++)
			rmq[i][j] = std::max(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
}

INT query(INT l, INT r)
{
	INT length = r - l + 1;
	INT k = 0;
	while (1 << (k + 1) < length) k++;
	return std::max(rmq[k][l], rmq[k][r - (1 << k) + 1]);
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		rmq[0][i] = readIn();

	goRMQ();
	while (m--)
	{
		INT l = readIn();
		INT r = readIn();
		printOut(query(l, r));
	}
}

int main()
{
	run();
	return 0;
}
