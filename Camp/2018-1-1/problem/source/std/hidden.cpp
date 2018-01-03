#include <cstdio>
#include <cstring>

const int N = 10 + 1, INF = 1 << 27;

inline void check(int &lhs, int rhs) { lhs = (lhs < rhs ? lhs : rhs); }

int n;
int a[N][N], len[N];

int b[N][N], f[N][N][N][N][1 << N];
bool flag[N][N][N];

bool check(int x, int y, int z) {
  if (b[z][len[z]] & ~b[x][len[x]]) return false;
  for (int i = 0; i < len[z]; ++i) if (a[z][i] == a[x][y]) ++y;
  return y == len[x];
}

int solve(int l, int x, int r, int y, int mask) {
  int &res = f[l][x][r][y][mask &= (1 << n) - 1];
  if (res != -1) return res;
  if (mask == (1 << n) - 1 && !x && y == len[r]) return 0;
  res = INF;
  if (l < n && !x) {
    for (int i = 0; i <= n; ++i) {
      if (mask >> i & 1) continue;
      for (int j = 0; j <= len[i]; ++j) if (flag[i][j][l]) check(res, solve(i, j, r, y, mask | (1 << i)));
    }
  } else {
    for (int i = 0; i < n; ++i) if (!(mask >> i & 1) && flag[r][y][i]) check(res, solve(l, x, i, 0, mask | (1 << i)));
    for (int i = 1; i < 10; ++i) {
      bool u = x && i == a[l][x - 1], v = i == a[r][y];
      if (u && v) check(res, solve(l, x - 1, r, y + 1, mask) + 1);
      if (u && (b[r][y] >> i & 1)) check(res, solve(l, x - 1, r, y, mask) + 1);
      if (v && (b[l][x] >> i & 1)) check(res, solve(l, x, r, y + 1, mask) + 1);
    }
  }
  return res;
}

int main() {
  freopen("hidden.in", "r", stdin);
  freopen("hidden.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    for (len[i] = 0;; ++len[i]) {
      scanf("%d", &a[i][len[i]]);
      if (a[i][len[i]] == 0) break;
    }
    for (int j = 0; j < len[i]; ++j) b[i][j + 1] = b[i][j] | (1 << a[i][j]);
  }
  b[n][0] = ~0U;
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= len[i]; ++j)
      for (int k = 0; k <= n; ++k)
        flag[i][j][k] = (i != k && check(i, j, k));
  memset(f, -1, sizeof f);
  int ans = INF;
  for (int i = 0; i <= n; ++i) check(ans, solve(i, len[i], n, 0, 1 << i));
  printf("%d\n", ans == INF ? -1 : ans);
  return 0;
}
