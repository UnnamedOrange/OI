#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;
struct person{
	int ahead;
	int next;
}a[100000005];
//int ;

int n,m;
int plusnext(int i,int n){
	if(n==0) return i;//���ص��� ���� n �� ��Ծ Ҫ�����˵��±� 
	n--;
	plusnext(a[i].next,n);
}
int plusahead(int i,int n){
	if(n==0) return i;
	 plusahead(a[i].ahead,n--);
}

int main(){
	freopen("joseph.in","r",stdin);
	freopen("joseph.out","w",stdout);
	cin>>n>>m;
	
	
	//���� 
	a[1].ahead = n;
	a[1].next = 2;
	
	for (int i=2;i<=n-1;i++){
		a[i].ahead = i-1;
		a[i].next = i+1;
	}
	
	a[n].ahead = n-1;
	a[n].next = 1;
	
	
	//*******��ʼ�� 
	int plus = m - 1;
	int start=1;
	int disap=0;
	a[0].next = 1;
	
	n--;
	//������ʽ // fucking problem
	while(n--){
		
	start = a[disap].next; 
	//fucking problem
	//cout<<"LOOK";
	disap = plusnext(start,plus);//��ʧ ���±� //��һ�غ� Ϊ m 
	//cout<<"5"<<endl;
	//fucking problem
	a[ a[ disap ].ahead ].next = a[ disap ].next;
	a[ a[ disap ].next ].ahead = a[ disap ].ahead;
		
	}
	
	cout<<a[disap].next;
//	cout<<"5";
	
	
	return 0;
}
/*	//plus  cycle+problem       no need now
	int plus = m - 1;
	int nowplus;
	nowplus = plus; 
	if(nowplus>=n) nowplus = nowplus % n; // ��ѭ��ʹ��   n��Ϊ�ɱ� 
	
	*/
	//idx cycleproblem
	
/*	for(int i=1;i<=n;i++)
	if(i = m-1) a[i] = a[m+1];
	int k = n;
	a[i] = a[i+1];
	n--;
	a[m+k]//XX
	//a[m+k-1] == m+k;
	a[m+k-1] = m+k+1;
*/

