#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=100005;

int n,o,m;

struct hehe{
	string name;
	vector<int>cj;
}r[MAXN];


int main(){
	freopen("pamffo.in","r",stdin);
	freopen("pamffo.out","w",stdout);
	cin>>n;
	while(n--){
		scanf("%d",&o);
		if(o==1){
			string s;
			int time;
			cin>>s;
			scanf("%d",&time);
			int q=0;
			for(int i=1;i<=m;i++)
				if(r[i].name.length()==s.length()){
					int p=0;
					for(int j=0;j<s.length();j++)
						if(r[i].name[j]!=s[j]){
							p=1;
							break;
						}
					if(!p){
						q=1;
						r[i].cj.push_back(time);
						break;
					}
				}
			if(!q){
				m++;
				r[m].name=s;
				r[m].cj.push_back(time);
			}
		}
		else{
			string s;
			int time,qtime;
			int sum=0;
			cin>>s;
			scanf("%d%d",&qtime,&time);
			for(int i=1;i<=m;i++)
				if(r[i].name.length()==s.length()){
					int p=0;
					for(int j=0;j<s.length();j++)
						if(r[i].name[j]!=s[j]){
							p=1;
							break;
						}
					if(!p){
						for(int j=0;j<r[i].cj.size();j++)
							if(r[i].cj[j]>qtime)
								break;
							else
								sum++;
						break;
					}
				}
			cout<<sum<<endl;
		}
	}
	return 0;
}
