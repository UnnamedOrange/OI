#include<bits/stdc++.h>
using namespace std;
int t,n,m,x[26];
char s[100010];
inline int ran()
{
	return (rand()<<15)+rand();
}
inline void pr()
{
	int i;
	for(i=0;i<26;i++)
	  {
	   x[i]=i;
	   swap(x[i],x[ran()%(i+1)]);
	  }
	for(i=0;i<n;i++)
	  s[i]=x[s[i]-'a']+'a';
	s[n]=0;
	printf("%d\n%s\n",n,s);
}
int main()
{
	srand(time(0));
	ran();
	freopen("string10.in","w",stdout);
	int i;
	t=20;
	m=100000;
	printf("%d\n",t);
	while(t--)
	  {
	   if(t==19)
	     {
		  n=m;
		  for(i=0;i<n;i++)
		    s[i]='a';
		  pr();
		  s[ran()%n]='a';
		  pr();
		  t--;
		 }
	   if(t==17)
	     {
		  n=m-1;
		  for(i=0;i<n;i++)
		    s[i]='a';
		  pr();
		  s[ran()%n]='a';
		  pr();
		  t--;
		 }
	   if(t==15)
	     {
		  n=m;
		  for(i=0;i<n;i++)
		    s[i]=(i&1?'a':'b');
		  pr();
		 }
	   if(t==14)
	     {
		  n=m;
		  for(i=0;i<n;i++)
		    s[i]=(i+(i>=n/2)&1?'a':'b');
		  pr();
		 }
	   if(t==13)
	     {
		  n=m-1;
		  for(i=0;i<n;i++)
		    s[i]=(i&1?'a':'b');
		  pr();
		  s[ran()%n]='a';
		  pr();
		  t--;
		 }
	   if(t==11)
	     {
		  n=m;
		  for(i=0;i<n;i++)
		    s[i]='a';
		  s[n/2]=s[n/2-1]='b';
		  pr();
		 }
	   if(t==10)
	     {
		  n=m-1;
		  for(i=0;i<n;i++)
		    s[i]='a';
		  s[n/2]='b';
		  pr();
		  s[ran()%n]='a';
		  pr();
		  t--;
		 }
	   if(t<=8)
	     {
		  n=m-ran()%2;
		  for(i=0;i<n;i++)
		    s[i]='a'+ran()%26;
	   	  for(i=0;i<n;i++)
	 	    s[i]=s[n-1-i];
	      if(ran()%2)
	        s[ran()%n]='a';
		  pr();
		 }
	  }
	return 0;
}

