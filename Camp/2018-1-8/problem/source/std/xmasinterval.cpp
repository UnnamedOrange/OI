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

const int MAXN = 5e5 + 5, MAXM = 5e5 + 5;
const int MOD = 1e9 + 9;

int N, M;
Pii A[MAXN];
int B[MAXM];

inline void mod(int &x)
{
	if (x >= MOD)
		x -= MOD;
}

namespace SEGT
{

	const int SIZE = MAXN << 3;

	int size;
	int sum[SIZE];
	int tAdd[SIZE], tMul[SIZE];
	int L, R;
	int X;
	void(*tagF)(int, int, int);

#define LC (u << 1)
#define RC (u << 1 | 1)

	inline void tagMul(int u, int x, int len = 0)
	{
		tMul[u] = (LL)tMul[u] * x % MOD;
		tAdd[u] = (LL)tAdd[u] * x % MOD;
		sum[u] = (LL)sum[u] * x % MOD;
	}

	inline void pushdownMul(int u)
	{
		if (tMul[u] != 1) {
			tagMul(LC, tMul[u]);
			tagMul(RC, tMul[u]);
			tMul[u] = 1;
		}
	}

	inline void tagAdd(int u, int x, int len)
	{
		pushdownMul(u);
		mod(tAdd[u] += x);
		mod(sum[u] += (LL)x * len % MOD);
	}

	inline void pushdown(int u, int len)
	{
		pushdownMul(u);
		if (tAdd[u]) {
			tagAdd(LC, tMul[u], len - (len >> 1));
			tagAdd(RC, tMul[u], len >> 1);
			tAdd[u] = 0;
		}
	}

	void _modify(int u, int l, int r)
	{
		if (L <= l && r <= R) {
			tagF(u, X, r - l + 1);
			return;
		}
		pushdown(u, r - l + 1);
		int mid = (l + r) >> 1;
		if (L <= mid)
			_modify(LC, l, mid);
		if (mid < R)
			_modify(RC, mid + 1, r);
		mod(sum[u] = sum[LC] + sum[RC]);
	}

	void _query(int u, int l, int r)
	{
		if (L <= l && r <= R) {
			mod(X += sum[u]);
			return;
		}
		pushdown(u, r - l + 1);
		int mid = (l + r) >> 1;
		if (L <= mid)
			_query(LC, l, mid);
		if (mid < R)
			_query(RC, mid + 1, r);
	}

	inline void init(int n)
	{
		size = n;
		for (int i = 1, bnd = (size + 1) << 2; i <= bnd; ++i) {
			tMul[i] = 1;
		}
	}

	inline void add(int l, int r, int x)
	{
		L = l; R = r; X = x;
		tagF = tagAdd;
		_modify(1, 0, size);
	}

	inline void mul(int l, int r, int x)
	{
		L = l; R = r; X = x;
		tagF = tagMul;
		_modify(1, 0, size);
	}


	inline int query(int l, int r)
	{
		L = l; R = r; X = 0;
		_query(1, 0, size);
		return X;
	}

}

inline bool mycmp(const Pii &a, const Pii &b)
{
	return a.x < b.x || (a.x == b.x && a.y > b.y);
}

void input()
{
	read(N); read(M);
	for (int i = 1; i <= N; ++i) {
		read(A[i].x); read(A[i].y);
	}
	for (int i = 1; i <= M; ++i) {
		read(B[i]);
	}
}

void solve()
{
	std::sort(B + 1, B + M + 1);
	M = std::unique(B + 1, B + M + 1) - B - 1;

	for (int i = 1; i <= N; ++i) {
		A[i].x = std::lower_bound(B + 1, B + M + 1, A[i].x) - B;
		A[i].y = std::upper_bound(B + 1, B + M + 1, A[i].y) - B - 1;
	}
	std::sort(A + 1, A + N + 1, mycmp);
	SEGT::init(M);
	SEGT::add(0, 0, 1);
	for (int i = 1; i <= N; ++i) {
		int l = A[i].x;
		int r = A[i].y;
		if (l <= r) {
			SEGT::mul(r, M, 2);
			SEGT::add(r, r, SEGT::query(l - 1, r - 1));
		}
	}

	int ans = SEGT::query(M, M);

	write(ans); putchar('\n');
}

int main()
{
	freopen("xmasinterval.in", "r", stdin);
	freopen("xmasinterval.out", "w", stdout);

	input();
	solve();
}

// 杨花榆荚无才思，惟解漫天作雪飞。
//     -- 韩愈《晚春》