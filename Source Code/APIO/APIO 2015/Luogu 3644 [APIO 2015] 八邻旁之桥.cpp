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
#define loop register int
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
int k, n;
LL base;
struct Place
{
	int a, b;
	bool operator<(const Place& y) const
	{
		return a + b < y.a + y.b;
	}
} places[maxn];

#define RunInstance(x) delete new x
struct cheat
{
	int all[maxn * 2];
	cheat()
	{
		for (int i = 1; i <= n; i++)
		{
			all[i - 1] = places[i].a;
			all[i - 1 + n] = places[i].b;
		}
		std::nth_element(all, all + n, all + (n << 1));
		int mid = all[n];
		LL ans = 0;
		for (loop i = 0, to = n << 1; i < to; i++)
			ans += std::abs(all[i] - mid);
		printOut(ans + base);
	}
};

struct work
{
	struct MultiSet : public std::multiset<int>
	{
		LL sum;
		MultiSet() : sum() {}
		void push(int t)
		{
			sum += t;
			std::multiset<int>::insert(t);
		}
		void pop(int t)
		{
			sum -= t; // note
			std::multiset<int>::erase(std::multiset<int>::find(t));
		}
	};
	struct OppositeSet
	{
		MultiSet small, big;
		void adjust()
		{
			if (!((small.size() + big.size()) & 1))
			{
				while (small.size() > big.size())
				{
					big.push(*small.rbegin());
					small.pop(*small.rbegin());
				}
				while (small.size() < big.size())
				{
					small.push(*big.begin());
					big.pop(*big.begin());
				}
			}
			else
			{
				while (small.size() > big.size() + 1)
				{
					big.push(*small.rbegin());
					small.pop(*small.rbegin());
				}
				while (small.size() < big.size() + 1)
				{
					small.push(*big.begin());
					big.pop(*big.begin());
				}
			}
		}
		void push(int x)
		{
			if (!big.size() || x < *big.begin())
				small.push(x);
			else
				big.push(x);
			adjust();
		}
		void pop(int x)
		{
			if (big.size() && x >= *big.begin())
				big.pop(x);
			else
				small.pop(x);
			adjust();
		}
	} set1, set2;

	static LL calc(const OppositeSet& set)
	{
		if (!set.small.size()) return 0;
		LL mid = *set.small.rbegin();
		return mid * set.small.size() - set.small.sum + set.big.sum - mid * set.big.size();
	}

	work()
	{
		LL INF;
		memset(&INF, 0x3f, sizeof(INF));
		std::sort(places + 1, places + 1 + n);
		for (int i = 1; i <= n; i++)
		{
			set2.push(places[i].a);
			set2.push(places[i].b);
		}

		LL ans = calc(set2);
		for (int i = 1; i <= n; i++)
		{
			set1.push(places[i].a);
			set1.push(places[i].b);
			set2.pop(places[i].a);
			set2.pop(places[i].b);
			ans = std::min(ans, calc(set1) + calc(set2));
		}
		printOut(ans + base);
	}
};

void run()
{
	k = readIn();
	n = readIn();

	int valid = 0;
	for (int i = 1; i <= n; i++)
	{
		char type[2][4];
		scanf("%s", type[0]);
		int p1 = readIn();
		scanf("%s", type[1]);
		int p2 = readIn();
		if (type[0][0] == type[1][0])
			base += std::abs(p1 - p2);
		else
		{
			if (type[0][0] == 'B')
				std::swap(p1, p2);
			valid++;
			places[valid].a = p1;
			places[valid].b = p2;
		}
	}
	n = valid;
	base += n;

	if (k == 1)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
	run();
	return 0;
}