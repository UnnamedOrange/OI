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

const int maxn = int(5e5) + 5;
class fhqTreap
{
	struct Node
	{
		int val;
		unsigned short key;
		int size;
		Node* ch[2];
		Node() {}
		void maintain() { size = 1 + ch[0]->size + ch[1]->size; }
	};
	Node* null;

	void alloc(Node* &node)
	{
		if (node == null)
		{
			node = new Node;
			node->ch[0] = node->ch[1] = null;
			node->size = 1;
			node->key = rand();
		}
	}
	Node* clone(const Node* node)
	{
		Node* ret = new Node(*node);
		return ret;
	}
	typedef std::pair<Node*, Node*> DNode;
	DNode split(Node* r, const int& x)
	{
		DNode ret(null, null);
		if (r == null) return ret;
		if (x < r->val)
		{
			ret = split(r->ch[0], x);
			r = clone(r); // note
			r->ch[0] = ret.second;
			ret.second = r;
		}
		else
		{
			ret = split(r->ch[1], x);
			r = clone(r); // note
			r->ch[1] = ret.first;
			ret.first = r;
		}
		r->maintain();
		return ret;
	}
	Node* merge(Node* left, Node* right)
	{
		if (left == null || right == null) return right == null ? left : right; // note
		if (left->key < right->key)
		{
			left = clone(left); // note
			left->ch[1] = merge(left->ch[1], right);
			left->maintain();
			return left;
		}
		else
		{
			right = clone(right); // note
			right->ch[0] = merge(left, right->ch[0]);
			right->maintain();
			return right;
		}
	}
	int kth(Node* node, int k)
	{
		if (node->ch[0]->size + 1 == k) return node->val;
		if (k < node->ch[0]->size + 1) return kth(node->ch[0], k);
		else return kth(node->ch[1], k - node->ch[0]->size - 1);
	}
	int size;
	Node* version[maxn];

public:
	fhqTreap() : size()
	{
		null = new Node;
		null->ch[0] = null->ch[1] = null;
		null->size = 0;
		version[0] = null;
	}
	void insert(const int& x)
	{
		DNode ret;
		ret = split(version[size], x);
		Node* node = null;
		alloc(node);
		node->val = x;
		version[size] = merge(merge(ret.first, node), ret.second);
	}
	void erase(const int& x)
	{
		DNode ret;
		ret = split(version[size], x - 1);
		Node* left = ret.first;
		ret = split(ret.second, x);
		Node* t = merge(ret.first->ch[0], ret.first->ch[1]); // 注意理清各结点间的关系
															 //delete ret.first; // 可持久化后不能删除
		version[size] = merge(left, merge(t, ret.second));
	}
	void clone(int ver)
	{
		version[++size] = version[ver];
	}
	int pre(int x)
	{
		DNode q = split(version[size], x - 1);
		if (!q.first->size) return -2147483647;
		return kth(q.first, q.first->size);
	}
	int next(int x)
	{
		DNode q = split(version[size], x);
		if (!q.second->size) return 2147483647;
		return kth(q.second, 1);
	}
	int kth(int k)
	{
		return kth(version[size], k);
	}
	int rank(int x)
	{
		DNode q = split(version[size], x - 1);
		return q.first->size + 1;
	}
};

void run()
{
	fhqTreap set;
	int n = readIn();
	for (int i = 1; i <= n; i++)
	{
		int ver = readIn();
		set.clone(ver);
		int ins = readIn();
		int x = readIn();
		if (ins == 1) set.insert(x);
		else if (ins == 2) set.erase(x);
		else if (ins == 3) printOut(set.rank(x));
		else if (ins == 4) printOut(set.kth(x));
		else if (ins == 5) printOut(set.pre(x));
		else if (ins == 6) printOut(set.next(x));
	}
}

int main()
{
	run();
	return 0;
}