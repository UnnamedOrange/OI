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
	putchar(' ');
}

INT n, m;
class BlockList
{
	static const INT size = 1000;
	struct Block
	{
		bool flip;
		INT s;
		INT v[size];
		Block() : flip(), s() {}
		Block(INT* begin, INT* end, bool flip = false) : flip(flip)
		{
			s = end - begin;
			std::copy(begin, end, v);
		}
		Block(INT begin, INT end) : flip()
		{
			s = end - begin;
			for (int i = begin; i < end; i++)
				v[i - begin] = i;
		}
		void pushdown()
		{
			if (flip)
			{
				std::reverse(v, v + s);
				flip = false;
			}
		}
	};
	typedef std::list<Block>::iterator IT;
	std::list<Block> blocks;
	static IT Next(IT it) { return ++it; }
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
				it = merge(it, next);
				next = Next(it);
			}
		}
	}
	IT merge(IT l, IT r)
	{
		if (l->flip && r->flip)
		{
			std::swap(l, r);
		}
		else
		{
			l->pushdown();
			r->pushdown();
		}
		std::copy(r->v, r->v + r->s, l->v + l->s);
		l->s += r->s;
		blocks.erase(r);
		return l;
	}
	IT split(IT it, INT k)
	{
		if (k >= it->s) return it;
		if (it->flip)
		{
			blocks.insert(it, Block(it->v + it->s - k, it->v + it->s, it->flip));
			it->s -= k;
			return --it;
		}
		else
		{
			blocks.insert(Next(it), Block(it->v + k, it->v + it->s));
			it->s = k;
			return it;
		}
	}

public:
	void build(INT k)
	{
		INT s = 1;
		while (k - s + 1 >= size)
		{
			blocks.push_back(Block(s, s + size));
			s += size;
		}
		if (k - s + 1 > 0)
			blocks.push_back(Block(s, k + 1));
	}
	void flip(INT l, INT r)
	{
		l--;
		INT k = l;
		IT begin = locate(k);
		begin = split(begin, k);
		begin++;
		k = r - l;
		IT it;
		for (it = begin; k && it != blocks.end(); it++)
		{
			if (k >= it->s)
			{
				it->flip ^= 1;
				k -= it->s;
			}
			else
			{
				it = split(it, k);
				k -= it->s;
				it->flip ^= 1;
			}
		}
		std::reverse(begin, it);
		maintain();
	}
	void wander()
	{
		INT k = 0;
		for (IT it = blocks.begin(); it != blocks.end(); it++)
		{
			if (it->flip)
				for (int i = it->s - 1; i >= 0; i--)
					printOut(it->v[i]);
			else
				for (int i = 0; i < it->s; i++)
					printOut(it->v[i]);
		}
	}
};

void run()
{
	n = readIn();
	m = readIn();
	BlockList bl;
	bl.build(n);
	while (m--)
	{
		INT l = readIn();
		INT r = readIn();
		bl.flip(l, r);
	}
	bl.wander();
}

int main()
{
	run();
	return 0;
}