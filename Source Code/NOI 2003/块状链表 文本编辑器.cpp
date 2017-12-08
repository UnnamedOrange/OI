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
#include <list>
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

struct BlockList
{
	static const INT maxn = 2 * 1024 * 1024 + 5;
	static const INT size = 1500; //std::sqrt(maxn)(1450)

	struct Block
	{
		INT s;
		char v[size];
		Block() : s(), v() {}
		Block(char* begin, char* end) : s(), v()
		{
			s = end - begin;
			memcpy(v, begin, sizeof(char) * s);
		}
	};
	std::list<Block> blocks;
	typedef std::list<Block>::iterator IT;

	IT locate(INT k, INT& remain)
	{
		IT it;
		remain = k;
		for (it = blocks.begin(); it != blocks.end(); it++)
		{
			if (remain <= it->s)
				return it;
			remain -= it->s;
		}
		return it;
	}
	void merge(IT l, IT r)
	{
		memcpy(l->v + l->s, r->v, sizeof(char) * r->s);
		l->s += r->s;
		blocks.erase(r);
	}
	void split(IT it, INT k)
	{
		if (k == it->s) return;
		IT next = it;
		next++;
		blocks.insert(next, Block(it->v + k, it->v + it->s));
		it->s = k;
	}
	void insert(char* begin, char* end, INT k)
	{
		IT it = locate(k, k);
		if (it != blocks.end())
			split(it, k);
		while (end - begin >= size)
		{
			blocks.insert(it, Block(begin, begin + size));
			begin += size;
		}
		if (end - begin)
		{
			blocks.insert(it, Block(begin, end));
		}
		if (it != blocks.end())
		{
			IT next = it;
			next++;
			if (next != blocks.end() && it->s + next->s <= size)
				merge(it, next);
		}
	}
	void erase(INT k, INT s)
	{
		IT it = locate(k, k);
		split(it, k);
		it++;
		IT next = it;
		while (s > 0)
		{
			next++;
			if (it->s < s)
			{
				s -= it->s;
				blocks.erase(it);
			}
			else
			{
				split(it, s);
				s -= it->s;
				blocks.erase(it);
			}
			it = next;
		}
		it = next;
		it--;
		if (next != blocks.end() && it->s + next->s <= size)
			merge(it, next);
	}
	void wander(INT k, INT s)
	{
		IT it = locate(k, k);
		while (s--)
		{
			putchar(it->v[k - 1]);
			k++;
			if (k >= it->s)
			{
				it++;
				k = 0;
			}
		}
	}
};

char buffer[2 * 1024 * 1024 + 5];
void run()
{
	INT q = readIn();
	BlockList editor;
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
			editor.insert(buffer, buffer + length, pos);
			break;
		}
		case 'D':
		{
			INT length = readIn();
			editor.erase(pos, length);
			break;
		}
		case 'G':
		{
			INT length = readIn();
			editor.wander(pos, length);
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