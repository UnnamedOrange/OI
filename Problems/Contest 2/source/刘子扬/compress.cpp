#include<bits/stdc++.h>
using namespace std;
const int MAXN = 80020;
char a[MAXN];
char b[MAXN];
char c[MAXN*2+5];
int len_a,len_b,len_c;
int main(){
	
	scanf("%s",a);
	scanf("%s",b);
	len_a = strlen(a);
	len_b = strlen(b);
	len_c = len_a + len_b + 5;
	int k = 0;
	int up = 0;
	int r=0;
	for(int i=len_a-1;i>=0;i--)
	for(int j=len_b-1;j>=0;j--)
	{   up = len_a + len_b - i -j - 2;
		k = up;
		int I = a[i] - '0';
		int J = b[j] - '0';
		int p = I*J  + c[k];
		r = p/10;
		int cnt = p%10;
		c[k] = cnt;
		k++;
		c[k] += r;
		
	}
	
	//if(!r) c[k] = r;
	int flag=0;
	for(int i=k;i>=0;i--){
		if(c[i]!=0) flag = 1;
		if(flag == 1)
		printf("%d",c[i]);
	}
	
	
	return 0;
}
