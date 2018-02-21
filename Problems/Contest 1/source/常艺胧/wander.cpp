/*
3 3
1 2 5
2 3 4
1 3 10
*/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
#define MAXN 200005 
int flag = 0;
int o = 0;
int maxw = -1;
struct Vtx{
	int to;
	Vtx *next;
	int wet;
	Vtx() : next(NULL),wet(0){}
};
struct VtxHead : Vtx{
	Vtx *head;
	int  dist;
	void operator += (int to){
		if(head == NULL){
			next = new Vtx;
			next->to = to;
			head = next;
		}
		else{
			next->next = new Vtx;
			next = next->next;
			next->to = to;
		}
	}
	VtxHead() : head(NULL) ,dist(INT_MAX) {} 
}Graph[MAXN];
void calc(int start)
{
	Graph[start].dist = 0;
	queue<int> tv;
	tv.push(start);
	
	while(!tv.empty())
	{
		int from = tv.front();
//		cout << "from=" << from << endl;
		tv.pop();

		for(Vtx *i = Graph[from].head;i;i = i->next)
		{
			 if(Graph[from].dist + i->wet < Graph[i->to].dist)
			 {
				maxw = max(maxw,i->wet);
			 	Graph[i->to].dist = Graph[from].dist + i->wet;
			 	tv.push(i->to);
			 }
		}
	}
}
int main()
{
	freopen("wander.in","r",stdin);
	freopen("wander.out","w",stdout);
	int n,m;
//	cin >> n >> m;
	scanf("%d %d",&n,&m);
	if(n == 1 && m == 1)
	{
//		cout << 0 << endl << 0 << endl;
		printf("0\n0");
		return 0;
	}
	for(int i = 1;i <= m;i++)
	{
		int v,u;
		if(v == 1 && u == n)
		{
			flag = 1;
		}
		scanf("%d %d",&v,&u);
		Graph[v] += u;
		int w;
//		cin >> w; 
		scanf("%d",&w);
		Graph[v].next->wet = w;
//		cout << "wet=" << Graph[v].next->wet << endl;
	}
	calc(1);
	int ans = Graph[n].dist;
//	cout << ans << endl << 0;
	if(flag != 0)
	{
		o = ans - maxw; 
	}
	printf("%d\n%d",ans,o);
	return 0;
}
