#include <bits/stdc++.h>

#define For(i, j, k) for(int i = j; i <= k; i++)

using namespace std;

int randint(int l, int r){
	return rand() % (r - l + 1) + l; 
}

int n, N[7] = {0, 5, 100, 1500, 10000, 50000, 1000000};
int mx = 1e5;

int A[1000010];

int main(){

	int T = 10;

	srand(time(0));

	For(taskid, 1, 6){

		For(Case, 1, T){

			char s[50];
			sprintf(s, "subtask%d/%d.in", taskid, Case);
			freopen(s, "w", stdout);
			
			n = N[taskid] - randint(0, min(10, n / 2));

			printf("%d\n", n);

			if(Case == 1) For(i, 1, n) A[i] = randint(1, 11) / 10 + 1;
			else if(Case == 2) For(i, 1, n) A[i] = randint(1, mx);
			else if(Case == 4) For(i, 1, n) A[i] = mx / n * (n + 1 - i) - randint(0, mx / n + 1);
			else if(Case == 5) For(i, 1, n) A[i] = mx - randint(1, 100);
			else if(Case == 6) For(i, 1, n) A[i] = randint(1, mx / 2) + (mx / 2 * (i % 2));
			else if(Case == 7){
				int d = sqrt(n);
				For(i, 1, n) A[i] = randint(1, mx / d) + (mx / d * (i % d));
			}
			else if(Case == 8 || Case == 9) For(i, 1, n) A[i] = randint(1, sqrt(1ll * randint(1, mx) * randint(1, mx)));
			else For(i, 1, n) A[i] = randint(1, mx);

			int t = pow(n, 0.8);
			For(i, 1, n) if(rand() % t == 0) A[i] = randint(1, mx);

			For(i, 1, n) printf("%d%c", max(1, min(mx, A[i])), i == n ? '\n' : ' ');
		}
	}

	return 0;
}
