#include<bits/stdc++.h>
using namespace std;
int t,n,w,p,q,x[510],u;
inline int ran()
{
	return (rand()<<15)+rand();
}
int main()
{
	srand(time(0));
	ran();
	freopen("variable10.in","w",stdout);
	int i,j,k,l;
	t=10;
	n=500;
	p=1000;
	q=1000;
	u=100;
	printf("%d\n",t);
	while(t--)
	  {
	w=ran()%1000000+1;
	   printf("%d %d %d %d\n",n,w,p,q);
	   for(i=1;i<=n;i++)
	     x[i]=ran()%2;
	   for(i=1;i<=p;i++)
	     printf("%d %d %d %d %d %d %d %d %d\n",ran()%n+1,ran()%n+1,ran()%n+1,ran()%u+1,ran()%u+1,ran()%u+1,ran()%1000+1,ran()%1000+1,ran()%1000+1);
	   for(i=1;i<=q;i++)
	     {
		  j=ran()%n+1;
		  k=ran()%n+1;
		  if(x[j]>x[k])
		    swap(j,k);
		  if(x[j]==x[k])
		    if(ran()%10)
		      l=0;
		    else
		      l=1;
		  else
		    if(ran()%20)
		      l=0;
		    else
		      l=2;
		  printf("%d %d %d\n",j,k,l);
		 }
	  }
	return 0;
}

