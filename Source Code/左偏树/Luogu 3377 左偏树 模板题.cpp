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
	putchar('\n');
}

//because of the merge operation, the method of "null" is not available
//so use NULL to replace it
template <typename T>
class Leftist
{
	struct Node
	{
		T v;
		INT dis;
		Node* ch[2];
		Node() : v(), dis(-1), ch() {}
		Node(const T v) : v(v), dis(0), ch() {}
	};
	Node* root;
	INT s;

private:
	void operator= (const Leftist& b) {} //no copy function

public:
	Leftist() : root(), s() {}
	~Leftist()
	{
		clear();
	}
private:
	void clear(Node* &r)
	{
		if (!r) return;
		clear(r->ch[0]);
		clear(r->ch[1]);
		delete r;
		r = NULL;
	}
public:
	void clear()
	{
		clear(root);
		s = 0;
	}

	//the below are significant
private:
	static Node* merge(Node* a, Node* b)
	{
		if (!a) return b;
		else if (!b) return a;
		if (b->v < a->v)
			std::swap(a, b);
		a->ch[1] = merge(a->ch[1], b);
		if (a->ch[1])
			a->dis = a->ch[1]->dis + 1;
		else
			a->dis = 0;
		return a;
	} //core
public:
	void merge(Leftist &inner)
	{
		root = merge(root, inner.root);
		s += inner.s;
		inner.root = NULL;
		inner.s = NULL;
	}

public:
	void push(const T v)
	{
		root = merge(root, new Node(v));
		s++;
	}
public:
	T top()
	{
		return root->v;
	}
public:
	void pop()
	{
		Node* old = root;
		root = merge(root->ch[0], root->ch[1]);
		delete old;
		s--;
	}
public:
	INT size() { return s; }
};

const INT maxn = 100005;
INT n, m;
struct DS
{
	INT parent[maxn];
	void clear(INT size)
	{
		for (int i = 0; i <= size; i++)
			parent[i] = i;
	}
	INT find(INT x)
	{
		if (parent[x] == x) return x;
		return parent[x] = find(parent[x]);
	}
	void unite(INT x, INT y)
	{
		parent[find(y)] = find(x);
	}
	bool judge(INT x, INT y)
	{
		return find(x) == find(y);
	}
} ds;

struct Node
{
	INT val;
	INT pos;
	Node() : val(), pos() {}
	Node(INT val, INT pos) : val(val), pos(pos) {}
	bool operator< (const Node& b) const
	{
		if (val != b.val) return val < b.val;
		return pos < b.pos;
	}
};
Leftist<Node> ls[maxn];

bool dead[maxn];

void run()
{
	n = readIn();
	m = readIn();
	ds.clear(n);
	for (int i = 1; i <= n; i++)
		ls[i].push(Node(readIn(), i));
	while (m--)
	{
		INT ins = readIn();
		if (ins == 1)
		{
			INT x = readIn();
			INT y = readIn();
			if (dead[x] || dead[y]) continue;
			if (ds.judge(x, y)) continue;
			ls[ds.find(x)].merge(ls[ds.find(y)]);
			ds.unite(x, y);
		}
		else if (ins == 2)
		{
			INT x = readIn();
			if (dead[x])
			{
				printOut(-1);
				continue;
			}
			Node ans = ls[ds.find(x)].top();
			printOut(ans.val);
			dead[ans.pos] = true;
			ls[ds.find(x)].pop();
		}
	}
}

int main()
{
	run();
	return 0;
}