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
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = LL;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int maxn = int(1e5) + 5;
int n;
LL p, q;
int a[maxn];
int bound;
int disc[maxn];
void discretize()
{
	for (int i = 1; i <= n; i++)
		disc[i] = a[i];
	std::sort(disc + 1, disc + 1 + n);
	bound = std::unique(disc + 1, disc + 1 + n) - (disc + 1);
	for (int i = 1; i <= n; i++)
		a[i] = std::lower_bound(disc + 1, disc + 1 + bound, a[i]) - disc;
}

class FuncSegTree
{
	int size = 0;
	struct Node
	{
		ULL hash;
		int lc, rc;
		Node() : hash(), lc(), rc() {}
	} nodes[maxn * 20];
	std::vector<int> versions;

	int bound;
	ULL power[maxn];

	int g_Pos;
	void insert(int& node, int l, int r, int src)
	{
		if (!(l <= g_Pos && g_Pos <= r))
		{
			node = src;
			return;
		}
		node = size++;
		if (l == r)
		{
			nodes[node].hash = nodes[src].hash + 1;
			return;
		}
		int mid = (l + r) >> 1;
		insert(nodes[node].lc, l, mid, nodes[src].lc);
		insert(nodes[node].rc, mid + 1, r, nodes[src].rc);
		nodes[node].hash = nodes[nodes[node].lc].hash * power[r - mid] +
			nodes[nodes[node].rc].hash;
	}

public:
	FuncSegTree()
	{
		versions.push_back(size++);
		power[0] = 1;
		for (int i = 1; i <= n; i++)
			power[i] = power[i - 1] * 1313131;
	}
	void SetBound(int b) { bound = b; }
	void clone()
	{
		versions.push_back(versions.back());
	}
	void insert(int pos)
	{
		g_Pos = pos;
		insert(versions.back(), 1, bound, versions.back());
	}
	bool comp(int l1, int r1, int l2, int r2) const
	{
		bool temp = l1 < l2;
		l1 = versions[l1 - 1];
		r1 = versions[r1];
		l2 = versions[l2 - 1];
		r2 = versions[r2];
		int l = 1, r = bound;
		while (r - l > 0)
		{
			int mid = (l + r) >> 1;
			if (nodes[nodes[r1].lc].hash - nodes[nodes[l1].lc].hash ==
				nodes[nodes[r2].lc].hash - nodes[nodes[l2].lc].hash)
			{
				l = mid + 1;
				l1 = nodes[l1].rc;
				r1 = nodes[r1].rc;
				l2 = nodes[l2].rc;
				r2 = nodes[r2].rc;
			}
			else
			{
				r = mid;
				l1 = nodes[l1].lc;
				r1 = nodes[r1].lc;
				l2 = nodes[l2].lc;
				r2 = nodes[r2].lc;
			}
		}
		if (nodes[r1].hash - nodes[l1].hash !=
			nodes[r2].hash - nodes[l2].hash)
			return nodes[r1].hash - nodes[l1].hash >
			nodes[r2].hash - nodes[l2].hash;
		return temp;
	}
};
FuncSegTree fst;
class SegTree
{
	struct Node
	{
		int l1, l2, r1, r2;
		LL sl, sr, sx;
	} nodes[maxn * 2];
	static inline int code(int l, int r)
	{
		return (l + r) | (l != r);
	}

	void update(int l, int r)
	{
		Node& t = nodes[code(l, r)];
		int mid = (l + r) >> 1;
		Node& lc = nodes[code(l, mid)];
		Node& rc = nodes[code(mid + 1, r)];
		t.l1 = std::min(lc.l1, rc.l1);
		t.l2 = std::max(lc.l2, rc.l2);
		t.r1 = std::min(lc.r1, rc.r1);
		t.r2 = std::max(lc.r2, rc.r2);
		t.sl = lc.sl + rc.sl;
		t.sr = lc.sr + rc.sr;
		t.sx = lc.sx + rc.sx;
	}
	void pushdown(int l, int r)
	{
		Node& t = nodes[code(l, r)];
		int mid = (l + r) >> 1;
		Node& lc = nodes[code(l, mid)];
		Node& rc = nodes[code(mid + 1, r)];
		if (t.l1 > lc.l1)
		{
			lc.sl = (LL)t.l1 * lc.sx;
			lc.l1 = lc.l2 = t.l1;
		}
		if (t.l1 > rc.l1)
		{

		}
	}

