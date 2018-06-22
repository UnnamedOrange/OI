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

const int mod = 998244353;
const int maxn = int(5e5) + 5;
int n, m;
int a[maxn];

#define RunInstance(x) delete new x
struct cheat
{
	LL ans;
	int temp[maxn];
	void mergesort(int l, int r)
	{
		if (l == r) return;
		int mid = (l + r) >> 1;
		mergesort(l, mid);
		mergesort(mid + 1, r);
		int i = l, j = mid + 1, k = l;
		while (k <= r)
		{
			if (j > r || (i <= mid && a[i] <= a[j]))
			{
				temp[k++] = a[i++];
			}
			else
			{
				ans += mid - i + 1;
				temp[k++] = a[j++];
			}
		}
		for (i = l; i <= r; i++)
			a[i] = temp[i];
	}
	cheat() : ans()
	{
		mergesort(1, n);
		printOut(ans % mod);
	}
};
struct brute
{
	static const int maxN = 205;
	int f[maxN][maxN][maxN];
	int sum1[maxN];
	int sum2[maxN];

	brute()
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				f[0][i][j] = a[i] < a[j];

		LL t = ((LL)n * (n - 1) / 2 - (n - 2) - (n - 2) - 1) % mod;
		for (int i = 1; i <= m; i++)
		{
			std::memset(sum1, 0, sizeof(sum1));
			std::memset(sum2, 0, sizeof(sum2));
			for (int j = 1; j <= n; j++)
				for (int k = 1; k <= n; k++) if (j != k)
				{
					sum1[j] = (sum1[j] + f[i - 1][j][k]) % mod;
					sum2[k] = (sum2[k] + f[i - 1][j][k]) % mod;
				}

			for (int j = 1; j <= n; j++)
				for (int k = 1; k <= n; k++) if (j != k)
				{
					f[i][j][k] = ((LL)sum1[j] - f[i - 1][j][k] +
						sum2[k] - f[i - 1][j][k] + f[i - 1][k][j] +
						t * f[i - 1][j][k]) % mod;
				}
		}

		int ans = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j < i; j++)
				ans = (ans + f[m][i][j]) % mod;
		printOut(ans);
	}
};
struct work
{
	work()
	{

	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();

	if (!m)
		RunInstance(cheat);
	else if (n <= 200)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("mksort.in", "r", stdin);
	freopen("mksort.out", "w", stdout);
#endif
	run();
	return 0;
}