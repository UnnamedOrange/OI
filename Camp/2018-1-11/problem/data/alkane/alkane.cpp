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


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <climits>
#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <string>

#define x first
#define y second
#define MP std::make_pair
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#ifdef __linux__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

typedef long long LL;
typedef std::pair<int, int> Pii;

const int oo = 0x3f3f3f3f;

template<typename T> inline bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
template<typename T> inline bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
std::string procStatus()
{
    std::ifstream t("/proc/self/status");
    return std::string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}
template<typename T> T read(T &x)
{
    int f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = -1;
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

const int MOD = 998244353, G = 3;
const int SIZE = (1 << 20) + 5;

inline int mod(int x) { return x >= MOD ? x - MOD : x; }
inline void modr(int &x) { if (x >= MOD) x -= MOD; }

int fpm(int base, int exp)
{
    int ret = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1)
            ret = (LL)ret * base % MOD;
        base = (LL)base * base % MOD;
    }
    return ret;
}

namespace Poly
{

int n, in;
int wn[SIZE];
int rev[SIZE];

void init(int n_)
{
    int step = 0;
    for (n = 1; n < n_; n <<= 1) ++step;
    for (int i = 1; i < n; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (step - 1));
    }
    in = fpm(n, MOD - 2);
    int g = fpm(G, (MOD - 1) / n);
    wn[0] = 1;
    for (int i = 1; i <= n; ++i) {
        wn[i] = (LL)wn[i - 1] * g % MOD;
    }
}

void dft(int a[], int f)
{
    for (int i = 0; i < n; ++i) {
        if (i < rev[i])
            std::swap(a[i], a[rev[i]]);
    }
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += (k << 1)) {
            int t = n / (k << 1);
            for (int j = 0; j < k; ++j) {
                int w = f == 1 ? wn[t * j] : wn[n - t * j];
                int x = a[i + j];
                int y = (LL)a[i + j + k] * w % MOD;
                a[i + j] = mod(x + y);
                a[i + j + k] = mod(x - y + MOD);
            }
        }
    }
    if (f == -1) {
        for (int i = 0; i < n; ++i) {
            a[i] = (LL)a[i] * in % MOD;
        }
    }
}

}

int N;
int A[SIZE], B[SIZE];
int I2, I3, I6, I24;

void calc(int l, int r)
{
    if (l + 1 == r)
        return;
    int mid = (l + r) >> 1, len = r - l;

    calc(l, mid);

    static int tmp[SIZE];
    static int L[SIZE], C1[SIZE], C2[SIZE];

    Poly::init(len * 2);         // mid - l + len * 2, originally

    std::fill(L, L + Poly::n, 0); std::copy(A + l, A + mid, L);
    std::fill(C1, C1 + Poly::n, 0); std::copy(A, A + r - l, C1);
    std::fill(C2, C2 + Poly::n, 0); for (int i = 0; i * 2 < len; ++i) C2[i * 2] = A[i];

    for (int i = l, j; (j = i * 3 + 1) < r; ++i) {
        if (j >= mid)
            modr(A[j] += (LL)A[i] * I3 % MOD);
    }

    Poly::dft(L, 1);
    Poly::dft(C1, 1); Poly::dft(C2, 1);

    if (l != 0) {
        for (int i = 0; i < Poly::n; ++i) tmp[i] = (LL)L[i] * C1[i] % MOD * C1[i] % MOD;
        Poly::dft(tmp, -1);
        for (int i = mid; i < r; ++i) modr(A[i] += (LL)tmp[i - l - 1] * I2 % MOD);
    } else {
        for (int i = 0; i < Poly::n; ++i) tmp[i] = (LL)L[i] * C1[i] % MOD * C1[i] % MOD;
        Poly::dft(tmp, -1);
        for (int i = mid; i < r; ++i) modr(A[i] += (LL)tmp[i - l - 1] * I6 % MOD);
    }

    for (int i = 0; i < Poly::n; ++i) tmp[i] = (LL)L[i] * C2[i] % MOD;
    Poly::dft(tmp, -1);
    for (int i = mid; i < r; ++i) modr(A[i] += (LL)tmp[i - l - 1] * I2 % MOD);

    calc(mid, r);
}

void prework(int n)
{
    ++n;
    I2 = fpm(2, MOD - 2);
    I3 = fpm(3, MOD - 2);
    I6 = fpm(6, MOD - 2);
    I24 = fpm(24, MOD - 2);

    // calc A(x)
    A[0] = 1;
    calc(0, n);

    static int A1[SIZE], A2[SIZE], A3[SIZE], A4[SIZE];
    static int P[SIZE], Q[SIZE];

    for (int i = 0; i < n; ++i) {
        A1[i] = A2[i * 2] = A3[i * 3] = A4[i * 4] = A[i];
    }

    Poly::init(n * 4);
    Poly::dft(A1, 1); Poly::dft(A2, 1); Poly::dft(A3, 1); Poly::dft(A4, 1);

    // calc P(x)
    for (int i = 0; i < Poly::n; ++i) {
        LL s = 0;
        (s += 6LL * A4[i]) %= MOD;
        (s += 8LL * A3[i] % MOD * A1[i]) %= MOD;
        (s += 6LL * A2[i] % MOD * A1[i] % MOD * A1[i]) %= MOD;
        (s += 3LL * A2[i] % MOD * A2[i]) %= MOD;
        (s += (LL)A1[i] * A1[i] % MOD * A1[i] % MOD * A1[i]) %= MOD;
        P[i] = s * I24 % MOD;
    }
    Poly::dft(P, -1);
    for (int i = n - 1; i > 0; --i) {
        P[i] = P[i - 1];
    }
    P[0] = 0;

    // calc Q(x)
    for (int i = 0; i < Poly::n; ++i) {
        LL x = A1[i] - 1 + MOD;
        LL y = A2[i] - 1 + MOD;
        Q[i] = (x * x + y) % MOD * I2 % MOD;
    }
    Poly::dft(Q, -1);

    // calc B(x), finally
    for (int i = 0; i < n; ++i) {
        B[i] = mod(mod(P[i] - Q[i] + MOD) + (!(i & 1)) * A[i >> 1]);
    }
}

void solve()
{
    int T;
    read(T);
    while (T--) {
        int n;
        read(n);
        write(B[n]); putchar('\n');
    }
}

int main()
{
    // freopen("alkane.in", "r", stdin);
    // freopen("alkane.out", "w", stdout);

    prework(1e5);
    solve();

    // std::cout << procStatus();

    return 0;
}