	int g_L, g_R, g_Pos, g_Val, g_Val2;
	LL query_(int l, int r)
	{
		if (g_L <= l && r <= g_R)
		{
			Node& t = nodes[code(l, r)];
			if (t.l1 >= g_Pos)
				return t.sr - t.sl + t.sx;
			if (t.r2 < g_Pos)
				return 0;
			if (t.r1 >= g_Pos && t.l2 <= g_Pos)
				return t.sr - (LL)t.sx * (g_Pos - 1);
		}
		pushdown(l, r);
		int mid = (l + r) >> 1;
		LL ret = 0;
		if (g_L <= mid) ret += query_(l, mid);
		if (g_R > mid) ret += query_(mid + 1, r);
		return ret;
	}
	void modify_(int l, int r)
	{
		// TODO
		pushdown(l, r);
		int mid = (l + r) >> 1;
		if (g_L <= mid) modify_(l, mid);
		if (g_R > mid) modify_(mid + 1, r);
		update(l, r);
	}

public:
	void build(int l, int r)
	{
		if (l == r)
		{
			Node& t = nodes[code(l, r)];
			t.l1 = t.l2 = l;
			t.r1 = t.r2 = n;
			t.sl = l;
			t.sr = n;
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid);
		build(mid + 1, r);
		update(l, r);
	}
	// 查询左端点在 [l, r]，在满足前 i 位等于答案时（在区间内时）且第 i + 1 位大于等于答案时（从 least 到 n 时）区间总个数
	LL query(int l, int r, int least)
	{
		g_L = l;
		g_R = r;
		g_Pos = least;
		return query_(1, n);
	}
	// 使左端点在 [l, r] 的右端点区间的左端点至少为 valL，右端点至多为 valR
	void modify(int l, int r, int valL, int valR)
	{
		g_L = l;
		g_R = r;
		g_Val = valL;
		g_Val2 = valR;
		modify_(l, r);
	}
	// 计算出区间的左右端点
	std::pair<int, int> wander()
	{

	}
};

#define RunInstance(x) delete new x
struct brute
{
	std::vector<std::pair<int, int>> pairs;

	brute()
	{
		fst.SetBound(n);
		for (int i = 1; i <= n; i++)
		{
			fst.clone();
			fst.insert(a[i]);
		}
		for (int i = 1; i <= n; i++)
			for (int j = i; j <= n; j++)
			{
				pairs.push_back(std::make_pair(i, j));
			}

		std::partial_sort(pairs.begin(), pairs.begin() + q, pairs.end(),
			[&](const std::pair<int, int>& a, const std::pair<int, int>& b)
		{
			return fst.comp(a.first, a.second, b.first, b.second);
		});

		for (int i = p - 1; i < q; i++)
		{
			printOut(pairs[i].first);
			putchar(' ');
			printOut(pairs[i].second);
			putchar('\n');
		}
	}
};
struct work
{
	std::vector<std::vector<int>> poss;

	struct HeapNode
	{
		int l, r;
		HeapNode() = default;
		HeapNode(int l, int r) : l(l), r(r) {}
		bool operator<(const HeapNode& b) const
		{
			return !fst.comp(l, r, b.l, b.r);
		}
	};

	SegTree st;
	LL check(int num, int s)
	{
		LL ret = 0;
		for (int i = 0, size = poss[num].size(); i < size; i++)
		{
			int L = i ? poss[num][i - 1] : 1;
			int R = poss[num][i] - 1;
			if (i + s - 1 >= size - 1)
				break;
			int least;
			if (i + s - 1 < 0)
				least = 1;
			else
				least = poss[num][i + s - 1];
			ret += st.query(L, R, least);
		}
		return ret;
	}

	int sel[maxn];

	work()
	{
		poss.resize(bound + 1);
		for (int i = 1; i <= n; i++)
			poss[a[i]].push_back(i);

		q = q - p + 1;
		std::priority_queue<HeapNode> pq;
		for (int i = 1; i <= bound; i++)
		{
			poss[i].push_back(n + 1);

			int l = 0, r = poss[i].size();
			while (r - l > 0)
			{
				int mid = (l + r) >> 1;
				if (check(i, mid) < p)
					l = mid + 1;
				else
					r = mid;
			}
			if (l < poss[i].size())
				p -= check(i, l + 1); // 减去包含了大于 l 个 i 的区间
			sel[i] = l;
			for (int j = 0, size = poss[i].size(); j < size; j++)
			{
				int valL, valR;
				if (j + l - 1 < 0)
					valL = 1;
				else if (j + l - 1 >= size)
					valL = n + 1;
				else
					valL = poss[i][j + l - 1];

				if (j + l >= size)
					valR = n;
				else
					valR = poss[i][j + l] - 1;

				int L = j ? poss[i][j - 1] : 1;
				int R = poss[i][j] - 1;
				if (L <= R)
					st.modify(L, R, valL, valR);
			}
		}

		fst.SetBound(n);
		for (int i = 1; i <= n; i++)
		{
			fst.clone();
			fst.insert(a[i]);
		}

		std::pair<int, int> pth = st.wander();
		HeapNode node(pth.first, pth.second);
		for (int i = 1; i <= n; i++)
			if (i != node.l)
			{
				int l = i, r = n + 1;
				while (r - l > 0)
				{
					int mid = (l + r) >> 1;
					if (node < HeapNode(i, mid)) // node 严格大于
						l = mid + 1;
					else
						r = mid;
				}
				if (l <= n)
					pq.push(HeapNode(i, l));
			}
		pq.push(node);

		for (LL i = 1; i <= q; i++)
		{
			HeapNode t = pq.top();
			pq.pop();
			if (t.l != t.r)
				pq.push(HeapNode(t.l, t.r - 1));

			printOut(t.l);
			putchar(' ');
			printOut(t.r);
			putchar('\n');
		}
	}
};

void run()
{
	n = readIn();
	p = readIn();
	q = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	discretize();

	if (n <= 1000)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
	run();
	return 0;
}