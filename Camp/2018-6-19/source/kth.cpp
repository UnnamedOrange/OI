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
#define EAX register int
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = int;
INT_PUT readIn()
{
	EAX a = 0; EAX positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(EAX x)
{
	char buffer[20]; EAX length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

#define min(a, b) ((a) < (b) ? (a) : (b))

const int INF = (~(int(1) << (sizeof(int) * 8 - 1))) >> 1;
const int maxn = int(8e4) + 5;
int n, m;
int a[maxn];

const int maxN = 500;
int sqrtN = maxN, N;
int inBlock[maxn];
int lBegin[maxN];
int rEnd[maxN];

int tag[maxN];
int sort[maxn];
int temp[maxN * 2];
void initBlocks()
{
	N = (n - 1) / sqrtN + 1;
	for (EAX i = 1; i <= n; i++)
	{
		EAX ib = inBlock[i] = (i - 1) / sqrtN;
		if (!lBegin[ib])
			lBegin[ib] = i;
		rEnd[ib] = i;
	}
	std::memcpy(sort, a, sizeof(sort));
	for (EAX i = 0; i < N; i++)
		std::sort(sort + lBegin[i], sort + rEnd[i] + 1);
}

void Rebuild(int l, int r, int x)
{
	EAX ib = inBlock[l];
	EAX t = tag[ib];
	if (x >= t) return;
	if (t != INF)
	{
		for (EAX i = lBegin[ib]; i < l; i++)
			a[i] = min(a[i], t);
		for (EAX i = l; i <= r; i++)
			a[i] = min(a[i], x);
		for (EAX i = r + 1, to = rEnd[ib]; i <= to; i++)
			a[i] = min(a[i], t);
	}
	else
	{
		for (EAX i = l; i <= r; i++)
			a[i] = min(a[i], x);
	}
	EAX L = lBegin[ib];
	EAX R = rEnd[ib];
	std::memcpy(sort + L, a + L, sizeof(int) * (R - L + 1));
	std::sort(sort + L, sort + R + 1);
	tag[ib] = INF;
}

void run()
{
	n = readIn();
	m = readIn();
	for (EAX i = 1; i <= n; i++)
		a[i] = readIn();
	initBlocks();
	for (EAX i = 0; i < N; i++)
		tag[i] = INF;

	while (m--)
	{
		int type = readIn();
		int l = readIn();
		int r = readIn();
		int x = readIn();

		if (type == 1)
		{
			if (inBlock[l] == inBlock[r])
			{
				Rebuild(l, r, x);
			}
			else
			{
				for (EAX i = inBlock[l] + 1, to = inBlock[r]; i < to; i++)
					tag[i] = min(tag[i], x);
				Rebuild(l, rEnd[inBlock[l]], x);
				Rebuild(lBegin[inBlock[r]], r, x);
			}
		}
		else
		{
			if (inBlock[l] == inBlock[r])
			{
				temp[0] = 0;
				EAX t;
				t = tag[inBlock[l]];
				if (t != INF)
					for (EAX i = l; i <= r; i++)
						temp[++temp[0]] = min(a[i], t);
				else
					for (EAX i = l; i <= r; i++)
						temp[++temp[0]] = a[i];
				std::nth_element(temp + 1, temp + x, temp + 1 + temp[0]);
				printOut(temp[x]);
			}
			else
			{
				temp[0] = 0;
				EAX t;
				t = tag[inBlock[l]];
				if (t != INF)
					for (EAX i = l, to = rEnd[inBlock[l]]; i <= to; i++)
						temp[++temp[0]] = min(a[i], t);
				else
					for (EAX i = l, to = rEnd[inBlock[l]]; i <= to; i++)
						temp[++temp[0]] = a[i];
				t = tag[inBlock[r]];
				if (t != INF)
					for (EAX i = lBegin[inBlock[r]]; i <= r; i++)
						temp[++temp[0]] = min(a[i], t);
				else
					for (EAX i = lBegin[inBlock[r]]; i <= r; i++)
						temp[++temp[0]] = a[i];
				std::sort(temp + 1, temp + 1 + temp[0]);

				int L = 1, R = n;
				EAX from = inBlock[l] + 1;
				EAX to = inBlock[r] - 1;
				while (R - L > 0)
				{
					EAX mid = (L + R) >> 1;
					EAX count = 0;
					// check
					{
						if (from <= to)
							for (EAX i = from; i <= to; i++)
								if (mid >= tag[i])
									count += rEnd[i] - lBegin[i] + 1;
								else
									count += std::upper_bound(sort + lBegin[i], sort + rEnd[i] + 1, mid) - (sort + lBegin[i]);
						if (temp[0]) count += std::upper_bound(temp + 1, temp + 1 + temp[0], mid) - (temp + 1);
					}

					if (count < x)
						L = mid + 1;
					else
						R = mid;
				}
				printOut(L);
			}
		}
	}
}

int main()
{
#ifndef LOCAL
	freopen("kth.in", "r", stdin);
	freopen("kth.out", "w", stdout);
#endif
	run();
	return 0;
}