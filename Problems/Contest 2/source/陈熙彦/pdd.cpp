#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=1000005;
int n,f[MAXN],Map[MAXN];
int main()
{
	freopen("pdd.in","r",stdin);
	freopen("pdd.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&Map[i]);
	for(int i=n-1; i>=1; i--)
		for(int j=n; j>i; j--){
			if(Map[j]>=Map[i]) f[i]=max(f[i],f[j]+1);
		}
	int maxn=0;
	for(int i=1; i<=n; i++){
		f[i]++;
		maxn=max(maxn,f[i]);
	}
	printf("%d\n",maxn);
	bool flag=false;
	for(int i=1; i<=n; i++){
		if(flag) cout << " ";
		flag=true;
		printf("%d",f[i]); 
	}
	return 0;
}
/*
6
1 4 2 8 5 7
*/
