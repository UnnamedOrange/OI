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

const int MAXN = 1e5 + 5, LOGN = 18;

int N, Q, online;
vector<int> G[MAXN];
int C[MAXN];

void input()
{
    read(N); read(Q); read(online);
    for (int i = 1; i <= N; ++i) {
        read(C[i]);
    }
    for (int i = 1; i < N; ++i) {
        int u, v;
        read(u); read(v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
}

std::set<int> S[MAXN];
int dfsclock, dfnL[MAXN], dfnR[MAXN], id[MAXN];
int dep[MAXN], fa[MAXN][LOGN];

void dfs(int u, int f)
{
    dfnL[u] = ++dfsclock;
    id[dfsclock] = u;
    S[C[u]].insert(dfnL[u]);
    for (auto v : G[u]) {
        if (v == f)
            continue;
        dep[v] = dep[u] + 1;
        fa[v][0] = u;
        for (int i = 1; i < LOGN; ++i) {
            fa[v][i] = fa[fa[v][i - 1]][i - 1];
        }
        dfs(v, u);
    }
    dfnR[u] = dfsclock;
}

int getLCA(int u, int v)
{
    if (dep[u] < dep[v])
        std::swap(u, v);
    for (int i = LOGN - 1; i >= 0; --i) {
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    }
    if (u == v)
        return u;
    for (int i = LOGN - 1; i >= 0; --i) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

namespace SEGT
{

const int SIZE = 8e7 + 5;

int size, lc[SIZE], rc[SIZE];
int sum[SIZE];

inline int add(int v, int l, int r, int p, int x)
{
    int u = ++size;
    if (l == r) {
        sum[u] = sum[v] + x;
        return u;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) {
        lc[u] = add(lc[v], l, mid, p, x);
        rc[u] = rc[v];
    } else {
        lc[u] = lc[v];
        rc[u] = add(rc[v], mid + 1, r, p, x);
    }
    sum[u] = sum[lc[u]] + sum[rc[u]];
    return u;
}

inline int getsum(int u, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return sum[u];
    int mid = (l + r) >> 1;
    return (ql <= mid ? getsum(lc[u], l, mid, ql, qr) : 0) + (mid < qr ? getsum(rc[u], mid + 1, r, ql, qr) : 0);
}

}

namespace BIT
{

int root[MAXN];

inline void add(int p, int q, int x)
{
    for (; p <= N; p += p & -p) {
        root[p] = SEGT::add(root[p], 1, N, q, x);
    }
}

inline int getsum(int p, int ql, int qr)
{
    int ret = 0;
    for (; p; p -= p & -p) {
        ret += SEGT::getsum(root[p], 1, N, ql, qr);
    }
    return ret;
}

}

inline void contrib(int u, int v, int f)
{
    u = id[u];
    v = id[v];
    BIT::add(C[u], dfnL[getLCA(u, v)], f);
}

void solve()
{
    dep[1] = 1;
    dfs(1, 0);

    for (int i = 1; i <= N; ++i) {
        for (auto it = S[i].begin(); it != S[i].end(); ++it) {
            BIT::add(i, *it, +1);
            if (it != S[i].begin())
                contrib(*std::prev(it), *it, -1);
        }
    }

    int lastans = 0;
    while (Q--) {
        int op, u, c, l, r;
        read(op); read(u);
        u ^= lastans;
        if (op == 1) {
            read(l); read(r);
            l ^= lastans;
            r ^= lastans;

            lastans = BIT::getsum(r, dfnL[u], dfnR[u]) - BIT::getsum(l - 1, dfnL[u], dfnR[u]);
            write(lastans); putchar('\n');

        } else if (op == 2) {
            read(c);
            c ^= lastans;

            auto it = S[C[u]].find(dfnL[u]);
            bool p = it != S[C[u]].begin();
            bool n = std::next(it) != S[C[u]].end();
            if (p)
                contrib(*std::prev(it), *it, +1);
            if (n)
                contrib(*it, *std::next(it), +1);
            if (p && n)
                contrib(*std::prev(it), *std::next(it), -1);

            BIT::add(C[u], dfnL[u], -1);
            S[C[u]].erase(it);
            C[u] = c;
            BIT::add(C[u], dfnL[u], +1);

            it = S[C[u]].insert(dfnL[u]).x;
            p = it != S[C[u]].begin();
            n = std::next(it) != S[C[u]].end();
            if (p)
                contrib(*std::prev(it), *it, -1);
            if (n)
                contrib(*it, *std::next(it), -1);
            if (p && n)
                contrib(*std::prev(it), *std::next(it), +1);
        }

        if (!online)
            lastans = 0;
    }
}

int main()
{
    // freopen("xmastree1.in", "r", stdin);
    // freopen("xmastree1.out", "w", stdout);

    input();
    solve();
}

// 竹外一枝斜，想佳人，天寒日暮。
//     -- 曹组《蓦山溪·梅》
