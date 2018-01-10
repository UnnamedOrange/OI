#include<bits/stdc++.h>
using namespace std;
#define LL long long

const int N=1e7;
const int maxn=N+10;
const int maxp=5971549;

int T,primes,prime[maxp],mu[maxn],mu2[maxn],d0[maxn];
LL n;
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

int main()
{
	freopen("function.in","r",stdin);
	freopen("function.out","w",stdout);
	scanf("%d",&T);
	init(N);
	while (T--)
	{
		LL i,j,Ans=0,last=0;
		scanf("%lld",&n);
		for (i=1;i<=n;i=j+1)
		{
			j=n/(n/i);
			LL tmp=S_mu2(j);
			Ans+=(tmp-last)*S_d0(n/i);
			last=tmp;
		}
		printf("%lld\n",Ans);
	}
}

