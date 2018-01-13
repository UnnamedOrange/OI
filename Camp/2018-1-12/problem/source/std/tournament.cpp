#include <bits/stdc++.h>

#define For(i, j, k) for(int i = j; i <= k; i++)
#define Forr(i, j, k) for(int i = j; i >= k; i--)

using namespace std;

const int Mod = 998244353, r = 3;
const int N = 300010;

typedef long long LL;

LL Pow(LL x, LL e){
	LL ret = 1;
	while(e){
		if(e & 1) ret = ret * x % Mod;
		x = x * x % Mod;
		e >>= 1;
	}
	return ret;
}

int rev[N];
LL w[N];

void DFT(LL *A, int n, bool inv){
	For(i, 0, n - 1) if(i < rev[i]) swap(A[i], A[rev[i]]);
	for(int m = 1; m < n; m <<= 1){
		LL coe = Pow(r, (Mod - 1) / (m << 1));
		if(inv) coe = Pow(coe, Mod - 2);

		w[0] = 1;
		for(int i = 1; i < m; ++i) w[i] = w[i - 1] * coe % Mod;
		
		for(int i = 0; i < n; i += (m << 1))
			for(int j = 0; j < m; ++j){
				LL x = A[i + j], y = w[j] * A[i + j + m] % Mod;
				(A[i + j] += y) %= Mod;
				A[i + j + m] = (Mod + x - y) % Mod;
			}	
	}
}

LL tmp[N];

void Inverse(LL *A, LL *B, int n){
	if(n == 1){
		B[0] = Pow(A[0], Mod - 2);
		return;
	}

	Inverse(A, B, n >> 1);

	n <<= 1;
	For(i, 0, n - 1) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (n >> 1));

	For(i, 0, n / 2 - 1) tmp[i] = A[i], tmp[i + n / 2] = 0;
	DFT(tmp, n, 0), DFT(B, n, 0);
	For(i, 0, n - 1) B[i] = (2 * B[i] - tmp[i] * B[i] % Mod * B[i] % Mod + Mod) % Mod;
	DFT(B, n, 1);

	LL inv = Pow(n, Mod - 2);
	For(i, 0, n - 1) B[i] = i < n / 2 ? B[i] * inv % Mod : 0;
}

LL fac[N], rfac[N];
LL F[N], G[N], A[N];
int k, n;

int main(){
	freopen("tournament9.in", "r", stdin);
	freopen("tournament9.out", "w", stdout);

	int m;
	scanf("%d%d", &m, &k);
	n = 1;
	while(n <= m) n <<= 1;

	fac[0] = 1;
	For(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	rfac[n] = Pow(fac[n], Mod - 2);
	Forr(i, n, 1) rfac[i - 1] = rfac[i] * i % Mod;

	For(i, 1, n - 1) G[i] = Pow(2, 1ll * i * (i - 1) / 2) * rfac[i] % Mod;
	G[0] = 1;

	Inverse(G, F, n);
	For(i, 0, n - 1) F[i] = i >= k ? 0 : (Mod - F[i] + (i == 0 ? 2 : 0)) % Mod;
	F[0] = Mod - 1;

	Inverse(F, A, n);
	For(i, 0, n - 1) A[i] = A[i] * fac[i] % Mod;
	
	printf("%lld\n", (G[m] * fac[m] + A[m]) % Mod);
	return 0;
}
