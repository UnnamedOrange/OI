#include<bits/stdc++.h>
#define MAXN 100005

using namespace std;

string s1, s2;
int a[MAXN], b[MAXN];
int ans[MAXN];
int x;

int main( )
{
//	freopen("compress.in", "r",stdin);
//	freopen("compress.out","w",stdout);

	cin >> s1 >> s2;
	
	int len1 = s1.length(),
		len2 = s2.length();
	
	for(int i = 0; i <= len1; i++)
	{
		a[i + 1] = s1[len1 - 1 - i] - '0';
	}
	for(int i = 0; i <= len2; i++)
	{
		b[i + 1] = s2[len2 - i - 1] - '0';
	}
	
	for(int i = 1; i <= len1; i++)
	{
		for(int l = 1; l <= len2; l++)
		{
			ans[i + l - 1] = a[i] * b[l] + x + ans[i + l - 1];
			ans[i + l] += ans[i + l - 1] / 10;
			ans[i + l - 1] = ans[i + l - 1] % 10;
		}
	}
	int j = len1 + len2;
	ans[j] += x;
	while(ans[j] == 0 && j) j--; 
	if(j < 1) printf("0");
	else for(int i = j; i >= 1; i--)
			printf("%d", ans[i]);	
	return 0;
}

