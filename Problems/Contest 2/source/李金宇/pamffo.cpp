#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("pamffo.in","r",stdin);
	freopen("pamffo.out","w",stdout);
	char nm[105];
	int a[100005];
	int n,x,time,qtime,cnt=0,book=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		book=0;
		cin>>x>>nm;
		if(x==1){
			cin>>time;
			cnt++;
			a[cnt]=time;
		}
		else{
			cin>>qtime>>time;
			for(int i=1;i<=cnt;i++)if(a[i]==qtime)cout<<i<<endl,book=1;
			if(book==0)cout<<0<<endl;
		}
	}
	for(int i=1;i<=cnt;i++)cout<<a[i];
}
