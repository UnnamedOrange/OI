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
	putchar('\n');
}

const int maxn = int(1e5) + 5;
int n, m;
struct Task
{
	int s, e, p;
	void read() { s = readIn(); e = readIn(); p = readIn(); }
} tasks[maxn];
LL lastans = 1;
int pos, k;

struct fhqTreap
{
	struct Node
	{
		unsigned int key;
		Node* ch[2];
		int size;
		int val;
		LL sum;
		void maintain()
		{
			size = 1 + ch[0]->size + ch[1]->size;
			sum = val + ch[0]->sum + ch[1]->sum;
		}
	};
	Node* null;
	Node* version[maxn];

	static inline unsigned int RAND()
	{
		static ULL base;
		base = base * 131313131 + 20000919;
		return base;
	}
	Node* alloc(const int& val)
	{
		Node* ret = new Node;
		ret->ch[0] = ret->ch[1] = null;
		ret->val = val;
		ret->size = 1;
		ret->key = RAND();
		ret->maintain();
		return ret;
	}
	Node* clone(const Node* r)
	{
		return new Node(*r);
	}

	typedef std::pair<Node*, Node*> DNode;
	DNode split(Node* r, const int& x)
	{
		DNode ret(null, null);
		if (r == null) return ret;
		if (x < r->val)
		{
			ret = split(r->ch[0], x);
			r = clone(r);
			r->ch[0] = ret.second;
			ret.second = r;
		}
		else
		{
			ret = split(r->ch[1], x);
			r = clone(r);
			r->ch[1] = ret.first;
			ret.first = r;
		}
		r->maintain();
		return ret;
	}
	Node* merge(Node* left, Node* right)
	{
		if (left == null || right == null) return right == null ? left : right;
		if (left->key < right->key)
		{
			left = clone(left);
			left->ch[1] = merge(left->ch[1], right);
			left->maintain();
			return left;
		}
		else
		{
			right = clone(right);
			right->ch[0] = merge(left, right->ch[0]);
			right->maintain();
			return right;
		}
	}

	int size;

	LL query(Node* node, int k)
	{
		if (node == null) return 0;
		if (k < node->ch[0]->size + 1)
			return query(node->ch[0], k);
		else if (k == node->ch[0]->size + 1)
			return node->ch[0]->sum + node->val;
		else
			return node->ch[0]->sum + node->val + query(node->ch[1], k - node->ch[0]->size - 1);
	}

public:
	fhqTreap()
	{
		null = new Node;
		null->ch[0] = null->ch[1] = null;
		null->sum = null->val = null->size = 0;
		version[size = 0] = null;
	}
	void clone()
	{
		size++;
		version[size] = version[size - 1];
	}
	void erase(const int& x)
	{
		DNode ret = split(version[size], x - 1);
		Node* left = ret.first;
		ret = split(ret.second, x);
		Node* mid = ret.first;
		Node* right = ret.second;
		version[size] = merge(merge(left, merge(mid->ch[0], mid->ch[1])), right);
	}
	void insert(const int& x)
	{
		DNode ret = split(version[size], x);
		version[size] = merge(merge(ret.first, alloc(x)), ret.second);
	}
	LL query(int ver, int k)
	{
		Node* entrance = version[ver];
		if (!k) return 0;
		if (k >= entrance->size) return entrance->sum;
		return query(entrance, k);
	}
} treap;

struct Event
{
	int type;
	int pos;
	int idx;
	Event() {}
	Event(int type, int pos, int idx) : type(type), pos(pos), idx(idx) {}
	bool operator<(const Event& b) const
	{
		return pos < b.pos;
	}
} events[maxn * 2];
int nEvent;

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		tasks[i].read();
	for (int i = 1; i <= n; i++)
	{
		events[++nEvent] = Event(true, tasks[i].s, i);
		events[++nEvent] = Event(false, tasks[i].e + 1, i);
	}
	std::sort(events + 1, events + 1 + nEvent);

	int pre = 0;
	for (int i = 1; i <= nEvent; i++)
	{
		const Event& e = events[i];
		for (; pre < e.pos; pre++)
			treap.clone();
		if (e.type == 0)
		{
			treap.erase(tasks[e.idx].p);
		}
		else if (e.type == 1)
		{
			treap.insert(tasks[e.idx].p);
		}
	}
	for (; pre < n; pre++)
		treap.clone();

	while (m--)
	{
		pos = readIn();
		int a = readIn();
		int b = readIn();
		int c = readIn();
		k = 1 + ((LL)a * lastans + b) % c;

		printOut(lastans = treap.query(pos, k));
	}
}

int main()
{
	run();
	return 0;
}