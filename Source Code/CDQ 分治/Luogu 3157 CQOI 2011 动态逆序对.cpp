#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <cassert>
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
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef long long INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
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

const int maxn = int(1e5) + 5;
int n, m;
int a[maxn];
int pos[maxn];
int isDel[maxn];
int nIns;
struct Instruction
{
	int time;
	int pos;
	int val;
	int ansIdx;
} ins[maxn];
LL ans[maxn];

struct BIT
{
	LL bit[maxn];
	static inline int lowbit(int x)
	{
		return x & -x;
	}
	BIT() : bit() {}
	void add(int pos, int x)
	{
		while (pos <= n)
		{
			bit[pos] += x;
			pos += lowbit(pos);
		}
	}
	int query(int pos)
	{
		int ret = 0;
		while (pos)
		{
			ret += bit[pos];
			pos ^= lowbit(pos);
		}
		return ret;
	}
	void clear(int pos)
	{
		while (pos <= n)
		{
			if (bit[pos]) bit[pos] = 0;
			else break;
			pos += lowbit(pos);
		}
	}
} bit;
Instruction temp[maxn];
void cdq1(int l, int r)
{
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	cdq1(l, mid); cdq1(mid + 1, r);
	int i = l, j = mid + 1, k = l;
	while (k <= r)
	{
		if (!(j <= r) || (i <= mid && ins[i].val < ins[j].val))
		{
			bit.add(ins[i].pos, 1);
			temp[k++] = ins[i++];
		}
		else
		{
			ans[ins[j].ansIdx] += bit.query(n) - bit.query(ins[j].pos);
			temp[k++] = ins[j++];
		}
	}
	for (i = l; i <= r; i++)
		ins[i] = temp[i];
	for (i = l; i <= r; i++)
		bit.clear(ins[i].pos);
}
bool comp(const Instruction& a, const Instruction& b)
{
	return a.time < b.time;
}
void cdq2(int l, int r)
{
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	cdq2(l, mid); cdq2(mid + 1, r);
	int i = l, j = mid + 1, k = l;
	while (k <= r)
	{
		if (!(j <= r) || (i <= mid && ins[i].val > ins[j].val))
		{
			bit.add(ins[i].pos, 1);
			temp[k++] = ins[i++];
		}
		else
		{
			ans[ins[j].ansIdx] += bit.query(ins[j].pos);
			temp[k++] = ins[j++];
		}
	}
	for (i = l; i <= r; i++)
		ins[i] = temp[i];
	for (i = l; i <= r; i++)
		bit.clear(ins[i].pos);
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 1; i <= n; i++)
		pos[a[i]] = i;
	for (int i = 1; i <= m; i++)
	{
		ins[m + 1 - i].time = m + 1 - i;
		isDel[ins[m + 1 - i].pos = pos[ins[m + 1 - i].val = readIn()]] = i;
		ins[m + 1 - i].ansIdx = i;
	}

	LL inv = 0;
	for (int i = 1; i <= n; i++)
	{
		LL t = bit.query(n) - bit.query(a[i]);
		if (!isDel[i])
		{
			bit.add(a[i], 1);
			inv += t;
		}
		else
			ans[isDel[i]] += t;
	}
	memset(bit.bit, 0, sizeof(bit.bit));
	for (int i = n; i >= 1; i--)
	{
		if (!isDel[i])
			bit.add(a[i], 1);
		else
			ans[isDel[i]] += bit.query(a[i]);
	}
	memset(bit.bit, 0, sizeof(bit.bit));

	cdq1(1, m);
	std::sort(ins + 1, ins + 1 + m, comp);
	cdq2(1, m);

	for (int i = m - 1; i >= 1; i--)
		ans[i] += ans[i + 1];
	for (int i = 1; i <= m; i++)
		printOut(inv + ans[i]);
}

int main()
{
	run();
	return 0;
}