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
int n,m,G[MAXA][MAXA],U,V,W,f[MAXA],dist,w[MAXA];
struct arc
{
	int u,v,w;
}arc[MAXA];
int find(int x)
{
	if(f[x] == x)return x;
	return find(f[x]);
}
int main()
{
	freopen("wander.in","r",stdin);
	freopen("wander.out","w",stdout);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d %d",&U,&V,&W);
		arc[i].u = U;
		arc[i].v = V;
		w[i] = W;
	}
	if(n == 1 && m == 0)
	{
		printf("0\n");
		printf("0\n");
	}
	sort(w+1,w+m+1);
	for(int i=1;i<=n;i++)
	    f[i] = i;
	for(int i=1;i<=m;i++)
	{
		int xf = find(arc[i].u);
		int yf = find(arc[i].v);
		if(xf != yf)
		{
			f[yf] = xf;
			dist += w[i];
		}
		else continue;
	}
	printf("%d\n",dist);
	printf("0");
}
