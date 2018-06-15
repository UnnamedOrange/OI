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

const int INF = (~(int(1) << (sizeof(int) * 8 - 1))) >> 1;
const int maxn = 105;
const int maxm = 10;
int n, m;
int rect[maxn][maxm];

struct HashTable
{
	static const int size = 2003;
	struct Node
	{
		int key;
		int val;
		int next;
		Node() {}
		explicit Node(int key) : key(key), val(-INF), next(-1) {} // note
		Node& operator=(int x)
		{
			val = x;
			return *this;
		}
	};
	HashTable() { clear(); }
	int head[size];
	std::vector<Node> nodes;
	void clear()
	{
		memset(head, -1, sizeof(head));
		nodes.clear();
	}
	Node& operator[](int key)
	{
		int cnt = head[key % size];
		if (~cnt)
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
		else
		{
			head[key % size] = nodes.size();
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
	return (S & (-1 ^ (1 << (bit << 1)) ^ (1 << ((bit << 1) | 1)))) |
		(val << (bit << 1));
}
inline void checkmax(int& x, int val)
{
	x = std::max(x, val);
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			rect[i][j] = readIn();

	int ans = -INF;

	int cnt = 0;
	f[cnt][0] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			int pre = cnt;
			cnt = !cnt;
			f[cnt].clear();
			for (const auto& t : f[pre].nodes)
			{
				int S = t.key;
				int plug1 = test(S, j - 1);
				int plug2 = test(S, j);
				if (plug1 == 0 && plug2 == 0)
				{
					if (i + 1 <= n && j + 1 <= m)
						checkmax(f[cnt][set(set(S, j - 1, 1), j, 2)].val,
							t.val + rect[i][j]);
					checkmax(f[cnt][S].val, t.val); // note
				}
				else if (plug1 == 0 && plug2 == 1)
				{
					if (i + 1 <= n)
						checkmax(f[cnt][set(set(S, j - 1, 1), j, 0)].val,
							t.val + rect[i][j]);
					if (j + 1 <= m)
						checkmax(f[cnt][set(set(S, j - 1, 0), j, 1)].val,
							t.val + rect[i][j]);
				}
				else if (plug1 == 0 && plug2 == 2)
				{
					if (i + 1 <= n)
						checkmax(f[cnt][set(set(S, j - 1, 2), j, 0)].val,
							t.val + rect[i][j]);
					if (j + 1 <= m)
						checkmax(f[cnt][set(set(S, j - 1, 0), j, 2)].val,
							t.val + rect[i][j]);
				}
				else if (plug1 == 1 && plug2 == 0)
				{
					if (i + 1 <= n)
						checkmax(f[cnt][set(set(S, j - 1, 1), j, 0)].val,
							t.val + rect[i][j]);
					if (j + 1 <= m)
						checkmax(f[cnt][set(set(S, j - 1, 0), j, 1)].val,
							t.val + rect[i][j]);
				}
				else if (plug1 == 1 && plug2 == 1)
				{
					int match = 1;
					int k;
					for (k = j + 1; match; k++)
					{
						if (test(S, k) == 1) match++;
						else if (test(S, k) == 2) match--;
					}
					k--; // note: ±ðÍüÁË¡­¡­
					S = set(set(S, j - 1, 0), j, 0);
					checkmax(f[cnt][set(S, k, 1)].val, t.val + rect[i][j]);
				}
				else if (plug1 == 1 && plug2 == 2)
				{
					if (!set(set(S, j - 1, 0), j, 0))
						ans = std::max(ans, t.val + rect[i][j]); // note
				}
				else if (plug1 == 2 && plug2 == 0)
				{
					if (i + 1 <= n)
						checkmax(f[cnt][set(set(S, j - 1, 2), j, 0)].val,
							t.val + rect[i][j]);
					if (j + 1 <= m)
						checkmax(f[cnt][set(set(S, j - 1, 0), j, 2)].val,
							t.val + rect[i][j]);
				}
				else if (plug1 == 2 && plug2 == 1)
				{
					checkmax(f[cnt][set(set(S, j - 1, 0), j, 0)].val,
						t.val + rect[i][j]);
				}
				else if (plug1 == 2 && plug2 == 2)
				{
					int match = -1;
					int k;
					for (k = j - 2; match; k--)
					{
						if (test(S, k) == 1) match++;
						else if (test(S, k) == 2) match--;
					}
					k++;
					S = set(set(S, j - 1, 0), j, 0);
					checkmax(f[cnt][set(S, k, 2)].val, t.val + rect[i][j]);
				}
			}
		}

		if (i != n)
		{
			int pre = cnt;
			cnt = !cnt;
			f[cnt].clear();
			for (const auto& t : f[pre].nodes)
				f[cnt][t.key << 2] = t.val;
		}
	}
	printOut(ans);
}

int main()
{
	run();
	return 0;
}