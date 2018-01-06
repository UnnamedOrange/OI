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

const int MAXN = 1e5 + 5, MAXM = 2e5 + 5, MAXK = 505;
const int MOD = 998244353;

int N, M, K;
vector<int> G[MAXN];
int indeg[MAXN];

void input()
{
    read(N); read(M); read(K);
    for (int i = 1; i <= M; ++i) {
        int u, v;
        read(u); read(v);
        G[u].push_back(v);
        ++indeg[v];
    }
}

inline int mod(int x)
{
    return x >= MOD ? x - MOD : x;
}

void solve()
{
    static int fac[MAXK];
    static int S2[MAXK][MAXK];

    fac[0] = 1;
    for (int i = 1; i <= K; ++i) {
        fac[i] = (LL)fac[i - 1] * i % MOD;
    }
    S2[0][0] = 1;
    for (int i = 1; i <= K; ++i) {
        for (int j = 1; j <= i; ++j) {
            S2[i][j] = ((LL)S2[i - 1][j] * j + S2[i - 1][j - 1]) % MOD;
        }
    }

    static int q[MAXN];
    static int f[MAXN][MAXK];
    int front = 0, rear = 0;

    assert(indeg[1] == 0);
    q[rear++] = 1;
    f[1][0] = 1;
    while (front != rear) {
        int u = q[front++];
        for (auto v : G[u]) {
            f[v][0] = mod(f[v][0] + f[u][0]);
            for (int j = 1; j <= K; ++j) {
                f[v][j] = mod(f[v][j] + mod(f[u][j - 1] + f[u][j]));
            }
            if (--indeg[v] == 0)
                q[rear++] = v;
        }
    }

    for (int i = 1; i <= N; ++i) {
        int ans = 0;
        for (int j = 0; j <= K; ++j) {
            ans = (ans + (LL)S2[K][j] * fac[j] % MOD * f[i][j]) % MOD;
        }
        write(ans); putchar('\n');
    }
}

int main()
{
    // freopen("xmasdag.in", "r", stdin);
    // freopen("xmasdag.out", "w", stdout);

    input();
    solve();
}

// Justin Wong: 科大有个班级做游戏，男生要说假话，女生说真话。
//              班主任向班里的50个同学挨个询问我们班有几个女生，
//              第一个同学说1个，第二个同学说两个，依此类推，第五十个同学说50个。
//              那么这个班男女比例是多少？
//   -- 男女生比例 tuna-collection#76
