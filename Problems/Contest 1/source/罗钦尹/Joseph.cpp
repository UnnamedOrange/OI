#include<iostream>
using namespace std;
int n,m;

struct monkey{
	int Num;
	monkey *Next;
};
monkey *Head,*Temp;

void c(){
	int i=0;
	Head=new monkey;
	Temp=Head;
	while(i<n){
		i++;
		Temp->Num=i;
		if(i==n){
			Temp->Next=Head;
		}
		else Temp->Next=new monkey;
		Temp=Temp->Next;
	}
	return;
}

int main(){
	freopen("Joseph.in","r",stdin);
	freopen("Joseph.out","w",stdout);
	cin>>n>>m;
	c();
	monkey *Now;
	Now =Head;
	while(Now->Next!=Now){
		int x=0;
		while(x<m-1){
			x++;
			Now=Now->Next;
		}
		Now->Next=Now->Next->Next;		
}
	Now->Num--;
	if(Now->Num==0) cout<<n;
		else cout<<Now->Num;
	return 0;
}
