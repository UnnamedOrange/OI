#include<cstdio>
#include<algorithm>
#define fo(i,a,b) for(i=a;i<=b;i++)
using namespace std;
typedef long long ll;
const int maxn=1000000+10,mo=998244353;
int f[maxn],g[maxn],dp[maxn],sum[maxn],p[maxn],kk[maxn],bb[maxn],deg[maxn],c[maxn];
int h[maxn],go[maxn*2],nxt[maxn*2];
char s[maxn];
int i,j,k,l,t,n,m,ans,tot;
void add(int x,int y){
	deg[y]++;
	go[++tot]=y;
	nxt[tot]=h[x];
	h[x]=tot;
}
int qsm(int x,int y){
	if (!y) return 1;
	int t=qsm(x,y/2);
	t=(ll)t*t%mo;
	if (y%2) t=(ll)t*x%mo;
	return t;
}
void dfs(int x,int y){
	p[x]=y;
	if (deg[x]==1){
		kk[x]=f[x]=0;
		bb[x]=c[x];
		return;
	}
	int t=h[x],l=0,r=qsm(deg[x],mo-2),k=1,b=0;
	while (t){
		if (go[t]!=y){
			dfs(go[t],x);
			(k-=(ll)r*kk[go[t]]%mo)%=mo;
			(b+=(ll)r*(bb[go[t]]+c[x])%mo)%=mo;
			(l+=f[go[t]])%=mo;
		}
		t=nxt[t];
	}
	f[x]=qsm(deg[x]-l,mo-2);
	if (y) (b+=(ll)r*c[x]%mo)%=mo;
	l=qsm(k,mo-2);
	kk[x]=(ll)r*l%mo;
	bb[x]=(ll)b*l%mo;
}
void dg(int x,int y){
	if (y){
		int l=(sum[y]-f[x])%mo;
		(l+=g[y])%=mo;
		g[x]=qsm(deg[y]-l,mo-2);
	}
	int t=h[x];
	while (t){
		if (go[t]!=y) (sum[x]+=f[go[t]])%=mo;
		t=nxt[t];
	}
	t=h[x];
	while (t){
		if (go[t]!=y) dg(go[t],x);
		t=nxt[t];
	}
}
void travel(int x,int y){
	if (!c[x]) (ans+=dp[x])%=mo;
	int t=h[x];
	while (t){
		if (go[t]!=y){
			dp[go[t]]=(ll)dp[x]*g[go[t]]%mo;
			travel(go[t],x);
		}
		t=nxt[t];
	}
}
int main(){
	freopen("sad.in","r",stdin);freopen("sad.out","w",stdout);
	/*int sizz = 512 << 20; // 512MB
    char *pp = (char*)malloc(sizz) + sizz;
    __asm__("movl %0, %%esp\n" :: "r"(pp));*/
	scanf("%d",&n);
	scanf("%s",s+1);
	fo(i,1,n) c[i]=s[i]-'0';
	fo(i,1,n-1){
		scanf("%d%d",&j,&k);
		add(j,k);add(k,j);
	}
	dfs(1,0);
	ans=bb[1];
	dg(1,0);
	dp[1]=1;
	travel(1,0);
	(ans+=mo)%=mo;
	printf("%d\n",ans);
}
