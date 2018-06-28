#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
#define N 270
#define ll long long
#define add(x, y) (x = (x + (y)) % mod)
using namespace std;
int n, m, mod, R, nStatus, fa[25], to[25];
ll ans;
struct matrix
{
	ll a[N][N];
	matrix() { memset(a, 0, sizeof(a)); }
	matrix operator*(matrix b)
	{
		matrix re;
		for (int i = 1; i <= nStatus; i++)
			for (int k = 1; k <= nStatus; k++)
				if (a[i][k])
					for (int j = 1; j <= nStatus; j++)
						add(re.a[i][j], a[i][k] * b.a[k][j]);
		return re;
	}
} T;
matrix matksm(matrix a, int b)
{
	matrix r;
	for (int i = 1; i <= nStatus; i++)
		r.a[i][i] = 1;
	for (; b; b >>= 1, a = a * a)
		if (b & 1)
			r = r * a;
	return r;
}
struct Node
{
	int a[11];
	Node() { memset(a, 0, sizeof(a)); }
	friend bool operator<(const Node p, const Node q)
	{
		for (int i = 0; i < n; i++)
		{
			if (p.a[i] < q.a[i])
				return 1;
			if (p.a[i] > q.a[i])
				return 0;
		}
		return 0;
	}
	void decode(int s)
	{
		bool lst = 0;
		int cnt = 0;
		for (int i = 0; i < n; i++)
			if ((s >> i) & 1)
			{
				if (!lst)
					a[i] = ++cnt;
				else
					a[i] = a[i - 1];
				lst = 1;
			}
			else
				a[i] = 0, lst = 0;
	}
	void outp()
	{
		for (int i = 0; i < 11; i++)
			cout << a[i];
		puts("");
	}
} o, fid[10010];
map<Node, int> id;
bool End[10010];
int getfa(int v)
{
	if (fa[v] == v)
		return v;
	return (fa[v] = getfa(fa[v]));
}
void merge(int x, int y)
{
	if (getfa(x) != getfa(y))
		fa[fa[x]] = fa[y];
}
bool ok[11];
bool check(Node p, Node q)
{
	for (int i = 0; i < n; i++)
		if (!p.a[i] && !q.a[i])
			return 0;
	int np = 0;
	for (int i = 0; i < n; i++)
		np = std::max(np, p.a[i]);
	memset(ok, 0, sizeof(ok));
	for (int i = 0; i < n; i++)
		if (q.a[i])
			ok[p.a[i]] = 1;
	for (int i = 1; i <= np; i++)
		if (!ok[i])
			return 0;
	return 1;
}
int CodeTransfer(Node p, Node q)
{
	for (int i = 1; i <= (n << 1); i++)
		fa[i] = i;
	for (int i = 0; i < n; i++)
		if (p.a[i] && q.a[i])
			merge(p.a[i] + n, q.a[i]);
	int tp = 0;
	for (int i = 0; i < n; i++)
		if (q.a[i])
			q.a[i] = getfa(q.a[i]);
	memset(to, 0, sizeof(to));
	for (int i = 0; i < n; i++)
		if (q.a[i])
		{
			if (!to[q.a[i]])
				to[q.a[i]] = ++tp;
			q.a[i] = to[q.a[i]];
		}

	return id[q];
}

void SearchStatus(int v, int nBlock)
{
	if (v >= n)
	{
		id[o] = ++nStatus;
		fid[nStatus] = o;
		if (nBlock == 1)
			End[nStatus] = 1;
		return;
	}
	for (int i = 0; i <= nBlock + 1; i++)
	{
		if (v)
		{
			if (o.a[v - 1] && i && i != o.a[v - 1])
				continue;
			if (!o.a[v - 1] && !i)
				continue;
		}
		o.a[v] = i;
		SearchStatus(v + 1, std::max(i, nBlock));
		o.a[v] = 0;
	}
}
void init()
{
	SearchStatus(0, 0);
	for (int i = 1; i <= nStatus; i++)
		for (int s = 0; s < (1 << n); s++)
		{
			Node p;
			p.decode(s);
			if (check(fid[i], p))
				T.a[i][CodeTransfer(fid[i], p)] = 1;
		}
}
int main()
{
	//freopen("matrix.in", "r", stdin);
	//freopen("matrix.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &mod);
	init();
	T = matksm(T, m - 1);

	for (int s = 0; s < (1 << n); s++)
	{
		Node p;
		p.decode(s);
		int idp = id[p];
		for (int i = 1; i <= nStatus; i++)
			if (End[i])
				add(ans, T.a[idp][i]);
	}
	printf("%lld", ans);
	return 0;
}