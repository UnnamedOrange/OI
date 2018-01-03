#include<bits/stdc++.h>
using namespace std;
int n,a,b,x[4],m=1000000000;
inline int ran()
{
	return (rand()<<15)+rand();
}
int main()
{
	srand(time(0));
	ran();
	freopen("stone5.in","w",stdout);
	int i,j,k=0;
	n=20;
	a=ran()%m+1;
	b=ran()%m+1;
	printf("%d %d %d\n",n,a,b);
	for(i=1;i<=n;i++)
	  {
	   do
	   j=ran()%m+1;
	   while(j%(a+b)<min(a,b));
	   printf("%d ",j);
	   j%=a+b;
	   x[(j>=min(a,b))+(j>=max(a,b))+(j>=max(a,b) && j>=2*min(a,b))]++;
	  }
	printf("\n");
	for(i=0;i<4;i++)
	  cerr<<x[i]<<" ";
	return 0;
}

