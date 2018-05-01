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

const int maxn = 2005;
int n, a, b, bitlen;
LL y[maxn];

#define RunInstance(x) delete new x
struct work1
{
	static const int maxN = 105;
	LL ans;
	bool f[maxN][maxN];
	work1() : ans()
	{
		for (int i = 0; i <= bitlen; i++)
			ans |= LL(1) << i;
		for (int i = bitlen; ~i; i--)
		{
			memset(f, 0, sizeof(f));
			for (int j = 1; j <= n; j++)
			{
				f[j][1] = ((y[j] | ans) <= ans) && !(y[j] & (LL(1) << i));
				for (int k = 2, to = std::min(j, b); k <= to; k++)
				{
					for (int s = k - 1; s < j; s++)
					{
						LL delta = y[j] - y[s];
						if ((delta | ans) <= ans && !(delta & (LL(1) << i)))
							f[j][k] |= f[s][k - 1];
					}
				}
			}
			bool bOk = false;
			for (int j = a; j <= b; j++)
				if (f[n][j])
				{
					bOk = true;
					break;
				}
			if (bOk)
				ans ^= LL(1) << i;
		}
		printOut(ans);
	}
};
struct work2
{
	LL ans;
	int INF;
	int f[maxn];

	work2() : ans()
	{
		memset(&INF, 0x3f, sizeof(INF));
		for (int i = 0; i <= bitlen; i++)
			ans |= LL(1) << i;
		for (int i = bitlen; ~i; i--)
		{
			memset(f, 0x3f, sizeof(f));
			f[0] = 0;
			if ((y[1] | ans) <= ans && !(y[1] & (LL(1) << i)))
				f[1] = 1;
			for (int j = 2; j <= n; j++)
				for (int k = 0; k < j; k++)
				{
					LL delta = y[j] - y[k];
					if ((delta | ans) <= ans && !(delta & (LL(1) << i)))
						f[j] = std::min(f[j], f[k] + 1);
				}
			if (f[n] <= b)
				ans ^= LL(1) << i;
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	a = readIn();
	b = readIn();
	for (int i = 1; i <= n; i++)
		y[i] = readIn();
	for (int i = 2; i <= n; i++)
		y[i] += y[i - 1];
	bitlen = 63;
	while (bitlen && !(y[n] & (LL(1) << bitlen)))
		bitlen--;

	if (a != 1)
		RunInstance(work1);
	else
		RunInstance(work2);
}

int main()
{
	run();
	return 0;
}