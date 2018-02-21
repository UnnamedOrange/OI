#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
long long f[10005],a[10005][10005],n,m,s,e,len;
bool b[10005][10005],is[10005];
void dothejob(int x)
{
	is[x] = true;
	for(int i = 1; i <= n; i++){
		if(b[x][i]){
			if(!is[i]){
				f[i] = f[x]+a[x][i];
				dothejob(i);
			}
			else{
				if(f[x]+a[x][i] < f[i]){
					f[i] = f[x]+a[x][i];
					dothejob(i);
				}
			}
		}
	}
}
int main()
{
	freopen("wander.in","r",stdin);
	freopen("wander.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= m; i++){
		scanf("%d%d%d",&s,&e,&len);
		if(b[s][e]){
			a[s][e] = min(a[s][e],len);
			a[e][s] = a[s][e];
		}
		else{
			b[s][e] = true;
			b[e][s] = true;
			a[s][e] = len;
			a[e][s] = len;
		}
	}
	dothejob(1);
	cout << f[n] <<endl<< 0;
	return 0;
}
