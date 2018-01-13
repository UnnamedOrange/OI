#include<cstdio>
#include<algorithm>
#include<ctime>
#define fo(i,a,b) for(i=a;i<=b;i++)
using namespace std;
typedef long long ll;
const int maxn=1000000+10;
int i,j,k,l,t,n,m,tot,a,b,d;
ll s,ss,sss,lim;
ll random(ll x){
	ll t=rand()%10000;
	t=t*10000+rand()%10000;
	t=t*10000+rand()%10000;
	return t%x;
}
int main(){
	freopen("success10.in","w",stdout);
	srand(time(0));
	ss=100000000000000000;sss=100000000;
	s=(ll)random(sss+1)+ss-sss;
	d=1000000000;
	m=random(d)+1;
	//n=m-random(101);
	n=m-1000;
	lim=min((ll)100000,(ll)s/n);
	t=random(lim)+1;
	/*n=random(11);t=random(11);m=random(11)+90;
	s=n*t;
	s+=random(100-s+1);*/
	printf("%lld %d %d %d\n",s,t,n,m);
}
