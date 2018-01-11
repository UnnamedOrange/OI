#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
using namespace std;

void read(int &x)
{
	char c=getchar(); x=0;
	while (c<'0'||c>'9') c=getchar();
	while (c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
}

const int maxn=2e5+10;
int n,m,last,col[maxn],Rr[maxn];
set<int> S,S0[maxn];

namespace Splay{
	int root,son[maxn][2],fa[maxn],sz[maxn],val[maxn];
#define lc (son[x][0])
#define rc (son[x][1])

	inline void update(int x)
	{
		sz[x]=sz[lc]+sz[rc]+val[x];
	}

	void rotate(int x)
	{
		int y=fa[x],z=fa[y];
		int d=son[y][1]==x;
		int c=son[x][d^1];
		if (c) fa[c]=y;
		fa[y]=x; fa[x]=z;
		if (z) son[z][son[z][1]==y]=x;
		son[x][d^1]=y;
		son[y][d]=c;
		update(y); update(x);
	}

	void splay(int x,int f)
	{
		while (fa[x]!=f)
		{
			int y=fa[x],z=fa[y];
			if (z==f) {rotate(x); break;}
			if ((son[z][1]==y)^(son[y][1]==x))
				rotate(x),rotate(x);
			else
				rotate(y),rotate(x);
		}
		if (!f) root=x;
	}

	int build(int l,int r,int f)
	{
		if (l>r) return 0;
		int x=(l+r)>>1;
		fa[x]=f;
		lc=build(l,x-1,x);
		rc=build(x+1,r,x);
		update(x);
		return x;
	}

	void init()
	{
		int i;
		for (i=1;i<=n;i++)
			read(val[i<<1]);
		root=build(1,n<<1,0);
	}

	void move(int f,int l,int r)
	{
		int tmp;
		if (last) tmp=last;
		else
		{
			set<int>::iterator it;
			it=S0[f].lower_bound(l);
			if (it==S0[f].begin()) tmp=(f<<1)-1;
			else tmp=Rr[*(--it)]<<1;
		}
		l=(l<<1)-1; r<<=1;
		splay(l,0);
		splay(r,l);
		int u=son[l][0],v=son[r][1];
		son[l][0]=son[r][1]=0;
		fa[u]=fa[v]=0;
		update(r);
		update(l);
		if (!u) root=v;
		else if (!v) root=u;
		else
		{
			root=u;
			for (;son[u][1];u=son[u][1]);
			splay(u,0);
			son[u][1]=v;
			fa[v]=u;
			update(u);
		}
		splay(tmp,0);
		u=tmp; v=son[tmp][1];
		if (!v)
		{
			fa[l]=u;
			son[u][1]=l;
			update(u);
		}
		else
		{
			fa[v]=r;
			fa[l]=u;
			son[u][1]=l;
			son[r][1]=v;
			update(r);
			update(l);
			update(u);
		}
	}

	void modify(int x,int v)
	{
		splay(x<<1,0);
		val[x<<1]=v;
		update(x);
	}

	int size(int x)
	{
		splay((x<<1)-1,0);
		splay(x<<1,(x<<1)-1);
		return val[x<<1]+sz[son[x<<1][0]];
	}
}

void Add(int l,int r,int fa)
{
	Rr[l]=r;
	col[l]=fa;
	S.insert(l);
	S0[fa].insert(l);
}

void Dec(int pos,int c)
{
	S.erase(pos);
	S0[c].erase(pos);
}

int main()
{
//	freopen("tree1.in","r",stdin);
//	freopen("tree1.ans","w",stdout);
	int op,x,l,r,v,pos,c;
	read(n); read(m);
	Splay::init();
	Rr[n+1]=n+1;
	S.insert(n+1);
	Add(2,n,1);
	Splay::move(1,2,n);
	while (m--)
	{
		read(op);
		if (op==0)
		{
			read(x); read(l); read(r); last=0;
			int tmp=*(--S.upper_bound(l));
			if (tmp!=l)
			{
				pos=tmp; c=col[pos]; tmp=Rr[pos]+1;
				if (c-x) Splay::move(x,l,min(r,Rr[pos]));
				last=Rr[pos]<<1;
				if (Rr[pos]>r) Add(r+1,Rr[pos],c);
				Rr[pos]=l-1; col[pos]=c;
			}
			for (pos=tmp;Rr[pos]<=r;pos=Rr[pos]+1)
			{
				c=col[pos];
				if (c-x) Splay::move(x,pos,Rr[pos]);
				last=Rr[pos]<<1;
				Dec(pos,c);
			}
			if (pos<=r)
			{
				c=col[pos];
				if (c-x) Splay::move(x,pos,r);
				Add(r+1,Rr[pos],c);
				Dec(pos,c);
			}
			Add(l,r,x);
		}

		if (op==1)
		{
			read(x); read(v);
			Splay::modify(x,v);
		}
		if (op==2)
		{
			read(x);
			printf("%d\n",Splay::size(x));
		}
	}
}

