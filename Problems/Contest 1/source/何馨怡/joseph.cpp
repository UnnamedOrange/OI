#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cassert>

using namespace std;

int n ,m;

struct People{
	int Num;
	People *next;
};

People *Head, *Temp;

void Cycle( )
{
	int i = 0;
	Head = new People;
	Temp = Head;
	while(i < n)
	{
		i++;
		Temp->Num = i;
		if(i == n)
		{
			Temp->next = Head;
		}
		else Temp->next = new People;
		     Temp = Temp->next;
	}
	return;
}

int main( )
{
	freopen("joseph.in","r",stdin);
	freopen("joseph.out","w",stdout);
	
	cin >> n >> m;
	
	Cycle( );
	People *now;
	now  = Head;
	while(now->next != now)
	{
		int x = 0;
		while(x < m - 1)
		{
			x++;
			now = now->next;
		}
		now->next = now->next->next;
	}
	now->Num--;
	if(now->Num == 0) cout << n << endl;
	else cout << now->Num << endl;
	
	return 0;
}
