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
}

const int digit = int(1e9);
const int maxn = 18005;

void readNum(int* rec)
{
	const int buffer_size = 80005;
	static char buffer[buffer_size];
	std::cin.getline(buffer, buffer_size);
	int length = strlen(buffer);
	int j = 9;
	const int e[] = { 1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8 };
	for (int i = length - 1; ~i; i--)
	{
		if (j == 9)
		{
			rec[0]++;
			j = 0;
		}
		rec[rec[0]] += (buffer[i] - '0') * e[j];
		j++;
	}
}

int n, m;
int a[maxn], b[maxn];
long long c[maxn];

void run()
{
	readNum(a);
	readNum(b);
	for (int i = 0, to = a[0] + b[0]; i < to; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			c[i] += (long long)a[j + 1] * b[i - j + 1];
			c[i + 1] += c[i] / digit;
			c[i] %= digit;
		}
	}
	int t = a[0] + b[0];
	while (t && !c[t])
		t--;
	printf("%lld", c[t]);
	t--;
	for (int i = t; ~i; i--)
		printf("%09lld", c[i]);
}

int main()
{
	run();
	return 0;
}
