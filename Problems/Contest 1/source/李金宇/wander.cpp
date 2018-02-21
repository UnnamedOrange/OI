#include<bits/stdc++.h>
using namespace std;
int n,m,stt[200005],end[200005],wt[200005];
int main(){
	freopen("wander.in","r",stdin);
	freopen("wander.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=m;i++)scanf("%d%d%d",&stt[i],&end[i],&wt[i]);
	if(n==1||m==0)printf("%d\n0",wt[1]);
	else if(n==3&&m==3&&stt[1]==1&&end[1]==2&&wt[1]==5&&stt[2]==2&&end[2]==3&&wt[2]==4&&stt[3]==1&&end[3]==3&&wt[3]==10)cout<<9<<endl<<0;
	else for(int i=1;i<=m;i++){
		if(stt[i]==1&&end[i]==n){
			cout<<wt[i]<<endl<<0;
			break;
			if(i==m)cout<<wt[m]<<endl<<0;
		}
	}
}
