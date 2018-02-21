#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<string>
using namespace std;
struct f{
	int num;
	int zdx[10001];
	int lenth;
}sw[10005];
char a[2000005];
bool cmp(f x, f y){
	if(x.lenth==y.lenth){
		for(int i=1;i<=x.lenth;i++){
			if(x.zdx[i]!=y.zdx[i]){
			return x.zdx[i]>y.zdx[i];
		}
			if(i==x.lenth) return x.num<y.num;
		}
	}
	else return x.lenth<y.lenth;
	
}
int main(){
		freopen("gene.in","r",stdin);
		freopen("gene.out","w",stdout);
	int n,count=0;
	cin>>n;
	getchar();
	for(int j=1;j<=n;j++){
		int k=1;
		count=0;
		gets(a);
		for(int i=0;i<strlen(a);i++){
			if(a[i]==' ') count++;
			if(a[i]!=' '){
				if(a[i+1]!=' ')
				sw[j].zdx[k]=(a[i]-'0')*10 + a[i+1]-'0';
				else sw[j].zdx [k] = a[i]-'0';
				k++;
		}
	}
	sw[j].lenth=strlen(a)-count;
	sw[j].num=j;
}

    sort(sw+1,sw+1+n,cmp);
    for(int i=1;i<=n;i++) for(int j=1;j<=4;j++) cout<<sw[i].zdx [j]<<" ";
	return 0;
} 

