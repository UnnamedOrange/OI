#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
bool Alive[1000000000];
int main() {
	freopen("joseph.in","r",stdin);
	freopen("joseph.out","w",stdout);
	int m,n;
	cin>>n>>m;
	if(m != 2) {
		int temp = n,ans;
		int Pos = 1,Crt = 0;
		while(temp) {
			if(Pos > n) {
				Pos = 1;
			}
			if(!Alive[Pos]) {
				Crt++;
			}
			if(Crt == m && !Alive[Pos]) {
				Alive[Pos] = true;
				Crt = 0;
				temp--;
				ans = Pos;
			}
			Pos++;
		}
		cout<<ans;
	} else if(m == 2) {
		int temp = m;
		while(temp < n) {
			temp *= 2;
		}
		temp -= (m - 1);
		long long ans = temp;
		for(int j = temp; j>n; j--) {
			ans -= m;
		}
		cout<<ans;
	}
	return 0;
}
