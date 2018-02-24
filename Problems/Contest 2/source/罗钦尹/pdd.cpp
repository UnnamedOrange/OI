#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int f[100001];
int main(){
	freopen("pdd.in","r",stdin);
	freopen("pdd.out","w",stdout);
	int n;
	int a[100001];
	cin>>n;
	for(int i=1;i<=n;i++)
	cin>>a[i];
	int maxx=-1;
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[j]<=a[i]&&i>j){
				f[i]=max(0,f[j]);
			}
		}
		f[i]++;
		if(f[i]>maxx) maxx=f[i];
	}
	cout<<maxx<<endl;
	for(int i=n;i>=1;i--)
	cout<<f[i]<<" ";
	return 0;
}
