#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

INT n, m;
class Splay
{
	struct Node
	{
		INT v;
		INT s;
		bool flip;
		Node* ch[2];
		Node() : v(), s(), flip(), ch() {}
		void maintain()
		{
			s = ch[0]->s + ch[1]->s + 1;
		}
		INT comp(INT k)
		{
			if (ch[0]->s + 1 == k) return -1;
			return ch[0]->s + 1 < k;
		}
		void pushdown()
		{
			Node* r = this;
			if (r->flip)
			{
				std::swap(r->ch[0], r->ch[1]);
				r->ch[0]->flip = !r->ch[0]->flip;
				r->ch[1]->flip = !r->ch[1]->flip;
				r->flip = false;
			}
		}
	};
	Node* null;
	Node* root;

public:
	Splay()
	{
		null = new Node;
		root = null->ch[0] = null->ch[1] = null;
	}

public:
	void clear() { clear(root); }
private:
	void clear(Node* &r)
	{
		if (r == null) return;
		clear(r->ch[0]);
		clear(r->ch[1]);
		delete r;
		r = null;
	}

public:
	void build(INT size)
	{
		clear(root);
		build(root, 0, size);
	}
private:
	void build(Node* &node, INT l, INT r)
	{
		node = new Node;
		node->ch[0] = node->ch[1] = null;
		node->maintain();
		INT mid = (l + r) >> 1;
		node->v = mid;

		if (l < mid) build(node->ch[0], l, mid - 1);
		if (r > mid) build(node->ch[1], mid + 1, r);
		node->maintain();
	}

private:
	void rotate(Node* &r, INT d)
	{
		Node* k = r->ch[d ^ 1];
		r->ch[d ^ 1] = k->ch[d];
		k->ch[d] = r;
		r->maintain();
		k->maintain();
		r = k;
	}

public:
	void select(INT k) { select(root, k); }
	void select(Node* &r, INT k)
	{
		r->pushdown();
		INT d = r->comp(k);
		if (d == -1) return;
		INT k1 = k - d * (r->ch[0]->s + 1);
		Node* p = r->ch[d];
		p->pushdown();
		INT d2 = p->comp(k1);
		INT k2 = k1 - d2 * (p->ch[0]->s + 1);
		if (d2 != -1)
		{
			select(p->ch[d2], k2);
			if (d == d2)
				rotate(r, d ^ 1);
			else
				rotate(r->ch[d], d2 ^ 1);
		}
		rotate(r, d ^ 1);
	}

private:
	Node* merge(Node* &r, Node* right)
	{
		select(r, r->s);
		r->ch[1] = right;
		r->maintain();
		return r;
	}

private:
	Node* split(Node* &r, INT k)
	{
		select(r, k);
		Node* ret = r->ch[1];
		r->ch[1] = null;
		r->maintain();
		return ret;
	}

public:
	void flip(INT l, INT r)
	{
		Node* mid = split(root, l);
		Node* right = split(mid, r - l + 1);
		mid->flip = !mid->flip;
		merge(root, merge(mid, right));
	}

public:
	void wander() { wander(root); }
private:
	void wander(Node* &r)
	{
		if (r == null) return;
		r->pushdown();
		wander(r->ch[0]);
		if (r->v)
		{
			printOut(r->v);
			putchar(' ');
		}
		wander(r->ch[1]);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	Splay splay;
	splay.build(n);
	while (m--)
	{
		INT l = readIn();
		INT r = readIn();
		splay.flip(l, r);
	}
	splay.wander();
}

int main()
{
	run();
	return 0;
}