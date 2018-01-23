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

const INT mod = INT(1e9) + 7;
const INT maxn = 100005;
INT n, q;
INT nSize;
INT nBlock;
INT a[maxn];
INT inv[maxn];
INT bound;
INT disc[maxn];
void discretize()
{
	for (int i = 1; i <= n; i++)
		disc[i] = a[i];
	std::sort(disc + 1, disc + 1 + n);
	bound = std::unique(disc + 1, disc + 1 + n) - (disc + 1);
	for (int i = 1; i <= n; i++)
		a[i] = std::lower_bound(disc + 1, disc + 1 + bound, a[i]) - disc;
}
INT Inv(INT x)
{
	INT ret = 1;
	INT y = mod - 2;
	while (y)
	{
		if (y & 1) ret = (long long)ret * x % mod;
		x = (long long)x * x % mod;
		y >>= 1;
	}
	return ret;
}

INT inBlocks[maxn];
void initBlocks()
{
	for (int i = 1; i <= n; i++)
	{
		inBlocks[i] = (i - 1) / nSize;
	}
}

struct Query
{
	INT l, r;
	INT ans;
	void read()
	{
		l = readIn();
		r = readIn();
	}
} querys[maxn];
INT idx[maxn];

INT times[maxn];
INT buf[maxn];
long long sum;
inline void in(INT j)
{
	if (times[a[j]]) sum = (sum + mod - buf[a[j]]) % mod;
	times[a[j]]++;
	buf[a[j]] = (long long)buf[a[j]] * disc[a[j]] % mod;
	sum = (sum + buf[a[j]]) % mod;
}
inline void out(INT j)
{
	sum = (sum + mod - buf[a[j]]) % mod;
	times[a[j]]--;
	buf[a[j]] = (long long)buf[a[j]] * inv[j] % mod;
	if (times[a[j]]) sum = (sum + buf[a[j]]) % mod;
}
void handle()
{
	for (int i = 1; i <= bound; i++)
		buf[i] = 1;
	INT cntL = 1;
	INT cntR = 1;
	times[a[1]] = 1;
	buf[a[1]] = disc[a[1]] % mod;
	sum = buf[a[1]];
	for (int i = 1; i <= q; i++)
	{
		Query& query = querys[idx[i]];
		INT l = query.l;
		INT r = query.r;
		INT& ans = query.ans;

		while (cntL > l)
		{
			cntL--;
			in(cntL);
		}
		while (cntR < r)
		{
			cntR++;
			in(cntR);
		}
		while (cntL < l)
		{
			out(cntL);
			cntL++;
		}
		while (cntR > r)
		{
			out(cntR);
			cntR--;
		}
		ans = sum;
	}
}

void run()
{
	n = readIn();
	q = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	nSize = std::sqrt(q);
	nBlock = (n + nSize - 1) / nSize;
	initBlocks();

	for (int i = 1; i <= n; i++)
		inv[i] = Inv(a[i]);
	discretize();

	for (int i = 1; i <= q; i++)
		querys[i].read();
	for (int i = 1; i <= q; i++)
		idx[i] = i;
	std::sort(idx + 1, idx + 1 + q,
		[](const INT& a, const INT& b)
	{
		const Query& x = querys[a];
		const Query& y = querys[b];
		if (inBlocks[x.l] != inBlocks[y.l])
			return inBlocks[x.l] < inBlocks[y.l];
		else
			return inBlocks[x.l] & 1 ? x.r > y.r : x.r < y.r;
	});

	handle();
	for (int i = 1; i <= q; i++)
		printOut(querys[i].ans);
}

int main()
{
	run();
	return 0;
}