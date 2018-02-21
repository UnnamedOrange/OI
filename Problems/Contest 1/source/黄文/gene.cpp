#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
struct Data{
	vector<int> data;
	int Len;
	int num;
}a[100000];
bool judge(Data w,Data y){
	for(int i = 0;i<w.Len;i++){
		if(w.data[i] < y.data[i]){
			return 0;
		}
		if(w.data[i] > y.data[i]){
			return 1;
		}
	}
	return w.num < y.num;
}
bool Cmp(const Data & x,const Data & y){ 
	if(x.Len != y.Len){
		return x.Len < y.Len;
	}else{
		return judge(x,y);
	}
}
int main(){
	freopen("gene.in","r",stdin);
	freopen("gene.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		scanf("%d",&a[i].Len);
		a[i].num = i;
		for(int j = 0;j<a[i].Len;j++){
			int t1;
			scanf("%d",&t1);
			a[i].data.push_back(t1);
		}
	}
	sort(a + 1,a + n + 1,Cmp);
	for(int i = 1;i<=n;i++){
		cout<<a[i].num<<" ";
	}
	return 0;
}
