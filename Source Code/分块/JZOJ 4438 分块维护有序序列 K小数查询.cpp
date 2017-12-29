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

const INT maxn = 80005;
const INT maxi = 285;
INT n, q;
INT sqrtN, N;
INT a[maxn];
INT buf[maxi][maxi];
INT flag[maxi];
inline INT inB(INT x)
{
	return (x - 1) / sqrtN;
}

INT check(INT l, INT r, INT v)
{
	INT ret = 0;
	INT lInBlock = inB(l);
	INT rInBlock = inB(r);
	if (lInBlock == rInBlock)
	{
		for (int i = l; i <= r; i++)
		{
			ret += (a[i] + flag[lInBlock] <= v);
		}
	}
	else
	{
		INT lEnd = (lInBlock + 1) * sqrtN;
		INT rBegin = rInBlock * sqrtN + 1;
		for (int i = l; i <= lEnd; i++)
			ret += (a[i] + flag[lInBlock] <= v);
		for (int i = lInBlock + 1; i <= rInBlock - 1; i++)
			ret += std::upper_bound(buf[i] + 1, buf[i] + 1 + buf[i][0], v - flag[i]) - (buf[i] + 1);
		for (int i = rBegin; i <= r; i++)
			ret += (a[i] + flag[rInBlock] <= v);
	}
	return ret;
}
void rebuild(INT block)
{
	INT begin = block * sqrtN + 1;
	INT end = std::min(n, (block + 1) * sqrtN);
	INT* b = buf[block];
	b[0] = 0;
	for (int i = begin; i <= end; i++)
		b[++b[0]] = a[i];
	std::sort(b + 1, b + 1 + b[0]);
}

void run()
{
	n = readIn();
	sqrtN = std::sqrt(n);
	N = (n + sqrtN - 1) / sqrtN;
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 0; i < N; i++)
		rebuild(i);

	q = readIn();
	while (q--)
	{
		INT ins = readIn();
		INT l = readIn();
		INT r = readIn();
		INT x = readIn();
		if (ins == 1)
		{
			INT lInBlock = inB(l);
			INT rInBlock = inB(r);
			if (lInBlock == rInBlock)
			{
				for (int i = l; i <= r; i++)
					a[i] += x;
				rebuild(lInBlock);
			}
			else
			{
				INT lEnd = (lInBlock + 1) * sqrtN;
				INT rBegin = rInBlock * sqrtN + 1;
				for (int i = l; i <= lEnd; i++)
					a[i] += x;
				rebuild(lInBlock);
				for (int i = lInBlock + 1; i <= rInBlock - 1; i++)
					flag[i] += x;
				for (int i = rBegin; i <= r; i++)
					a[i] += x;
				rebuild(rInBlock);
			}
		}
		else if (ins == 2)
		{
			INT L = -5000000;
			INT R = 5000000;
			while (R - L > 0)
			{
				INT mid = L + ((R - L) >> 1);
				if (check(l, r, mid) < x)
				{
					L = mid + 1;
				}
				else
				{
					R = mid;
				}
			}
			printOut(L);
		}
	}
}

int main()
{
	run();
	return 0;
}