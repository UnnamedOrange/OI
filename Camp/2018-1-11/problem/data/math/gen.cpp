#include <bits/stdc++.h>

#define inline __attribute__((always_inline)) inline

typedef long long i64;

const int MOD = 1073741824;

enum {
  MAXN = 200000 + 5,
  LIMIT = 21
};

template <typename T> inline void mod(T &x) {
  if (x >= MOD) x -= MOD;
  if (x < 0) x += MOD;
}

int totp;
int pri[MAXN];

bool ish[MAXN];
int mu[MAXN];
int S[MAXN];
int S2[MAXN];
int last[MAXN];

int *sum[MAXN];

void euler() {
  int i, j, x;
  
  ish[1] = true;
  last[1] = 1;
  mu[1] = 1;
  S[1] = 1;
  S2[1] = 1;
  
  for (i=2; i<MAXN; ++i) {
    if (!ish[i]) {
      pri[totp++] = i;
      
      last[i] = 1;
      mu[i] = -1;
      S[i] = 2;
      S2[i] = 3;
    }
    for (j=0; (i64) i*pri[j] < MAXN; ++j) {
      x = i*pri[j];
      ish[x] = true;
      if (i%pri[j] == 0) {
	last[x] = last[i];
	mu[x] = 0;
	if (last[x] > 1) {
	  S[x] = S[x/last[x]] * S[last[x]];
	  S2[x] = S2[x/last[x]] * S2[last[x]];
	} else {
	  S[x] = S[i]+1;
	  S2[x] = S2[i]+2;
	}
	break;
      } else {
	last[x] = i;
	mu[x] = -mu[i];
	S[x] = S[pri[j]] * S[i];
	S2[x] = S2[pri[j]] * S2[i];
      }
    }
  }
}

int T[LIMIT][LIMIT][MAXN];

int query(int n, int m) {
  int res(0), d, lst, i, nd, md;
  if (m<n) std::swap(n, m);
  for (d=1; d<=n; d=lst+1) {
    nd = n/d, md = m/d;
    lst = std::min(n / nd, m / md);
    if (md < LIMIT)
      mod(res += T[nd][md][lst] - T[nd][md][d-1]);      
    else {
      for (i=d; i<=lst; ++i)
	if (mu[i])
	  mod(res += (i64) sum[i][nd] * sum[i][md] * mu[i] % MOD);
    }
  }
  return res;
}

void init() {
  int i, d, end, j;
  euler();
  sum[0] = new int [MAXN];
  for (d=1; d<MAXN; ++d) {
    end = (MAXN-1)/d + 1;
    sum[d] = new int [end];
    for (i=1; i<end; ++i) mod(sum[d][i] = sum[d][i-1] + (i64) S[i] * S2[i*d] % MOD);
  }
  for (i=1; i<LIMIT; ++i)
    for (j=i; j<LIMIT; ++j)
      for (d=1; d<MAXN; ++d)
  	mod(T[i][j][d] = T[i][j][d-1] + (i64) sum[d][i] * sum[d][j] * mu[d] % MOD);
}

int rand(int x, int y) {
  return x + (i64) rand() * rand() % (y-x+1);
}

void make(int maxn, int q, bool samenm, bool samem, FILE *IN, FILE *OUT) {
#define RAND() (rand(std::max(maxn*4/5,1), maxn))

  assert(!samem || !samenm);
  assert(1 <= maxn && maxn < MAXN);
  assert(1 <= q && q <= 10000);

  assert(IN);
  assert(OUT);
  
  int n, m(RAND());
  fprintf(IN, "%d\n", q);
  while (q--) {
    n = RAND();
    if (!samem) m = RAND();    
    if (samenm) m = n;
    fprintf(IN, "%d %d\n", n, m);
    fprintf(OUT, "%d\n", query(n, m));
  }
  
  fclose(IN);
  fclose(OUT);

#undef RAND
}

#define IN(x) fopen("math"#x".in", "w"), fopen("math"#x".out", "w")

int main() {
  srand(978);
  init();
  make(100, 10, 0, 0, IN(0));
  make(1000, 10, 0, 0, IN(1));
  make(200000, 20, 0, 0, IN(2));
  make(200000, 20, 0, 0, IN(3));
  make(200000, 1250, 0, 0, IN(4));
  make(200000, 9998, 1, 0, IN(5));
  make(200000, 9999, 0, 1, IN(6));
  make(200000, 10000, 0, 0, IN(7));
  make(200000, 10000, 0, 0, IN(8));
  make(200000, 10000, 0, 0, IN(9));  
  return 0;
}
