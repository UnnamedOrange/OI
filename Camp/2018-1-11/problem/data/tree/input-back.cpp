#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
using namespace std;
#define DEBUG(...) fprintf(stderr,__VA_ARGS__)

int rand(int l,int r)
{
	int p=(rand()<<15)+rand();
	p=abs(p);
	return l+p%(r-l+1);
}

int n,m;

void make1() //no 2
{
	n=99991; m=200000;
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
	n=99992; m=200000;
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
	n=99993; m=200000;
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
	n=99994; m=200000;
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
	n=99995; m=200000;

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
	n=99996; m=200000;
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
	n=100000; m=200000;
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

int main()
{
	srand(time(NULL));

	freopen("tree1.in","w",stdout);
	make1();
	fclose(stdout);
	DEBUG("tree1 finished!\n\n");

	freopen("tree2.in","w",stdout);
	make2();
	fclose(stdout);
	DEBUG("tree2 finished!\n\n");

	freopen("tree3.in","w",stdout);
	make3();
	fclose(stdout);
	DEBUG("tree3 finished!\n\n");

	freopen("tree4.in","w",stdout);
	make4();
	fclose(stdout);
	DEBUG("tree4 finished!\n\n");

	freopen("tree5.in","w",stdout);
	make5();
	fclose(stdout);
	DEBUG("tree5 finished!\n\n");

	freopen("tree6.in","w",stdout);
	make6();
	fclose(stdout);
	DEBUG("tree6 finished!\n\n");

	freopen("tree7.in","w",stdout);
	make0();
	fclose(stdout);
	DEBUG("tree7 finished!\n\n");

	freopen("tree8.in","w",stdout);
	make0();
	fclose(stdout);
	DEBUG("tree8 finished!\n\n");

	freopen("tree9.in","w",stdout);
	make0();
	fclose(stdout);
	DEBUG("tree9 finished!\n\n");

	freopen("tree10.in","w",stdout);
	make0();
	fclose(stdout);
	DEBUG("tree10 finished!\n\n");
}

