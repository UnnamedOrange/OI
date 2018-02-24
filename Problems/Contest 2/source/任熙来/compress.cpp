#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
#include<vector>
#include<stack>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<cctype>
#define MAXA 90000
// Winner Winner Chicken Dinner
using namespace std;
char bufx[MAXA],bufy[MAXA];
int x[MAXA],y[MAXA],result[MAXA*2],temp,jw,k,zero;
int main()
{
	gets(bufx);
	gets(bufy);
	int xlen = strlen(bufx);
	int ylen = strlen(bufy);
	if((xlen == 1 && bufx[0] == '0') || (ylen == 1 && bufy[0] == '0'))
	{
		printf("0");
		return 0;
	}
	for(int i=xlen-1;i>=0;i--)
	{
		if(bufx[i] == '0')
	    {
	    	xlen--;
	    	zero++;
		}
		else break;
	}
	    
	for(int i=ylen-1;i>=0;i--)
	{
		if(bufy[i] == '0')
	    {
	    	ylen--;
	    	zero++;
		}
		else break;
	}
	    
	for(int i=xlen-1;i>=0;i--)
	    x[xlen-i-1] = bufx[i] - '0';
	for(int i=ylen-1;i>=0;i--)
	    y[ylen-i-1] = bufy[i] - '0';
	for(int i=0;i<ylen;i++)//travel y
	{
		for(int j=0;j<=xlen;j++)//travel x
		{
			temp = y[i] * x[j];
			temp += jw;
			jw = temp / 10;
			temp %= 10;
			result[i+j] += temp;
		}
	}
	jw = 0;
	while(result[k] != 0)
	{
		if(result[k] >= 10)
		{
			jw = result[k] / 10;
			result[k] %= 10;
		}
		else jw = 0;
		k++;
		result[k] += jw;
	}
	for(int i=k-1;i>=0;i--)
	    printf("%d",result[i]);
	if(zero)
	   for(int i=1;i<=zero;i++)
	       printf("0");
}
