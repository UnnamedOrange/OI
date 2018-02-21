#include<iostream>
#include<cstdio>
using namespace std;
int n,m;
long long f[10000][10000];
long long b[10000][10000];

int main(){
    freopen("wander.in","r",stdin);
    freopen("wander.out","w",stdout); 
    int h,x,y;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d %d",&x,&y,&h);
		b[x][y]=b[y][x]=h;
		f[x][y]=f[y][x]=h;
	}
	int maxx=-1;
	for(int k=1;k<=m;k++){
		for(int i=1;i<=m;i++){
			for(int j=1;j<=m;j++){
				if(b[i][j]>b[i][k]+b[k][j] && i!=j && i!=k && k!=j){
					b[i][j]=b[i][k]+b[k][j];
					if(maxx<b[i][j])maxx=b[i][j];
				}
		}
	}}
	cout<<b[1][n]<<endl;
	
	if(f[1][n])printf("0");
	else {
		cout<<b[1][n]-maxx;
	}
	return 0;
}
