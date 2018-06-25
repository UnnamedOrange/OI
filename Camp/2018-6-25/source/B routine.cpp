#include <cctype>
#include <climits>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
#include <list>
#include <functional>
using namespace std;
#define N 200005																							//ATTTTTTTTT!
#define LL long long
const int mo = 1000000007;
const int B = 11003;
int n, m, a[N], disc[N], bound, C[N];
int root, cnt, lc[3000005], rc[3000005], l1[N], l2[N], r1[N], r2[N], sx[N], Rt[N];
LL sl[N], sr[N], w[3000005], H[N];
LL L, R;
vector <int> poss[N];
struct O {
	int l, r;
}A, Ans[N];
void up(int u) {
	l1[u] = min(l1[lc[u]], l1[rc[u]]);
	l2[u] = max(l2[lc[u]], l2[rc[u]]);
	r1[u] = min(r1[lc[u]], r1[rc[u]]);
	r2[u] = max(r2[lc[u]], r2[rc[u]]);
	sl[u] = sl[lc[u]] + sl[rc[u]];
	sr[u] = sr[lc[u]] + sr[rc[u]];
	sx[u] = sx[lc[u]] + sx[rc[u]];
}
void build(int &u, int p, int q) {
	u = ++cnt;
	if (p == q) {
		l1[u] = l2[u] = p, r1[u] = r2[u] = n;
		sl[u] = p; sr[u] = n; sx[u] = 1;
		return;
	}
	build(lc[u], p, (p + q) / 2);
	build(rc[u], (p + q) / 2 + 1, q);
	up(u);
}
void down(int u) {
	if (l1[u] > l1[lc[u]]) {
		sl[lc[u]] = 1ll * l1[u] * sx[lc[u]];
		l1[lc[u]] = l2[lc[u]] = l1[u];
	}
	if (l1[u] > l1[rc[u]]) {
		sl[rc[u]] = 1ll * l1[u] * sx[rc[u]];
		l1[rc[u]] = l2[rc[u]] = l1[u];
	}
	if (r2[u] < r2[lc[u]]) {
		sr[lc[u]] = 1ll * r2[u] * sx[lc[u]];
		r1[lc[u]] = r2[lc[u]] = r2[u];
	}
	if (r2[u] < r2[rc[u]]) {
		sr[rc[u]] = 1ll * r2[u] * sx[rc[u]];
		r1[rc[u]] = r2[rc[u]] = r2[u];
	}
}
LL get(int u, int p, int q, int l, int r, int k) {
	if (!sx[u]) return 0;
	if (l <= p && q <= r) {
		if (r2[u] <= k) return sr[u] - sl[u] + sx[u];
		if (l1[u] > k) return 0;
		if (l2[u] <= k && r1[u] >= k) return 1ll * sx[u] * (k + 1) - sl[u];
	}
	down(u);
	LL ans = 0;
	if (l <= (p + q) / 2) ans += get(lc[u], p, (p + q) / 2, l, r, k);
	if (r > (p + q) / 2) ans += get(rc[u], (p + q) / 2 + 1, q, l, r, k);
	return ans;
}
void cover(int u, int p, int q, int l, int r, int ll, int rr) {
	if (!sx[u]) return;
	if (l <= p && q <= r) {
		int fl = 1;
		if (r2[u]<ll || l1[u]>rr) {
			sx[u] = sl[u] = sr[u] = 0;
		}
		else
			if (l1[u] >= ll && r2[u] <= rr) {
				//nothing
			}
			else
				if (l2[u] <= ll && r1[u] >= ll && r2[u] <= rr) {
					sl[u] = 1ll * ll*sx[u];
				}
				else
					if (l1[u] >= ll && l2[u] <= rr && r1[u] >= rr) {
						sr[u] = 1ll * rr*sx[u];
					}
					else
						if (l2[u] <= ll && r1[u] >= rr) {
							sl[u] = 1ll * ll*sx[u];
							sr[u] = 1ll * rr*sx[u];
						}
						else fl = 0;
						if (fl) {
							l1[u] = max(l1[u], ll);
							l2[u] = max(l2[u], ll);
							r1[u] = min(r1[u], rr);
							r2[u] = min(r2[u], rr);
							return;
						}
	}
	down(u);
	if (l <= (p + q) / 2) cover(lc[u], p, (p + q) / 2, l, r, ll, rr);
	if (r > (p + q) / 2) cover(rc[u], (p + q) / 2 + 1, q, l, r, ll, rr);
	up(u);
}
LL check(int I, int mid) {
	LL ans = 0;
	for (unsigned i = 1; i < poss[I].size(); ++i)
		if (poss[I][i - 1] + 1 <= n)
			ans += get(root, 1, n, poss[I][i - 1] + 1, poss[I][i], i + mid >= poss[I].size() ? n : poss[I][i + mid] - 1);
	return ans;
}
void go(int u, int p, int q) {
	if (sx[u] < L) { L -= sx[u]; return; }
	if (p == q) { --L; A.l = p; A.r = r1[u]; return; }
	down(u);
	go(rc[u], (p + q) / 2 + 1, q);
	if (!L) return;
	go(lc[u], p, (p + q) / 2);
}
void build2(int &u, int p, int q) {
	u = ++cnt;
	if (p == q) {
		w[u] = 0; return;
	}
	build2(lc[u], p, (p + q) / 2);
	build2(rc[u], (p + q) / 2 + 1, q);
}
void add(int &u, int v, int p, int q, int k) {
	u = ++cnt;
	if (p == q) {
		w[u] = w[v] + 1; return;
	}
	lc[u] = lc[v]; rc[u] = rc[v];
	if (k <= (p + q) / 2) add(lc[u], lc[v], p, (p + q) / 2, k);
	else add(rc[u], rc[v], (p + q) / 2 + 1, q, k);
	w[u] = (w[lc[u]] * H[q - (p + q) / 2] + w[rc[u]]) % mo;
}
int CMP(int ar, int al, int br, int bl, int p, int q) {
	if (p == q) {
		if (w[ar] - w[al] == w[br] - w[bl]) return 0;
		return w[ar] - w[al] < w[br] - w[bl] ? 1 : -1;
	}
	if ((w[lc[ar]] - w[lc[al]] - w[lc[br]] + w[lc[bl]]) % mo)
		return CMP(lc[ar], lc[al], lc[br], lc[bl], p, (p + q) / 2);
	else return CMP(rc[ar], rc[al], rc[br], rc[bl], (p + q) / 2 + 1, q);
}
bool operator<(O a, O b) {
	int fl = CMP(Rt[a.r], Rt[a.l - 1], Rt[b.r], Rt[b.l - 1], 1, n);
	if (fl == 0) return a.l > b.l; else return fl > 0;
}
struct GCMP {
	bool operator()(O a, O b) {
		return b < a;
	}
};
priority_queue <O, vector<O>, GCMP> G;
int main() {
	ios::sync_with_stdio(0);
	cin >> n >> L >> R;
	L = 1ll * n*(n + 1) / 2 - L + 1;
	R = 1ll * n*(n + 1) / 2 - R + 1;
	swap(L, R); R = R - L + 1;
	for (int i = 1; i <= n; ++i) cin >> a[i], disc[i] = a[i];
	sort(disc + 1, disc + n + 1);
	bound = unique(disc + 1, disc + n + 1) - disc - 1;
	for (int i = 1; i <= bound; ++i) poss[i].push_back(0);
	for (int i = 1; i <= n; ++i) {
		a[i] = lower_bound(disc + 1, disc + bound + 1, a[i]) - disc;
		poss[a[i]].push_back(i);
	}
	for (int i = 1; i <= bound; ++i) poss[i].push_back(n + 1);
	//	for (int i=1;i<=n;++i) printf("%d ",a[i]); puts(""); 					
	build(root, 1, n);
	for (int i = 1; i <= bound; ++i) {
		int l = 0, r = poss[i].size() - 2, mid;
		while (l < r) {
			mid = (l + r) / 2;
			if (L <= check(i, mid)) r = mid; else l = mid + 1;
		}
		if (l) L -= check(i, l - 1);
		C[i] = l;
		for (unsigned j = 1; j < poss[i].size(); ++j)
			if (poss[i][j - 1] + 1 <= n)
				cover(root, 1, n, poss[i][j - 1] + 1, poss[i][j],
					j + l - 1 >= poss[i].size() ? n + 1 : poss[i][j + l - 1],
					j + l >= poss[i].size() ? n : poss[i][j + l] - 1);
	}
	//	for (int i=1;i<=bound;++i) printf("%d ",C[i]); puts("");
	go(root, 1, n);
	//	printf("first %d %d\n",A.l,A.r);
	for (int i = 1; i <= cnt; ++i) lc[i] = rc[i] = 0; cnt = 0;
	build2(Rt[0], 1, n);
	H[0] = 1;
	for (int i = 1; i <= n; ++i) H[i] = H[i - 1] * B%mo;
	for (int i = 1; i <= n; ++i) add(Rt[i], Rt[i - 1], 1, n, a[i]);
	G.push(A);
	for (int i = 1; i <= n; ++i)
		if (i != A.l) {
			int l = i, r = n + 1, mid;
			while (l < r) {
				mid = (l + r) / 2;
				if (A < (O) { i, mid }) r = mid; else l = mid + 1;
			}
			if (l <= n) G.push((O) { i, l });
		}
	m = 0;
	while (R--) {
		A = G.top(); G.pop();
		Ans[++m] = A;
		++A.r;
		if (A.r <= n) G.push(A);
	}
	for (int i = m; i; --i) cout << Ans[i].l << ' ' << Ans[i].r << endl;
	return 0;
}