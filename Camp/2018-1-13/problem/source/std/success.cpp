#include<cstdio>
#include<algorithm>
#define fo(i,a,b) for(i=a;i<=b;i++)
#define fd(i,a,b) for(i=a;i>=b;i--)
using namespace std;
typedef long long ll;
const int maxn=2000+10,mo=1000000007;
int fac[maxn],inv[maxn],f[maxn][maxn],g[maxn][maxn],c[maxn][maxn],su[maxn],S[maxn],mit[maxn],mis[maxn];
int i,j,k,l,r,t,n,m,mn,ans;
ll s;
int qsm(int x,int y){
	if (!y) return 1;
	int t=qsm(x,y/2);
	t=(ll)t*t%mo;
	if (y%2) t=(ll)t*x%mo;
	return t;
}
int C(int x,int y){
	return c[x-n][y];
}
int main(){
	freopen("success.in","r",stdin);freopen("success.out","w",stdout);
	scanf("%lld%d%d%d",&s,&t,&n,&m);
	//s-=(ll)m;t--;
	mn=m-n;
	mit[0]=qsm(t,n);
	fo(i,1,mn) mit[i]=(ll)mit[i-1]*t%mo;
	mis[0]=1;
	fo(i,1,mn) mis[i]=(ll)mis[i-1]*(s%mo)%mo;
	fac[0]=1;
	fo(i,1,2*mn) fac[i]=(ll)fac[i-1]*i%mo;
	inv[2*mn]=qsm(fac[2*mn],mo-2);
	fd(i,2*mn-1,0) inv[i]=(ll)inv[i+1]*(i+1)%mo;
	fo(i,0,mn){
		l=min(i+n,2*mn);
		c[i][0]=1;
		fo(j,1,l) c[i][j]=(ll)c[i][j-1]*(i+n-j+1)%mo;
		fo(j,0,l) c[i][j]=(ll)c[i][j]*inv[j]%mo;
	}
	f[0][0]=g[0][0]=1;
	fo(i,1,2*mn)
		fo(j,0,i/2){
			f[i][j]=(ll)f[i-1][j]*(i-1)%mo;
			g[i][j]=(ll)g[i-1][j]*j%mo;
			if (i>1&&j){
				(f[i][j]+=(ll)f[i-2][j-1]*(i-1)%mo)%=mo;
				(g[i][j]+=(ll)g[i-2][j-1]*(i-1)%mo)%=mo;
			}
		}
	fo(i,0,mn)
		fo(j,0,min(m-(i+n),i+n)) (su[i]+=(ll)f[m-(i+n)+j][j]*C(m,m-(i+n)+j)%mo)%=mo;
	fo(i,0,mn)
		fo(j,0,min(i,m-i)) (S[i]+=(ll)g[i+j][j]*C(i+n,i+j)%mo)%=mo;
	fo(i,0,mn){
		fo(j,i,mn){
			l=(ll)C(j+n,j-i)*mit[i]%mo*mis[j-i]%mo*su[j]%mo*S[i]%mo;
			if ((m+j-i)%2) (ans-=l)%=mo;else (ans+=l)%=mo;
		}
	}
	fo(i,n+1,m) ans=(ll)ans*qsm(i,mo-2)%mo;
	if (n%2) ans=-ans;
	(ans+=mo)%=mo;
	printf("%d\n",ans);
}
