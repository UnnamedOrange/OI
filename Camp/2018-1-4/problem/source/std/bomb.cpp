#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
int n,m,a[1000010],b[1000010],c[1000010],d[1000010],x[1000010],y[1000010],f[1000010],g[1000010],w[1000010],p,q;
int v[1000010];
bool z[1000010];
inline void dfs(int i)
{
    int j;
    g[++p]=i;
    x[i]=y[i]=++q;
    z[i]=1;
    for(j=a[i];j>0;j=c[j])
      if(!x[f[b[j]]])
        {
         dfs(f[b[j]]);
         y[i]=min(y[i],y[f[b[j]]]);
        }
      else if(z[f[b[j]]])
        y[i]=min(y[i],x[f[b[j]]]);
    if(x[i]==y[i])
      {
       while(g[p]!=i)
         {
          f[g[p]]=i;
          c[d[i]]=a[g[p]];
          d[i]=d[g[p]];
          z[g[p--]]=0;
          v[i]++;
         }
       z[g[p--]]=0;
      }
}
inline void dp(int i)
{
    if(w[i])
      return;
    int j;
    for(j=a[i];j>0;j=c[j])
      if(f[b[j]]!=i)
        {
         dp(f[b[j]]);
         w[i]=max(w[i],w[f[b[j]]]);
        }
    w[i]+=v[i];
    p=max(p,w[i]);
}
int main()
{
	freopen("bomb.in","r",stdin);
	freopen("bomb.out","w",stdout);
	int i,j,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	  {
       scanf("%d%d",&j,&k);
       b[i]=k;
       c[i]=a[j];
       if(!a[j])
         d[j]=i;
       a[j]=i;
      }
    for(i=1;i<=n;i++)
      {
       f[i]=i;
       v[i]=1;
      }
    for(i=1;i<=n;i++)
      if(!x[i])
        dfs(i);
    p=0;
    for(i=1;i<=n;i++)
      if(f[i]==i)
        dp(i);
    printf("%d\n",p);
	return 0;
}

