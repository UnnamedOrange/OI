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
}

const INT maxn = 10000005;
const char* ans[] = { "Yes", "No" };
INT n, m;

INT isntPrime[maxn];
INT prime[664600];
void goSeive()
{
	isntPrime[0] = isntPrime[1] = true;
	for (int i = 2; i <= n; i++)
	{
		if (!isntPrime[i])
			prime[++prime[0]] = i;
		for (int j = 1; j <= prime[0]; j++)
		{
			if (i * prime[j] > n) break;
			isntPrime[i * prime[j]] = true;
			if (!(i % prime[j])) break;
		}
	}
}

void run()
{
	n = readIn();
	m = readIn();
	goSeive();
	while (m--)
		puts(ans[isntPrime[readIn()]]);
}

int main()
{
	run();
	return 0;
}
