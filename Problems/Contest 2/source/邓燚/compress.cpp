#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;

char a[80005],b[80005];
int c[80005],d[80005],e[80005];
int x;

int main() {
	gets(a);
	gets(b);

	int len1=strlen(a);
	int len2=strlen(b);

	for(int i=0; i<len1; i++) {
		c[i+1]=a[len1-1-i]-'0';
	}

	for(int i=0; i<len2; i++) {
		d[i+1]=b[len2-1-i]-'0';
	}

	for(int i=1; i<=len1; i++)
		for(int l=1; l<=len2; l++) {
			e[i+l-1]=c[i]*d[l]+x+e[i+l-1];
			e[i+l]+=e[i+l-1]/10;
			e[i+l-1]=e[i+l-1]%10;
		}

	int j=len1+len2;
 
   
	while(e[j]==0 && j)j--;

	if(j<1)printf("0");

	else {
		for(int i=j; i>=1; i--) {
			printf("%d",e[i]);
		}
	}
	return 0;
}
