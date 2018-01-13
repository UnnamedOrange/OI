#include<cstdio>
#include<algorithm>
#include<ctime>
#define fo(i,a,b) for(i=a;i<=b;i++)
#define fd(i,a,b) for(i=a;i>=b;i--)
using namespace std;
typedef long long ll;
const int maxn=1000000+10;
int belong[maxn],c[maxn],d[maxn];
int i,j,k,l,t,n,m,tot,a,b,v,lim;
int random(int x){
	ll t=rand()%10000;
	t=t*10000+rand()%10000;
	t=t*10000+rand()%10000;
	return t%x;
}
void work(){
	int k;
	fo(k,j+1,i) belong[k]=i-j;
	j=i;
}
int main(){
	freopen("schooldays18.in","w",stdout);
	srand(time(0));
	n=1000000;
	printf("%d\n",n);
	v=500;
	j=0;i=1;
	while (i<=n){
		if (i==n||random(v)==0) work();
		i++;
	}
	/*lim=1;
	fo(i,1,n){
		c[i]=random(min(lim,belong[i]))+1;
		d[i]=belong[i]+random(n-belong[i]+1);
		printf("%d %d\n",c[i],d[i]);
	}*/
	c[n+1]=n;
	fd(i,n,1){
		//c[i]=random(min(c[i+1],belong[i]))+1;
		if (belong[i]<c[i+1]) c[i]=belong[i];else c[i]=c[i+1];
		d[i]=belong[i]+random(n-belong[i]+1);
		//printf("%d %d\n",c[i],d[i]);
	}
	fo(i,1,n) printf("%d %d\n",c[i],d[i]);
}
