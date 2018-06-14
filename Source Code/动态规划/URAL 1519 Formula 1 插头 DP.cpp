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

const int maxn = 13;
int n, m;
int mn, mm;
int rect[maxn + 1][maxn + 1];

struct HashTable
{
	static const int size = int(1e4) + 7; // note: 不能开太大
	struct Node
	{
		int key;
		LL val;
		int next;
		Node() {}
		explicit Node(int key) : key(key), val(0), next(-1) {}
		Node& operator=(const LL& t) { val = t; return *this; }
		Node& operator+=(const LL& t) { val += t; return *this; }
	};
	std::vector<Node> nodes;
	int head[size];
	HashTable() { clear(); }
	void clear()
	{
		nodes.clear();
		std::memset(head, -1, sizeof(head));
	}
	Node& operator[](int key)
	{
		int cnt = head[key % size];
		if (!~cnt)
		{
			head[key % size] = nodes.size();
			nodes.push_back(Node(key));
			return nodes.back();
		}
		else
		{
			if (nodes[cnt].key == key)
				return nodes[cnt];
			while (~nodes[cnt].next)
			{
				cnt = nodes[cnt].next;
				if (nodes[cnt].key == key)
					return nodes[cnt];
			}
			nodes[cnt].next = nodes.size();
			nodes.push_back(Node(key));
			return nodes.back();
		}
	}
} f[2];

inline int test(register int S, register int bit)
{
	return (S >> (bit << 1)) & 3;
}
inline int set(register int S, register int bit, register int val)
{
	return (S & (-1 ^ (1 << (bit << 1)) ^ (1 << ((bit << 1) | 1)))) | (val << (bit << 1));
}
void Transfer(int i, int j, const HashTable::Node& from, HashTable& to)
{
	int S = from.key;
	if (rect[i][j])
	{
		register int plug1 = test(S, j - 1);
		register int plug2 = test(S, j);
		if (plug1 == 0 && plug2 == 0)
		{
			if (rect[i + 1][j] && rect[i][j + 1]) // note: 为了保证所有状态合法
				to[set(set(S, j - 1, 1), j, 2)] += from.val;
		}
		else if (plug1 == 0 && plug2 == 1)
		{
			if (rect[i][j + 1])
				to[set(set(S, j - 1, 0), j, 1)] += from.val;
			if (rect[i + 1][j])
				to[set(set(S, j - 1, 1), j, 0)] += from.val;
		}
		else if (plug1 == 0 && plug2 == 2)
		{
			if (rect[i][j + 1])
				to[set(set(S, j - 1, 0), j, 2)] += from.val;
			if (rect[i + 1][j])
				to[set(set(S, j - 1, 2), j, 0)] += from.val;
		}
		else if (plug1 == 1 && plug2 == 0)
		{
			if (rect[i][j + 1])
				to[set(set(S, j - 1, 0), j, 1)] += from.val;
			if (rect[i + 1][j])
				to[set(set(S, j - 1, 1), j, 0)] += from.val;
		}
		else if (plug1 == 1 && plug2 == 1)
		{
			int match = 1;
			int k;
			for (k = j + 1; match; k++) // note: 我们保证了所有状态都是合法的，因此一定能找到
			{
				if (test(S, k) == 1) match++;
				else if (test(S, k) == 2) match--;
			}
			k--;
			S = set(set(S, j - 1, 0), j, 0);
			S = set(S, k, 1);
			to[S] += from.val;
		}
		else if (plug1 == 1 && plug2 == 2)
		{
			if (i == mn && j == mm) // note: 最后一个非障碍格
				to[set(set(S, j - 1, 0), j, 0)] += from.val;
		}
		else if (plug1 == 2 && plug2 == 0)
		{
			if (rect[i][j + 1])
				to[set(set(S, j - 1, 0), j, 2)] += from.val;
			if (rect[i + 1][j])
				to[set(set(S, j - 1, 2), j, 0)] += from.val;
		}
		else if (plug1 == 2 && plug2 == 1)
			to[set(set(S, j - 1, 0), j, 0)] += from.val;
		else if (plug1 == 2 && plug2 == 2)
		{
			int k;
			int match = -1;
			for (k = j - 2; match; k--)
			{
				if (test(S, k) == 1) match++;
				else if (test(S, k) == 2) match--;
			}
			k++;
			S = set(set(S, j - 1, 0), j, 0);
			S = set(S, k, 2);
			to[S] += from.val;
		}
	}
	else
	{
		if (!test(S, j - 1) && !test(S, j))
			to[S] = from.val;
	}
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			char ch = getchar();
			while (!(ch == '*' || ch == '.')) ch = getchar();
			rect[i][j] = (ch == '.');
			if (rect[i][j])
			{
				mn = i;
				mm = j;
			}
		}
	}

	int cnt = 0;
	f[cnt][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			int pre = cnt;
			cnt = !cnt;
			f[cnt].clear();
			for (int k = 0, to = f[pre].nodes.size(); k < to; k++)
			{
				const HashTable::Node& p = f[pre].nodes[k];
				Transfer(i, j, p, f[cnt]);
			}
		}
		if (i != n)
		{
			int pre = cnt;
			cnt = !cnt;
			f[cnt].clear();
			for (int k = 0, to = f[pre].nodes.size(); k < to; k++)
			{
				const HashTable::Node& p = f[pre].nodes[k];
				f[cnt][p.key << 2] = p.val; // note: 这里的转移也必须保证状态合法（否则最后一段轮廓线可能非 0）
			}
		}
	}
	printOut(f[cnt][0].val);
}

int main()
{
	run();
	return 0;
}