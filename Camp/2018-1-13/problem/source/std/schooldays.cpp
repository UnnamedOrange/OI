#include<cstdio>
#include<algorithm>
#define fo(i,a,b) for(i=a;i<=b;i++)
#define fd(i,a,b) for(i=a;i>=b;i--)
using namespace std;
const int maxn=1000000+10,mo=1000000007;
struct dong{
    int c,f,g,ff,gg;
} tree[maxn*4];
int f[maxn],g[maxn],c[maxn],d[maxn],dl[maxn],left[maxn];
int i,j,k,l,t,n,m,head,tail;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9'){
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void cmp(int &f,int &g,int ff,int gg){
    if (ff>f) f=ff,g=gg;
    else if (f==ff) g=(g+gg)%mo;
}
void mark(int p,int ff,int gg){
    cmp(tree[p].f,tree[p].g,ff,gg);
    cmp(tree[p].ff,tree[p].gg,ff,gg);
}
void down(int p){
    if (tree[p].ff>-1){
        mark(p*2,tree[p].ff,tree[p].gg);
        mark(p*2+1,tree[p].ff,tree[p].gg);
        tree[p].ff=-1;tree[p].gg=0;
    }
}
void update(int p){
    int j=tree[p*2].c,k=tree[p*2+1].c;
    if (c[j]>c[k]) tree[p].c=j;else tree[p].c=k;
    j=tree[p*2].f;k=tree[p*2+1].f;
    if (j>=k){
        tree[p].f=j;tree[p].g=tree[p*2].g;
        if (j==k) (tree[p].g+=tree[p*2+1].g)%=mo;
    }
    else{
        tree[p].f=k;tree[p].g=tree[p*2+1].g;
    }
}
void build(int p,int l,int r){
    tree[p].ff=-1;tree[p].gg=0;
    if (l==r){
        /*if (l==0) tree[p].f=0,tree[p].g=1;
        else */tree[p].c=l,tree[p].f=-1,tree[p].g=0;
        return;
    }
    int mid=(l+r)/2;
    build(p*2,l,mid);build(p*2+1,mid+1,r);
    update(p);
}
int find(int p,int l,int r,int a,int b){
    if (l==a&&r==b) return tree[p].c;
    down(p);
    int mid=(l+r)/2;
    if (b<=mid) return find(p*2,l,mid,a,b);
    else if (a>mid) return find(p*2+1,mid+1,r,a,b);
    else{
        int j=find(p*2,l,mid,a,mid),k=find(p*2+1,mid+1,r,mid+1,b);
        if (c[j]>c[k]) return j;else return k;
    }
}
void change(int p,int l,int r,int a,int b,int ff,int gg){
    if (l==a&&r==b){
        mark(p,ff,gg);
        return;
    }
    down(p);
    int mid=(l+r)/2;
    if (b<=mid) change(p*2,l,mid,a,b,ff,gg);
    else if (a>mid) change(p*2+1,mid+1,r,a,b,ff,gg);
    else change(p*2,l,mid,a,mid,ff,gg),change(p*2+1,mid+1,r,mid+1,b,ff,gg);
    update(p);
}
void query(int p,int l,int r,int a,int b,int &f,int &g){
    if (a>b){
        f=-1;
        g=0;
        return;
    }
    if (l==a&&r==b){
        f=tree[p].f;
        g=tree[p].g;
        return;
    }
    down(p);
    int mid=(l+r)/2;
    if (b<=mid) query(p*2,l,mid,a,b,f,g);
    else if (a>mid) query(p*2+1,mid+1,r,a,b,f,g);
    else{
        int j,k;
        query(p*2,l,mid,a,mid,j,k);
        query(p*2+1,mid+1,r,mid+1,b,f,g);
        if (j>f) f=j,g=k;
        else if (j==f) g=(g+k)%mo;
    }
}
int get(){
    while (head<=tail&&dl[head]<j+1) head++;
    return d[dl[head]];
}
void prepare(){
    head=1;tail=0;
    j=0;
    fo(i,1,n){
        while (head<=tail&&d[dl[tail]]>=d[i]) tail--;
        dl[++tail]=i;
        while (i-get()>j) j++;
        left[i]=j;
    }
}
int binary(int l,int r,int x){
    int mid;
    while (l<r){
        mid=(l+r+1)/2;
        if (left[mid]<x) l=mid;else r=mid-1;
    }
    return l;
}
void trans(int l,int r,int k,int c){
    int st=max(k,l+c),ed=min(r,k-1+c),ff=-1,gg=0,i=st;
    while (i<=ed){
        if (left[i]>=k) return;
        if (left[i]>=l) break;
        if (i==st) query(1,0,n,l,i-c,ff,gg);
        else cmp(ff,gg,f[i-c],g[i-c]);
        if (ff!=-1) cmp(f[i],g[i],ff+1,gg);
        i++;
    }
    if (i>r) return;
    if (left[i]<l){
        int j=binary(i,r,l);
        query(1,0,n,l,k-1,ff,gg);
        if (ff!=-1) change(1,0,n,i,j,ff+1,gg);
        i=j+1;
    }
    while (i<=r){
        if (left[i]>=k) return;
        query(1,0,n,left[i],min(k-1,i-c),ff,gg);
        if (ff!=-1) cmp(f[i],g[i],ff+1,gg);
        i++;
    }
}
void solve(int l,int r){
    if (l>r) return;
    if (l==r){
        change(1,0,n,l,l,f[l],g[l]);
        query(1,0,n,l,l,f[l],g[l]);
        return;
    }
    int k=find(1,0,n,l+1,r);
    solve(l,k-1);
    trans(l,r,k,c[k]);
    solve(k,r);
}
int main(){
    freopen("schooldays18.in","r",stdin);freopen("schooldays18.out","w",stdout);
    int sizz = 512 << 20; // 512MB
    char *pp = (char*)malloc(sizz) + sizz;
    __asm__("movl %0, %%esp\n" :: "r"(pp));
    n=read();
    fo(i,1,n) c[i]=read(),d[i]=read();
    build(1,0,n);
    fo(i,1,n) f[i]=-1,g[i]=0;
    g[0]=1; 
    prepare();
    solve(0,n);
    if (f[n]<=0) printf("-1\n");else printf("%d %d\n",f[n],g[n]);
}
