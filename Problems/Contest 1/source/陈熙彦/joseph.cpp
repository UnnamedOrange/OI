#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
int n,m;
bool book[1000000005];
int main()
{
	freopen("joseph.in","r",stdin);
	freopen("joseph.out","w",stdout);
	cin >> n >> m;
	int nowg = n,
		nowc = 0,
		nowb = 0;
	while(nowg!=1)
	{
		nowc++;
		nowb++;
		if(nowb>n) nowb = 1;
		while(book[nowb] == true){
			nowb++;
			if(nowb>n) nowb = 1;
		}
		if(nowc==m){
			book[nowb] = true;
			nowc = 0;
			nowg--;
		}
	}
	for(int i = 1; i <= n; i++){
		if(book[i] == false){
			cout << i;
			return 0;
		}
	}
}
