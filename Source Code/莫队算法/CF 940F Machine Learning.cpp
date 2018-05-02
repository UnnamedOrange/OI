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
#define loop register int
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

const int maxn = int(1e5) + 5;
int n, m;
int a[maxn];
int nModify;
struct Modify
{
	int pos, val, pre;
	void read()
	{
		pos = readIn();
		val = readIn();
	}
	inline void forward() const { a[pos] = val; }
	inline void backward() const { a[pos] = pre; }
} modifys[maxn];
int nQuery;
struct Query
{
	int l, r, t;
	int ans;
	void read()
	{
		l = readIn();
		r = readIn();
		t = nModify;
	}
} querys[maxn];

int bound;
int disc[maxn * 2];
void discretize()
{
	for (loop i = 1; i <= n; i++)
		disc[++bound] = a[i];
	for (loop i = 1; i <= nModify; i++)
		disc[++bound] = modifys[i].val;
	std::sort(disc + 1, disc + 1 + bound);
	bound = std::unique(disc + 1, disc + 1 + bound) - (disc + 1);

	for (loop i = 1; i <= n; i++)
		a[i] = std::lower_bound(disc + 1, disc + 1 + bound, a[i]) - disc;
	for (loop i = 1; i <= nModify; i++)
		modifys[i].val = std::lower_bound(disc + 1, disc + 1 + bound, modifys[i].val) - disc;
}
void initModify()
{
	for (loop i = 1; i <= nModify; i++)
	{
		Modify& t = modifys[i];
		t.pre = a[t.pos];
		t.forward();
	}
}

int blockSize;
int inBlock[maxn];

int idx[maxn];
bool comp(const int& a, const int& b)
{
	const Query& x = querys[a];
	const Query& y = querys[b];
	if (inBlock[x.l] != inBlock[y.l]) return x.l < y.l;
	if (inBlock[x.r] != inBlock[y.r]) return (inBlock[x.l] & 1) ? x.r > y.r : x.r < y.r;
	return x.t < y.t;
}
void initBlock()
{
	blockSize = std::max(1.0, std::pow(n, (double)2 / 3));
	for (loop i = 1; i <= n; i++)
		inBlock[i] = (i - 1) / blockSize + 1;

	for (loop i = 1; i <= nQuery; i++)
		idx[i] = i;
	std::sort(idx + 1, idx + 1 + nQuery, comp);
}

int times[maxn * 2];
int cntL, cntR, cntT;

int sqrtN;
int belong[maxn];
int size[maxn];
int appear[maxn];
int b[maxn];
void init()
{
	sqrtN = std::max(2.0, std::sqrt(2 * std::sqrt(n))); // ×î´ó 2 * sqrt(n)
	for (loop i = 0; i <= n; i++)
		size[belong[i] = i / sqrtN]++;
	cntL = 1;
	cntR = 0;
	cntT = nModify;
	appear[0] = int(1e9);
	b[belong[0]]++;
}
inline void expandMex(int val)
{
	if (!(appear[val]++))
		b[belong[val]]++;
}
inline void shrinkMex(int val)
{
	if (!(--appear[val]))
		b[belong[val]]--;
}
int getAns()
{
	loop ans = 0;
	loop ib = 0;
	while (b[ib] == size[ib])
	{
		ans += sqrtN;
		ib++;
	}
	while (appear[ans])
		ans++;
	return ans;
}

inline void expand(int pos)
{
	int& t = times[a[pos]];
	shrinkMex(t);
	expandMex(++t);
}
inline void shrink(int pos)
{
	int& t = times[a[pos]];
	shrinkMex(t);
	expandMex(--t);
}
inline void expandT(int t)
{
	const Modify& T = modifys[t];
	if (cntL <= T.pos && T.pos <= cntR)
	{
		shrinkMex(times[a[T.pos]]);
		expandMex(--times[a[T.pos]]);
		T.forward();
		shrinkMex(times[a[T.pos]]);
		expandMex(++times[a[T.pos]]);
	}
	else
		T.forward();
}
inline void shrinkT(int t)
{
	const Modify& T = modifys[t];
	if (cntL <= T.pos && T.pos <= cntR)
	{
		shrinkMex(times[a[T.pos]]);
		expandMex(--times[a[T.pos]]);
		T.backward();
		shrinkMex(times[a[T.pos]]);
		expandMex(++times[a[T.pos]]);
	}
	else
		T.backward();
}

void solve()
{
	initBlock();
	init();
	for (int i = 1; i <= nQuery; i++)
	{
		Query& q = querys[idx[i]];

		while (cntL > q.l) expand(--cntL);
		while (cntR < q.r) expand(++cntR);
		while (cntL < q.l) shrink(cntL++);
		while (cntR > q.r) shrink(cntR--);
		while (cntT < q.t) expandT(++cntT);
		while (cntT > q.t) shrinkT(cntT--);

		q.ans = getAns();
	}

	for (int i = 1; i <= nQuery; i++)
		printOut(querys[i].ans);
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	while (m--)
	{
		int type = readIn();
		if (type == 1)
			querys[++nQuery].read();
		else
			modifys[++nModify].read();
	}
	discretize();
	initModify();

	solve();
}

int main()
{
	run();
	return 0;
}