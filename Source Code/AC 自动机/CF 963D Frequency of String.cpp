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

struct Pool
{
	typedef unsigned char BYTE;
	typedef unsigned long long PVOID;
	static const std::size_t threshold = int(6e4) * 232;
	PVOID pool;
	PVOID cnt;
	PVOID end;
	Pool() : pool(), cnt(), end() {}
	void* operator()(std::size_t size)
	{
		if (cnt + size >= end || !pool)
		{
			pool = (PVOID)new BYTE[threshold];
			cnt = pool;
			end = pool + threshold;
		}
		PVOID ret = cnt;
		cnt += size;
		return (void*)ret;
	}
} allocator;
struct ACAutomaton
{
	static const int alphabet = 26;
	static inline int code(char ch) { return ch - 'a'; }
	struct Node
	{
		void* operator new(std::size_t size) { return allocator(size); }
		void operator delete(void*) {}
		int cnt;
		Node* fail;
		Node* suffix;
		Node* ch[alphabet];
		Node() : cnt(), fail(), suffix(), ch() {}
	};
	Node* root;
	ACAutomaton() { root = new Node; }

	void insert(char* s, int idx)
	{
		Node* cnt = root;
		for (; *s; s++)
		{
			int x = code(*s);
			if (!cnt->ch[x])
				cnt->ch[x] = new Node;
			cnt = cnt->ch[x];
		}
		cnt->cnt = idx;
	}
	void build()
	{
		std::queue<Node*> q;
		q.push(root);
		while (!q.empty())
		{
			Node* cnt = q.front();
			q.pop();
			for (int i = 0; i < alphabet; i++)
			{
				Node* &to = cnt->ch[i];
				Node* t = cnt == root ? root : cnt->fail->ch[i];
				if (!to)
					to = t;
				else
				{
					to->fail = t;
					to->suffix = to->fail->cnt ? to->fail : to->fail->suffix;
					q.push(to);
				}
			}
		}
	}
	void match(char* s, const std::function<void(int pos, int idx)> callback)
	{
		Node* cnt = root;
		for (int pos = 0; *s; s++, pos++)
		{
			int x = code(*s);
			cnt = cnt->ch[x];

			for (Node* t = cnt; t; t = t->suffix)
			{
				if (t->cnt)
				{
					callback(pos, t->cnt);
				}
			}
		}
	}
} ac;

const int maxn = int(1e5) + 5;
char str[maxn];
int n;
int k[maxn];
int len[maxn];
char buffer[maxn];

std::vector<std::vector<int> > pos;
void callback(int p, int idx)
{
	pos[idx].push_back(p);
}

void run()
{
	scanf("%s", str);
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		k[i] = readIn();
		scanf("%s", buffer);
		len[i] = strlen(buffer);
		ac.insert(buffer, i);
	}
	ac.build();

	pos.resize(n + 1);
	ac.match(str, callback);

	for (int i = 1; i <= n; i++)
	{
		const std::vector<int>& vec = pos[i];
		if (vec.size() < k[i])
			printOut(-1);
		else
		{
			int ans = maxn;
			for (int j = 0, r = k[i] - 1; r < vec.size(); j++, r++)
				ans = std::min(ans, len[i] + vec[r] - vec[j]);
			printOut(ans);
		}
	}
}

int main()
{
	run();
	return 0;
}