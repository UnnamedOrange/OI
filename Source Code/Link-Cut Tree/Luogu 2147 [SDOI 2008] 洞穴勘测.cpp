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

const int maxn = 10005;
int n, m;

typedef class LinkCutTree
{
	typedef struct SplayNode
	{
		bool flag; // reverse
		SplayNode* ch[2];
		SplayNode* parent;
		SplayNode() : flag() {}
		void pushdown()
		{
			if (flag)
			{
				std::swap(ch[0], ch[1]);
				ch[0]->flag ^= 1;
				ch[1]->flag ^= 1;
				flag = false;
			}
		}
	} Node;
	Node* null;
	Node nodes[maxn];

	int isRoot(Node* node)
	{
		return node->parent->ch[0] != node && node->parent->ch[1] != node;
	}
	int trace(Node* node)
	{
		return node->parent->ch[1] == node; // �� 0 �� 1
	}
	void rotate(Node* r) // ��ת�� r �ĸ�����λ��
	{
		Node* father = r->parent; // �����
		Node* grand = father->parent; // ү���
		int d = trace(r);
		if (!isRoot(father)) grand->ch[grand->ch[1] == father] = r; // ү���Ķ��ӱ���� r
		father->ch[d] = r->ch[d ^ 1];
		father->ch[d]->parent = father; // r ���ӽ��� parent �����˱仯
		father->parent = r; // r �ĸ����� parent �����˱仯
		r->ch[d ^ 1] = father;
		r->parent = grand; // r �ĸ���㷢���˱仯
	}
	void pushdown(Node* r) // �´����� r �������ϵı��
	{
		if (isRoot(r)) return void(r->pushdown());
		pushdown(r->parent);
		r->pushdown();
	}
	void splay(Node* r) // ��ת r ���� 
	{
		pushdown(r);
		while (!isRoot(r)) // ����������ת
		{
			Node* father = r->parent;
			// �����һ���ͣ�����ת���棻�����֮���Σ�����ת����
			if (!isRoot(father)) rotate(trace(r) == trace(father) ? father : r);
			rotate(r);
		}
	}
	void reverse(Node* r)
	{
		r->flag ^= 1;
	}

public:
	LinkCutTree()
	{
		null = new Node;
		null->parent = null->ch[0] = null->ch[1] = null;
	}
	void init()
	{
		for (int i = 1; i <= n; i++)
			nodes[i].ch[0] = nodes[i].ch[1] = nodes[i].parent = null;
	}
	void access(int code) // ֮ǰ�� node->ch[1] �� parent û��
	{
		Node* pre = null;
		Node* node = nodes + code;
		while (node != null)
		{
			splay(node);
			node->ch[1] = pre;
			pre = node;
			node = node->parent;
		}
	}
	void makeroot(int code) // ָ������Ϊ��Ӧ��ͨ���� LCT �еĸ�
	{
		Node* node = nodes + code;
		access(code);
		splay(node); // ע�������Ҳ�� Splay �ĸ�
		reverse(node);
	}
	int findroot(int code) // Ѱ��ĳ������Ӧ��ͨ���� LCT �еĸ�
	{
		Node* node = nodes + code;
		access(code);
		splay(node);
		while (node->ch[0] != null)
			node = node->ch[0];
		return node - nodes;
	}
	void link(int x, int y)
	{
		makeroot(x); // x ���� Splay �ĸ����
		(nodes + x)->parent = nodes + y;
	}
	void cut(int x, int y)
	{
		Node* node = nodes + y;
		makeroot(x);
		access(y);
		splay(node);
		(nodes + x)->parent = node->ch[0] = null;
	}
} LCT;

LCT tree;

void run()
{
	n = readIn();
	m = readIn();
	tree.init();
	while (m--)
	{
		char ins[10];
		scanf("%s", ins);
		int x = readIn();
		int y = readIn();
		if (ins[0] == 'Q')
			puts(tree.findroot(x) == tree.findroot(y) ? "Yes" : "No");
		else if (ins[0] == 'D')
			tree.cut(x, y);
		else if (ins[0] == 'C')
			tree.link(x, y);
	}
}

int main()
{
	run();
	return 0;
}