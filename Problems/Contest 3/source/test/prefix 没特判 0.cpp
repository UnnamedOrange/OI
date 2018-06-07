#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

typedef long long LL;

const int MOD=100003;

int jc[MOD],ny[MOD];

int C(int n,int m)
{
	if (n<m) return 0;
	return (LL)jc[n]*ny[m]%MOD*ny[n-m]%MOD;
}

int main()
{
	freopen("prefix.in","r",stdin);freopen("prefix.out","w",stdout);
	jc[0]=jc[1]=ny[0]=ny[1]=1;
	for (int i=2;i<MOD;i++) jc[i]=(LL)jc[i-1]*i%MOD,ny[i]=(LL)(MOD-MOD/i)*ny[MOD%i]%MOD;
	for (int i=2;i<MOD;i++) ny[i]=(LL)ny[i-1]*ny[i]%MOD;
	int T;scanf("%d",&T);
	while (T--)
	{
		LL n,m;int x;scanf("%lld%lld%d",&n,&m,&x);
		n=n+m-1;m--;
		int ans=1;
		while (n)
		{
			ans=(LL)ans*C(n%MOD,m%MOD);
			n/=MOD;m/=MOD;
		}
		printf("%d\n",(LL)ans*x%MOD);
	}
	return 0;
}
