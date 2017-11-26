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

template <typename T>
class Splay
{
	struct Node
	{
		T v;
		INT s;
		Node* ch[2];
		Node() : v(), s(), ch() {}

		INT comp(const T x) const
		{
			if (!(v < x) && !(x < v)) return -1;
			return v < x;
		}
		INT compRank(INT k) const
		{
			if (k == ch[0]->s + 1) return -1;
			return k > ch[0]->s + 1;
		}
		void maintain()
		{
			s = ch[0]->s + ch[1]->s + 1;
		}
		static void rotate(Node* &r, INT d)
		{
			Node* k = r->ch[d ^ 1];
			r->ch[d ^ 1] = k->ch[d];
			k->ch[d] = r;
			r->maintain();
			k->maintain();
			r = k;
		}
		static void splay(Node* &r, INT k)
		{
			if (k <= 0 || k > r->s) return;
			INT d = compRank;
			if (d == -1)
				return;
			INT k1 = k - d * (r->ch[0]->s + 1);
			INT d2 = r->ch[d]->compRank(k1);
			INT k2 = k1 - d2 * (r->ch[d]->ch[0]->s + 1);
			if (d2 != -1)
			{
				if (d == d2)
					rotate(r, d ^ 1);
				else
					rotate(r->ch[d], d2 ^ 1);
			}
			rotate(r, d ^ 1);
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
	~Splay()
	{
		clear();
		delete null;
	}

public:
	void clear()
	{
		clear(root);
	}
private:
	void clear(Node* r)
	{
		if (r == null) return;
		clear(r->ch[0]);
		clear(r->ch[1]);
		delete r;
	}

public:
	void build(T* begin, T* end)
	{
		clear();
		std::sort(begin, end);
		build(root, begin, std::unique(begin, end));
	}
private:
	void build(Node* &r, T* begin, T* end)
	{
		if (begin == end)
		{
			r = null;
			return;
		}
		INT s = end - begin;
		r = new Node;
		build(r->ch[0], begin, begin + s / 2);
		r->v = begin[s / 2];
		build(r->ch[1], begin + s / 2 + 1, end);
		r->maintain();
	}

public:
	void print()
	{
		print(root);
	}
private:
	void print(Node* r)
	{
		if (r == null) return;
		print(r->ch[0]);
		cout << r->v << " ";
		print(r->ch[1]);
	}
};

void run()
{
	Splay<INT> splay;
	INT a[] = { 1, 3, 5, 2, 6, 2, 1 };
	splay.build(a, a + (sizeof(a) / sizeof(INT)));
	splay.print();
}

int main()
{
	run();
	return 0;
}
