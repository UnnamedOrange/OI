#include<bits/stdc++.h>
using namespace std;
const int q=998244353;
int n,m,x[1210][10],f[510][1210][70],g[1210],p;
char s[110];
inline bool pd(int j,int n)
{
	int i;
	for(i=j+1;i<n;i++)
	  if(j-(i-j)+1<0 || s[j-(i-j)+1]==s[i])
	    return 0;
	return 1;
}
inline void add(int k)
{
	int n=strlen(s);
	int i,j;
	for(i=0,j=0;j<n;j++)
	  {
	   if(!x[i][s[j]-'0'])
	     {
	      x[i][s[j]-'0']=++p;
	      x[p][2]=i;
	      x[p][5]=s[j]-'0';
		 }
	   i=x[i][s[j]-'0'];
	   if(pd(j,n))
	     x[i][4]|=k;
	  }
	x[i][3]|=k;
}
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int i,j,k,l,u,v;
	   scanf("%d%d",&n,&m);
	   for(i=1;i<=n;i++)
	     {
		  scanf("%s",&s);
		  add(1<<i-1);
		  k=strlen(s);
		  for(j=0;k-1-j>j;j++)
		    swap(s[j],s[k-1-j]);
		  for(j=0;j<k;j++)
		    s[j]^=1;
		  add(1<<i-1);
		 }
	   k=1;
	   g[1]=0;
	   for(u=1;u<=k;u++)
	     {
		  i=g[u];
		  if(x[i][0])
		    g[++k]=x[i][0];
		  if(x[i][1])
		    g[++k]=x[i][1];
		  if(!i)
		    continue;
		  for(j=x[x[i][2]][6];j && !x[j][x[i][5]];j=x[j][6]);
		  if(x[j][x[i][5]] && x[j][x[i][5]]!=i)
		    x[i][6]=x[j][x[i][5]];
		  if(!x[i][0])
		    x[i][0]=x[x[i][6]][0];
		  if(!x[i][1])
		    x[i][1]=x[x[i][6]][1];
		  for(j=3;j<=5;j++)
		    x[i][j]|=x[x[i][6]][j];
		 }
	   f[0][0][0]=1;
	   for(i=1;i<=m;i++)
	     for(j=0;j<=p;j++)
	       for(k=0;k<(1<<n);k++)
	         for(l=0;l<=1;l++)
	           {
				u=x[j][l];
				v=k|x[u][3];
				f[i][u][v]=(f[i][u][v]+f[i-1][j][k])%q;
			   }
	   k=0;
	   for(i=0;i<=p;i++)
	     for(j=0;j<(1<<n);j++)
	       if((j|x[i][4])==(1<<n)-1)
	         k=(k+f[m][i][j])%q;
	   printf("%d\n",k);
	return 0;
}

