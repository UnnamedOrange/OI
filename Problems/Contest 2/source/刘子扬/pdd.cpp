#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 5;
int h[MAXN];
long long f[MAXN];
int main(){
	freopen("pdd.in","r",stdin);
	freopen("pdd.out","w",stdout);
	long long n;cin>>n;
	for(long long i=1;i<=n;i++)
	scanf("%lld",h+i);
//	cin>>h[i];
	long long maxx=-1;
	long long maxn=-1;
	//int h_max;
	//long long h_f;
	for(long long i=n;i>=1;i--){
		maxx = 0;
		//if(h[i]<=h_max) f[i] = maxn+1;
		//else 
		for(long long j=n;j>=i;j--){
			if(h[i]<=h[j] && f[j]>maxx) maxx=f[j];
		}
		
		f[i] = maxx+1;
		if(f[i]>maxn){
			maxn = f[i];
			//h_max = h[i];
		} 
		
	}
	cout<<maxn<<endl;
	printf("%lld",f[1]);
	for(int i=2;i<=n;i++)
	printf(" %lld",f[i]);
	//cout<<f[i]<<" ";
	return 0;
}
