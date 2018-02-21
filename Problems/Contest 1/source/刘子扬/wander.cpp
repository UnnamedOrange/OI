#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;
int map[1000][1000];
int point,bian;
int main(){
	freopen("wander.in","r",stdin);
	freopen("wander.out","w",stdout);
	cin>>point>>bian;
	int a,b,weight;
	memset(map,INT_MAX,sizeof(int));
	for(int i=1;i<=bian;i++){
		scanf("%d %d %d",&a,&b,&weight);
		map[a][b] = weight;
	}
	//相同的情况好像不是很需要考虑 i = j的情况 
	for(int k=1;k<=point;k++)
	for(int i=1;i<=point;i++)
	for(int j=1;j<=point;j++)
	{
		if(map[i][k]+map[k][j] < map[i][j]) 
		map[i][j] = map[i][k]+map[k][j];
	}
	cout<<map[1][point]<<endl;
	cout<<0;
	return 0;
}
/*

3 3
1 2 5
2 3 4
1 3 10

// 9
   0


*/
