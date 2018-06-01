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
typedef int INT_PUT;
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
const int maxn = int(1e5) + 5;
int n;
int a[maxn];

int t[maxn];
int f[maxn];

int g[maxn];

int temp[maxn];
int count_[maxn];
void cdq(int l, int r)
{
	if (l == r)
	{
		if (f[l] == 1)
			g[l] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	cdq(l, mid);

	for (int i = l; i <= r; i++)
		temp[i] = i;
	std::sort(temp + l, temp + mid + 1,
		[](const int& x, const int& y)
	{
		if (a[x] != a[y]) return a[x] < a[y];
		return f[x] < f[y];
	});
	std::sort(temp + mid + 1, temp + r + 1, // note
		[](const int& x, const int& y)
	{
		if (a[x] != a[y]) return a[x] < a[y];
		return f[x] < f[y];
	});
	for (int i = l; i <= mid; i++) // clean the count array
		count_[f[temp[i]]] = 0;
	for (int i = mid + 1; i <= r; i++)
		count_[f[temp[i]] - 1] = 0;
	int i = l, j = mid + 1;
	while (i <= mid || j <= r)
	{
		if (j > r || (i <= mid && a[temp[i]] < a[temp[j]])) // note
		{
			int pos = f[temp[i]];
			count_[pos] = (count_[pos] + g[temp[i]]) % mod;
			i++;
		}
		else
		{
			int pos = f[temp[j]];
			g[temp[j]] = (g[temp[j]] + count_[pos - 1]) % mod;
			j++;
		}
	}

	cdq(mid + 1, r); // note
}

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();

	for (int i = 1; i <= n; i++)
	{
		if (!t[0] || t[t[0]] < a[i])
		{
			t[++t[0]] = a[i];
			f[i] = t[0];
		}
		else
		{
			int* p = std::lower_bound(t + 1, t + 1 + t[0], a[i]);
			f[i] = p - t;
			*p = a[i];
		}
	}

	cdq(1, n);

	int ans = 0;
	for (int i = 1; i <= n; i++)
		if (f[i] == t[0])
			ans = (ans + g[i]) % mod;
	printOut(ans);
}

int main()
{
	run();
	return 0;
}