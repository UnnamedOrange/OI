#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	freopen("joseph.in","r",stdin);
    freopen("joseph.out","w",stdout); 
	long long n,m;
	cin>>n>>m;
	long long res=0;
	for(int i=2;i<=n;i++){
		res=(res+m)%i;
	}
	cout<<res+1;
	return 0;
}
