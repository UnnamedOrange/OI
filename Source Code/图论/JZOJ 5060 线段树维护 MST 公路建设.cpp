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

const INT maxn = 105;
const INT maxm = 100005;
const INT maxq = 15005;
INT n, m, q;
struct Edge
{
	INT from, to, cost;
	void read()
	{
		from = readIn();
		to = readIn();
		cost = readIn();
	}
} edges[maxm];
#define RunInstance(x) delete new x
struct work
{
	struct DS
	{
		INT parent[maxn];
		DS()
		{
			for (int i = 1; i <= n; i++)
				parent[i] = i;
		}
		INT find(INT x)
		{
			if (x == parent[x])
				return x;
			return parent[x] = find(parent[x]);
		}
		void unite(INT x, INT y)
		{
			parent[find(y)] = find(x);
		}
		bool judge(INT x, INT y)
		{
			return find(x) == find(y);
		}
	};
	class SegTree
	{
		struct Node
		{
			INT edges[maxn];
			INT var;
			void clear()
			{
				edges[0] = 0;
				var = 0;
			}
		} nodes[maxm * 2];
		static inline INT code(INT l, INT r)
		{
			return l + r | l != r;
		}

#define PARAM INT l, INT r

		void merge(Node& t, const Node& f, const Node& g)
		{
			INT save[maxn * 2];
			save[0] = 0;
			INT i = 1, j = 1;
			while (i <= f.edges[0] || j <= g.edges[0])
			{
				INT l = f.edges[i];
				INT r = g.edges[j];
				if (j > g.edges[0] || (i <= f.edges[0] && edges[l].cost < edges[r].cost))
				{
					save[++save[0]] = l;
					i++;
				}
				else
				{
					save[++save[0]] = r;
					j++;
				}
			}
			DS ds;
			t.clear();
			for (int i = 1; i <= save[0]; i++)
			{
				const Edge& e = edges[save[i]];
				INT u = e.from;
				INT v = e.to;
				INT c = e.cost;
				if (!ds.judge(u, v))
				{
					ds.unite(u, v);
					t.var += c;
					t.edges[++t.edges[0]] = save[i];
				}
			}
		}
		INT g_L, g_R;
		void query_(PARAM)
		{
			Node& t = nodes[code(l, r)];
			if (g_L <= l && r <= g_R)
			{
				merge(nodes[0], nodes[0], t);
				return;
			}
			INT mid = ((l + r) >> 1);
			if (g_L <= mid) query_(l, mid);
			if (g_R > mid) query_(mid + 1, r);
		}

	public:
		void build(INT l, INT r)
		{
			Node& t = nodes[code(l, r)];
			if (l == r)
			{
				t.edges[0] = 1;
				t.edges[1] = l;
				t.var = edges[l].cost;
				return;
			}
			INT mid = ((l + r) >> 1);
			build(l, mid);
			build(mid + 1, r);
			merge(t, nodes[code(l, mid)], nodes[code(mid + 1, r)]);
		}
		INT query(INT l, INT r)
		{
			g_L = l;
			g_R = r;
			nodes[0].clear();
			query_(1, m);
			return nodes[0].var;
		}
	} st;

	work()
	{
		st.build(1, m);
		while (q--)
		{
			INT l = readIn();
			INT r = readIn();
			printOut(st.query(l, r));
		}
	}
};
struct cheat
{
	struct Query
	{
		INT l, r, ans;
		void read()
		{
			l = readIn();
			r = readIn();
			ans = 0;
		}
	} querys[maxm];
	std::vector<INT> offline[maxm];
	struct BIT
	{
		INT bit[maxm];
		INT origin[maxm];
		BIT() : bit(), origin() {}
		static inline INT lowbit(INT x)
		{
			return x & -x;
		}
		void add(INT pos, INT val)
		{
			origin[pos] += val;
			while (pos <= m)
			{
				bit[pos] += val;
				pos += lowbit(pos);
			}
		}
		INT query(INT pos)
		{
			INT ret = 0;
			while (pos)
			{
				ret += bit[pos];
				pos -= lowbit(pos);
			}
			return ret;
		}
		INT query(INT l, INT r)
		{
			return query(r) - query(l - 1);
		}
		void set(INT pos, INT val)
		{
			add(pos, val - origin[pos]);
		}
	} bit;

	cheat()
	{
		for (int i = 1; i <= q; i++)
		{
			querys[i].read();
			offline[querys[i].l].push_back(i);
		}

		INT save[maxn];
		save[0] = 0;
		for (int i = m; i >= 1; i--)
		{
			save[++save[0]] = i;
			work::DS ds;
			bit.set(m + 1 - i, edges[i].cost);
			for (int j = save[0]; j >= 1; j--)
			{
				const Edge& e = edges[save[j]];
				if (ds.judge(e.from, e.to))
				{
					bit.set(m + 1 - save[j], 0);
					for (int k = j; k < save[0]; k++)
						save[k] = save[k + 1];
					save[0]--;
					break;
				}
				ds.unite(e.from, e.to);
			}
			for (int j = 0; j < offline[i].size(); j++)
			{
				Query& Q = querys[offline[i][j]];
				Q.ans = bit.query(m + 1 - Q.r, m + 1 - Q.l);
			}
		}
		for (int i = 1; i <= q; i++)
			printOut(querys[i].ans);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	q = readIn();
	for (int i = 1; i <= m; i++)
		edges[i].read();

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("highway.in", "r", stdin);
	freopen("highway.out", "w", stdout);
#endif
	run();
	return 0;
}