#include<bits/stdc++.h>
using namespace std;

const int maxn=4010;

int n,m,K,a[maxn],b[maxn],na[maxn][maxn],nb[maxn][maxn],dp[maxn][maxn];

int main()
{
	freopen("subsequence.in","r",stdin);
	freopen("subsequence.out","w",stdout);
	int i,j,k;
	scanf("%d%d%d",&n,&m,&K);
	for (i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (i=1;i<=m;i++)
		scanf("%d",&b[i]);
	for (k=1;k<=K;k++)
	{
		na[n][k]=n+1;
		nb[m][k]=m+1;
		na[n+1][k]=n+1;
		nb[m+1][k]=m+1;
	}
	for (i=n-1;i>=0;i--)
	{
		for (k=1;k<=K;k++)
			na[i][k]=na[i+1][k];
		na[i][a[i+1]]=i+1;
	}
	for (i=m-1;i>=0;i--)
	{
		for (k=1;k<=K;k++)
			nb[i][k]=nb[i+1][k];
		nb[i][b[i+1]]=i+1;
	}
	memset(dp,-1,sizeof(dp));
	dp[0][0]=0;
	for (i=0;;i++)
	for (j=0;j<=n+1;j++)
		if (dp[i][j]!=-1)
		{
			if (j==n+1&&dp[i][j]==m+1) {printf("%d\n",i); return 0;}
			for (k=1;k<=K;k++)
				dp[i+1][na[j][k]]=max(dp[i+1][na[j][k]],nb[dp[i][j]][k]);
		}
}

