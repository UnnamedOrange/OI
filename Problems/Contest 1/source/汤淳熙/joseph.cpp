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

int main(void)
{
#ifndef LOCAL
	freopen("joseph.in", "r", stdin);
	freopen("joseph.out", "w", stdout);
#endif	

	int n, m;
	scanf("%d %d", &n, &m);

	long long Pst = 0;
	for (int i = 2; i <= n; ++i)
		Pst = (Pst + m) % i;

	printf("%d\n", Pst + 1);

	return 0;
}
