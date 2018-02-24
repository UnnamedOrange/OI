#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100001;

char a[MAXN],b[MAXN];
int A[MAXN],B[MAXN],la,lb;
int C[MAXN],lc,l;

int main(){
	cin>>a>>b;
	la=strlen(a);
	lb=strlen(b);
	lc=la+lb;
	for(int i=0;i<la;i++)
		A[i]=a[la-i-1]-'0';
	for(int i=0;i<lb;i++)
		B[i]=b[lb-i-1]-'0';
	for(int i=0;i<lb;i++){
		for(int j=0;j<la;j++){
			C[i+j]+=B[i]*A[j];
			if(C[i+j]>=10){
				C[i+j+1]+=C[i+j]/10;
				C[i+j]%=10;
			}
		}
	}
	while(C[lc]==0&&lc)
		lc--;
	for(int i=lc;i>=0;i--)
		cout<<C[i];
	return 0;
}
