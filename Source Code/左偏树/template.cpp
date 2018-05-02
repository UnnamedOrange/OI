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
}

template <typename T, typename C = std::less<T> >
class priority_queue
{
	struct Node
	{
		T v;
		int dis;
		Node* ch[2];
		Node() : v(), dis(-1), ch() {}
		Node(const T& v) : v(v), dis(0), ch() {}
	};
	Node* root;
	int s;

private:
	void operator=(const priority_queue&) {} // ½ûÖ¹¿½±´

public:
	priority_queue() : root(), s() {}
	~priority_queue() { clear(); }

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
	void clear() { clear(root); }

public:
	int size() { return s; }
	bool empty() { return !s; }

	// significant below
private:
	static Node* merge(Node* a, Node* b)
	{
		if (!b) return a;
		if (!a) return b;
		if (C()(b->v, a->v)) std::swap(a, b);
		a->ch[1] = merge(a->ch[1], b);
		if (!a->ch[0] || (a->ch[1] && a->ch[1]->dis > a->ch[0]->dis)) // note
			std::swap(a->ch[0], a->ch[1]);
		if (a->ch[1])
			a->dis = a->ch[1]->dis + 1;
		else
			a->dis = 0;
		return a;
	}
public:
	void merge(priority_queue& b)
	{
		root = merge(root, b.root);
		s += b.s;
		b.root = NULL;
		b.s = NULL;
	}

public:
	void push(const T& x)
	{
		root = merge(root, new Node(x));
		s++;
	}
	const T& top() const
	{
		return root->v;
	}
	void pop()
	{
		Node* del = root;
		root = merge(root->ch[0], root->ch[1]);
		delete del;
		s--;
	}
};

void run()
{

}

int main()
{
	run();
	return 0;
}