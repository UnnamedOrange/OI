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
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = int(2e5) + 10;
int n, m;
int a[maxn];
struct Query
{
	int l, r;
	int ans;
	void read()
	{
		l = readIn();
		r = readIn();
	}
} querys[maxn];

const int maxN = 450;
int NB;
int bsize[maxN];
inline int code(int x)
{
	return x / NB;
}

int sqrtN;
int N;
int inBlock[maxn];
void initBlocks()
{
	sqrtN = n / std::max(std::sqrt(m), 1.0);
	N = (n - 1) / sqrtN + 1;
	for (int i = 1; i <= n; i++)
		inBlock[i] = (i - 1) / sqrtN;

	NB = std::sqrt(n);
	for (int i = 0; i <= n + 1; i++)
		bsize[code(i)]++;
}
int idx[maxn];
bool comp(const int& a, const int& b)
{
	const Query& x = querys[a];
	const Query& y = querys[b];
	if (inBlock[x.l] != inBlock[y.l]) return x.l < y.l;
	return (inBlock[x.l] & 1) ? x.r > y.r : x.r < y.r;
}

int buf[maxN];
int times[maxn];
int solve()
{
	int ret = 0;
	int b = code(ret);
	while (buf[b] == bsize[b])
	{
		ret += NB;
		b = code(ret);
	}
	while (times[ret]) ret++;
	return ret;
}
int cntL, cntR, ans;
void init()
{
	cntL = cntR = 1;
	++times[a[1]];
	buf[code(a[1])]++;
}
void expand(int pos)
{
	if (!(times[a[pos]]++))
		buf[code(a[pos])]++;
}
void shrink(int pos)
{
	if (!(--times[a[pos]]))
		buf[code(a[pos])]--;
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = std::min(readIn(), n + 1);
	for (int i = 1; i <= m; i++)
		querys[i].read();

	initBlocks();

	for (int i = 1; i <= m; i++)
		idx[i] = i;
	std::sort(idx + 1, idx + 1 + m, comp);

	init();
	for (int i = 1; i <= m; i++)
	{
		Query& q = querys[idx[i]];
		while (cntL > q.l) expand(--cntL);
		while (cntR < q.r) expand(++cntR);
		while (cntL < q.l) shrink(cntL++);
		while (cntR > q.r) shrink(cntR--);

		q.ans = solve();
	}
	for (int i = 1; i <= m; i++)
		printOut(querys[i].ans);
}

int main()
{
	run();
	return 0;
}