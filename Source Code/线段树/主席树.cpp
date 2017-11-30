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
using std::cin;
using std::cout;
using std::endl;
typedef int INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT maxn = 2e5 + 5;
const INT LOG = 32;
INT n, m;
INT origin[maxn];
INT minx = ~(1 << 31);
INT maxx = 1 << 31;
struct PST
{
	struct NODE
	{
		INT l, r;
		NODE *lc, *rc;
		INT size;
		NODE() {}
		NODE(INT l, INT r, NODE* lc, NODE* rc) : l(l), r(r), lc(lc), rc(rc), size(lc->size + rc->size) {}
		NODE(INT l, INT r, NODE* lc, NODE* rc, INT size) : l(l), r(r), lc(lc), rc(rc), size(size) {}
	} *roots[maxn], *null, pool[maxn * LOG], *crt;
	PST()
	{
		null = new NODE(minx - 1, minx - 1, NULL, NULL, 0);
		null->lc = null->rc = null;
	}

	NODE* insert(NODE* pre, INT l, INT r, INT x)
	{
		if (x > r || x < l) return pre;
		else if (l == r)
			return new(crt++) NODE(l, r, null, null, pre->size + 1);
		else
		{
			INT mid = l + (r - l) / 2;
			return new(crt++) NODE(l, r, insert(pre->lc, l, mid, x), insert(pre->rc, mid + 1, r, x));
		}
	}
	void build()
	{
		crt = pool;
		roots[0] = null;

		for (int i = 1; i <= n; i++)
		{
			roots[i] = insert(roots[i - 1], minx, maxx, origin[i]);
		}
	}

	INT query(INT ql, INT qr, INT k)
	{
		INT l = minx, r = maxx;
		NODE* tl = roots[ql - 1];
		NODE* tr = roots[qr];

		while (l != r)
		{
			INT mid = l + (r - l) / 2;
			INT contain = tr->lc->size - tl->lc->size;

			if (k <= contain)
			{
				tl = tl->lc;
				tr = tr->lc;

				r = mid;
			}
			else
			{
				k -= contain;

				tl = tl->rc;
				tr = tr->rc;

				l = mid + 1;
			}
		}
		return l;
	}
} pst;

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		origin[i] = readIn();
		minx = std::min(minx, origin[i]);
		maxx = std::max(maxx, origin[i]);
	}
	pst.build();
	while (m--)
	{
		INT from = readIn();
		INT to = readIn();
		INT k = readIn();
		printf("%d\n", pst.query(from, to, k));
	}
}

int main()
{
	run();
	return 0;
}
