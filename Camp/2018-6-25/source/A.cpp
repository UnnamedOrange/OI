#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <functional>
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = int;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int mod = int(1e9) + 7;
const int maxn = int(1e6) + 5;
const int maxm = int(1e5) + 5;
int n, m;
int val[maxn];
struct Ins
{
	int type;
	int x, a;
	void read()
	{
		char buffer[5];
		scanf("%s", buffer);
		type = (buffer[0] == 'Q') + 1;
		x = readIn();
		a = readIn();
	}
} inss[maxm];

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		for (int i = 1; i <= m; i++)
		{
			const Ins& ins = inss[i];
			if (ins.type == 1)
			{
				val[ins.x] = ins.a;
			}
			else
			{
				if (ins.x > n)
				{
					for (int j = 1; j <= n; j++)
						putchar(val[j] + '0');
				}
				else
				{
					LL num = 0;
					for (int i = 1; i <= n; i++)
						(num *= 10) += val[i];
					LL q = 0;
					for (int i = 1; i <= ins.x; i++)
						(q *= 10) += ins.a;
					printOut(num % q % mod);
				}
			}
		}
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		char ch = getchar();
		while (!std::isdigit(ch))
			ch = getchar();
		val[i] = ch - '0';
	}
	m = readIn();
	for (int i = 1; i <= m; i++)
		inss[i].read();

	if (n <= 10)
		RunInstance(brute);
}

int main()
{
	run();
	return 0;
}