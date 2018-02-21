#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
struct pp{
	int length,number;
	vector<int> c;
}q[10005];
int n,a,flag = 0;
bool rule(pp fir,pp sec)
{
	if(fir.length > sec.length) return false;
	else if(fir.length < sec.length) return true;
	else{
		if(fir.c > sec.c) return true;
		else return false;
	}
}
int main()
{
	freopen("gene.in","r",stdin);
	freopen("gene.out","w",stdout);
	scanf("%d",&n);
	for(int i = 1; i <= n; i++){
		scanf("%d",&q[i].length);
		q[i].number = i;
		for(int j = 1; j <= q[i].length; j++){
			scanf("%d",&a); 
			q[i].c.push_back(a);
		}
	}
	sort(q+1,q+1+n,rule);
	for(int i = 1; i <= n; i++){
		if(flag) printf(" ");
		printf("%d",q[i].number);
		flag = 1;
	}
	return 0;
}
