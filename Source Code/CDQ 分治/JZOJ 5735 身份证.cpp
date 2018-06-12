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
char buffer[maxn];
int pos[maxn][3];
int querys[maxn][3];
int L[maxn][3];
int R[maxn][3];

struct Trie
{
	static const int alphabet = 26;
	static inline int code(char ch) { return ch - 'a'; }
	struct Node
	{
		int parent;
		int ch[alphabet];
		Node(int parent = 0) : parent(parent), ch() {}
	};
	std::vector<Node> nodes;
	int wander;

	Trie() : wander()
	{
		nodes.push_back(Node());
	}

	int insert(const char* s)
	{
		int cnt = 0;
		for (; *s; s++)
		{
			int x = code(*s);
			if (!nodes[cnt].ch[x])
			{
				nodes[cnt].ch[x] = nodes.size();
				nodes.push_back(Node(cnt));
			}
			cnt = nodes[cnt].ch[x];
		}
		return cnt;
	}
	void stepin(char ch)
	{
		int x = code(ch);
		if (!nodes[wander].ch[x])
		{
			nodes[wander].ch[x] = nodes.size();
			nodes.push_back(Node(wander));
		}
		wander = nodes[wander].ch[x];
	}
	void stepback()
	{
		wander = nodes[wander].parent;
	}

	std::vector<int> dfn;
	std::vector<int> end;
	int stamp;

	void DFS(int node)
	{
		++stamp;
		dfn[node] = stamp;
		for (int i = 0; i < alphabet; i++)
			if (int t = nodes[node].ch[i])
				DFS(t);
		end[node] = stamp;
	}
	void DFS()
	{
		stamp = 0;
		dfn.resize(nodes.size());
		end.resize(nodes.size());
		DFS(0);
	}
} trie[3];

struct BIT
{
	int c[maxn];
	BIT() : c() {}
	static inline int lowbit(int x) { return x & -x; }
	void add(int pos, int val)
	{
		while (pos <= trie[2].nodes.size())
		{
			c[pos] += val;
			pos += lowbit(pos);
		}
	}
	int query(int pos)
	{
		int ret = 0;
		while (pos)
		{
			ret += c[pos];
			pos ^= lowbit(pos);
		}
		return ret;
	}
	void clear(int pos)
	{
		while (pos)
		{
			if (c[pos]) c[pos] = 0;
			else break;
			pos += lowbit(pos);
		}
	}
} bit;

#define RunInstance(x) delete new x
struct brute
{
	int ans[maxn];

	struct Ins
	{
		int x, y, z;
		int idx;
		int mul;
		Ins() {}
		Ins(int x, int y, int z, int idx, int mul) : x(x), y(y), z(z), idx(idx), mul(mul) {}
		bool operator<(const Ins& b) const
		{
			if (x != b.x) return x < b.x;
			if (y != b.y) return y < b.y;
			if (z != b.z) return z < b.z;
			return idx < b.idx;
		}
	};
	std::vector<Ins> inss;
	std::vector<Ins> temp;

	BIT bit;

	void cdq(int l, int r)
	{
		if (l == r)
			return;
		int mid = (l + r) >> 1;
		cdq(l, mid);
		cdq(mid + 1, r);

		int i = l, j = mid + 1, k = l;
		while (i <= mid || j <= r)
		{
			if (j > r || (i <= mid && inss[i].y <= inss[j].y))
			{
				if (!inss[i].idx)
					bit.add(inss[i].z, 1);
				temp[k++] = inss[i++];
			}
			else
			{
				if (inss[j].idx)
					ans[inss[j].idx] += bit.query(inss[j].z) * inss[j].mul;
				temp[k++] = inss[j++];
			}
		}
		for (i = l; i <= r; i++)
		{
			inss[i] = temp[i];
			bit.clear(inss[i].z);
		}
	}
	brute() : ans()
	{
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < 3; j++)
				pos[i][j] = trie[j].dfn[pos[i][j]];

		for (int i = 1; i <= m; i++)
			for (int j = 0; j < 3; j++)
			{
				L[i][j] = trie[j].dfn[querys[i][j]];
				R[i][j] = trie[j].end[querys[i][j]];
			}

