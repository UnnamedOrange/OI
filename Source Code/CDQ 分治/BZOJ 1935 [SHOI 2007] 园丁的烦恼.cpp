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
struct Point
{
	int x, y;
	void read()
	{
		x = readIn();
		y = readIn();
	}
} points[maxn];
struct Query
{
	int x1, y1;
	int x2, y2;
	void read()
	{
		x1 = readIn();
		y1 = readIn();
		x2 = readIn();
		y2 = readIn();
	}
} querys[maxn];

struct Ins
{
	int type;
	int x, y;
	int idx;
	int sig;
	Ins() {}
	Ins(int x, int y, int idx, int sig) : type(true), x(x), y(y), idx(idx), sig(sig) {}
	bool operator<(const Ins& b) const
	{
		if (x != b.x) return x < b.x;
		if (y != b.y) return y < b.y;
		return type < b.type; // note
	}
};
int ans[maxn];

int N;
Ins inss[maxn * 5];
Ins temp[maxn * 5];
void cdq(int l, int r)
{
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	cdq(l, mid);
	cdq(mid + 1, r);

	int i = l, j = mid + 1, k = l;
	int t = 0;
	while (i <= mid || j <= r)
	{
		if (j > r || (i <= mid && inss[i].y <= inss[j].y))
		{
			if (inss[i].type == 0)
				t++;
			temp[k++] = inss[i++];
		}
		else
		{
			if (inss[j].type == 1)
				ans[inss[j].idx] += inss[j].sig * t;
			temp[k++] = inss[j++];
		}
	}
	for (i = l; i <= r; i++)
		inss[i] = temp[i];
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		points[i].read();
	for (int i = 1; i <= m; i++)
		querys[i].read();

	for (int i = 1; i <= n; i++)
	{
		inss[N].type = 0;
		inss[N].x = points[i].x;
		inss[N].y = points[i].y;
		N++;
	}
	for (int i = 1; i <= m; i++)
	{
		const Query& q = querys[i];
		inss[N++] = Ins(q.x2, q.y2, i, 1);
		inss[N++] = Ins(q.x1 - 1, q.y2, i, -1);
		inss[N++] = Ins(q.x2, q.y1 - 1, i, -1);
		inss[N++] = Ins(q.x1 - 1, q.y1 - 1, i, 1);
	}
	std::sort(inss, inss + N);

	cdq(0, N - 1);
	for (int i = 1; i <= m; i++)
		printOut(ans[i]);
}

int main()
{
	run();
	return 0;
}