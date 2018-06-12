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
typedef LL INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = std::getchar();
	while (!(std::isdigit(ch) || ch == '-')) ch = std::getchar();
	if (ch == '-')
	{
		positive = false;
		ch = std::getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = std::getchar();
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

const int mod = 998244353;
LL n, a, b, c, d;
LL gcd(LL a, LL b)
{
	return b ? gcd(b, a % b) : a;
}
int T;
struct Query
{
	LL n, a, b, c, d;
	void read()
	{
		n = readIn();
		a = readIn();
		b = readIn();
		c = readIn();
		d = readIn();
	}
	void release()
	{
		::n = n;
		::a = a;
		::b = b;
		::c = c;
		::d = d;
	}
} querys[5];

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		for (int o = 1; o <= T; o++)
		{
			querys[o].release();
			int ans = 0;
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j < i; j++)
				{
					if (a * i <= b * j && j * d <= c * i && gcd(i, j) == 1)
					{
						ans++;
					}
				}
			}
			printOut(ans);
		}
	}
};
struct cheat
{
	static const int maxn = int(1e7);

	bool isntPrime[maxn + 5];
	int mu[maxn + 5];
	int prime[664580];

	void init()
	{
		prime[0] = 0;
		mu[0] = 0;
		mu[1] = 1;
		for (int i = 2; i <= int(1e7); i++)
		{
			if (!isntPrime[i])
			{
				prime[++prime[0]] = i;
				mu[i] = -1;
			}
			for (int j = 1, p = prime[j], s = i * p; j <= prime[0] && s <= int(1e7); j++, p = prime[j], s = i * p)
			{
				isntPrime[s] = true;
				if (i % p)
					mu[s] = -mu[i];
				else
				{
					mu[s] = 0;
					break;
				}
			}
		}

		for (int i = 2; i <= int(1e7); i++)
			mu[i] += mu[i - 1];
	}

	LL sum[maxn + 5];

	LL calc(LL up, LL down)
	{
		LL ans = 0;

		sum[0] = 0;
		for (int i = 1; i <= n; i++)
			sum[i] = (sum[i - 1] + up * i / down) % mod;

		for (int i = 1, t; i <= n; i = t + 1)
		{
			t = n / (n / i);
			ans -= (mu[t] - mu[i - 1]) * sum[n / i];
		}
		return ans;
	}

	void solve()
	{
		printOut(((calc(a, b) - calc(c, d) + (n >= b)) % mod + mod) % mod);
	}

	cheat() : isntPrime()
	{
		init();

		for (int i = 1; i <= T; i++)
		{
			querys[i].release();
			solve();
		}
	}
};
struct work
{
	static const int maxn = int(1e7);

	bool isntPrime[maxn + 5];
	int mu[maxn + 5];
	int prime[664580];

	void init()
	{
		prime[0] = 0;
		mu[0] = 0;
		mu[1] = 1;
		for (int i = 2; i <= int(1e7); i++)
		{
			if (!isntPrime[i])
			{
				prime[++prime[0]] = i;
				mu[i] = -1;
			}
			for (int j = 1, p = prime[j], s = i * p; j <= prime[0] && s <= int(1e7); j++, p = prime[j], s = i * p)
			{
				isntPrime[s] = true;
				if (i % p)
					mu[s] = -mu[i];
				else
				{
					mu[s] = 0;
					break;
				}
			}
		}

		for (int i = 2; i <= int(1e7); i++)
			mu[i] += mu[i - 1];
	}

	struct HashTable
	{
		static const int size = int(1e6) + 3;
		struct Node
		{
			ULL key;
			LL val;
			int next;
			Node() {}
			Node(ULL key, LL val) : key(key), val(val), next(-1) {}
		};
		int head[size];
		std::vector<Node> nodes;
		HashTable()
		{
			std::memset(head, -1, sizeof(head));
		}
		int query(ULL key) const
		{
			int cnt = head[key % size];
			while (~cnt)
			{
				const Node& t = nodes[cnt];
				if (t.key == key)
					return cnt;
				cnt = t.next;
			}
			return -1;
		}
		void insert(ULL key, LL val)
		{
			int cnt = head[key % size];
			if (!~cnt)
			{
				head[key % size] = nodes.size();
				nodes.push_back(Node(key, val));
			}
			else
			{
				while (~nodes[cnt].next)
				{
					if (nodes[cnt].key == key) throw;
					cnt = nodes[cnt].next;
				}
				nodes[cnt].next = nodes.size();
				nodes.push_back(Node(key, val));
			}
		}
	} hash;

	LL Mu(LL n)
	{
		if (n <= LL(1e7)) return mu[n];
		LL ans = hash.query(n);
		if (~ans) return hash.nodes[ans].val;
		ans = 1;
		for (LL i = 2, t; i <= n; i = t + 1)
		{
			t = n / (n / i);
			ans = (ans - (t - i + 1) % mod * Mu(n / i)) % mod;
		}
		hash.insert(n, ans);
		return ans;
	}

	LL F(LL n)
	{
		if (n & 1) return (n + 1) / 2 % mod * (n % mod) % mod;
		return n / 2 % mod * ((n + 1) % mod) % mod;
	}
	LL Euclid(LL a, LL b, LL c, LL n)
	{
		if (a >= c || b >= c)
			return ((a / c) * F(n) % mod + (b / c) * (n + 1) % mod + Euclid(a % c, b % c, c, n)) % mod;
		if (!a)
			return 0;
		return ((a * n + b) / c % mod * n - Euclid(c, c - b - 1, a, (a * n + b) / c - 1)) % mod;
	}

	LL calc(LL up, LL down)
	{
		LL ans = 0;

		LL pre = 0;
		for (LL i = 1, t; i <= n; i = t + 1)
		{
			t = n / (n / i);
			LL cnt = Mu(t);
			ans -= (cnt - pre) % mod * Euclid(up, 0, down, n / i) % mod;
			ans %= mod;
			pre = cnt;
		}
		return ans;
	}

	void solve()
	{
		printOut(((calc(a, b) - calc(c, d) + (n >= b)) % mod + mod) % mod);
	}

	work() : isntPrime()
	{
		init();

		for (int i = 1; i <= T; i++)
		{
			querys[i].release();
			solve();
		}
	}
};

void run()
{
	T = readIn();
	for (int i = 1; i <= T; i++)
		querys[i].read();

	LL maxn = 0;
	for (int i = 1; i <= T; i++)
		maxn = std::max(maxn, querys[i].n);

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("fraction.in", "r", stdin);
	freopen("fraction.out", "w", stdout);
#endif
	run();
	return 0;
}