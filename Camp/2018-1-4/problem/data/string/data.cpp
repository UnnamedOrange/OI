#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<time.h>
using namespace std;
const int q=998244353;
int n,m,s;
int main()
{
	srand(time(0));
	freopen("string10.in","w",stdout);
	int i,j,k,l,u,v;
	n=6;
	m=500;
	s=100;
	printf("%d %d\n",n,m);
	for(i=1;i<=n;i++)
	  {
	   k=rand()%s+1;
	   if(i==n)
	     k=s;
	   for(j=1;j<=k;j++)
	     printf("%d",rand()&1);
	   printf("\n");
	  }
	return 0;
}

