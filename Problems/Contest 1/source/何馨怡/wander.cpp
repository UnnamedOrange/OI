#include<iostream>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<vector>
#include<queue>


using namespace std;

int n, m, node, dis[1000], head[1000], inf = 9999999, vis[10000];

struct edge
{
	int v, w, next;
}e[10000];

void add_edge(int src, int to, int weight)
{
	e[node].v = to;
	e[node].w = weight;
	e[node].next = head[src];
	head[src] = node++;
}

void spfa()
{
	queue<int>que;
	for(int i = 1; i <= n; i++)
	{
		dis[i] = inf;
		vis[i] = 0;
	}
	dis[1] = 0;
	que.push(1);
	while(!que.empty())
	{
		int now = que.front();
		que.pop();
		vis[now] = 1;
		for(int i = head[now]; i >= 0;i = e[i].next)
		{
			int to = e[i].v;
			if(dis[to] == inf || dis[to] > dis[now] + e[i].w)
			{
				dis[to] = dis[now] + e[i].w;
				if(vis[to] == 0)
				{
					vis[to] = 1;
					que.push(to);
				}
			}
		}
	}
}

int main( )
{
	freopen("wander.in","r",stdin);
	freopen("wander.out","w",stdout);
	cin >> n >> m;
	memset(head,-1,sizeof(head));
	for(int i = 1;i  <= n;i++)
	{
		int a,b, c;
		cin >> a>>b>>c;
		add_edge(a,b,c);
	}
	spfa();
	cout << dis[n] << " "<< "0";
	return 0;
}









