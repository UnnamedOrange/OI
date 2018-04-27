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
	void operator=(const priority_queue&) {} // 禁止拷贝

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

// if (x <= L) f[x] += w; // 让新的边权为 0
// if (L < x && x <= L + w) f[x] = f[L] + (w - (x - L)); // 让新的边权为 x - L
// if (L + w < x && x <= R + w) f[x] = f[L]; // 让新的边权为 w
// if (x > R + w) f[x] = f[L] + ((x - R) - w); // 让新的边权为 x - R

const int maxn = int(6e5) + 5;
int n, m, E;
int degree[maxn];
int parent[maxn];
int weight[maxn];
priority_queue<long long, std::greater<long long> > pq[maxn];
LL sum;

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 2; i <= n + m; i++)
	{
		degree[parent[i] = readIn()]++;
		sum += weight[i] = readIn();
	}
	for (int i = n + m; i > 1; i--)
	{
		long long l = 0, r = 0;
		if (i <= n)
		{
			for (int j = 1; j < degree[i]; j++)
				pq[i].pop(); // 最后留下了 L 和 R
			r = pq[i].top();
			pq[i].pop();
			l = pq[i].top();
			pq[i].pop();
		}
		pq[i].push(l + weight[i]);
		pq[i].push(r + weight[i]);
		pq[parent[i]].merge(pq[i]); // 合并到父结点
	}
	for (int i = 1; i <= degree[1]; i++)
		pq[1].pop(); // 最后只剩下了 L
	while (pq[1].size())
	{
		sum -= pq[1].top(); // 依次减去横坐标，正好就是函数值
		pq[1].pop();
	}
	printOut(sum);
}

int main()
{
	run();
	return 0;
}