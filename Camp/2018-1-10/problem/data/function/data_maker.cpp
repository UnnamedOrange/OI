#include<bits/stdc++.h>
using namespace std;
#define LL long long

const int N=1e7;
const int maxn=N+10;
const int maxp=5971549;

int T,primes,prime[maxp],mu[maxn],mu2[maxn],d0[maxn];
LL n,n0[25],ans[25];
bool vis[maxn];

void init(int N)
{
	int i,j;
	vis[1]=1; mu[1]=1; mu2[1]=1; d0[1]=1;
	for (i=2;i<=N;i++)
	{
		if (!vis[i])
		{
			prime[++primes]=i;
			mu[i]=-1;
			d0[i]=2;
		}
		for (j=1;j<=primes&&i*prime[j]<=N;j++)
		{
			vis[i*prime[j]]=1;
			if (i%prime[j])
			{
				mu[i*prime[j]]=-mu[i];
				d0[i*prime[j]]=d0[i]<<1;
			}
			else
			{
				d0[i*prime[j]]=(d0[i]<<1)-d0[i/prime[j]];
				break;
			}
		}
		mu2[i]=mu2[i-1]+(mu[i]!=0);
	}
	for (i=2;i<=N;i++) d0[i]+=d0[i-1];
}

LL S_mu2(LL n)
{
	if (n<=N) return mu2[n];
	LL i,Ans=0;
	for (i=1;(LL)i*i<=n;i++)
		Ans+=mu[i]*(n/i/i);
	return Ans;
}

LL S_d0(LL n)
{
	if (n<=N) return d0[n];
	LL i,j,Ans=0;
	for (i=1;i<=n;i=j+1)
	{
		j=n/(n/i);
		Ans+=(j-i+1)*(n/i);
	}
	return Ans;
}

LL rand(LL s,LL t)
{
	LL p=abs(rand()^((LL)rand()<<15)^((LL)rand()<<30)^((LL)rand()<<45)^((LL)rand()<<60));
	return p%(t-s+1)+s;
}

char in_name[99],out_name[99];

int main()
{
	srand(time(NULL));
	init(N);
	for (int case_id=0;case_id<10;case_id++)
	{
		T=case_id?10:0;
		for (int c=1;c<=T;c++)
		{
			LL i,j,Ans=0,last=0;
			LL range;
			if (case_id<3) range=1e6;
			else if (case_id<5) range=1e8;
			else range=1e8;
			n=n0[c]=rand(range*3/4,range);
			for (i=1;i<=n;i=j+1)
			{
				j=n/(n/i);
				LL tmp=S_mu2(j);
				Ans+=(tmp-last)*S_d0(n/i);
				last=tmp;
			}
			ans[c]=Ans;
		}

		sprintf(in_name,"function%d.in",case_id);
		sprintf(out_name,"function%d.out",case_id);

		freopen(in_name,"w",stdout);
		printf("%d\n",T);
		for (int c=1;c<=T;c++)
			printf("%lld\n",n0[c]);
		fclose(stdout);

		freopen(out_name,"w",stdout);
		for (int c=1;c<=T;c++)
			printf("%lld\n",ans[c]);
		fclose(stdout);

		fprintf(stderr,"case #%d finished\n",case_id);
	}
}

