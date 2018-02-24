#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
using namespace std;
const int MAXN = 1e6 + 5;
int dp[MAXN][2];
int main() {
	freopen("pdd.in","r",stdin);
	freopen("pdd.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i = 1; i<=n; i++) {
		scanf("%d",&dp[i][0]);
		dp[i][1] = 1;
	}
	int Maxn = 0;
	for(int i = n; i>=1; i--) {
		int l = 0;
		for(int j = n; j>i; j--) {
			if(dp[i][0] <= dp[j][0] && dp[j][1] > l) {
				l = dp[j][1];
			}
		}
		if(l) {
			dp[i][1] = l + 1;
			Maxn = max(Maxn,dp[i][1]);
		}
	}
	printf("%d\n",Maxn);
	for(int i = 1; i<=n; i++) {
		printf("%d ",dp[i][1]);
	}
	return 0;
}
