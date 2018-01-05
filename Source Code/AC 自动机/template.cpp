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

const INT maxn = INT(1e6) + 5;
INT n;

class ACAutomation
{
	static const INT alphabet = 26;
	inline static INT code(char ch)
	{
		return ch - 'a';
	}

	INT clock_;
	struct Node
	{
		Node* c[alphabet];
		Node* fail;
		INT count;

		INT dfn;
		Node() : c(), fail(), count(), dfn(-1) {}
	};
	Node* root;

public:
	ACAutomation()
	{
		root = new Node;
	}

	void insert(const char* T)
	{
		Node* cnt = root;
		for (; *T != '\0'; T++)
		{
			Node* &next = cnt->c[code(*T)];
			if (!next)
				next = new Node;
			cnt = next;
		}
		cnt->count++;
	}
	void init()
	{
		BFS();
	}
	void BFS()
	{
		static Node* q[maxn];
		INT head = 0, tail = 0;
		q[tail++] = root;
		while (head != tail)
		{
			Node* p = q[head++];
			for (int i = 0; i < alphabet; i++)
			{
				if (Node* &p2 = p->c[i])
				{
					q[tail++] = p2;

					Node* pre = p->fail;
					while (pre && !pre->c[i])
						pre = pre->fail;
					p2->fail = pre ? pre->c[i] : root;
				}
			}
		}
	}
	INT match(const char* S)
	{
		clock_++;
		INT ret = 0;
		Node* cnt = root;
		for (; *S != '\0'; S++)
		{
			INT ch = code(*S);
			while (cnt && !cnt->c[ch]) cnt = cnt->fail;
			cnt = cnt ? cnt->c[ch] : root;
			for (Node* t = cnt; t; t = t->fail)
			{
				if (t->dfn != clock_)
				{
					t->dfn = clock_;
					ret += t->count;
				}
			}
		}
		return ret;
	}
};

char buffer[maxn];
void run()
{
	n = readIn();
	ACAutomation ac;
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", buffer);
		ac.insert(buffer);
	}
	ac.init();
	scanf("%s", buffer);
	printOut(ac.match(buffer));
}

int main()
{
	run();
	return 0;
}