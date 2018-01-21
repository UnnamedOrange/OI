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
void printOut(long long x)
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

const INT maxn = 50005;
const INT maxN = 230;
INT lastans;
INT n, q;
INT sqrtN, N;
INT a[maxn];
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

INT inBlock[maxn];
INT lBegin[maxN];
INT rEnd[maxN];
void initBlocks()
{
	sqrtN = std::sqrt(n);
	N = (n + sqrtN - 1) / sqrtN;
	for (int i = 1; i <= n; i++)
	{
		INT t = inBlock[i] = (i - 1) / sqrtN;
		if (!lBegin[t])
			lBegin[t] = i;
		rEnd[t] = i;
	}
}

struct BIT
{
	INT bit[maxn];
	static inline INT lowbit(INT x)
	{
		return x & -x;
	}
	BIT() : bit() {}
	void inc(INT x, INT val)
	{
		while (x <= bound)
		{
			bit[x] += val;
			x += lowbit(x);
		}
	}
	INT query(INT x)
	{
		INT ret = 0;
		while (x)
		{
			ret += bit[x];
			x ^= lowbit(x);
		}
		return ret;
	}
	INT query(INT l, INT r)
	{
		return query(r) - query(l - 1);
	}
};
long long times[maxN][maxn];
long long ans[maxN][maxN];
void initAns()
{
	for (int i = 1; i <= n; i++)
		times[inBlock[i]][a[i]]++;
	for (int i = 1; i < N; i++)
		for (int j = 1; j <= bound; j++)
			times[i][j] += times[i - 1][j];
	for (int i = 0; i < N; i++)
		for (int j = 2; j <= bound; j++)
			times[i][j] += times[i][j - 1];

	for (int i = 0; i < N; i++)
	{
		long long t = 0;
		BIT bit;
		for (int j = lBegin[i]; j <= n; j++)
		{
			t += bit.query(a[j] + 1, bound);
			bit.inc(a[j], 1);
			if (j == rEnd[inBlock[j]])
				ans[i][inBlock[j]] = t;
		}
	}
}

INT temp[maxn];
INT buf[maxn];
long long p;
void mergeSort(INT l, INT r)
{
	if (l == r)
		return;
	INT mid = l + ((r - l) >> 1);
	mergeSort(l, mid);
	mergeSort(mid + 1, r);
	INT i = l, j = mid + 1, k = l;
	while (k <= r)
	{
		if (j > r || (i <= mid && buf[i] <= buf[j]))
		{
			temp[k++] = buf[i++];
		}
		else
		{
			temp[k++] = buf[j++];
			p += mid - i + 1;
		}
	}
	for (i = l; i <= r; i++)
		buf[i] = temp[i];
}
INT getPair()
{
	if (!buf[0]) return 0;
	p = 0;
	mergeSort(1, buf[0]);
	return p;
}

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	discretize();
	initBlocks();
	initAns();

	q = readIn();
	while (q--)
	{
		INT l = readIn() ^ lastans;
		INT r = readIn() ^ lastans;
		long long t = 0;
		if (inBlock[l] == inBlock[r])
		{
			buf[0] = 0;
			for (int i = l; i <= r; i++)
				buf[++buf[0]] = a[i];
			t += getPair();
		}
		else
		{
			t = ans[inBlock[l] + 1][inBlock[r] - 1];
			long long* right = times[inBlock[r] - 1];
			long long* left = times[inBlock[l]];
			for (int i = l, to = rEnd[inBlock[l]]; i <= to; i++)
				t += right[a[i] - 1] - left[a[i] - 1];
			for (int i = lBegin[inBlock[r]]; i <= r; i++)
				t += right[bound] - right[a[i] + 1 - 1] + left[bound] - left[a[i] + 1 - 1];

			buf[0] = 0;
			for (int i = l, to = rEnd[inBlock[l]]; i <= to; i++)
				buf[++buf[0]] = a[i];
			for (int i = lBegin[inBlock[r]]; i <= r; i++)
				buf[++buf[0]] = a[i];
			t += getPair();
		}
		printOut(lastans = t);
	}
}

int main()
{
	run();
	return 0;
}