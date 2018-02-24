#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
using namespace std;
struct Task {
	int Sum;
	int Time[1000];
	Task() {
		Sum = 0;
	}
};
map<string,Task> Table;
int main() {
	freopen("pamffo.in","r",stdin);
	freopen("pamffo.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i = 1; i<=n; i++) {
		int t1,qTime,Time;
		string Name;
		scanf("%d",&t1);

		if(t1 == 1) {
			cin>>Name;
			Task & Pos = Table[Name];
			scanf("%d",&Time);
			Pos.Sum++;
			Pos.Time[Pos.Sum] = Time;
		} else {
			cin>>Name;
			Task & Pos = Table[Name];
			scanf("%d%d",&qTime,&Time);
			if(!Table.count(Name)) {
				printf("0\n");
			} else {
				if(!Pos.Sum) {
					printf("0\n");
				} else if(qTime < Pos.Time[1]) {
					printf("0\n");
				} else if(qTime >= Pos.Time[Pos.Sum]) {
					printf("%d\n",Pos.Sum);
				} else {
					int l = 1,r = Pos.Sum;
					int mid = 0;
					while(l + 1 < r) {
						mid = ((l + r) >> 1);
						if(Pos.Time[mid] <= qTime) {
							l = mid;
						} else {
							r = mid;
						}
					}
					printf("%d\n",l);
				}
			}
		}
	}
	return 0;
}
