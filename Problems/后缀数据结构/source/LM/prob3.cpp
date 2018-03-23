#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
const int maxn=6000005;
int son[maxn][26],link[maxn],len[maxn],tot=0,last,root,tax[maxn],rk[maxn],n,size[maxn];
char str[maxn>>1];
ull ans=0;
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
			link[nv]=link[v];link[np]=link[v]=nv;
			while(now&&son[now][ch]==v) son[now][ch]=nv,now=link[now];
		}
	}
	last=np;
}
void radixsort()
{
	for(int i=1;i<=tot;i++) tax[len[i]]++;
	for(int i=1;i<=tot;i++) tax[i]+=tax[i-1];
	for(int i=1;i<=tot;i++) rk[tax[len[i]]--]=i;
}
int main()
{
	freopen("prob3.in","r",stdin);
	freopen("prob3.out","w",stdout);
	scanf("%s",str);
	n=strlen(str)-1;
	root=last=newnode(0);
	for(int i=0;str[i];i++) extend(str[i]-'a');
//	radixsort();
	for(int i=1;i<=tot;i++) ans+=(ull)(len[i]-len[link[i]])*(ull)(len[i]+len[link[i]]+1)/2;
	printf("%llu",ans);
	return 0;
}
