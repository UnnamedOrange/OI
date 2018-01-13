#include <bits/stdc++.h>

#define For(i, j, k) for(int i = j; i <= k; i++)

using namespace std;

typedef long double lf;

const int N = 1e6 + 10;
const int T = 200;

int rk[N], w[N], n;
int nxt[N], pre[N];

bool cmp(int x, int y){
	return w[x] ^ w[y] ? w[x] < w[y] : x < y;
}

int main(){

	For(taskid, 1, 6){

		For(Case, 1, 10){

			char s[50];
			sprintf(s, "subtask%d/%d.in", taskid, Case);
			freopen(s, "r", stdin);
			sprintf(s, "subtask%d/%d.out", taskid, Case);
			freopen(s, "w", stdout);

			cerr << taskid << ": " << Case << endl;

			scanf("%d", &n);
			For(i, 1, n) scanf("%d", &w[i]), rk[i] = i;
			sort(rk + 1, rk + n + 1, cmp);

			For(i, 1, n) nxt[i] = i + 1, pre[i] = i - 1;

			lf ans = 0.0;

			For(i, 1, n){
				int x = rk[i], l = x, r = x;
				lf lw = 0.0, rw = 0.0, coe = 1.0;

				For(j, 1, T){
					if(l) lw += coe * (l - pre[l]), l = pre[l];
					if(r <= n) rw += coe * (nxt[r] - r), r = nxt[r];
					coe *= 0.5;
				}

				ans += w[x] * lw * rw * 0.5;
				nxt[pre[x]] = nxt[x], pre[nxt[x]] = pre[x];
			}

			printf("%.12Lf\n", ans / n / n);
		}
	}
	return 0;
}
