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
typedef long long INT_PUT;
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

LL a, b;

struct HashTable
{
	static const int mod = 1000007;
	int size;
	int head[mod];
	struct Node
	{
		LL key;
		LL map;
		int next;
	} nodes[100000];
	HashTable() : size()
	{
		memset(head, -1, sizeof(head));
	}
	LL query(LL key)
	{
		int idx = key % mod;
		for (int i = head[idx]; ~i; i = nodes[i].next)
			if (nodes[i].key == key)
				return nodes[i].map;
		return -1;
	}
	void insert(LL key, LL map)
	{
		int idx = key % mod;
		nodes[size].key = key;
		nodes[size].map = map;
		nodes[size].next = head[idx];
		head[idx] = size;
		size++;
	}
} hash;
const int threshold = int(1e7);
LL mu[threshold + 1];
void Euler()
{
	mu[0] = 0;
	mu[1] = 1;
	static int prime[threshold];
	static bool isntPrime[threshold + 1];
	for (int i = 2; i <= threshold; i++)
	{
		if (!isntPrime[i])
		{
			prime[++prime[0]] = i;
			mu[i] = -1;
		}
		for (int j = 1, p = prime[j], s = i * p; j <= prime[0] && s <= threshold; j++, p = prime[j], s = i * p)
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
	for (int i = 1; i <= threshold; i++) mu[i] += mu[i - 1];
}
LL sieve(LL n)
{
	if (n <= threshold) return mu[n];
	LL ans;
	if ((ans = hash.query(n)) != -1) return ans;
	ans = 1;
	for (LL i = 2, t; i <= n; i = t + 1)
	{
		t = n / (n / i);
		ans -= (t - i + 1) * sieve(n / i);
	}
	hash.insert(n, ans);
	return ans;
}

void run()
{
	Euler();
	a = readIn();
	b = readIn();
	printOut(sieve(b) - sieve(a - 1));
}

int main()
{
	run();
	return 0;
}