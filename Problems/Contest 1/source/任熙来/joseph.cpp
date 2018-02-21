#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<climits>
#include<vector>
#include<stack>
#include<queue>
#define MAXA 100000
using namespace std;
int n,m,i=1,j=1,zys,step=1;
int a[MAXA];
int main()
{
	freopen("joseph.in","r",stdin);
	freopen("joseph.out","w",stdout);
	scanf("%d %d",&n,&m);
	zys = n;
	while(1)
	{
		if(i == zys+1)
		   i = 1;
		if(a[i] == 0&&n == 1)
			break;
		if(a[i] == 0 && step == m)
		{
			a[i] = 1;
			step = 1;
			n--;
			j++;
			i++;
			continue;
		}
		if(a[i] == 1)
		{
			j++;
			i++;
			continue;
		}
		if(a[i] == 0)
		{
			step++;
			j++;
			i++;
			continue;
		}
	}
	printf("%d",j % zys);
}
