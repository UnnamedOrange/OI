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
#define MAXA 100
using namespace std;
int n,c[MAXA],cc[MAXA],maxd,mark[MAXA],maxj;
int gene[MAXA][MAXA];
int main()
{
	freopen("gene.in","r",stdin);
	freopen("gene.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&c[i]);
		for(int j=0;j<c[i];j++)
		{
			scanf("%d",&gene[i][j]);
		}
	}
	for(int i=0;i<n;i++)
	    cc[i] = c[i];
	sort(c,c+n);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
	    {
	    	if(cc[j] == c[i] && mark[j] == 0 && maxd < gene[j][0])
	    	{
	    		maxd = gene[j][0];
	    		maxj = j;
			}
		}
		printf("%d ",maxj+1);
		maxd = 0;
		mark[maxj] = 1;
	}
}
/*
10
5 4 4 6 10 10
5 10 3 3 6 4
2 7 5
5 5 10 10 7 4
3 10 9 3
1 1
2 10 1
1 9
3 2 7 8
1 9
*/
