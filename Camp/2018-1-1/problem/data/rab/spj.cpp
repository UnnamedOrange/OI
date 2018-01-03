#include <stdlib.h>
#include <string.h>
#include  <stdio.h>
#include   <math.h>
#include   <time.h>
#include   <vector>
#include   <bitset>
#include    <queue>
#include      <set>
#include      <map>
#include<algorithm>
#include <iostream>
using namespace std;

FILE *fin, *fout, *fstdout, *freport;

void Done(int report)
{
	fprintf(freport, "%d\n", report);
	fclose(freport);
	exit(0);
}

const int N=100005;

int flag=10,n,m,Ansm,fa[N],vis[N],col[N],w[N],Ans[N];

void check()
{
	fscanf(fin,"%d",&n);
	for(int i=1;i<=n;i++)
		vis[i]=1;
	for(int i=1;i<=n;i++)
		fscanf(fin,"%d",&fa[i]),vis[fa[i]]=0;
	for(int i=1;i<=n;i++)
		fscanf(fin,"%d",&col[i]);
	fscanf(fout,"%d",&m);
	fscanf(fstdout,"%d",&Ansm);
	if(m>n)
		Done(0);
	if(m!=-1&&Ansm==-1)
		Done(0);
	if(m==-1&&Ansm!=-1)
		Done(0);
	for(int i=1;i<=m;i++)
	{
		fscanf(fout,"%d",&w[i]);
		/*if(w[i]<w[i-1])
			Done(0);
		if(!vis[w[i]])
			Done(0);*/
	}
	for(int i=1;i<=Ansm;i++)
		fscanf(fstdout,"%d",&Ans[i]);
	if(m!=Ansm||flag==5)
	{
		flag=5;return;
	}
	for(int i=1;i<=Ansm;i++)
		if(w[i]!=Ans[i])
		{
			flag=5;return;
		}
}

int main(int argc, char* argv[])
{
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "r");
	fstdout = fopen(argv[3], "r");
	freport = fopen(argv[5], "w");
	int t;
	fscanf(fin,"%d",&t);
	while(t--)
		check();
	Done(flag);
}

