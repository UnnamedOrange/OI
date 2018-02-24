#include<bits/stdc++.h>
using namespace std;
#define MAXN 100005
int dis = 0;
int ans = 0;
struct people
{
//	bool operator < (const people x) const
//	{
//		return ti < x.time;
//	}
	map<string,int> m,ti;
	
}p[MAXN];
int k = 1;
int main()
{
	freopen("pamffo.in","r",stdin);
	freopen("pamffo.out","w",stdout);
	int n,flag = 0;
	string a;
	int t,te;
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		int x;
		cin >> x;
		if(x == 1)
		{
			flag = 1;
			cin >> a;
			scanf("%d",&p[k++].ti[a]); 
			p[k].m[a]++;
//			sort(p + 1,p + k + 1);
		}
		else{
			ans = 0;
			cin >> a;
			scanf("%d%d",&t,&te);
			if(flag == 0){
				cout << "0" << endl;	
				continue;
			} 
			else{
				int o = 0,u = 0,y = 0;
				for(int j = 1;j <= k;j++)
				{
					if(p[j].ti[a] > t)
					{
						if(j == 1)
						{
							y = 1;
						}
						o = 1;
						dis = j - 1;
						break;
					}	
					else
					{
						if(p[j].ti[a] == t)
						{
							o = 1;
							dis = j;
							break;
						}
						if(p[j].ti[a] < t)
							u = 1;	
					}
				}
				if((o == 0 && u == 0) || y == 1)  
				{
					cout << "0" << endl;
					continue;
				}
				if(o == 0 && u == 1)
				{
					if(dis == 0)
						dis = k;
				}
				for(int l = 1;l <= dis;l++)
				{
					ans += p[l].m[a];
				}
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}
