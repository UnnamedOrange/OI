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

const INT maxn = 100005;
INT n, m;
INT sqrtN;
INT N;

INT S[32];
INT a[maxn];
INT buf[320][20005];
INT flag[maxn];

void init(INT x = 0)
{
	if (x > 10000) return;
	if (x)
		S[++S[0]] = x;
	init(x * 10 + 4);
	init(x * 10 + 7);
}

void run()
{
	init();
	std::sort(S + 1, S + 1 + S[0]);
	n = readIn();
	m = readIn();
	sqrtN = std::sqrt(n);

	for (int i = 1; i <= n; i++)
	{
		a[i] = readIn();
		buf[(i - 1) / sqrtN][a[i]]++;
	}

	while (m--)
	{
		char ins[10];
		scanf("%s", ins);
		if (ins[0] == 'c')
		{
			INT l = readIn();
			INT r = readIn();
			INT lInBlock = (l - 1) / sqrtN;
			INT lEnd = (lInBlock + 1) * sqrtN;
			INT rInBlock = (r - 1) / sqrtN;
			INT rBegin = rInBlock * sqrtN + 1;

			INT ans = 0;
			if (lInBlock == rInBlock)
			{
				for (int i = l; i <= r; i++)
				{
					if (std::binary_search(S + 1, S + 1 + S[0], a[i] + flag[lInBlock]))
						ans++;
				}
			}
			else
			{
				for (int i = l; i <= lEnd; i++)
				{
					if (std::binary_search(S + 1, S + 1 + S[0], a[i] + flag[lInBlock]))
						ans++;
				}
				for (int i = lInBlock + 1; i <= rInBlock - 1; i++)
				{
					for (int j = 1; j <= S[0]; j++)
						ans += buf[i][S[j] - flag[i]];
				}
				for (int i = rBegin; i <= r; i++)
				{
					if (std::binary_search(S + 1, S + 1 + S[0], a[i] + flag[rInBlock]))
						ans++;
				}
			}
			printOut(ans);
		}
		else if (ins[0] == 'a')
		{
			INT l = readIn();
			INT r = readIn();
			INT v = readIn();
			INT lInBlock = (l - 1) / sqrtN;
			INT lEnd = (lInBlock + 1) * sqrtN;
			INT rInBlock = (r - 1) / sqrtN;
			INT rBegin = rInBlock * sqrtN + 1;

			if (lInBlock == rInBlock)
			{
				for (int i = l; i <= r; i++)
				{
					buf[lInBlock][a[i]]--;
					a[i] += v;
					buf[lInBlock][a[i]]++;
				}
			}
			else
			{
				for (int i = l; i <= lEnd; i++)
				{
					buf[lInBlock][a[i]]--;
					a[i] += v;
					buf[lInBlock][a[i]]++;
				}
				for (int i = lInBlock + 1; i <= rInBlock - 1; i++)
				{
					flag[i] += v;
				}
				for (int i = rBegin; i <= r; i++)
				{
					buf[rInBlock][a[i]]--;
					a[i] += v;
					buf[rInBlock][a[i]]++;
				}
			}
		}
	}
}

int main()
{
	run();
	return 0;
}