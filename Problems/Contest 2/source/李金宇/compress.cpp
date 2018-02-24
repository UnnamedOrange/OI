#include<bits/stdc++.h>
using namespace std;
int main(){
	char A[80005],B[80005];
	cin>>A>>B;
	int a[80005],b[80005],c[200005],la=strlen(A),lb=strlen(B),lc,x;
	memset(a,0,sizeof(a)),memset(b,0,sizeof(b)),memset(c,0,sizeof(c));
	for(int i=0;i<la;i++)a[la-i]=A[i]-'0';
	for(int i=0;i<lb;i++)b[lb-i]=B[i]-'0';
	for(int i=1;i<=la;i++){
		x=0;
		for(int j=1;j<=lb;j++){
			c[i+j-1]=a[i]*b[j]+x+c[i+j-1];
			x=c[i+j-1]/10;
			c[i+j-1]%=10;
		}
		c[i+lb]=x;
	}
	lc=la+lb;
	while(c[lc]==0&&lc>1)lc--;
	for(int i=lc;i>=1;i--)cout<<c[i];
}
