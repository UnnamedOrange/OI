#include "diff.h"
#include <algorithm>

static const int N = 1005;
static int n, R, C, a[N], b[N], count;
static long long ans, ret;

template <class T>
T abs(T x) { return x < 0 ? -x : x; }

long long getDistance(int x, int y)
{
	if (x < 1 || x > R || y < 1 || y > C)
	{
		printf("Invalid query");
		exit(1);
	}
	count = count + 1;
	int i;
	long long ret = 0;
	for (i = 1; i <= n; i++)
		ret += abs(x - a[i]) + abs(y - b[i]);
	return ret;
}

int main()
{
	int i;
	scanf("%d%d%d", &n, &R, &C);
	for (i = 1; i <= n; i++)
		scanf("%d%d", a + i, b + i);
	scanf("%lld", &ans);
	ret = getMiniumDistance(R, C);
	if (ans == ret)
	{
		printf("get OK with %d queries\n", count);
		return 0;
	}
	else
	{
		printf("Wrong Answer: expected %lld, found %lld\n", ans, ret);
		return 1;
	}
}