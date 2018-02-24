#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
const int Max = 80005;
char a[Max],b[Max];
int shu1[Max],shu2[Max],ans[Max*2];
int main()
{
	scanf("%s",&a);
	scanf("%s",&b);
	int lena=strlen(a),
		lenb=strlen(b);
	for(int i=0,j=lena-1; i<lena; i++,j--) shu1[j]=a[i]-'0';
	for(int i=0,j=lenb-1; i<lenb; i++,j--) shu2[j]=a[i]-'0';
	for(int i=0; i<lena; i++)
		for(int j=0; j<lenb; j++){
			ans[i+j]+=shu1[i]*shu2[j];
			int rest=ans[i+j]/10;
			ans[i+j]%=10;
			int wei=1;
			while(rest){
				ans[i+j+1]+=rest;
				rest=ans[i+j+wei]/10;
				ans[i+j+wei]%=10;
			}
		}
	bool flag=false;
	for(int i=Max*2;i>=0;i--){
		if(ans[i]!=0) flag=true;
		if(flag) cout << ans[i];
	}
	return 0;
}
