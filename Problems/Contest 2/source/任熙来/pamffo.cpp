#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
#include<vector>
#include<stack>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<cctype>
#define MAXA 100500
// Winner Winner Chicken Dinner
using namespace std;

struct Rx
{
	string Askto;
	int qTime,Time;
}Asker[MAXA];

int n,Command,cnt;
map<string,int> Eat_Chicken;
int main()
{
	freopen("pamffo.in","r",stdin);
	freopen("pamffo.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		string Name;
		int T,qT;
		scanf("%d",&Command);
		if(Command == 1)
		{
			cin >> Name >> T;
			Eat_Chicken[Name] = T;
			continue;
		}
		else
		{
			cin >> Name >> qT >> T;
			cnt++;
			Asker[cnt].Askto = Name;
			Asker[cnt].qTime = qT;
			Asker[cnt].Time  = T;
		}
	}
	
	for(int i=1;i<=cnt;i++)
	{
		int Chicken_Time = Eat_Chicken[Asker[i].Askto];
		if(Asker[i].Time < Chicken_Time)
		{
			printf("0\n");
			continue;
		}
		else
		{
			if(Asker[i].qTime >= Chicken_Time)
			{
				printf("1\n");
				continue;
			}
			else
			{
				printf("0\n");
				continue;
			}
		}
	}
}
/*
6
2 db 100 100
1 pamffo 101
1 db 102
2 db 100 103
2 db 102 104
2 db 101 105
*/
