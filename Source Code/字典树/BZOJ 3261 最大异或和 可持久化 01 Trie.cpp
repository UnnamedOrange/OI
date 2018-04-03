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
	static bool printed;
	putchar('\n');
}

const int maxn = int(6e5) + 5;
class Func01Trie
{
	static const int bitlen = 24;
	struct Node
	{
		int val;
		Node* ch[2];
		Node() : val() {}
	};
	Node* null;
	int size;
	Node* version[maxn];

	Node* clone(const Node* r)
	{
		return new Node(*r);
	}

	int g_Val;
	void insert(Node* &node, int depth, Node* source)
	{
		node = clone(source);
		node->val++;
		if (!~depth)
			return;
		bool next = g_Val & (1 << (depth));
		insert(node->ch[next], depth - 1, source->ch[next]);
	}

public:
	Func01Trie()
	{
		null = new Node;
		null->ch[0] = null->ch[1] = null;
		version[size = 0] = null;
	}
	void clone()
	{
		size++;
		version[size] = version[size - 1];
	}
	void insert(int num)
	{
		g_Val = num;
		insert(version[size], bitlen - 1, version[size]);
	}
	int query(int l, int r, int x)
	{
		Node* lnode = version[l - 1];
		Node* rnode = version[r];
		int sum = 0;
		for (int i = bitlen - 1; ~i; i--)
		{
			bool bit = x & (1 << i);
			if (rnode->ch[!bit]->val - lnode->ch[!bit]->val)
			{
				sum |= 1 << i;
				lnode = lnode->ch[!bit];
				rnode = rnode->ch[!bit];
			}
			else
			{
				lnode = lnode->ch[bit];
				rnode = rnode->ch[bit];
			}
		}
		return sum;
	}
} trie;

int a[maxn];
int n;

void run()
{
	n = readIn();
	int q = readIn();
	a[1] = 0;
	n++;
	trie.clone();
	trie.insert(0);
	for (int i = 2; i <= n; i++)
	{
		a[i] = readIn() ^ a[i - 1];
		trie.clone();
		trie.insert(a[i]);
	}

	while (q--)
	{
		char ins[10];
		scanf("%s", ins);
		if (ins[0] == 'A')
		{
			n++;
			a[n] = readIn();
			a[n] ^= a[n - 1];
			trie.clone();
			trie.insert(a[n]);
		}
		else if (ins[0] == 'Q')
		{
			int l = readIn();
			int r = readIn();
			int x = readIn() ^ a[n];
			printOut(trie.query(l, r, x));
		}
	}
}

int main()
{
	run();
	return 0;
}