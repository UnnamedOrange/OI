#include<bits/stdc++.h>
#define L long long
using namespace std;
const int q=1000000007;
int n,a,b,x[4],f[4];
inline int power(int a,int b)
{
	if(!b)
	  return 1;
	int c=power(a,b>>1);
	c=(L)c*c%q;
	if(b&1)
	  c=(L)c*a%q;
	return c;
}
int main()
{
	freopen("stone.in","r",stdin);
	freopen("stone.out","w",stdout);
	int i,j,k=0;
	scanf("%d%d%d",&n,&a,&b);
	if(a>b)
	  swap(a,b),k=1;
	for(i=1;i<=n;i++)
	  {
	   scanf("%d",&j);
	   j%=a+b;
	   x[(j>=a)+(j>=b)+(j>=b && j>=2*a)]++;
	  }
	f[0]=((L)(power(2,x[1])-1)*power(2,x[2]+x[3])+(L)(power(2,x[3])-x[3]-1+q)*power(2,x[2])+(L)x[3]*(x[2]?power(2,x[2]-1):0))%q;
	f[2]=((x[2]?power(2,x[2]-1):0)+(L)x[3]*(x[2]?power(2,x[2]-1):1))%q;
	f[3]=(x[2]?power(2,x[2]-1):1);
	for(i=0;i<4;i++)
	  f[i]=(L)f[i]*power(2,x[0])%q;
	if(k)
	  swap(f[0],f[1]);
	for(i=0;i<4;i++)
	  printf("%d ",f[i]);
	printf("\n");
	return 0;
}

