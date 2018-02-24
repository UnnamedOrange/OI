#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
//#include<bits/stdc++.h>
using namespace std; 
const long long MAXN = 100005;
long long s1[MAXN],s2[MAXN];
long long ans[MAXN];
int main()
{
	string a,b;
	cin >> a >> b;
	if(a == "0" || b == "0")
	{
		cout << "0";
		return 0;
	}
	int lena = 1;
	for(int i = a.length() - 1;i >= 0;i--)
	{
		s1[lena++] = a[i] - '0';
	}
	lena--;
	int lenb = 1;
	for(int i = b.length() - 1;i >= 0;i--)
	{
		s2[lenb++] = b[i] - '0';
	} 
	lenb--;
	for(int i = 1;i <= lena;i++)
	{
		for(int j = 1;j <= lenb;j++)
		{
			ans[i + j - 1] += s1[i] * s2[j];
			ans[i + j] += ans[i + j - 1]/10;
			ans[i + j - 1] = ans[i + j - 1]%10; 
		}
	}
	for(int i = lena + lenb;i > 0;i--)
	{
		if(ans[i] != 0)
		{
			for(int j = i;j >= 1;j--)
			{
				printf("%d",ans[j]);
			}
			break;
		}
	}
	return 0;
}
