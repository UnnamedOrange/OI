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

class BlockList
{
	static const INT size = 5000;
	struct Block
	{
		INT s;
		char v[size];
		Block() : s() {}
		Block(char* begin, char* end) : s(), v()
		{
			s = end - begin;
			std::copy(begin, end, v);
		}
	};
	std::list<Block> blocks;
	typedef std::list<Block>::iterator IT;
	static IT Next(IT it) { IT ret = it; return ++ret; }

	IT locate(INT& k)
	{
		IT it;
		for (it = blocks.begin(); it != blocks.end(); it++)
		{
			if (k <= it->s)
				return it;
			k -= it->s;
		}
		return it;
	}
	void maintain()
	{
		IT it;
		for (it = blocks.begin(); it != blocks.end(); it++)
		{
			IT next = Next(it);
			while (next != blocks.end() && it->s + next->s <= size)
			{
				merge(it, next);
				next = Next(it);
			}
		}
	}
	void merge(IT l, IT r)
	{
		std::copy(r->v, r->v + r->s, l->v + l->s);
		l->s += r->s;
		blocks.erase(r);
	}
	bool split(IT it, INT k)
	{
		if (k >= it->s) return false;
		blocks.insert(Next(it), Block(it->v + k, it->v + it->s));
		it->s = k;
		return true;
	}

public:
	void insert(char* begin, char* end, INT k)
	{
		IT it = locate(k);
		if (it != blocks.end())
		{
			split(it, k);
			it++;
		}
		while (end - begin >= size)
		{
			blocks.insert(it, Block(begin, begin + size));
			begin += size;
		}
		if (end - begin)
		{
			blocks.insert(it, Block(begin, end));
		}
		maintain();
	}
	void erase(INT k, INT s)
	{
		IT it = locate(k);
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
		maintain();
	}
	typedef void(*Func)(const char& v);
	void wander(INT k, INT s, Func op)
	{
		IT it = locate(k);
		k--;
		while (s--)
		{
			op(it->v[k++]);
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
			editor.wander(pos + 1, length, [](const char& ch) { putchar(ch); });
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