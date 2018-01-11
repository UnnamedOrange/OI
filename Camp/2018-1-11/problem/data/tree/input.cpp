#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
using namespace std;
#define DEBUG(...) fprintf(stderr,__VA_ARGS__)

int rand(int l,int r)
{
	int p=(rand()<<30)^(rand()<<15)^rand();
	return l+abs(p)%(r-l+1);
}

int n,m;

void make1() //no 2
{
	printf("%d %d\n",n,m);
	int i,op,l,r,x,val;
	for (i=1;i<=n;i++)
		printf("%d ",rand(1,10000));
	printf("\n");
	while (m--)
	{
		op=rand(1,1001);
		if (op<=1000)
		{
			l=rand(3*(n>>2),n);
			r=rand(l,min(l+10,n));
			x=rand(1,l-1);
			printf("0 %d %d %d\n",x,l,r);
		}
		else
		{
			x=rand(1,n);
			val=rand(1,10000);
			printf("1 %d %d\n",x,val);
		}
	}
}

void make2() //no 0,1
{
	printf("%d %d\n",n,m);
	int i,x;
	for (i=1;i<=n;i++)
		printf("%d ",rand(1,10000));
	printf("\n");
	while (m--)
	{
		x=rand(1,n);
		printf("2 %d\n",x);
	}
}

void make3() //0;1,2
{
	printf("%d %d\n",n,m);
	int i,op,l,r,x,val;
	for (i=1;i<=n;i++)
		printf("%d ",rand(1,10000));
	printf("\n");
	for (i=1;i<=n;i++)
	{
		l=rand(2,n);
		r=rand(l,n);
		x=rand(1,l-1);
		printf("0 %d %d %d\n",x,l,r);
	}
	for (i=n+1;i<=m;i++)
	{
		op=rand(1,600);
		if (op<=300)
		{
			x=rand(1,n);
			val=rand(1,10000);
			printf("1 %d %d\n",x,val);
		}
		else
		{
			x=rand(1,n);
			printf("2 %d\n",x);
		}
	}
}

void make4() //l==r random
{
	printf("%d %d\n",n,m);
	int i,op,l,x,val;
	for (i=1;i<=n;i++)
		printf("%d ",rand(1,10000));
	printf("\n");
	while (m--)
	{
		op=rand(1,900);
		if (op<=300)
		{
			l=rand(2,n);
			x=rand(1,l-1);
			printf("0 %d %d %d\n",x,l,l);
		}
		else if (op<=600)
		{
			x=rand(1,n);
			val=rand(1,10000);
			printf("1 %d %d\n",x,val);
		}
		else
		{
			x=rand(1,n);
			printf("2 %d\n",x);
		}
	}
}

void make5() //l==r
{
	printf("%d %d\n",n,m);
	int i,op,l,x,val;
	for (i=1;i<=n;i++)
		printf("%d ",rand(1,10000));
	printf("\n");

	for (i=3;i<=n;i+=2,m--)
		printf("0 %d %d %d\n",i-2,i,i);

	for (i=1;i<=100000;i++,m--)
	{
		op=rand(1,1000);
		if (op<=50)
		{
			l=rand(3*(n>>2),n);
			x=rand(1,l-1);
			printf("0 %d %d %d\n",x,l,l);
		}
		else if (op<=200)
		{
			for (l=1;l&1;l=rand(2,n));
			x=rand(1,l-1);
			printf("0 %d %d %d\n",x,l,l);
		}
		else if (op<=400)
		{
			x=rand(1,n);
			val=rand(1,10000);
			printf("1 %d %d\n",x,val);
		}
		else
		{
			x=rand(1,n);
			printf("2 %d\n",x);
		}
	}

	while (m--)
	{
		op=rand(1,1000);
		if (op<=300)
		{
			l=rand(2,n);
			x=rand(1,l-1);
			printf("0 %d %d %d\n",x,l,l);
		}
		else if (op<=600)
		{
			x=rand(1,n);
			val=rand(1,10000);
			printf("1 %d %d\n",x,val);
		}
		else
		{
			x=rand(1,n);
			printf("2 %d\n",x);
		}
	}
}

