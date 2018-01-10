#include<bits/stdc++.h>
using namespace std;
#define LL long long

const int maxn=4010;
const int mo=998244353;

int n,m,K,a[maxn],b[maxn],p[maxn];
int na[maxn][maxn],nb[maxn][maxn],dp[maxn][maxn];
char in_name[99],out_name[99];

int rand(int s,int t)
{
	int p=abs(rand()^(rand()<<15)^(rand()<<30));
	return s+p%(t-s+1);
}

int main()
{
	srand(time(NULL));
	int i,j,k;

	for (int case_id=0;case_id<10;case_id++)
	{
		memset(na,0,sizeof(na));
		memset(nb,0,sizeof(nb));
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		if (case_id==0) n=rand(14,18),m=rand(14,18),K=2;
		else if (case_id<5)
		{
			n=rand(250,300);
			m=rand(250,300);
			int tmp=(int)sqrt(min(n,m));
			K=rand(tmp,2*tmp);
		}
		else
		{
			n=rand(3333,4000);
			m=rand(3333,4000);
			if (case_id<7) n=rand(1700,2000),m=rand(1700,2000);
			int tmp=(int)sqrt(min(n,m));
			K=rand(tmp/2,2*tmp);
		}
		fprintf(stderr,"%d %d %d\n",n,m,K);

		for (k=1;k<=K;k++) p[k]=k;
		for (i=1;i<=n;i++)
		{
			int Sum=0;
			for (k=1;k<=K;k++) Sum+=p[k];
			int tmp=rand(1,Sum);
			for (k=1;k<=K;k++)
			{
				tmp-=p[k];
				if (tmp<=0) {a[i]=k; break;}
			}
			for (k=1;k<=K;k++) p[k]++;
			p[a[i]]=0;
		}

		for (k=1;k<=K;k++) p[k]=k;
		for (i=1;i<=m;i++)
		{
			int Sum=0;
			for (k=1;k<=K;k++) Sum+=p[k];
			int tmp=rand(1,Sum);
			for (k=1;k<=K;k++)
			{
				tmp-=p[k];
				if (tmp<=0) {b[i]=k; break;}
			}
			for (k=1;k<=K;k++) p[k]++;
			p[b[i]]=0;
		}

		sprintf(in_name,"subsequence%d.in",case_id);
		sprintf(out_name,"subsequence%d.out",case_id);

		freopen(in_name,"w",stdout);
		printf("%d %d %d\n",n,m,K);
		for (i=1;i<=n;i++)
			printf("%d ",a[i]);
		puts("");
		for (i=1;i<=m;i++)
			printf("%d ",b[i]);
		puts("");
		fclose(stdout);

		freopen(out_name,"w",stdout);
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
		bool flag=1;
		for (i=0;;i++)
		{
			for (j=0;j<=n+1;j++)
			{
				if (j==n+1&&dp[i][j]==m+1)
				{
					printf("%d\n",i);
					fprintf(stderr,"%d (%d)\n",i,i*K);
					flag=0;
					break;
				}
				for (k=1;k<=K;k++)
					dp[i+1][na[j][k]]=max(dp[i+1][na[j][k]],nb[dp[i][j]][k]);
			}
			if (!flag) break;
		}
		fclose(stdout);

		fprintf(stderr,"case #%d finished\n",case_id);
	}
}

