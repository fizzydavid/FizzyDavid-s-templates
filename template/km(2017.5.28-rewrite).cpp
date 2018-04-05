//by yjz
#include<bits/stdc++.h>
using namespace std;
#define FF first
#define SS second
#define PB push_back
#define MP make_pair
typedef long long ll;
const int Imx=2147483647;
const int mod=1000000007;
const ll Lbig=2e18;
//My own input/output stream
#define geti(x) x=getnum()
#define getii(x,y) geti(x),geti(y)
#define getiii(x,y,z) getii(x,y),geti(z)
#define puti(x) putnum(x),putsp()
#define putii(x,y) puti(x),putnum(y),putsp()
#define putiii(x,y,z) putii(x,y),putnum(z),putsp()
#define putsi(x) putnum(x),putendl()
#define putsii(x,y) puti(x),putnum(y),putendl()
#define putsiii(x,y,z) putii(x,y),putnum(z),putendl()
inline ll getnum()
{
	register ll r=0;register bool ng=0;register char c;c=getchar();
	while(c!='-'&&(c<'0'||c>'9'))c=getchar();
	if(c=='-')ng=1,c=getchar();
	while(c>='0'&&c<='9')r=r*10+c-'0',c=getchar();
	if(ng)r=-r;return r;
}
template <class T> inline void putnum(T x)
{
	if(x<0)putchar('-'),x=-x;
	register short a[20]={},sz=0;
	while(x>0)a[sz++]=x%10,x/=10;
	if(sz==0)putchar('0');
	for(int i=sz-1;i>=0;i--)putchar('0'+a[i]);
}
inline void putsp(){putchar(' ');}
inline void putendl(){putchar('\n');}
inline char mygetchar(){register char c=getchar();while(c==' '||c=='\n')c=getchar();return c;}
struct KM
{
	int n,m,w[411][411],q[411],qn;
	int mx[411],my[411],mkx[411],mky[411],slk[411],lx[411],ly[411],pre[411];
	void Init(int N,int M)
	{
		n=N;m=max(N,M);
		memset(w,0,sizeof(w));
	}
	void addedge(int x,int y,int v)
	{
		w[x][y]=max(w[x][y],v);
	}
	#define qadd(x) mkx[x]=X,q[qn++]=x
	void findroute(int y)
	{
		int x,ny;
		while(y)
		{
			x=pre[y];
			ny=mx[x];
			mx[x]=y;
			my[y]=x;
			y=ny;
		}
	}
	void solve(int X)
	{
		memset(pre,0,sizeof(pre));
		for(int i=1;i<=m;i++)slk[i]=mod;
		qn=0;
		qadd(X);
		while(true)
		{
			for(int i=0;i<qn;i++)
			{
				int x=q[i];
				for(int y=1;y<=m;y++)
				{
					if(mky[y]==X)continue;
					if(lx[x]+ly[y]==w[x][y])
					{
						pre[y]=x;
						if(!my[y])
						{
							findroute(y);
							return;
						}
						mky[y]=X;
						qadd(my[y]);
					}
					else if(lx[x]+ly[y]-w[x][y]<slk[y])
					{
						pre[y]=x;
						slk[y]=lx[x]+ly[y]-w[x][y];
					}
				}
			}
			qn=0;
			int d=mod;
			for(int y=1;y<=m;y++)if(mky[y]!=X)d=min(d,slk[y]);
			for(int x=1;x<=n;x++)if(mkx[x]==X)lx[x]-=d;
			for(int y=1;y<=m;y++)
			{
				if(mky[y]==X)ly[y]+=d;
				else if(slk[y]!=mod)slk[y]-=d;
			}
			for(int y=1;y<=m;y++)
			{
				if(mky[y]!=X&&slk[y]==0)
				{
					if(!my[y])
					{
						findroute(y);
						return;
					}
					mky[y]=X;
					qadd(my[y]);
				}
			}
		}
	}
	ll solve()
	{
		memset(mx,0,sizeof(mx));
		memset(my,0,sizeof(my));
		memset(mkx,0,sizeof(mkx));
		memset(mky,0,sizeof(mky));
		memset(ly,0,sizeof(ly));
		for(int i=1;i<=n;i++)lx[i]=*max_element(w[i]+1,w[i]+1+m);
		for(int i=1;i<=n;i++)
		{
			solve(i);
/*			cout<<"bfs:"<<i<<endl;
			for(int j=1;j<=n;j++)cout<<mx[j]<<" ";cout<<endl;
			for(int j=1;j<=n;j++)cout<<my[j]<<" ";cout<<endl;
			for(int j=1;j<=n;j++)cout<<lx[j]<<" ";cout<<endl;
			for(int j=1;j<=n;j++)cout<<ly[j]<<" ";cout<<endl;*/
		}
		ll ans=0;
		for(int i=1;i<=n;i++)ans+=w[i][mx[i]];
		return ans;
	}
	void out()
	{
		for(int i=1;i<=n;i++)
		{
			if(w[i][mx[i]]==0)
			{
				puti(0);
			}
			else puti(mx[i]);
		}
		puts("");
	}
}graph;
int n,m,en;
int main()
{
	getiii(n,m,en);
	graph.Init(n,m);
	for(int i=1;i<=en;i++)
	{
		int x,y,v;
		getiii(x,y,v);
		graph.addedge(x,y,v);
	}
	ll cost=graph.solve();
	putsi(cost);
	graph.out();
	return 0;
}
