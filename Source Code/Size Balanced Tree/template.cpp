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
#include <list>
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
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
void printOut(INT x)
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

template<typename T>
class SBT
{
	struct Node
	{
		T v;
		INT s;
		Node* ch[2];
		Node() : v(), s(), ch() {}
		Node(const T& v) : v(v), s(), ch() {}
		void maintain()
		{
			s = ch[0]->s + ch[1]->s + 1;
		}
		INT comp(const T& x) const
		{
			if (!(v < x) && !(x < v)) return -1;
			return v < x;
		}
		INT compRank(INT k) const
		{
			if (ch[0]->s + 1 == k) return -1;
			return ch[0]->s + 1 < k;
		}
	};
	Node* null;
	Node* root;

public:
	SBT()
	{
		null = new Node;
		root = null->ch[0] = null->ch[1] = null;
	}
	~SBT()
	{
		clear();
		delete null;
	}

private:
	void clear(Node* &r)
	{
		if (r == null) return;
		clear(r->ch[0]);
		clear(r->ch[1]);
		delete r;
	}
public:
	void clear() { clear(root); }

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

private:
	void adjust(Node* &r, INT d)
	{
		if (r->ch[d] == null) return;
		else if (r->ch[d]->ch[d]->s > r->ch[d ^ 1]->s)
			rotate(r, d ^ 1);
		else if (r->ch[d]->ch[d ^ 1]->s > r->ch[d ^ 1]->s)
		{
			rotate(r->ch[d], d);
			rotate(r, d ^ 1);
		}
		else return;
		adjust(r->ch[0], 0);
		adjust(r->ch[1], 1);
		adjust(r, 0);
		adjust(r, 0);
	}

private:
	void insert(Node* &r, const T& x)
	{
		if (r == null)
		{
			r = new Node(x);
			r->ch[0] = r->ch[1] = null;
			r->maintain();
			return;
		}
		INT d = r->comp(x);
		if (d == -1) return;
		insert(r->ch[d], x);
		r->maintain();
		adjust(r, d ^ 1);
	}
public:
	void insert(const T x) { insert(root, x); }

private:
	bool count(Node* r, const T& x) const
	{
		if (r == null)
			return false;
		INT d = r->comp(x);
		if (d == -1) return true;
		return count(r->ch[d], x);
	}
public:
	bool count(const T x) const { return count(root, x); }

public:
	INT size() const { return root->s; }

private:
	void deleteNode(Node* &r, Node* parent)
	{
		if (r->ch[1] == null)
		{
			parent->v = r->v;
			Node* del = r;
			r = r->ch[0];
			delete del;
			return;
		}
		deleteNode(r->ch[1], parent);
		r->maintain();
	}
	void erase(Node* &r, const T& x)
	{
		if (r == null)
			return;
		INT d = r->comp(x);
		if (d == -1)
		{
			if (r->ch[0] == null || r->ch[0] == null)
			{
				Node* k;
				if (r->ch[0] != null) k = r->ch[0];
				else k = r->ch[1];
				delete r;
				r = k;
			}
			else
			{
				deleteNode(r->ch[0], r);
				r->maintain();
				adjust(r, 1);
			}
			return;
		}
		else
			erase(r->ch[d], x);
		r->maintain();
		adjust(r, d); //TODO
	}
public:
	void erase(const T x) { erase(root, x); }

private:
	INT rank(Node* r, const T& x, INT k) const
	{
		if (r == null)
			return 0;
		INT d = r->comp(x);
		if (d == -1)
			return k + r->ch[0]->s + 1;
		return rank(r->ch[d], x, k + d * (r->ch[0]->s + 1));
	}
public:
	INT rank(const T x) const { return rank(root, x, 0); }

private:
	const T& kth(Node* r, INT k)
	{
		INT d = r->compRank(k);
		if (d == -1)
			return r->v;
		return kth(r->ch[d], k - d * (r->ch[0]->s + 1));
	}
public:
	bool kth(INT k, T& ans)
	{
		if (!(0 < k && k <= root->s)) return false;
		ans = kth(root, k);
		return true;
	}
};

void run()
{
	SBT<INT> set;
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