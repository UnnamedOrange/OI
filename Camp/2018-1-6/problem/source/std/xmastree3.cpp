// Copyright (C) 2017 __debug.

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; version 3

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; If not, see <http://www.gnu.org/licenses/>.


#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

#define x first
#define y second
#define MP std::make_pair
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(), (x).end()
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#ifdef __linux__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

using std::pair;
using std::vector;
using std::string;

typedef long long LL;
typedef pair<int, int> Pii;

const int oo = 0x3f3f3f3f;

template<typename T> inline bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
template<typename T> inline bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
string procStatus()
{
    std::ifstream t("/proc/self/status");
    return string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}
template<typename T> T read(T &x)
{
    int f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        f = (ch == '-' ? -1 : 1);
    for (x = 0; isdigit(ch); ch = getchar())
        x = 10 * x + ch - '0';
    return x *= f;
}
template<typename T> void write(T x)
{
    if (x == 0) {
        putchar('0');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static char s[20];
    int top = 0;
    for (; x; x /= 10)
        s[++top] = x % 10 + '0';
    while (top)
        putchar(s[top--]);
}
// EOT

const int MAXN = 55, MAXK = 15, MAXS = 1 << MAXK;
const int MOD = 998244353;

struct Edge {
    int v, next;
    Edge() { }
    Edge(int v_, int next_): v(v_), next(next_) { }
};

int N, K;
int tote, head[MAXN];
Edge edge[MAXN * 2 + 5];
int dp[MAXN][MAXS];

inline void addEdge(int u, int v)
{
    edge[++tote] = Edge(v, head[u]);
    head[u] = tote;
}

void calc(int u, int fa)
{
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].v;
        if (v != fa)
            calc(v, u);
    }

    for (int k = K - 1; k >= 0; --k) {
        static int cur[MAXS], nxt[MAXS];
        int sbnd = 1 << k, sall = sbnd - 1;
        memset(cur, 0, sizeof(*cur) * sbnd);
        cur[0] = 1;

        for (int j = head[u]; j; j = edge[j].next) {
            int v = edge[j].v;
            if (v == fa) continue;

            memset(nxt, 0, sizeof(*nxt) * sbnd);
            for (int s = 0; s < sbnd; ++s) {
                if (!cur[s]) continue;
                int rs = sall ^ s;
                for (int s0 = rs; ; s0 = (s0 - 1) & rs) {
                    (nxt[s | s0] += (LL)cur[s] * dp[v][s0] % MOD) %= MOD;
                    if (!s0) break;
                }
            }
            memcpy(cur, nxt, sizeof(*cur) * sbnd);

            for (int s = 0; s < sbnd; ++s) {
                (dp[v][s] += dp[v][s | sbnd]) %= MOD;
            }
        }

        for (int s = 0; s < sbnd; ++s) {
            (dp[u][s | sbnd] += cur[s]) %= MOD;
        }
    }
}

void input()
{
    read(N); read(K);
    for (int i = 1; i < N; ++i) {
        int u, v;
        read(u); read(v);
        --u; --v;
        addEdge(u, v);
        addEdge(v, u);
    }
}

void solve()
{
    calc(0, -1);
    int ans = 0;
    for (int s = 0; s < (1 << K); ++s) {
        (ans += dp[0][s]) %= MOD;
    }
    printf("%d\n", ans);
}

int main()
{
    // freopen("xmastree3.in", "r", stdin);
    // freopen("xmastree3.out", "w", stdout);

    input();
    solve();
}

// 别君去兮何时还？且放白鹿青崖间。须行即骑访名山。
//     -- 李白《梦游天姥吟留别 / 别东鲁诸公》
