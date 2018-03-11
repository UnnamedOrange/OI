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
#include <unordered_map>
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

const int mod = int(1e9) + 7;
const int inv2 = 500000004;
LL N;

const int threshold = 6666666;
std::unordered_map<LL, LL> map;
int phi[threshold + 1];
void Euler()
{
	static bool isntPrime[threshold + 1];
	static int prime[threshold + 1];
	phi[0] = 0;
	phi[1] = 1;
	for (int i = 2; i <= threshold; i++)
	{
		if (!isntPrime[i])
		{
			prime[++prime[0]] = i;
			phi[i] = i - 1;
		}
		for (int j = 1, p = prime[j], s = i * p; j <= prime[0] && s <= threshold; j++, p = prime[j], s = i * p)
		{
			isntPrime[s] = true;
			if (i % p)
				phi[s] = phi[i] * (p - 1);
			else
			{
				phi[s] = phi[i] * p;
				break;
			}
		}
	}
	for (int i = 1; i <= threshold; i++)
		(phi[i] += phi[i - 1]) %= mod;
}
LL sieve(LL n)
{
	if (n <= threshold) return phi[n];
	if (map.count(n)) return map[n];
	LL ans = (n & 1) ? (n % mod * (((n + 1) >> 1) % mod)) : ((n >> 1) % mod * ((n + 1) % mod));
	for (LL i = 2, t; i <= n; i = t + 1)
	{
		t = n / (n / i);
		ans = (ans - (t - i + 1) % mod * sieve(n / i)) % mod + mod;
	}
	return map[n] = ans % mod;
}

void run()
{
	Euler();
	N = readIn();
	printOut(sieve(N));
}

int main()
{
	run();
	return 0;
}