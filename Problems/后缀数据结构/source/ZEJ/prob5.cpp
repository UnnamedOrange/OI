#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>

#define fo(a,b,c) for(int a=b;a<=c;a++)
#define fd(a,b,c) for(int a=b;a>=c;a--)
#define ll long long
using namespace std;
const int maxn = 1000010;
int sa[maxn], sa2[maxn], rk[maxn], cnt[maxn], hei[maxn];
int n, m;
char s[maxn];
void getsa() {
	int m = 256; n--;
	fo(i, 0, m)cnt[i] = 0;
	fo(i, 0, n)cnt[rk[i] = s[i]]++;
	fo(i, 1, m)cnt[i] += cnt[i - 1];
	fd(i, n, 0)sa[--cnt[rk[i]]] = i;
	for (int k = 1; k <= n; k <<= 1) {
		int p = 0;
		fo(i, n - k + 1, n)sa2[p++] = i;
		fo(i, 0, n)if (sa[i] >= k)sa2[p++] = sa[i] - k;
		fo(i, 0, m)cnt[i] = 0;
		fo(i, 0, n)cnt[rk[sa2[i]]]++;
		fo(i, 1, m)cnt[i] += cnt[i - 1];
		fd(i, n, 0)sa[--cnt[rk[sa2[i]]]] = sa2[i];
		swap(rk, sa2);
		rk[sa[0]] = 0; p = 0;
		fo(i, 1, n)rk[sa[i]] = sa2[sa[i]] == sa2[sa[i - 1]] && sa[i] + k <= n && sa[i - 1] + k <= n && sa2[sa[i] + k] == sa2[sa[i - 1] + k] ? p : ++p;
		if (p == n)break;
		m = p;
	}
	int lcp = 0;
	fo(i, 0, n)rk[sa[i]] = i;
	fo(i, 0, n) {
		lcp ? --lcp : 0;
		if (!rk[i])continue;
		int j = sa[rk[i] - 1];
		while (s[i + lcp] == s[j + lcp])lcp++;
		hei[rk[i]] = lcp;
	}
}
int k = 0, ans, top;
int sta[maxn];
int main() {
	freopen("prob5.in", "r", stdin);
	freopen("prob5.out", "w", stdout);
	scanf("%s", s);
	scanf("%d", &k); k--;
	n = strlen(s);
	getsa();
	fo(i, 1, n) {
		while (top&&hei[sta[top]] >= hei[i]) {
			if (sta[top] - sta[top - 1] + i - sta[top] - 1 >= k)ans += hei[sta[top]] - max(hei[sta[top - 1]], hei[i]);
			top--;
		}
		sta[++top] = i;
	}
	while (top&&hei[sta[top]] >= 0) {
		if (sta[top] - sta[top - 1] + n - sta[top] >= k)ans += hei[sta[top]] - hei[sta[top - 1]];
		top--;
	}
	printf("%d\n", ans);
}