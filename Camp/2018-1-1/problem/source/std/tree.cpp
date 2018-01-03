#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <cctype>
#include <algorithm>

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)

#ifdef __WIN32
#define LLFORMAT "I64"
#else
#define LLFORMAT "ll"
#endif

using namespace std;

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;

typedef long long LL;

const LL OO = 0x3f3f3f3f3f3f3f3fLL;

inline int fpm(LL b, int e, int m)
{
	LL t = 1;
	for ( ; e; e >>= 1, (b *= b) %= m)
		if (e & 1) (t *= b) %= m;
	return t;
}

const int Mod = 1004535809;

const int maxn = 110;

int n;
int a[maxn + 5];

int dp[maxn + 5][maxn + 5][maxn + 5];

int fac[maxn + 5];
int ifac[maxn + 5];

inline void prepare()
{
	fac[0] = 1;
	REP(i, 0, maxn) fac[i + 1] = (LL)fac[i] * (i + 1) % Mod;
	ifac[maxn] = fpm(fac[maxn], Mod - 2, Mod);
	for (int i = maxn - 1; i >= 0; --i) ifac[i] = (LL)ifac[i + 1] * (i + 1) % Mod;
}

int main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	prepare();
	scanf("%d", &n);
	if (n == 0) return 0;
	REP(i, 0, n) scanf("%d", a + i);
	dp[0][0][0] = 1;
	REP(i, 0, n) REP(j, 0, n) REP(k, 0, n) if (dp[i][j][k]) 
	{
		(dp[i + 1][j][k] += dp[i][j][k]) %= Mod;
		REP(l, 0, a[i]) 
		{
			if (k + l > n - 2) break;
			(dp[i + 1][j + 1][k + l] += (LL)dp[i][j][k] * ifac[l] % Mod) %= Mod;
		}
	}
	printf("%d", n);
	REP(i, 2, n + 1)
	{
		int ret = (LL)dp[n][i][i - 2] * fac[i - 2] % Mod;
		(ret += Mod) %= Mod;
		printf(" %d", ret);
	}
	printf("\n");
	return 0;
}
