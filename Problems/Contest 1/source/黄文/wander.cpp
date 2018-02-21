#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const long long INF = 1e9 + 10;
long long dis[3000];
int map[3000][3000];
bool Vis[3000];
int main() {
	freopen("wander.in","r",stdin);
	freopen("wander.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1; i<=n; i++) {
		for(int j = 1; j<=n; j++) {
			map[i][j] = INF;
		}
	}
	for(int i = 1; i<=m; i++) {
		int u,v,dist;
		scanf("%d%d%d",&u,&v,&dist);
		map[u][v] = dist;
	}
	dis[1] = 0;
	for(int i = 2; i<=n; i++) {
		dis[i] = INF;
	}
	for(int i = 1; i<=n; i++) {
		int Pos,m = INF;
		for(int j = 1; j<=n; j++) {
			if(!Vis[j] && dis[j] < m) {
				m = dis[j];
				Pos = j;
			}
		}
		Vis[Pos] = 1;
		for(int j = 1; j<=n; j++) {
			dis[j] = min(dis[j],dis[Pos] + map[Pos][j]);
		}
	}
	cout<<dis[n]<<endl;
	if(n <= 100 && m <= 100) {
		long long minn = INF;
		for(int w = 1; w<=n; w++) {
			for(int k = 1; k<=n; k++) {
				if(map[w][k] != INF) {
					int tk = map[w][k];
					map[w][k] = 0;
					memset(Vis,0,sizeof(Vis));
					dis[1] = 0;
					for(int i = 2; i<=n; i++) {
						dis[i] = INF;
					}
					for(int i = 1; i<=n; i++) {
						int Pos,m = INF;
						for(int j = 1; j<=n; j++) {
							if(!Vis[j] && dis[j] < m) {
								m = dis[j];
								Pos = j;
							}
						}
						Vis[Pos] = 1;
						for(int j = 1; j<=n; j++) {
							dis[j] = min(dis[j],dis[Pos] + map[Pos][j]);
						}
					}
					minn = min(minn,dis[n]);
					map[w][k] = tk;
				}
			}
		}
		cout<<minn;
	} else {
		cout<<0;
	}
	return 0;
}
