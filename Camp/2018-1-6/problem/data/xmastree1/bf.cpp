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

int fa[MAXN];

void dfs(int u)
{
    for (auto v : G[u]) {
        if (v == fa[u])
            continue;
        fa[v] = u;
        dfs(v);
    }
}

int cnt[MAXN];

void count(int u)
{
    ++cnt[C[u]];
    for (auto v : G[u]) {
        if (v == fa[u])
            continue;
        count(v);
    }
}

void solve()
{
    dfs(1);

    int lastans = 0;
    while (Q--) {
        int op, u, c, l, r;
        read(op); read(u);
        u ^= lastans;
        if (op == 1) {
            read(l); read(r);
            l ^= lastans;
            r ^= lastans;
            memset(cnt + l, 0, sizeof(*cnt) * (r - l + 1));
            count(u);
            lastans = 0;
            for (int i = l; i <= r; ++i) {
                lastans += !!cnt[i];
            }
            printf("%d\n", lastans);
        } else if (op == 2) {
            read(c);
            c ^= lastans;
            C[u] = c;
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
