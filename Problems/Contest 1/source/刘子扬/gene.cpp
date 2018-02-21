#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;

int n;
char c[100000][1000];
int num[100000];
int fine[100000];

int comp(int a, int b){
	
	if(num[a] == num[b]){
		return strcmp(c[a],c[b]);
	}
	if(num[a]>num[b]) return 1;
	if(num[a]==num[b]) return 0;
	if(num[a]<num[b]) return -1;
	
	//return num[a] > num[b];
	
}
int main(){
	freopen("gene.in","r",stdin);
	freopen("gene.out","w",stdout);
	cin>>n; 
	int k=n;
	int idx = 1;
	k++;
	while(k--){
		gets(c[idx]);
		idx++;
	for(int i=0;i<strlen(c[idx]);i++)
		if(c[idx][i] == ' ') num[idx]++;
		num[idx]++;
		fine[idx] = idx;
	}
	sort(fine+1,fine+n+1,comp);
	//cout<<" ";int flag = 0
	for(int i=1;i<=n;i++)
	cout<<fine[i]<<" ";
	return 0;
}
