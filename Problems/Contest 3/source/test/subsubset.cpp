#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

typedef long long LL;

const int N=100005;
const int MOD=998244353;

int n,w[N],a[20][N*4],po[N],L,rev[N*4];

int ksm(int x,int y)
{
    int ans=1;
    while (y)
    {
        if (y&1) ans=(LL)ans*x%MOD;
        x=(LL)x*x%MOD;y>>=1;
    }
    return ans;
}

void NTT(int *a,int f)
{
    for (int i=0;i<L;i++) if (i<rev[i]) std::swap(a[i],a[rev[i]]);
    for (int i=1;i<L;i<<=1)
    {
        int wn=ksm(3,f==1?(MOD-1)/i/2:MOD-1-(MOD-1)/i/2);
        for (int j=0;j<L;j+=(i<<1))
        {
            int w=1;
            for (int k=0;k<i;k++)
            {
                int u=a[j+k],v=(LL)a[j+k+i]*w%MOD;
                a[j+k]=(u+v)%MOD;a[j+k+i]=(u+MOD-v)%MOD;
                w=(LL)w*wn%MOD;
            }
        }
    }
    int ny=ksm(L,MOD-2);
    if (f==-1) for (int i=0;i<L;i++) a[i]=(LL)a[i]*ny%MOD;
}

void solve(int l,int r,int d)
{
    if (l==r) {a[d][0]=1;a[d][1]=w[l];return;}
    int mid=(l+r)/2;
    solve(l,mid,d+1);
    for (int i=0;i<=mid-l+1;i++) a[d][i]=a[d+1][i];
    solve(mid+1,r,d+1);
    int lg=0;
    for (L=1;L<=r-l+1;L<<=1,lg++);
    for (int i=0;i<L;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
    for (int i=mid-l+2;i<L;i++) a[d][i]=0;
    for (int i=r-mid+1;i<L;i++) a[d+1][i]=0;
    NTT(a[d],1);NTT(a[d+1],1);
    for (int i=0;i<L;i++) a[d][i]=(LL)a[d][i]*a[d+1][i]%MOD;
    NTT(a[d],-1);
}

int main()
{
	freopen("subsubset.in","r",stdin);freopen("subsubset.out","w",stdout);
	scanf("%d",&n);
	po[0]=1;
	for (int i=1;i<=n;i++) po[i]=po[i-1]*2%MOD;
	for (int i=1;i<=n;i++) scanf("%d",&w[i]);
	solve(1,n,0);
	int ans=0;
	for (int i=1;i<=n;i++) (ans+=(LL)a[0][i]*po[n-i]%MOD)%=MOD;
	printf("%d",ans);
	return 0;
}
