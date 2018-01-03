#include<bits/stdc++.h>
using namespace std;
int t, n;
char s[100010];
int main()
{
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
	int i;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%s", &n, &s[0] + 1);
		for (i = 1; i < n; i++)
			if (s[i] != s[i + 1])
				break;
		if (i == n)
		{
			printf("-1\n");
			continue;
		}
		if (n & 1)
		{
			for (i = 1; i <= n / 2; i++)
				if (s[i] != s[n + 1 - i] || i > 1 && s[i] != s[i - 1])
					break;
			if (i > n / 2)
			{
				printf("-1\n");
				continue;
			}
			for (i = 1; i <= n - 2; i++)
				if (s[i] != s[i + 2])
					break;
			if (i > n - 2)
			{
				printf("-1\n");
				continue;
			}
		}
		for (i = 1; i <= n; i++)
			if (s[i] != s[n + 1 - i])
				break;
		if (i > n)
			printf("2\n");
		else
			printf("1\n");
	}
	return 0;
}