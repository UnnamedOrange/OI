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
using namespace std;
const int MAXN = 200005;

struct Main {
	struct Vtx {
		int To;
		long long Wgt;
		Vtx *Next;

		Vtx(void) : Next(NULL) {}
		Vtx(int To, long long Wgt) : 
			To(To), Wgt(Wgt), Next(NULL) {}
	};

	struct VtxHead : Vtx {
		Vtx *Head;
		long long Dist;

		void Grow(int To, long long Wgt)
		{
			if (Head)
				Next = Next->Next =
					new Vtx(To, Wgt); 
			else Head = Next =
				new Vtx(To, Wgt);
		}

		VtxHead(void) : 
			Head(NULL), Dist(LLONG_MAX) {}
	} G[MAXN], AntiG[MAXN];

	struct Unit {
		int u;
		long long Dist;

		bool operator < (const Unit &x) const
		{
			return Dist > x.Dist;
		}
	};

	inline void Search(VtxHead *Graph,
		int x)
	{
		priority_queue<Unit> Travel;
		Travel.push( (Unit) { x, 0 } );
		Graph[x].Dist = 0;
		
		while (!Travel.empty()) {
			register int From = Travel.top().u;
			long long CrtDist = Travel.top().Dist;
			Travel.pop();

			if (CrtDist <= Graph[From].Dist)
				for (register Vtx *i = Graph[From].Head;
					i; i = i->Next)
					if (Graph[From].Dist + i->Wgt <
						Graph[i->To].Dist) {
						Graph[i->To].Dist =
							Graph[From].Dist + i->Wgt;
	
						Travel.push(
							(Unit) { i->To, Graph[i->To].Dist } );
					}
		}
	}

	Main(void)
	{
		int n, m;
		scanf("%d %d", &n, &m);

		while (m--) {
			int u, v;
			long long Wgt;
			scanf("%d %d %lld", &u, &v, &Wgt);

			G[u].Grow(v, Wgt);
			AntiG[v].Grow(u, Wgt);
		}

		Search(G, 1);
		Search(AntiG, n);

		register long long MinDist = G[n].Dist;
		for (register int i = 1; i <= n; ++i)
			for (register Vtx *j = G[i].Head;
				j; j = j->Next)
				if (G[i].Dist + AntiG[j->To].Dist <
					MinDist)
					MinDist =
						G[i].Dist + AntiG[j->To].Dist;

		printf("%lld\n%lld\n",
			G[n].Dist, MinDist);
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("wander.in", "r", stdin);
	freopen("wander.out", "w", stdout);
#endif
	
	delete new Main;

	return 0;
}

/*
3 3
1 2 5
2 3 4
1 3 10
*/
