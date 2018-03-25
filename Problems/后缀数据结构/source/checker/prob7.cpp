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

const int maxn = 505;
int n;
char str[maxn];

bool check(int s)
{
	for (int i = s; i < n; i += s)
		if (std::strncmp(str, str + i, s))
			return false;
	return true;
}

void run()
{
	scanf("%s", str);
	n = strlen(str);

	int ans = 0;
	int to = std::sqrt(n);
	for (int i = 1; i <= to; i++)
	{
		if (n % i) continue;
		if (check(i)) ans = std::max(ans, n / i);
		if (check(n / i)) ans = std::max(ans, i);
	}
	printf("%d", ans);
}

int main()
{
#ifndef LOCAL
	freopen("prob7.in", "r", stdin);
	freopen("prob7.out", "w", stdout);
#endif 
	run();
	return 0;
}