void make6() //random
{
	printf("%d %d\n",n,m);
	int i,op,l,r,x,val;
	for (i=1;i<=n;i++)
		printf("%d ",rand(1,10000));
	printf("\n");
	while (m--)
	{
		op=rand(1,900);
		if (op<=300)
		{
			l=rand(2,n);
			r=rand(l,n);
			x=rand(1,l-1);
			printf("0 %d %d %d\n",x,l,r);
		}
		else if (op<=600)
		{
			x=rand(1,n);
			val=rand(1,10000);
			printf("1 %d %d\n",x,val);
		}
		else
		{
			x=rand(1,n);
			printf("2 %d\n",x);
		}
	}
}

void make0()
{
	printf("%d %d\n",n,m);
	int i,op,l,r,x,val,lastl,lastr;
	for (i=1;i<=n;i++)
		printf("%d ",rand(1,10000));
	printf("\n");

	lastl=2; lastr=rand(3,4);
	while (lastr<n)
	{
		l=lastr+1;
		r=rand(l,min(l+3,n));
		x=rand(lastl,lastr);
		printf("0 %d %d %d\n",x,l,r);
		lastl=l; lastr=r; m--;
	}

	for (i=1;i<=65000;i++,m--)
	{
		op=rand(1,1000);
		if (op<=80)
		{
			l=rand(3*(n>>2),n);
			r=rand(l,min(l+10,n));
			x=rand(1,l-1);
			printf("0 %d %d %d\n",x,l,r);
		}
		else if (op<=250)
		{
			x=rand(1,n);
			val=rand(1,10000);
			printf("1 %d %d\n",x,val);
		}
		else
		{
			x=rand(1,n);
			printf("2 %d\n",x);
		}
	}

	for (i=1;i<=65000;i++,m--)
	{
		op=rand(1,1000);
		if (op<=200)
		{
			l=rand(n>>1,n);
			r=rand(l,min(l+10,n));
			x=rand(1,l-1);
			printf("0 %d %d %d\n",x,l,r);
		}
		else if (op<=400)
		{
			x=rand(1,n);
			val=rand(1,10000);
			printf("1 %d %d\n",x,val);
		}
		else
		{
			x=rand(1,n);
			printf("2 %d\n",x);
		}
	}

	while (m--)
	{
		op=rand(1,1000);
		if (op<=300)
		{
			l=rand(2,n);
			r=rand(l,n);
			x=rand(1,l-1);
			printf("0 %d %d %d\n",x,l,r);
		}
		else if (op<=600)
		{
			x=rand(1,n);
			val=rand(1,10000);
			printf("1 %d %d\n",x,val);
		}
		else
		{
			x=rand(1,n);
			printf("2 %d\n",x);
		}
	}
}

int case_id;
char name[20];
int main()
{
	srand(time(NULL));

	for (case_id=1;case_id<=20;case_id++)
	{
		if (case_id<10)
		{
			memcpy(name,"tree .in",sizeof("tree .in"));
			name[4]='0'+case_id;
		}
		else
		{
			memcpy(name,"tree  .in",sizeof("tree  .in"));
			name[4]='0'+case_id/10;
			name[5]='0'+case_id%10;
		}
		freopen(name,"w",stdout);
		n=99980+case_id; m=200000;
		if (case_id<=1) make1();
		else if (case_id<=2) make2();
		else if (case_id<=4) make3();
//		else if (case_id<=6) make4();
		else if (case_id<=8) make5();
		else if (case_id<=12) make6();
		else make0();
		fclose(stdout);
		DEBUG("tree%d finished!\n\n",case_id);
	}
}

