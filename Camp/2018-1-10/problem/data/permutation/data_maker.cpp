#include<bits/stdc++.h>
using namespace std;
#define LL long long

const int maxn=1e5+10;
const int mo=998244353;

int n,A,B,cir,line,line0,a[maxn],b[maxn];
int p[maxn],pos[maxn];
char in_name[99],out_name[99];

int rand(int s,int t)
{
	int p=abs(rand()^(rand()<<15)^(rand()<<30));
	return s+p%(t-s+1);
}

int main()
{
	srand(time(NULL));
	int i;

	for (int case_id=0;case_id<10;case_id++)
	{
		memset(a,0,sizeof(a));
		A=B=0;
		if (case_id==0)
		{
			n=8;
			a[1]=2; a[2]=3; a[3]=0; a[4]=5;
			a[5]=0; a[6]=0; a[7]=0; a[8]=0;
			A=4; B=1;
		}
		else
		{
			n=rand(8e4,1e5); n-=n&1;
			cir=rand(0,500)*2;
			line=rand(0,1000);
			line0=rand(0,n/4);
			if (case_id<4) cir=line=line0=0;
			int used=0,x;
			while (cir)
			{
				x=rand(1,rand(1,cir/2))*2;
				for (i=1;i<=x;i++)
					a[used+i]=used+i+1;
				a[used+x]=used+1;
				used+=x;
				cir-=x;
			}
			while (line)
			{
				x=rand(1,rand(1,line));
				for (i=1;i<x;i++)
					a[used+i]=used+i+1;
				x&1?A++:B++;
				used+=x;
				line-=x;
			}
			while (line0--)
			{
				a[used+1]=used+2;
				used+=2;
				B++;
			}
			A+=n-used;
		}

		for (i=1;i<=n;i++) p[i]=i;
		for (i=1;i<=n;i++) swap(p[i],p[rand(1,i)]);
		for (i=1;i<=n;i++) pos[p[i]]=i;
		for (i=1;i<=n;i++) b[i]=p[a[pos[i]]];
		for (i=1;i<=n;i++) a[i]=b[i];

		sprintf(in_name,"permutation%d.in",case_id);
		sprintf(out_name,"permutation%d.out",case_id);

		freopen(in_name,"w",stdout);
		printf("%d\n",n);
		for (i=1;i<=n;i++)
			printf("%d ",a[i]);
		puts("");
		fclose(stdout);

		freopen(out_name,"w",stdout);
		int Ans=1;
		for (i=1;i<=A;i+=2)
			Ans=(LL)Ans*i%mo;
		Ans=(LL)Ans*Ans%mo;
		for (i=A+1;i<=A+B;i++)
			Ans=(LL)Ans*i%mo;
		printf("%d\n",Ans);
		fclose(stdout);

		fprintf(stderr,"case #%d finished\n",case_id);
	}
}

