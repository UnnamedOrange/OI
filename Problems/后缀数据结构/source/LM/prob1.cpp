#include<bits/stdc++.h>
using namespace std;
const int maxn=2000005;
int len[maxn],son[maxn][26],link[maxn],root,last,tot=0,n,k,rk[maxn],tax[maxn],size[maxn];
char str[maxn];bool visit[maxn];
inline int newnode(int _len) {len[++tot]=_len;return tot;}
void extend(int ch)
{
	int np=newnode(len[last]+1);
	int now=last;size[np]=1;
	while(now&&!son[now][ch]) son[now][ch]=np,now=link[now];
	if(!now) link[np]=root;
	else
	{
		int v=son[now][ch];
		if(len[v]==len[now]+1) link[np]=v;
		else
		{
			int nv=newnode(len[now]+1);
			memcpy(son[nv],son[v],sizeof(son[v]));
			link[nv]=link[v];link[v]=link[np]=nv;
			while(now&&son[now][ch]==v) son[now][ch]=nv,now=link[now];
		}
	}
	last=np;
}
void radixsort()
{
	for(int i=1;i<=tot;i++) tax[len[i]]++;
	for(int i=1;i<=n;i++) tax[i]+=tax[i-1];
	for(int i=1;i<=tot;i++) rk[tax[len[i]]--]=i;
}
int main()
{
	freopen("prob1.in","r",stdin);
	freopen("prob1.out","w",stdout);
	scanf("%s",str+1);scanf("%d",&k);
	n=strlen(str+1);
	root=last=newnode(0);
	for(int i=1;i<=n;i++) extend(str[i]-'a');
	radixsort();int ans=0;
	for(int i=tot;i;i--)
	{
		size[link[rk[i]]]+=size[rk[i]];
		if(size[rk[i]]==k) ans+=len[rk[i]]-len[link[rk[i]]];
	}
	printf("%d",ans);
	return 0;
}
