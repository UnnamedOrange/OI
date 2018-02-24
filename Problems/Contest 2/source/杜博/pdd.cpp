#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[3][1000005];
int max1=-1;
int main() {
	freopen("pdd.in","r",stdin);
	freopen("pdd.out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>dp[1][i];
		dp[2][i]=1;
	}
	for(int i=n-1;i>=1;i--){
		for(int j=i+1;j<=n;j++){
			if(dp[1][i]<dp[1][j]) dp[2][i]=max(dp[2][i],dp[2][j]+1);
		}
	}
    for(int i=1;i<=n;i++) max1=max(max1,dp[2][i]);
    cout<<max1<<endl;
    for(int i=1;i<=n;i++) cout<<dp[2][i]<<" ";
	return 0;
}

//0 4 3 3 2 1
