#include<iostream>
#include<algorithm>
using namespace std;
int Map[501][601];
int dp[401];
int main() {
	freopen("Wander.in","r",stdin);
	freopen("Wander.out","w",stdout);
	int n,m,min=99999999;//n��������m��������
	cin>>n>>m;
	int x,y,z;//x����㣬y���յ㣬z��Ȩ��
	if(n==1) cout<<"0"<<endl<<0;
	else {
		for(int i=1; i<=m; i++) {
			cin>>x>>y>>z;
			Map[x][y]=z;
			Map[y][x]=99999999;
		}
		for(int k=1; k<=n; k++) {
			for(int i=1; i<=n; i++) {
				for(int j=1; j<=n; j++) {
					if(Map[i][k]+Map[k][j]<Map[i][j])
						Map[i][j]=Map[i][k]+Map[k][j];
					}
			}
		}
		cout<<Map[1][n]<<endl<<0<<endl;
	}
	return 0;
}
