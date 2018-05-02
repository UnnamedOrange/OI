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

const int maxn = int(5e5) + 5;
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
		pre = a[pos];
		forward();
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

int sqrtN;
int N;
int inBlock[maxn];
void initBlocks()
{
	sqrtN = std::pow(n, (double)2 / 3);
	N = (n - 1) / sqrtN + 1;
	for (int i = 1; i <= n; i++)
		inBlock[i] = (i - 1) / sqrtN;
}
int idx[maxn];
bool comp(const int& a, const int& b)
{
	const Query& x = querys[a];
	const Query& y = querys[b];
	if (inBlock[x.l] != inBlock[y.l]) return x.l < y.l;
	if (inBlock[x.r] != inBlock[y.r]) return (inBlock[x.l] & 1) ? x.r > y.r : x.r < y.r;
	return x.t < y.t;
}

int cntL, cntR, cntT;
int ans;
int times[int(1e6) + 5];
inline void expand(int pos) { if (!(times[a[pos]]++)) ans++; }
inline void shrink(int pos) { if (!(--times[a[pos]])) ans--; }
inline void expandT(int idx)
{
	const Modify& t = modifys[idx];
	if (cntL <= t.pos && t.pos <= cntR)
	{
		if (!(--times[a[t.pos]])) ans--;
		t.forward();
		if (!(times[a[t.pos]]++)) ans++;
	}
	else
		t.forward();
}
inline void shrinkT(int idx)
{
	const Modify& t = modifys[idx];
	if (cntL <= t.pos && t.pos <= cntR)
	{
		if (!(--times[a[t.pos]])) ans--;
		t.backward();
		if (!(times[a[t.pos]]++)) ans++;
	}
	else
		t.backward();
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 1; i <= m; i++)
	{
		char type[5];
		scanf("%s", type);
		if (type[0] == 'Q')
			querys[++nQuery].read();
		else if (type[0] == 'R')
			modifys[++nModify].read();
	}

	initBlocks();
	for (int i = 1; i <= nQuery; i++)
		idx[i] = i;
	std::sort(idx + 1, idx + 1 + nQuery, comp);

	cntL = cntR = 1;
	cntT = nModify;
	times[a[1]]++;
	ans = 1;
	for (int i = 1; i <= nQuery; i++)
	{
		Query& q = querys[idx[i]];
		while (cntL > q.l) expand(--cntL);
		while (cntR < q.r) expand(++cntR);
		while (cntL < q.l) shrink(cntL++);
		while (cntR > q.r) shrink(cntR--);
		while (cntT < q.t) expandT(++cntT);
		while (cntT > q.t) shrinkT(cntT--);

		q.ans = ans;
	}

	for (int i = 1; i <= nQuery; i++)
		printOut(querys[i].ans);
}

int main()
{
	run();
	return 0;
}