#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<string>
using namespace std;
bool a[10000005]={0};
int n,m;
int main() {
	freopen("joseph.in","r",stdin);
	freopen("joseph.out","w",stdout);
	cin>>n>>m;
	int s=0;
	for(int k=0; k<n; k++) {
		for(int i=0; i<m; i++) {
			if(++s>n) s=1;
			if(a[s]) i--;
		}
		if(k==n-1)
		cout<<s;
		a[s]=true;
	}
	return 0;
}


