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
typedef unsigned long long ULL;
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
	putchar('\n');
}

template <typename T>
struct Treap
{
	static ULL randEx()
	{
#define r(x) (ULL(rand()) << x)
		return r(15) | r(0);
#undef r
	}
	struct Node
	{
		T v;
		ULL r;
		INT s;
		Node* ch[2];
		Node() : r(randEx()), v(), s(), ch() {}
		INT comp(T x)
		{
			if (!(v < x) && !(x < v))
				return -1;
			return v < x;
		}
		void maintain()
		{
			s = ch[0]->s + ch[1]->s + 1;
		}
	};
	Node *null, *root;

	Treap()
	{
		null = new Node;
		root = null->ch[0] = null->ch[1] = null;
	}
	~Treap()
	{
		clear(root);
		delete null;
	}
	void clear(Node* r)
	{
		if (r == null)
			return;
		clear(r->ch[0]);
		clear(r->ch[1]);
		delete r;
	}
	void rotate(Node* &r, INT d)
	{
		Node* k = r->ch[d ^ 1];
		r->ch[d ^ 1] = k->ch[d];
		r->maintain();
		k->ch[d] = r;
		r = k;
		r->maintain();
	}
	bool count(const T x)
	{
		return count(root, x);
	}
	bool count(Node* r, const T x)
	{
		if (r == null) return false;
		INT d = r->comp(x);
		if (d == -1) return true;
		return count(r->ch[d], x);
	}
	void insert(const T x)
	{
		insert(root, x);
	}
	void insert(Node* &r, const T x)
	{
		if (r == null)
		{
			r = new Node();
			r->ch[0] = r->ch[1] = null;
			r->v = x;
			r->maintain();
			return;
		}
		INT d = r->comp(x);
		if (d == -1) return;
		insert(r->ch[d], x);
		r->maintain();
		if (r->ch[d]->r > r->r)
			rotate(r, d ^ 1);
	}
	void erase(const T x)
	{
		erase(root, x);
	}
	void erase(Node* &r, const T x)
	{
		if (r == null) return;
		INT d = r->comp(x);
		if (d == -1)
		{
			if (r->ch[0] == null)
			{
				Node* k = r;
				r = r->ch[1];
				if (k != null) delete k;
				return;
			}
			else if (r->ch[1] == null)
			{
				Node* k = r;
				r = r->ch[0];
				if (k != null) delete k;
				return;
			}
			else
			{
				INT d2 = r->ch[0]->r < r->ch[1]->r;
				rotate(r, d2 ^ 1);
				erase(r->ch[d2 ^ 1], x);
			}
		}
		else
		{
			erase(r->ch[d], x);
		}
		r->maintain();
	}
	INT size()
	{
		return root->s;
	}
};

void run()
{
	Treap<INT> set;
	INT n = readIn();
	while (n--)
	{
		INT ins = readIn();
		if (ins == 1)
			set.insert(readIn());
		else if (ins == 2)
		{
			INT x = readIn();
			if (!set.count(x))
			{
				printOut(0);
			}
			else
			{
				set.erase(x);
				printOut(1);
			}
		}
		else
			printOut(set.size());
	}
}

int main()
{
	run();
	return 0;
}
