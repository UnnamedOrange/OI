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
}

INT q;

class Splay
{
	struct Node
	{
		char v;
		INT s;
		Node* ch[2];
		Node() : v(), s(), ch() {}
		void maintain()
		{
			s = ch[0]->s + ch[1]->s + 1;
		}
		INT comp(INT k)
		{
			if (k == ch[0]->s + 1) return -1;
			return ch[0]->s + 1 < k;
		}
	};
	Node *null;
	Node *root;

public:
	Splay()
	{
		null = new Node;
		null->ch[0] = null->ch[1] = null;
		root = new Node;
		root->ch[1] = new Node;
		root->ch[0] = root->ch[1]->ch[0] = root->ch[1]->ch[1] = null;
		root->ch[1]->maintain();
		root->maintain();
	}

private:
	void rotate(Node* &r, INT d)
	{
		Node* k = r->ch[d ^ 1];
		r->ch[d ^ 1] = k->ch[d];
		k->ch[d] = r;
		r->maintain();
		k->maintain();
		r = k;
	}
	void select(Node* &r, INT k)
	{
		INT d = r->comp(k);
		if (d == -1) return;
		INT k1 = k - d * (r->ch[0]->s + 1);
		Node* &p = r->ch[d];
		INT d2 = p->comp(k1);
		INT k2 = k1 - d2 * (p->ch[0]->s + 1);
		if (d2 != -1)
		{
			select(p->ch[d2], k2);
			if (d == d2)
				rotate(r, d ^ 1);
			else
				rotate(p, d2 ^ 1);
		}
		rotate(r, d ^ 1);
	}

public:
	void wander(INT l, INT r)
	{
		Node* mid = split(root, l + 1);
		Node* right = split(mid, r - l + 1);
		wander(mid);
		merge(root, merge(mid, right));
	}
private:
	void wander(Node* r)
	{
		if (r == null) return;
		wander(r->ch[0]);
		putchar(r->v);
		wander(r->ch[1]);
	}
private:
	Node* split(Node* &r, INT k)
	{
		select(r, k);
		Node* ret = r->ch[1];
		r->ch[1] = null;
		r->maintain();
		return ret;
	}
	Node* merge(Node* &l, Node* r)
	{
		select(l, l->s);
		l->ch[1] = r;
		l->maintain();
		return l;
	}
public:
	void erase(INT l, INT r)
	{
		Node* mid = split(root, l + 1);
		Node* right = split(mid, r - l + 1);
		merge(root, right);
	}
public:
	void insert(char* str, INT k)
	{
		INT length = strlen(str);
		Node* ins = null;
		make(ins, 0, length, str);
		Node* right = split(root, k + 1);
		merge(root, merge(ins, right));
	}
private:
	void make(Node* &node, INT l, INT r, char* str)
	{
		if (l >= r) return;
		node = new Node;
		node->ch[0] = node->ch[1] = null;
		INT mid = (l + r) >> 1;
		node->v = str[mid];
		make(node->ch[0], l, mid, str);
		make(node->ch[1], mid + 1, r, str);
		node->maintain();
	}
};

char buffer[2 * 1024 * 1024 + 5];
void run()
{
	q = readIn();
	Splay editor;
	INT pos = 0;
	while (q--)
	{
		char ins[10];
		scanf("%s", ins);
		switch (ins[0])
		{
		case 'M':
		{
			pos = readIn();
			break;
		}
		case 'I':
		{
			INT length = readIn();
			for (int i = 0; i < length; i++)
			{
				char ch = getchar();
				while (!(ch >= 32 && ch <= 126)) ch = getchar();
				buffer[i] = ch;
			}
			buffer[length] = '\0';
			editor.insert(buffer, pos);
			break;
		}
		case 'D':
		{
			INT length = readIn();
			editor.erase(pos, pos + length - 1);
			break;
		}
		case 'G':
		{
			INT length = readIn();
			editor.wander(pos, pos + length - 1);
			putchar('\n');
			break;
		}
		case 'P':
		{
			pos--;
			break;
		}
		case 'N':
		{
			pos++;
			break;
		}
		default:
			break;
		}
	}
}

int main()
{
	run();
	return 0;
}