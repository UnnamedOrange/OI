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
}

const int maxn = int(2e5) + 5;
int n, k;
char str[maxn];

class SAM
{
	static const int alphabet = 26;
	static inline int code(char ch) { return ch - 'a'; }
	struct Node
	{
		int len;
		int link;
		int next[alphabet];
	} nodes[maxn * 2];
	int last, size;

public:
	SAM() { nodes[last = size++].link = -1; }
	void extend(char ch)
	{
		int x = code(ch);
		int cur = size++;
		int p = last;
		last = cur;
		g[cur] = 1;

		nodes[cur].len = nodes[p].len + 1;
		for (; ~p && !nodes[p].next[x]; p = nodes[p].link) nodes[p].next[x] = cur;
		if (!~p) return void(nodes[cur].link = 0);
		int q = nodes[p].next[x];
		if (nodes[p].len + 1 == nodes[q].len) return void(nodes[cur].link = q);
		int clone = size++;
		nodes[clone] = nodes[q];
		nodes[clone].len = nodes[p].len + 1;
		nodes[cur].link = nodes[q].link = clone;
		for (; ~p && nodes[p].next[x] == q; p = nodes[p].link) nodes[p].next[x] = clone;
	}

private:
	int buf[maxn * 2];
	int sort[maxn * 2];
	int g[maxn * 2];
public:
	LL calc()
	{
		for (int i = 0; i < size; i++) buf[nodes[i].len]++;
		for (int i = 1; i < size; i++) buf[i] += buf[i - 1];
		for (int i = size - 1; ~i; i--) sort[--buf[nodes[i].len]] = i;
		LL ans = 0;
		for (int i = size - 1; i; i--)
		{
			int node = sort[i];
			int q;
			g[q = nodes[node].link] += g[node];
			if (g[node] >= k) ans += nodes[node].len - nodes[q].len;
		}
		return ans;
	}
} sam;

void run()
{
	scanf("%s", str);
	n = strlen(str);
	k = readIn();
	for (int i = 0; i < n; i++)
		sam.extend(str[i]);
	printOut(sam.calc());
}

int main()
{
#ifndef LOCAL
	freopen("prob5.in", "r", stdin);
	freopen("prob5.out", "w", stdout);
#endif
	run();
	return 0;
}