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
using INT_PUT = int;
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
}

const int maxn = int(1e5) + 5;
int T;
int n;
char s[maxn];
struct Case
{
	std::string str;
	Case()
	{
		static char buffer[maxn];
		scanf("%s", buffer);
		str = buffer;
	}
	void release()
	{
		n = str.length();
		strcpy(s, str.c_str());
	}
};
std::vector<Case> cases;

const int alphabet = 12;
inline int code(char ch) { return ch - 'a'; }
struct AlphaGraph
{
	int rect[alphabet][alphabet];
	AlphaGraph() { clear(); }
	void clear() { std::memset(rect, 0, sizeof(rect)); }
	void link(int from, int to) { rect[from][to]++; }
	void destroy(int from, int to) { rect[from][to]--; }

	bool vis[alphabet];
	int dfn[alphabet];
	int low[alphabet];
	int stack[alphabet + 1];
	bool inStack[alphabet];
	int N;
	int stamp;
	void Tarjan(int node)
	{
		dfn[node] = low[node] = ++stamp;
		stack[++stack[0]] = node;
		inStack[node] = true;
		for (int i = 0; i < alphabet; i++) if (rect[node][i])
		{
			if (!dfn[i])
			{
				Tarjan(i);
				low[node] = std::min(low[node], low[i]);
			}
			else if (inStack[i])
				low[node] = std::min(low[node], dfn[i]);
		}
		if (dfn[node] == low[node])
		{
			N++;
			int top;
			do
			{
				top = stack[stack[0]--];
				inStack[top] = false;
			} while (node != top);
		}
	}
	bool judge()
	{
		std::memset(vis, 0, sizeof(vis));
		std::memset(dfn, 0, sizeof(dfn));
		std::memset(low, 0, sizeof(low));
		std::memset(inStack, 0, sizeof(inStack));
		stack[0] = 0;
		stamp = 0;
		N = 0;
		for (int i = 0; i < alphabet; i++)
			if (!dfn[i])
				Tarjan(i);
		return N == alphabet;
	}
};

#define RunInstance(x) delete new x
struct brute
{
	struct Trie
	{
		struct Node
		{
			int next[alphabet];
			Node() : next() {}
		};
		std::vector<Node> nodes;
		Trie() : nodes(1) {}
		void clear()
		{
			nodes.clear();
			nodes.resize(1);
		}
		void insert(const char* s)
		{
			int cnt = 0;
			for (; *s; s++)
			{
				int x = code(*s);
				if (!nodes[cnt].next[x])
				{
					nodes[cnt].next[x] = nodes.size();
					nodes.push_back(Node());
				}
				cnt = nodes[cnt].next[x];
			}
		}
		AlphaGraph g;
		bool wander(const char* s)
		{
			g.clear();
			int cnt = 0;
			for (; *s; s++)
			{
				int x = code(*s);
				for (int i = 0; i < alphabet; i++) if (i != x && nodes[cnt].next[i])
					g.link(x, i);
				cnt = nodes[cnt].next[x];
			}
			for (int i = 0; i < alphabet; i++)
				if (nodes[cnt].next[i])
					return false;
			return g.judge();
		}
	} trie;
	brute()
	{
		for (auto& c : cases)
		{
			c.release();
			trie.clear();
			for (int i = 0; i < n; i++)
				trie.insert(s + i);
			for (int i = 0; i < n; i++)
				putchar('0' + trie.wander(s + i));
			putchar('\n');
		}
	}
};
template<int size>
struct Array
{
	int c[size];
	int& operator[](int x) { return c[x]; }
	const int& operator[](int x) const { return c[x]; }
};
struct work
{
	using Graph = std::vector<Array<alphabet>>;
	struct SAM
	{
		struct Node
		{
			int link;
			int len;
			int right;
			int next[alphabet];
			void clear()
			{
				std::memset(this, 0, sizeof(*this));
			}
			Node() { clear(); }
		};
		std::vector<Node> nodes;
		int pre;
		int length;
		void clear()
		{
			length = 0;
			nodes.clear();
			nodes.push_back(Node());
			nodes.back().link = -1;
			pre = 0;
		}
		SAM() { clear(); }
		int extend(char ch)
		{
			int x = code(ch);
			nodes.push_back(Node());
			int cur = nodes.size() - 1;
			nodes[cur].len = nodes[pre].len + 1;
			nodes[cur].right = length;
			length++;
			int p = pre;
			pre = cur;

			for (; ~p && !nodes[p].next[x]; p = nodes[p].link)
				nodes[p].next[x] = cur;
			if (!~p)
			{
				nodes[cur].link = 0;
				return cur;
			}
			int q = nodes[p].next[x];
			if (nodes[p].len + 1 == nodes[q].len)
			{
				nodes[cur].link = q;
				nodes[q].right = std::max(nodes[q].right, nodes[cur].right);
				return cur;
			}
			int clone = nodes.size();
			nodes.push_back(Node(nodes[q]));
			nodes[clone].len = nodes[p].len + 1;
			nodes[q].link = clone;
			nodes[cur].link = clone;
			nodes[clone].right = nodes[cur].right; // 保存 right（保存最大的就可以了）
			for (; ~p && nodes[p].next[x] == q; p = nodes[p].link)
				nodes[p].next[x] = clone;
			return cur;
		}
		void build(Graph& G)
		{
			G.clear();
			G.resize(nodes.size());
			for (int i = 1; i < nodes.size(); i++)
			{
				int parent = nodes[i].link;
				int x;
				x = code(s[n - 1 - (nodes[i].right - nodes[parent].len)]); // 找下一个字符
				G[parent][x] = i;
			}
		}
	} sam;
	int idx[maxn];
	Graph G;
	AlphaGraph g;
	bool bOk[maxn * 2];
	void DFS(int node)
	{
		bOk[node] = g.judge();
		for (int i = 0; i < alphabet; i++)
		{
			if (int to = G[node][i])
			{
				bOk[node] = false; // 有后继结点
				if (to == 1)
					int a = 1;
				for (int j = 0; j < alphabet; j++) if (i != j && G[node][j])
					g.link(i, j);
				DFS(to);
				for (int j = 0; j < alphabet; j++) if (i != j && G[node][j])
					g.destroy(i, j);
			}
		}
	}
	work()
	{
		for (auto& c : cases)
		{
			c.release();
			sam.clear();
			for (int i = n - 1; ~i; i--)
				idx[i] = sam.extend(s[i]);
			sam.build(G);

			g.clear();
			DFS(0);

			for (int i = 0; i < n; i++)
			{
				putchar('0' + bOk[idx[i]]);
			}
			putchar('\n');
		}
	}
};

void run()
{
	T = readIn();
	for (int i = 1; i <= T; i++)
		cases.push_back(Case());

	int mn = 0;
	for (const Case& c : cases)
		mn = std::max(mn, (int)c.str.length());

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
#endif
	run();
	return 0;
}