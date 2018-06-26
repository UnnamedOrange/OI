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
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = int;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int mod = int(1e9) + 7;
int n;

int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}

#define RunInstance(x) delete new x
struct brute1
{
	brute1()
	{
		register int ans = 0;
		for (register int i = 1; i <= n; i++)
			for (register int j = i + 1; j <= n; j++)
			{
				register int t;
				register int g = gcd(i, j);
				if (g == 1)
					ans = (t = ans + i + j) >= mod ? t - mod : t;
				else
					ans = (t = ans + (i + j) / g) >= mod ? t - mod : t;
			}
		ans = (ans - ((LL)n * n - n) % mod + mod) % mod;

		printOut((ans << 1) % mod);
	}
};
struct brute2
{
	static const int maxN = int(1e7) + 5;
	bool isntPrime[maxN]{};
	int prime[664580];
	int f[maxN];

	void init()
	{
		const int to = int(1e7);
		prime[0] = 0;
		isntPrime[1] = true;
		f[0] = 0;
		f[1] = 1;
		for (int i = 2; i <= to; i++)
		{
			if (!isntPrime[i])
			{
				prime[++prime[0]] = i;
				f[i] = 1 - i;
			}

			for (int j = 1, p = prime[j], s = i * p;
				j <= prime[0] && s <= to; j++, p = prime[j], s = i * p)
			{
				isntPrime[s] = true;
				if (i % p)
				{
					f[s] = (LL)f[i] * f[p] % mod;
				}
				else
				{
					f[s] = f[i];
					break;
				}
			}
		}

		for (int i = 2; i <= to; i++)
			f[i] = ((LL)f[i - 1] + f[i] + mod) % mod;
	}

	brute2()
	{
		init();
		LL ans = (LL)-2 * n * n;
		ans = (ans % mod + mod) % mod;
		for (int i = 1, t; i <= n; i = t + 1)
		{
			t = n / (n / i);
			int Div = n / i;
			ans = (ans + (LL)(Div + 1) * Div % mod * Div % mod *
				(f[t] - f[i - 1]) % mod + mod) % mod;
		}
		printOut(ans);
	}
};
struct work
{
	static const int maxN = int(1e7) + 5;
	bool isntPrime[maxN]{};
	int prime[664580];
	int f[maxN];

	void init()
	{
		const int to = int(1e7);
		prime[0] = 0;
		isntPrime[1] = true;
		f[0] = 0;
		f[1] = 1;
		for (int i = 2; i <= to; i++)
		{
			if (!isntPrime[i])
			{
				prime[++prime[0]] = i;
				f[i] = -i;
			}

			for (int j = 1, p = prime[j], s = i * p;
				j <= prime[0] && s <= to; j++, p = prime[j], s = i * p)
			{
				isntPrime[s] = true;
				if (i % p)
				{
					f[s] = (LL)f[i] * f[p] % mod;
				}
				else
				{
					f[s] = 0;
					break;
				}
			}
		}

		for (int i = 2; i <= to; i++)
			f[i] = ((LL)f[i - 1] + f[i] + mod) % mod;
	}
	struct HashTable
	{
		struct Node
		{
			int key;
			int val;
			int next;
			Node() = default;
			Node(int key) : key(key), val(), next(-1) {}
		};
		std::vector<Node> nodes;
		static const int size = int(1e6) + 7;
		int head[size];
		HashTable() { std::memset(head, -1, sizeof(head)); }
		int query(int key)
		{
			int cnt = head[key % size];
			while (~cnt)
			{
				if (nodes[cnt].key == key)
					return nodes[cnt].val;
				cnt = nodes[cnt].next;
			}
			return -1;
		}
		void insert(int key, int val)
		{
			int cnt = head[key % size];
			if (~cnt)
			{
				while (~nodes[cnt].next)
					cnt = nodes[cnt].next;
				nodes[cnt].next = nodes.size();
				nodes.push_back(Node(key));
				nodes.back().val = val;
			}
			else
			{
				head[key % size] = nodes.size();
				nodes.push_back(Node(key));
				nodes.back().val = val;
			}
		}
	} table;
	static inline int calc(int from, int to)
	{
		int x = from + to;
		int y = to - from + 1;
		if (!(x & 1)) x >>= 1;
		if (!(y & 1)) y >>= 1;
		return (LL)x * y % mod;
	}
	int F(int x)
	{
		if (x <= int(1e7))
			return f[x];
		int ret = table.query(x);
		if (~ret) return ret;
		ret = 1;
		for (int i = 2, t; i <= x; i = t + 1)
		{
			t = x / (x / i);
			ret = (ret - (LL)F(x / i) * calc(i, t)) % mod;
		}
		ret = (ret + mod) % mod;
		table.insert(x, ret);
		return ret;
	}
	int calcRight(int x)
	{
		int ret = 0;
		for (int i = 1, t; i <= x; i = t + 1)
		{
			t = x / (x / i);
			int val = x / i;
			ret = (ret + (LL)(t - i + 1) * (val + 1) % mod * val % mod * val) % mod;
		}
		return ret;
	}
	work()
	{
		init();
		LL ans = (LL)-2 * n * n;
		ans = (ans % mod + mod) % mod;
		for (int i = 1, t; i <= n; i = t + 1)
		{
			t = n / (n / i);
			int left = (F(t) - F(i - 1) + mod) % mod;
			int right = calcRight(n / i);
			ans = (ans + (LL)left * right) % mod;
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("box.in", "r", stdin);
	freopen("box.out", "w", stdout);
#endif
	run();
	return 0;
}