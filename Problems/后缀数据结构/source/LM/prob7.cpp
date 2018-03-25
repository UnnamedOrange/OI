#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1000005;
const int base=131;
typedef unsigned long long ull;
char str[maxn];
inline ull get(int s,int t)
{
	ull temp=1;
	for(int i=s;i<=t;i++) temp=temp*base+str[i];
	return temp;
}
int main()
{
	freopen("prob7.in","r",stdin);
	freopen("prob7.out","w",stdout);
	scanf("%s",str+1);
	int n=strlen(str+1);
	for(int i=1;i<=n;i++)
	{
		if(n%i) continue;
		int now=1;
		ull last=get(now,now+i-1);
		bool flag=false;now+=i;
		while(now+i-1<=n)
		{
			ull cur=get(now,now+i-1);
			if(cur!=last) flag=true;
			now+=i;
		}
		if(!flag) return printf("%d",n/i),0;
	}
	return 0;
}
