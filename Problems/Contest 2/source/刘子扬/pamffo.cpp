#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e2 + 20;
struct node{
	char name[105];
	long long time;
	long long num=0;
}eater[MAXN];
int main(){
	
	freopen("pamffo.in","r",stdin);
	freopen("pamffo.out","w",stdout);
	
	long long n;
	cin>>n;
	long long k=0;
	
	
	for(long long i=1;i<=n;i++){
		
		int type;
		scanf("%d",&type);
		if(type==1){
			
			k++;
			
			scanf("%s %lld",eater[k].name,&eater[k].time);
			eater[k].num = 1;
			for(long long j=k-1;j>=1;j--)
			if(strcmp(eater[k].name,eater[j].name)==0){
				eater[k].num = eater[j].num+1;
				break;
			}
			
			
		}
		
		if(type==2){
			
			long long qtime,time;
			
			int flag2=0;
			char qname[105];
			
			scanf("%s %lld %lld",qname,&qtime,&time);
			
			if(k==0){
				
			 putchar('0');
			putchar('\n');
			continue;
			}
			
			for(long long j=k;j>=1;j--){
				
				if( (strcmp(qname, eater[j].name)==0 ) && eater[j].time<=qtime ){
					
				cout<<eater[j].num<<endl;
				flag2=1;
				break;}
			}
			
			if(flag2==0) {
				putchar('0');
				putchar('\n');
				//cout<<"what just happen??"<<endl;
			}			

		}
		
		
	}
	return 0;
}
