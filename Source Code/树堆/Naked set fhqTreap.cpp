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

const int maxn = int(3e5) + 5;

template <typename T>
class fhqTreap
{
	struct Node
	{
		T val;
		unsigned int key;
		Node* ch[2];
		int size;
		Node() : key((rand() << 15) | rand()) {}
		void maintain()
		{
			size = ch[0]->size + ch[1]->size + 1;
		}
	};
	Node* null;
	Node* root;
	void alloc(Node* &node)
	{
		if (node == null)
		{
			node = new Node;
			node->size = 1;
			node->ch[0] = node->ch[1] = null;
		}
	}

	void split(Node* r, Node* &left, Node* &right, const T& x)
	{
		if (r == null) return void(left = right = null);
		if (x < r->val) right = r, split(r->ch[0], left, r->ch[0], x);
		else left = r, split(r->ch[1], r->ch[1], right, x);
		r->maintain(); // note
	}
	Node* merge(Node* left, Node* right)
	{
		if (left == null || right == null) return right == null ? left : right;
		if (left->key < right->key)
		{
			left->ch[1] = merge(left->ch[1], right);
			left->maintain(); // note
			return left;
		}
		else
		{
			right->ch[0] = merge(left, right->ch[0]); // note;
			right->maintain();
			return right;
		}
	}
	bool count(Node* &node, const T& x)
	{
		if (node == null) return false;
		if (x < node->val) return count(node->ch[0], x);
		else if (x > node->val) return count(node->ch[1], x);
		else return true;
	}

public:
	fhqTreap()
	{
		null = new Node;
		null->ch[0] = null->ch[1] = null;
		null->size = 0;
		root = null;
	}
	void insert(const T& x)
	{
		Node *left, *right;
		split(root, left, right, x);
		Node* node = null;
		alloc(node);
		node->val = x;
		root = merge(merge(left, node), right);
	}
	void erase(const T& x)
	{
		Node *left, *right;
		split(root, left, right, x - 1); // note: to optimize
		Node* del;
		split(right, del, right, x);
		delete del;
		root = merge(left, right);
	}
	bool count(const T& x)
	{
		return count(root, x);
	}
	int size() { return root->size; }
};

void run()
{
	fhqTreap<int> set;
	int n = readIn();

	while (n--)
	{
		int ins = readIn();
		if (ins == 1)
			set.insert(readIn());
		else if (ins == 2)
		{
			int x = readIn();
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