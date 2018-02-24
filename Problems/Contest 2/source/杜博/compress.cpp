#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char a[100000],b[100000];
int tot[100000000];
int main(){
	gets(a);
	gets(b);
	int k=0;
	for(int i=strlen(b)-1;i>=0;i--){
		int m=1;
		for(int j=strlen(a)-1;j>=0;j--){
		tot[m+k] +=	((int)a[j]-48)*((int)b[i]-48);
		m++;
		}
		k++;
	}
	for(int j=1;j<=10;j++)
	for(int i=1;i<=k+strlen(b)+100;i++){
		if(tot[i]>=10){
			int temp=tot[i]/10;
			tot[i+1]+=temp;
			tot[i]-=temp*10;
		}
	}
	int po=0;
	for(int i=strlen(b)+k+10;i>=1;i--){
		if(po==1){
		cout<<tot[i];
	}
		if(tot[i]!=0&&po==0){
			cout<<tot[i];
			po=1;
		}
	}
	return 0;
}

