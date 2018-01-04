#include<bits/stdc++.h>
using namespace std;
int t,n,x[510],m,p;
inline void rev(int k)
{
	int i;
	for(i=1; i<=(k>>1); i++)
		swap(x[i],x[k+1-i]);
}
inline void ss(int i,int k)
{
	int j,l;
	if(i+k>m)
		return;
	for(j=1; j<=n; j++)
		if(x[j]!=j)
			break;
	if(j>n)
	{
		p=1;
		return;
	}
	for(j=n; j>=2; j--)
	{
		l=k+(j<n && abs(x[j]-x[j+1])==1)-(j<n && abs(x[1]-x[j+1])==1);
		rev(j);
		ss(i+1,l);
		rev(j);
		if(p)
			return;
	}
}
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	int i,k;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(i=1; i<=n; i++)
			scanf("%d",&x[i]);
		for(i=1,k=0; i<n; i++)
			if(abs(x[i]-x[i+1])>1)
				k++;
		for(m=0;; m++)
		{
			p=0;
			ss(0,k);
			if(p)
				break;
		}
		printf("%d\n",m);
	}
	return 0;
}

