#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <cfloat>
#include <ctime>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <bitset>
#include <set>
#include <map>
#include <list>
using namespace std;
const int MAXN = 1e5 + 5;

struct Main {
	int n;
	map<string, list<int> > Win;
	
	Main(void)
	{
		scanf("%d", &n);
		
		while (n--) {
			int Type;
			scanf("%d", &Type);
			
			if (Type == 1) {
				string Name;
				int Time;
				
				cin >> Name;
				scanf("%d", &Time);
				
				Win[Name].push_back(Time);
			} else {
				string Name;
				int Time, Life;
				
				cin >> Name;
				scanf("%d %d", &Time, &Life);
				
				int Cnt = 0;
				for (list<int>::iterator i = 
					Win[Name].begin(); i !=
					Win[Name].end(); ++i)
					if (*i <= Time) ++Cnt;
					else break;
				
				printf("%d\n", Cnt);
			} 
		}
	}
};

int main(void)
{	
	freopen("pamffo.in", "r", stdin);
	freopen("pamffo.out", "w", stdout);

	delete new Main;
	
	return 0;
}