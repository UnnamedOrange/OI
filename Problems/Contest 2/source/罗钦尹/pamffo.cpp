#include<iostream>
#include<string.h>
#include<map>
using namespace std;
struct man{
	string name;
	int Time;
	map<string,int>dinner;
}a[100001];

int type,time,qtime;
string s;

int strcmpd(string f,string b){
	if(f.length()!=b.length()) return 0;
	else {
		for(int i=0;i<=f.length();i++){
			if(f[i]!=b[i])
			return 0;
		}
		return 1;
	}
}
int main(){
	freopen("pamffo.in","r",stdin);
	freopen("pamffo.out","w",stdout);
	
	int n,top=1,head=1;
	cin>>n;
	
	for(int i=1;i<=n;i++){
		cin>>type;
		if(type==1){
			cin>>a[i].name;
			cin>>a[i].Time;
			a[i].dinner[a[i].name]++;
		}
		if(type==2){
			cin>>s;
			cin>>qtime;
			cin>>time;
			int tot=0;
			for(int i=1;i<=n;i++){
				if(strcmpd(a[i].name,s)==1&&a[i].Time<=qtime) tot+=a[i].dinner[s];
				
			}
			cout<<tot<<endl;
		}
	}
	
	return 0;
} 
