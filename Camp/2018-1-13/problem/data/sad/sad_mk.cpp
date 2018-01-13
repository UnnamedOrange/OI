#include<cstdio>
#include<algorithm>
#include<ctime>
#define fo(i,a,b) for(i=a;i<=b;i++)
using namespace std;
typedef long long ll;
const int maxn=1000000+10;
int edge[maxn][2],id[maxn];
int i,j,k,l,t,n,m,tot,a,b;
int random(int x){
	ll t=rand()%10000;
	t=t*10000+rand()%10000;
	t=t*10000+rand()%10000;
	return t%x;
}
void add(int x,int y){
	if (random(2)==0) swap(x,y);
	tot++;
	edge[tot][0]=x;edge[tot][1]=y;
}
void makelian(){
	fo(i,2,n){
		//printf("%d %d\n",i-1,i);
		add(i-1,i);
	}
}
void maketree(){
	b=10;a=30000;
	fo(i,2,b){
		//printf("1 %d\n",i);
		add(1,i);
	}
	fo(i,b+1,b+a){
		//printf("%d %d\n",i-1,i);
		add(i-1,i);
	}
	fo(i,b+a+1,n){
		//printf("%d %d\n",random(i-1)+1,i);
		add(random(i-1)+1,i);
	}
}
void make(int c){
	fo(i,1,n) printf("%c",c+'0');
	printf("\n");
}
void ran(){
	fo(i,1,n) printf("%c",random(2)+'0');
	printf("\n");
}
void work(){
	fo(i,1,n) id[i]=i;
	random_shuffle(id+1,id+n+1);
	fo(i,1,n-1) printf("%d %d\n",id[edge[i][0]],id[edge[i][1]]);
}
int main(){
	freopen("sad20.in","w",stdout);
	srand(time(0));
	n=100000;
	printf("%d\n",n);
	//make(0);
	ran();
	//makelian();
	maketree();
	work();
}
