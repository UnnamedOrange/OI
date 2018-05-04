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
typedef LL INT_PUT;
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

const int maxn = int(3e5) + 5;
int n;
char str[maxn];
void readstr()
{
	char ch = getchar();
	while (!std::isalpha(ch)) ch = getchar();
	while (std::isalpha(ch))
	{
		str[++n] = ch;
		ch = getchar();
	}
}

struct SuffixAutomaton
{
	static const int alphabet = 26;
	static inline int code(char ch) { return ch - 'a'; }
	struct Node
	{
		int len;
		int suffix;
		int ch[alphabet];
	} nodes[maxn * 2];
	int size, last;
	SuffixAutomaton() { nodes[last = size++].suffix = -1; }

	int cnt;
	int leaf[maxn];

	void extend(char ch)
	{
		int x = code(ch);
		int p = last;
		int cur = leaf[++cnt] = last = size++;
		nodes[cur].len = nodes[p].len + 1;

		for (; ~p && !nodes[p].ch[x]; p = nodes[p].suffix)
			nodes[p].ch[x] = cur;
		if (!~p)
		{
			nodes[cur].suffix = 0;
			return;
		}
		int q = nodes[p].ch[x];
		if (nodes[p].len + 1 == nodes[q].len)
		{
			nodes[cur].suffix = q;
			return;
		}

		int clone = size++;
		nodes[clone] = nodes[q];
		nodes[clone].len = nodes[p].len + 1;
		nodes[q].suffix = nodes[cur].suffix = clone;
		for (; ~p && nodes[p].ch[x] == q; p = nodes[p].suffix)
			nodes[p].ch[x] = clone;
	}

	int k;
	int parent[21][maxn * 2];
	int buf[maxn * 2];
	int sort[maxn * 2];
	int weight[maxn * 2];
	void init()
	{
		while (1 << k <= size) k++;
		for (int i = 1; i <= size; i++)
			parent[0][i] = nodes[i].suffix;
		for (int i = 1; i <= k; i++)
			for (int j = 1; j <= size; j++)
				parent[i][j] = parent[i - 1][parent[i - 1][j]];

		for (int i = 0; i < size; i++) buf[nodes[i].len]++;
		for (int i = 1; i < size; i++) buf[i] += buf[i - 1];
		for (int i = size - 1; ~i; i--) sort[--buf[nodes[i].len]] = i;

		for (int i = 1; i <= n; i++)
			weight[leaf[i]] = 1;
		for (int i = size - 1; i; i--)
		{
			int node = sort[i];
			weight[parent[0][node]] += weight[node];
		}
	}
	LL query(int pos, int len)
	{
		int node = leaf[pos];
		for (int i = k; ~i; i--)
		{
			if (nodes[parent[i][node]].len < len) continue;
			node = parent[i][node];
		}
		return (LL)len * weight[node];
	}
} sam;

struct Manacher
{
	int size;
	char str[maxn * 2];
	int f[maxn * 2];

	void init()
	{
		str[0] = '#';
		for (int i = 1; i <= n; i++)
		{
			str[(i << 1) - 1] = ::str[i];
			str[i << 1] = '#';
		}
		size = 2 * n + 1;
	}

	void manacher(const std::function<void(int, int)> func)
	{
		int center = 0;
		int maxr = 0;
		for (int i = 1; i < size; i++)
		{
			if (i <= maxr)
				f[i] = std::min(f[(center << 1) - i], maxr - i + 1);
			else
				f[i] = 0;

			while (i - f[i] >= 0 && i + f[i] < size && str[i - f[i]] == str[i + f[i]])
			{
				f[i]++;
				if (i + f[i] - 1 > maxr)
				{
					maxr = i + f[i] - 1;
					center = i;
					if (str[maxr] != '#')
						func(((maxr + 1) >> 1), f[i]);
				}
			}
		}
	}
} manacher;

LL ans;
void callback(int pos, int len)
{
	ans = std::max(ans, sam.query(pos, len));
}

void run()
{
	readstr();

	for (int i = 1; i <= n; i++)
		sam.extend(str[i]);
	sam.init();
	manacher.init();

	manacher.manacher(callback);
	printOut(ans);
}

int main()
{
	run();
	return 0;
}