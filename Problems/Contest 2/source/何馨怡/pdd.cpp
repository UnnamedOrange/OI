#include<bits/stdc++.h>

using namespace std;

#define MAXN 1000005

int n;
int a[MAXN], f[MAXN];
int ans;

int main( )
{
	freopen("pdd.in", "r",stdin);
	freopen("pdd.out","w",stdout);
	
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		f[i] = 1;
	}
	
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j < i; j++)
		{
			if(a[i] >= a[j])
			{
				f[i] = max(f[j] + 1, f[i]);
			}
		}
		ans = max(ans, f[i]);
	}
	printf("%d\n", ans);
	
	int r = 0;
	int b, c;
	
	while(r != n - 1)
	{
		r++;
		ans = 0;
		for(int i = 1; i <= n; i++)
		{
			f[i] = 1;
		}
		
		for( b = r; b <= n; b++)
		{
			for( c = r; c < b; c++)
			{
				if(a[b] >= a[c])
				{
					f[b] = max(f[c] + 1, f[b]);
				}
			}
			ans = max(ans, f[b]);
		}
		printf("%d ", ans);
		
	}
	printf("%d", 1);
	return 0;
}