		for (int i = 1; i <= n; i++)
			inss.push_back(Ins(pos[i][0], pos[i][1], pos[i][2], 0, 0));
		for (int i = 1; i <= m; i++)
		{
			inss.push_back(Ins(R[i][0], R[i][1], R[i][2], i, 1));
			inss.push_back(Ins(L[i][0] - 1, R[i][1], R[i][2], i, -1));
			inss.push_back(Ins(R[i][0], L[i][1] - 1, R[i][2], i, -1));
			inss.push_back(Ins(R[i][0], R[i][1], L[i][2] - 1, i, -1));
			inss.push_back(Ins(L[i][0] - 1, L[i][1] - 1, R[i][2], i, 1));
			inss.push_back(Ins(L[i][0] - 1, R[i][1], L[i][2] - 1, i, 1));
			inss.push_back(Ins(R[i][0], L[i][1] - 1, L[i][2] - 1, i, 1));
			inss.push_back(Ins(L[i][0] - 1, L[i][1] - 1, L[i][2] - 1, i, -1));
		}
		temp.resize(inss.size());
		std::sort(inss.begin(), inss.end());

		cdq(0, inss.size() - 1);
		for (int i = 1; i <= m; i++)
			printOut(ans[i]);
	}
};
struct Ins
{
	int x, y;
	int idx, mul;
	bool operator<(const Ins& b) const
	{
		if (x != b.x) return x < b.x;
		if (y != b.y) return y < b.y;
		return idx < b.idx;
	}
	Ins() {}
	Ins(int x, int y, int idx, int mul) : x(x), y(y), idx(idx), mul(mul) {}
};
struct work
{
	std::vector<std::vector<int> > people;
	std::vector<std::vector<int> > offline;

	int ans[maxn];
	BIT bit;

	work() : ans(), people(trie[0].nodes.size()), offline(trie[0].nodes.size())
	{
		for (int i = 1; i <= n; i++)
		{
			int cnt = pos[i][0];
			while (true)
			{
				people[cnt].push_back(i);
				if (!cnt) break;
				cnt = trie[0].nodes[cnt].parent;
			}
		}

		for (int i = 1; i <= m; i++)
			offline[querys[i][0]].push_back(i);

		std::vector<Ins> inss;
		inss.reserve(maxn * 5);
		for (int i = 0, to = trie[0].nodes.size(); i < to; i++)
		{
			if (!offline[i].size()) continue;
			inss.clear();
			for (int j = 0; j < offline[i].size(); j++)
			{
				int idx = offline[i][j];
				int x2 = trie[1].end[querys[idx][1]];
				int x1 = trie[1].dfn[querys[idx][1]];
				int y2 = trie[2].end[querys[idx][2]];
				int y1 = trie[2].dfn[querys[idx][2]];
				inss.push_back(Ins(x2, y2, idx, 1));
				inss.push_back(Ins(x1 - 1, y2, idx, -1));
				inss.push_back(Ins(x2, y1 - 1, idx, -1));
				inss.push_back(Ins(x1 - 1, y1 - 1, idx, 1));
			}
			for (int j = 0; j < people[i].size(); j++)
			{
				int idx = people[i][j];
				int x = trie[1].dfn[pos[idx][1]];
				int y = trie[2].dfn[pos[idx][2]];
				inss.push_back(Ins(x, y, 0, 0));
			}
			std::sort(inss.begin(), inss.end());

			for (int j = 0; j < inss.size(); j++)
			{
				const Ins& I = inss[j];
				if (!I.idx)
					bit.add(I.y, 1);
				else
				{
					int& a = ans[I.idx];
					a += I.mul * bit.query(I.y);
				}
			}
			for (int j = 0; j < inss.size(); j++)
			{
				const Ins& I = inss[j];
				if (!I.idx)
					bit.clear(I.y);
			}
		}
		for (int i = 1; i <= m; i++)
			printOut(ans[i]);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			scanf("%s", buffer);
			pos[i][j] = trie[j].insert(buffer);
		}
	}

	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		char ins[5];
		scanf("%s", ins);
		int idx = readIn() - 1;
		if (ins[0] == '+')
		{
			char str[5];
			scanf("%s", str);
			trie[idx].stepin(str[0]);
		}
		else
		{
			trie[idx].stepback();
		}
		for (int j = 0; j < 3; j++)
			querys[i][j] = trie[j].wander;
	}

	for (int i = 0; i < 3; i++)
		trie[i].DFS();

	RunInstance(work);
#ifdef LOCAL
	readIn();
#endif
}

int main()
{
#ifndef LOCAL
	freopen("id.in", "r", stdin);
	freopen("id.out", "w", stdout);
#endif
	run();
	return 0;
}