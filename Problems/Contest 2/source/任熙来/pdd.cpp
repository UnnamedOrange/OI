#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
#include<vector>
#include<stack>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<cctype>
#define MAXA 1000500
// Winner Winner Chicken Dinner
using namespace std;
int n,a[MAXA],d[MAXA],Maxlen;
int main()
{
	freopen("pdd.in","r",stdin);
	freopen("pdd.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	    scanf("%d",&a[i]);
	for(int i=n;i>=1;i--)
	{
		d[i] = 1;
		for(int j=i;j<=n;j++)
		    if(a[i] < a[j])
		       d[i] = max(d[i],d[j]+1);
	}
	
	for(int i=1;i<=n;i++)
	    Maxlen = max(Maxlen,d[i]);
	    
	printf("%d\n",Maxlen);
	
	for(int i=1;i<=n;i++)
	    printf("%d ",d[i]);
}
/*
6
1 4 2 8 5 7
*/
