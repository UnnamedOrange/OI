#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN = 80000 + 5;
int Lgt;
char a[MAXN],b[MAXN];
int Ans[2*MAXN];
void Long(int la,int lb) {
	long long x = 0,y = 0;
	for(int i = 1; i<=la; i++) {
		x *= 10;
		x += a[i] - '0';
	}
	for(int i = 1; i<=lb; i++) {
		y *= 10;
		y += b[i] - '0';
	}
	cout<<x*y<<endl;
}
void Over(int Lgt_a,int Lgt_b) {
	for(int i = 0; i<Lgt_a; i++) {
		int Rem = 0;
		for(int j = 0; j<Lgt_b; j++) {
			if(i + j > Lgt) {
				Lgt++;
			}
			Ans[i + j] += (a[Lgt_a - i] - '0') * (b[Lgt_b - j] - '0') + Rem;
			Rem = Ans[i + j] / 10;
			Ans[i + j] %= 10;
		}
		if(Rem) {
			Lgt++;
			Ans[Lgt] = Rem;
		}
	}
	while(!Ans[Lgt] && Lgt) {
		Lgt--;
	}
	for(int i = Lgt; i>=0; i--) {
		printf("%d",Ans[i]);
	}
}
void Work() {
	int Lgt_a = strlen(a + 1),
	    Lgt_b = strlen(b + 1);
	if(Lgt_a <= 9 && Lgt_b <= 9) {
		Long(Lgt_a,Lgt_b);
	} else {
		Over(Lgt_a,Lgt_b);
	}
}

int main() {
	scanf("%s%s",a + 1,b + 1);
	Work();
	return 0;
}
