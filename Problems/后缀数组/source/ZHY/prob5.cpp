#include <bits/stdc++.h>
#define N 700005
using namespace std;
int lens, n, sa[N], x[N], y[N], tax[N], m, H[N];
char a[N];
inline void Sort()
{
	int i;
	for (i = 1; i <= m; ++i) tax[i] = 0;
	for (i = 1; i <= n; ++i) tax[x[y[i]]]++;
	for (i = 2; i <= m; ++i) tax[i] += tax[i - 1];
	for (i = n; i; --i) sa[tax[x[y[i]]]--] = y[i];
}
inline void suffix()
{
	int i, k, p = 0, j;
	for (i = 1; i <= n; ++i) x[i] = a[i], y[i] = i;
	m = 127, Sort();
	for (k = 1; p < n; k <<= 1, m = p)
	{
		for (p = 0, i = n - k + 1; i <= n; ++i) y[++p] = i;
		for (i = 1; i <= n; ++i) if (sa[i] > k) y[++p] = sa[i] - k;
		Sort(), swap(x, y), x[sa[1]] = p = 1;
		for (i = 2; i <= n; ++i) x[sa[i]] = ((y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? p : ++p);
	}
	for (k = 0, i = 1; i <= n; H[x[i++]] = k)
		for (k = k ? k - 1 : k, j = sa[x[i] - 1]; a[i + k] == a[j + k]; ++k);
}
int main()
{
	freopen("prob5.in", "r", stdin);
	freopen("prob5.out", "w", stdout);
	int i, j, k, lens, cnt = 0;
	scanf("%s", a + 1), n = strlen(a + 1);
	scanf("%d", &k);
	suffix();
	for (i = 1; i <= n; ++i)
	{
		for (lens = H[i] + 1, j = i + 1; lens <= n - sa[i] + 1; lens++, j = i + 1)
		{
			while (j <= n && H[j] >= lens) ++j;
			--j;
			if (j - i + 1 >= k) ++cnt;
			else break;
		}
	}
	printf("%d\n", cnt);
	return 0;
}