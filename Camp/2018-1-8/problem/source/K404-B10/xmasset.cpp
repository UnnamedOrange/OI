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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
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
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

INT type;
INT n, T;
const INT bit = 12;
const INT maxk = (1 << bit) + 5;
INT count1[maxk];
INT pos[maxk];
std::vector<INT> code;

#define RunInstance(x) delete new x
struct A
{
	A()
	{
		while (T--)
		{
			INT x = readIn();
			INT y = readIn();
			printOut(pos[(code[x - 1] ^ code[y - 1]) & code[x - 1]]);
		}
	}
};
struct B
{
	B()
	{
		while (T--)
		{
			INT q = readIn();
			INT h = readIn();
			puts(((code[q - 1] >> (h - 1)) & 1) ? "yes" : "no");
		}
	}
};

void run()
{
	for (int i = 1; i < 1 << bit; i++)
		count1[i] = count1[i >> 1] + bool(i & 1);
	for (int i = 1; i < 1 << bit; i++)
		pos[i] = pos[i >> 1] + 1;
	for (int i = 1; i < 1 << bit; i++)
		if (count1[i] == bit / 2)
			code.push_back(i);

	type = readIn();
	n = readIn();
	T = readIn();
	if (type == 1) RunInstance(A);
	else if (type == 2) RunInstance(B);
}

int main()
{
	run();
	return 0;
}