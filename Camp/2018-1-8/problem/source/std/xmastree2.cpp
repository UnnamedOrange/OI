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

const int MAXN = 3e4 + 5;

struct Edge {
	int v, next;

	Edge() { }
	Edge(int v_, int next_) : v(v_), next(next_) { }
};

int N;
int tote, head[MAXN];
Edge edge[MAXN << 1];
int A[MAXN], can[MAXN];
int fa[MAXN];
int fauf[MAXN];
int size[MAXN], sum[MAXN];

inline void addEdge(int u, int v)
{
	edge[++tote] = Edge(v, head[u]);
	head[u] = tote;
}

int getFather(int u)
{
	return fauf[u] == u ? u : fauf[u] = getFather(fauf[u]);
}

void dfs(int u)
{
	for (int i = head[u]; i; i = edge[i].next) {
		int v = edge[i].v;
		if (v != fa[u]) {
			fa[v] = u;
			dfs(v);
		}
	}
}

void input()
{
	read(N);
	for (int i = 1; i < N; ++i) {
		int u, v;
		read(u); read(v);
		addEdge(u, v);
		addEdge(v, u);
	}
	for (int i = 1; i <= N; ++i) {
		read(A[i]); read(can[i]);
	}
}

void solve()
{
	LL ans = 0;

	for (int rt = 1; rt <= N; ++rt) {
		if (can[rt]) {
			memset(fa + 1, 0, sizeof(*fa) * N);
			dfs(rt);

			LL cur = 0;

			for (int i = 1; i <= N; ++i) {
				fauf[i] = i;
				size[i] = 1;
				sum[i] = A[i];
				cur += A[i];
			}

			typedef std::pair<double, int> Atom;
			typedef __gnu_pbds::priority_queue<Atom, std::greater<Atom> > Heap;

			Heap q;
			Heap::point_iterator it[MAXN];

			for (int i = 1; i <= N; ++i) {
				if (i != rt)
					it[i] = q.push(MP((double)sum[i], i));
			}
			while (!q.empty()) {
				int u = q.top().y;
				q.pop();

				int v = getFather(fa[u]);
				cur += (LL)size[v] * sum[u];
				fauf[u] = v;
				size[v] += size[u];
				sum[v] += sum[u];
				if (v != rt)
					q.modify(it[v], MP((double)sum[v] / size[v], v));
			}

			chkmax(ans, cur);
		}
	}

	printf("%lld\n", ans);
}

int main()
{
	freopen("xmastree2.in", "r", stdin);
	freopen("xmastree2.out", "w", stdout);

	input();
	solve();
}

// 一个诚实的车夫或工人一定强于一个贪官污吏。
//   --老舍
