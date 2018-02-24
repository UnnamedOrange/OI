#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000005 
int n;
int a[MAXN];
int ans[MAXN];
int maxa = -1;
int main()
{
	freopen("pdd.in","r",stdin);
	freopen("pdd.out","w",stdout);
	cin >> n;
	for(int i = 0;i < n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i = 0;i < n;i++)
		ans[i] = 1;
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < i;j++)
		{
			if(a[j] < a[i])
				ans[i] = max(ans[i],ans[j] + 1);
		}
		maxa = max(maxa,ans[i]);
	 } 
	 printf("%d\n",maxa);
	 for(int i = n - 1;i >= 0;i--)
	 {
	 	printf("%d ",ans[i]);
	 }
	return 0;
}
