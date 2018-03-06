#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <cassert>
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
	INT_PUT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

struct ACAutomation
{
	static const int alphabet = 26;
	static inline int code(char ch)
	{
		return ch - 'a';
	}
	struct Node
	{
		Node* c[alphabet];
		Node* fail;
		Node* suffix;
		int cnt;
		Node() : c(), fail(), suffix(), cnt() {}
	};
	struct Pool
	{
		std::stack<Node*> p;
		std::stack<Node*> used;
		Node* alloc()
		{
			Node* ret;
			if (p.empty()) ret = new Node;
			else
			{
				ret = p.top();
				p.pop();
				used.push(ret);
				new(ret) Node;
			}
			return ret;
		}
		void reset()
		{
			while (!used.empty())
			{
				p.push(used.top());
				used.pop();
			}
		}
	};
	static Pool pool;

	Node* root;
	ACAutomation()
	{
		isInitialized = false;
		root = pool.alloc();
	}
	void reset()
	{
		pool.reset(); // 需要改造内存池
		new(this) ACAutomation;
	}

	bool isInitialized;

	void insert(const char* str)
	{
		if (isInitialized) throw;
		Node* cnt = root;
		for (; *str != '\0'; str++)
		{
			Node* &p = cnt->c[code(*str)];
			if (!p) p = pool.alloc();
			cnt = p;
		}
		cnt->cnt++;
	}
	void initialize()
	{
		if (isInitialized) throw;
		isInitialized = true;
		std::queue<Node*> q;
		q.push(root);
		while (!q.empty())
		{
			Node* cnt = q.front();
			q.pop();
			for (int i = 0; i < alphabet; i++)
			{
				Node* &to = cnt->c[i];
				Node* t = cnt == root ? root : cnt->fail->c[i]; // 由于是递推，所以 cnt->fail->c[i] 一定是已经算了的
				if (!to)
					to = t; // 没有的话直接 = cnt->fail->c[i] 构建 Trie 图
				else
				{
					to->fail = t; // 有的话计算出 Fail 指针
					to->suffix = to->fail->cnt ? to->fail : to->fail->suffix; //记住算出 suffix
					q.push(to);
				}
			}
		}
	}
	int match(const char* str)
	{
		if (!isInitialized) throw;
		int ret = 0;
		Node* cnt = root;
		for (; *str != '\0'; str++)
		{
			int c = code(*str);
			cnt = cnt->c[c]; // 直接走
			for (Node* t = cnt; t; t = t->suffix)
			{
				ret += t->cnt;
				t->cnt = 0;
			}
		}
		return ret;
	}
};
ACAutomation::Pool ACAutomation::pool;

int n;
ACAutomation ac;

void run()
{
	int T = readIn();
	while (T--)
	{
		n = readIn();
		ac.reset();
		for (int i = 1; i <= n; i++)
		{
			static char buffer[55];
			scanf("%s", buffer);
			ac.insert(buffer);
		}
		ac.initialize();
		static char buffer[1000005];
		scanf("%s", buffer);
		printOut(ac.match(buffer));
	}
}

int main()
{
	run();
	return 0;
}