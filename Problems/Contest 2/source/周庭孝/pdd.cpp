#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1000005;

int n,a[MAXN][2],ans;

int main(){
	freopen("pdd.in","r",stdin);
	freopen("pdd.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i][0]);
		a[i][1]=1;
	}
	for(int i=n;i>=1;i--){
		int l=0;
		for(int j=i+1;j<=n;j++)
			if(a[j][0]>=a[i][0]&&l<a[j][1])
				l=a[j][1];
		if(l>0)
			a[i][1]+=l;
		ans=max(ans,a[i][1]);
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;i++)
		printf("%d ",a[i][1]);
	return 0;
}
