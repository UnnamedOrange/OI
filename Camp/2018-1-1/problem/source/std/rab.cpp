#include<algorithm>
#include <iostream>
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
using namespace std;

namespace IO
{
	const int L=1<<15,Lim=1<<20;
	char buffer[L],*S,*T,ch,outbuf[Lim+5];
	int Now;
	
	inline char Gc()
	{
		if(S==T)
		{
			T=(S=buffer)+fread(buffer,1,L,stdin);
			if(S==T)
				return EOF;
		}
		return *S++;
	}
	
	inline void get(int& x)
	{
		for(ch=Gc();(ch<'0'||ch>'9')&&ch!='-';ch=Gc());
		int f=1;
		if(ch=='-')
			f=-1,ch=Gc();
		x=ch^'0';
		for(ch=Gc();ch>='0'&&ch<='9';ch=Gc())
			x=x*10+(ch^'0');
		x*=f;
	}
	
	inline void Pc(char ch)
	{
		outbuf[Now++]=ch;
		if(Now==Lim)
			fwrite(outbuf,1,Now,stdout),Now=0;
	}
	
	inline void put(int x)
	{
		if(x>9)
			put(x/10);
		Pc(x%10+'0');
	}
	
	inline void end()
	{
		if(Now)
			fwrite(outbuf,1,Now,stdout),Now=0;
	}
}

const int N=100005;

int n,m,fa[N],f[N],Ans[N];
vector<int> son[N];

void dp(int u)
{
	if(!son[u].size())
		return;
	int num[3]={};
	for(int i=0;i<son[u].size();i++)
		dp(son[u][i]),num[f[son[u][i]]]++;
	if((num[0]&1)+num[1]<num[2])
		f[u]=2;
	if((num[0]&1)+num[2]<num[1])
		f[u]=1;
}

void redWin(int u);
void firstWin(int u);

void allWin(int u)
{
	if(!son[u].size()&&!f[u])
		Ans[u]=1;
	for(int i=0;i<son[u].size();i++)
		allWin(son[u][i]);
}

void redWin(int u)
{
	if(f[u]==1)
		allWin(u);
	if(f[u]!=0)
		return;
	if(!son[u].size())
	{
		Ans[u]=1;return; 
	}
	for(int i=0;i<son[u].size();i++)
	{
		int v=son[u][i];
		if(f[v]==0)
			redWin(v);
		if(f[v]==2)
			firstWin(v);
	}
}

void firstWin(int u)
{
	if(!son[u].size())
		return;
	int num[3]={};
	for(int i=0;i<son[u].size();i++)
		num[f[son[u][i]]]++;
	if(num[0]%2||num[2]!=num[1]+1)
		return;
	for(int i=0;i<son[u].size();i++)
	{
		int v=son[u][i];
		if(f[v]==0)
			redWin(v);
		if(f[v]==2)
			firstWin(v);
	}
}

void solve()
{
	IO::get(n);
	for(int i=1;i<=n;i++)
		Ans[i]=0,son[i].clear();
	for(int i=1;i<=n;i++)
	{
		IO::get(fa[i]);
		if(fa[i])
			son[fa[i]].push_back(i);
	}
	for(int i=1;i<=n;i++)
		IO::get(f[i]),f[i]++;
	dp(1);
	if(f[1]==2)
		IO::Pc('-'),IO::Pc('1'),IO::Pc('\n');
	else
	{
		redWin(1);m=0;
		for(int i=1;i<=n;i++)
			m+=Ans[i];
		IO::put(m);
		for(int i=1;i<=n;i++)
			if(Ans[i])
				IO::Pc(' '),IO::put(i);
		IO::Pc('\n');
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("rab.in","r",stdin);
	freopen("rab.out","w",stdout);
#endif
	int T;scanf("%d",&T);
	while(T--)
		solve();
	IO::end();
	return 0;
}

