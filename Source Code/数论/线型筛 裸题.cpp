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
	char buffer[15];
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

INT n, m;
std::vector<INT> isPrime;

void seive_Onloglogn()
{
	INT to = std::sqrt(m);
	for (int i = 2; i <= to; i++)
		if (isPrime[i])
			for (int j = i * i; j <= m; j += i)
				isPrime[j] = false;
}
void seive_On()
{
	std::vector<INT> prime;
	prime.reserve(m);
	for (int i = 2; i <= m; i++)
	{
		if (isPrime[i]) prime.push_back(i);
		for (int j = 0; j < prime.size(); j++)
		{
			INT s = i * prime[j];
			if (s > m) break;
			isPrime[s] = false;
			if (!(i % prime[j])) break;
		}
	}
}
void goSum()
{
	for (int i = 1; i <= m; i++)
		isPrime[i] += isPrime[i - 1];
}

void run()
{
	n = readIn();
	m = readIn();
	isPrime.resize(m + 1, true);
	isPrime[0] = isPrime[1] = false;
	//seive_Onloglogn();
	seive_On();
	goSum();

	while (n--)
	{
		INT l = readIn();
		INT r = readIn();
		if (!(1 <= l && l <= r && r <= m))
			puts("Crossing the line");
		else
			printOut(isPrime[r] - isPrime[l - 1]);
	}
}

int main()
{
	run();
	return 0;
}
