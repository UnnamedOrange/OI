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

const int maxn = int(2e5) + 5;
int n, m;
int a[maxn];

struct Pool
{
	static const int megabyte = 90 * 1024 * 1024;
	typedef unsigned char BYTE;
	typedef unsigned long long PVOID;
	PVOID pool, cnt;
	void realloc()
	{
		pool = (PVOID)new BYTE[megabyte];
		cnt = pool;
	}
	Pool() { realloc(); }
	void* operator()(std::size_t size)
	{
		if (cnt + size > pool + megabyte)
			realloc();
		PVOID ret = cnt;
		cnt += size;
		return (void*)ret;
	}
} allocator;

class FuncSegTree
{
	struct Node
	{
		int val;
		int minval;
		Node* ch[2];
		Node() : val(), minval() {}
		void* operator new(std::size_t size) { return allocator(size); }
		void operator delete(void*) {}
		void maintain()
		{
			minval = std::min(ch[0]->minval, ch[1]->minval);
		}
	};
	Node* null;

	int size;
	Node* versions[maxn];

	int g_Pos, g_Val;

	void insert(Node* &node, int l, int r, Node* source)
	{
		if (!(l <= g_Pos && g_Pos <= r))
		{
			node = source;
			return;
		}
		node = new Node;
		if (l == r)
		{
			node->minval = node->val = g_Val;
			return;
		}
		int mid = (l + r) >> 1;
		insert(node->ch[0], l, mid, source->ch[0]);
		insert(node->ch[1], mid + 1, r, source->ch[1]);
		node->maintain();
	}

public:
	FuncSegTree()
	{
		null = new Node;
		null->ch[0] = null->ch[1] = null;
		versions[size = 0] = null;
	}
	void clone()
	{
		size++;
		versions[size] = versions[size - 1];
	}
	void insert(int pos, int val)
	{
		g_Pos = pos;
		g_Val = val;
		insert(versions[size], 0, n + 1, versions[size]);
	}
	int query(int L, int R)
	{
		Node* cnt = versions[R];
		int l = 0, r = n + 1;
		while (r - l)
		{
			int mid = (l + r) >> 1;
			if (cnt->ch[0]->minval >= L)
			{
				l = mid + 1;
				cnt = cnt->ch[1];
			}
			else
			{
				r = mid;
				cnt = cnt->ch[0];
			}
		}
		return l;
	}
} st;

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = std::min(readIn(), n - 1);

	for (int i = 1; i <= n; i++)
	{
		st.clone();
		st.insert(a[i], i);
	}

	while (m--)
	{
		int l = readIn();
		int r = readIn();
		printOut(st.query(l, r));
	}
}

int main()
{
	run();
	return 0;
}