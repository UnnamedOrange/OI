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
}

const int maxn = int(1e5) + 5;
struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxn];
	int i;
	int head[maxn];
	Graph() : i()
	{
		memset(head, -1, sizeof(head));
	}
	void addEdge(int from, int to)
	{
		edges[i].to = to;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
#define idx(G) idx_##G
#define wander(G, node) for (int idx(G) = G.head[node]; ~idx(G); idx(G) = G.edges[idx(G)].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx(G)]; int to = e.to
} G;
class Pool
{
	static const int size = int(3e6);
	typedef unsigned char BYTE;
	typedef void* PVOID;
	BYTE pool[size];
	PVOID cnt;

public:
	Pool() : cnt((PVOID)pool) {}
	PVOID operator()(std::size_t size)
	{
		PVOID ret = cnt;
		cnt = (PVOID)((BYTE*)(cnt)+size);
		return ret;
	}
} allocator;
template <typename T, typename C = std::less<T> >
class priority_queue
{
	struct Node
	{
		T v;
		int dis;
		Node* ch[2];
		Node(const T& v) : v(v), dis(0) {}
		void* operator new(std::size_t size) { return allocator(size); }
		void operator delete(void*) {}
	};
	Node* root;
	int s;

public:
	priority_queue() : root(), s(), sum() {}

private:
	static Node* merge(Node* a, Node* b)
	{
		if (!b) return a;
		if (!a) return b;
		if (C()(b->v, a->v))
			std::swap(a, b);
		a->ch[1] = merge(a->ch[1], b);
		if (!a->ch[0] || (a->ch[1] && a->ch[0]->dis < a->ch[1]->dis))
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
		s += b.s;
		sum += b.sum;
		root = merge(root, b.root);
		b.root = NULL;
		b.s = NULL;
		b.sum = NULL;
	}

public:
	LL sum;
	void push(const T& v)
	{
		sum += v;
		root = merge(root, new Node(v));
		s++;
	}
	void pop()
	{
		sum -= root->v;
		root = merge(root->ch[0], root->ch[1]);
		s--;
	}
	T top()
	{
		return root->v;
	}
	int size()
	{
		return s;
	}
};

int n, m;
int parent[maxn];
int cost[maxn];
int lead[maxn];
priority_queue<int, std::greater<int> > pq[maxn];

int q[maxn];
void BFS()
{
	int head = 0, tail = 0;
	q[tail++] = 1;
	while (head != tail)
	{
		int from = q[head++];
		pq[from].push(cost[from]);
		wander(G, from)
		{
			DEF(G);
			q[tail++] = to;
		}
	}
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		G.addEdge(parent[i] = readIn(), i);
		cost[i] = readIn();
		lead[i] = readIn();
	}
	BFS();

	LL ans = 0;
	for (int i = n - 1; ~i; i--)
	{
		int node = q[i];
		ans = std::max(ans, (LL)lead[node] * pq[node].size());
		priority_queue<int, std::greater<int> >& pqp = pq[parent[node]];
		pqp.merge(pq[node]);
		while (pqp.sum > m)
			pqp.pop();
	}
	printOut(ans);
}

int main()
{
	run();
	return 0;
}