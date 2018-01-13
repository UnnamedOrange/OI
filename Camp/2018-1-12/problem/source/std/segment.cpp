#include <bits/stdc++.h>

#define For(i, j, k) for(int i = j; i <= k; i++)

using namespace std;

typedef long long LL;

const int N = 350;
const int Mod = 998244353;

int dp[2][N][N], ans[2][N][N];
LL g[N];

void add(int &x, int y) {
	x += y;
	if (x >= Mod) x -= Mod;
}

LL Pow(LL x, int e) {
	LL ret = 1;
	while (e) {
		if (e & 1) ret = ret * x % Mod;
		x = x * x % Mod;
		e >>= 1;
	}
	return ret;
}

int n, m, x;

int main() {

	For(testid, 1, 20) {

		char f[50];
		sprintf(f, "segment%d.in", testid);
		freopen(f, "r", stdin);
		sprintf(f, "segment%d.out", testid);
		freopen(f, "w", stdout);

		scanf("%d%d%d", &m, &n, &x);

		if (m > n) {
			puts("0");
			continue;
		}

		For(i, 1, m) g[i] = Pow(i, x);

		memset(dp, 0, sizeof dp), memset(ans, 0, sizeof ans);

		int i = 0;
		dp[0][0][0] = 1;

		For(u, 1, n) {
			For(j, 0, m) For(k, 0, j) {
				int &val = dp[i][j][k], &s = ans[i][j][k];
				if (!val && !s) continue;

				s = (s + 1ll * g[j - k] * val) % Mod;

				For(dj, 0, 1) For(dk, 0, 1)
					if (j + dj >= k + dk) {
						add(dp[i ^ 1][j + dj][k + dk], val);
						add(ans[i ^ 1][j + dj][k + dk], s);
					}

				val = s = 0;
			}
			i ^= 1;
		}

		printf("%d\n", ans[i][m][m]);
	}

	return 0;
}
