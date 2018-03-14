#include<bits/stdc++.h>
using namespace std;
map<string, int> a;
string st[1000005];
int main()
{
	freopen("prob5.in", "r", stdin);
	freopen("prob5.out", "w", stdout);
	string str, s;
	cin >> str;
	int k; cin >> k;
	int n = str.size(), top = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			s.clear();
			for (int k = i; k <= j; k++) s += str[k];
			if (!a[s]) st[++top] = s;
			a[s]++;
		}
	}int ans = 0;
	for (int i = 1; i <= top; i++) if (a[st[i]] >= k) ans++;
	cout << ans;
}