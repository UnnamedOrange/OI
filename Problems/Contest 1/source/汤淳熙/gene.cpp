#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <cfloat>
#include <ctime>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <bitset>
#include <set>
#include <map>
using namespace std;
const int MAXN = 1e4 + 5;

int n, Idx[MAXN];
vector<int> a[MAXN];

bool Cpr(const int &x, const int &y)
{
	if (a[x].size() != a[y].size())
		return a[x].size() < a[y].size();

	for (register int i = 0; i < a[x].size(); ++i)
		if (a[x][i] != a[y][i])
			return a[x][i] > a[y][i];

	return false;
}

inline void Init(void)
{
	for (register int i = 1; i <= n; ++i)
		Idx[i] = i;
}

int main(void)
{
#ifndef LOCAL
	freopen("gene.in", "r", stdin);
	freopen("gene.out", "w", stdout);
#endif

	scanf("%d", &n);
	Init();

	for (register int i = 1; i <= n; ++i) {
		int c;
		scanf("%d", &c);
		a[i].resize(c);

		for (register int j = 0; j < c; ++j)
			scanf("%d", &a[i][j]);
	}

	stable_sort(Idx + 1, Idx + n + 1, Cpr);

	for (register int i = 1; i < n; ++i)
		printf("%d ", Idx[i]);
	printf("%d\n", Idx[n]);

	return 0;
}

/*
10
5 4 4 6 10 10
5 10 3 3 6 4
2 7 5
5 5 10 10 7 4
3 10 9 3
1 1
2 10 1
1 9
3 2 7 8
1 9
*/
