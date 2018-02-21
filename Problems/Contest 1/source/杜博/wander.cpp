#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<string>
using namespace std;
int tol=99999999;
int a[20005][20005],b[20005],c[20005];
int n,m;
void floay(){
	for(int i=1;i<=n;i++)
       for(int j=1;j<=n;j++)
          a[1][i]=min(a[1][i],a[1][j]+a[j][i]);
          return ;
}
int main(){
	freopen("wander.in","r",stdin);
	freopen("wander.out","w",stdout);
	cin>>n>>m;
	int u=1;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j]=99999999;
	for(int i=1;i<=m;i++) {
		int x,y,z;
		cin>>x>>y>>z;
		b[u]=x;
		c[u]=y;
		a[x][y]=z;
		u++;
	}
    floay();
	cout<<a[1][n];
	for(int p=1;p<=m;p++){
		int temp = a[b[p]][c[p]];
		a[b[p]][c[p]]=0;
		floay();
		tol=min(tol,a[1][n]);
		a[b[p]][c[p]]=temp;
	}
	cout<<endl;
	cout<<tol;
	return 0;
}


