#include<bits/stdc++.h>
#define MAXN 100005

using namespace std;

struct eat {
	
	int time;
	int qtime;	
}chicken[MAXN];

string name;
int n;
int s;

int main( )
{
	freopen("pamffo.in", "r",stdin);
	freopen("pamffo.out","w",stdout);
	scanf("%d", &n);
	
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &s);
		if(s == 2)
		{
			cin >> name;
			cin >> chicken[i].qtime;
			cin >> chicken[i].time;
			printf("0\n");
		}
		if(s == 1)
		{
			cin >> name;
			cin >> chicken[i].time;
			printf("0\n");
		}
	}
	
	return 0;
}






