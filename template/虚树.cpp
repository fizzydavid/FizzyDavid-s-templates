//by yjz
#include<bits/stdc++.h>
using namespace std;
#define FF first
#define SS second
#define PB push_back
#define MP make_pair
#define bged(v) (v).begin(),(v).end()
#define foreach(it,s) for(__typeof((s).begin()) it=(s).begin();it!=(s).end();it++)
typedef long long ll;
const int Imx=2147483647;
const ll Lbig=2e18;
const int mod=1e9+7;
//My i/o stream
struct fastio
{
	char s[100000];
	int it,len;
	fastio(){it=len=0;}
	inline char get()
	{
		if(it<len)return s[it++];it=0;
		len=fread(s,1,100000,stdin);
		if(len==0)return EOF;else return s[it++];
	}
	bool notend()
	{
		char c=get();
		while(c==' '||c=='\n')c=get();
		if(it>0)it--;
		return c!=EOF;
	}
}_buff;
#define geti(x) x=getnum()
#define getii(x,y) geti(x),geti(y)
#define getiii(x,y,z) getii(x,y),geti(z)
#define puti(x) putnum(x),putchar(' ')
#define putii(x,y) puti(x),puti(y)
#define putiii(x,y,z) putii(x,y),puti(z)
#define putsi(x) putnum(x),putchar('\n')
#define putsii(x,y) puti(x),putsi(y)
#define putsiii(x,y,z) putii(x,y),putsi(z)
inline ll getnum()
{
	ll r=0;bool ng=0;char c;c=_buff.get();
	while(c!='-'&&(c<'0'||c>'9'))c=_buff.get();
	if(c=='-')ng=1,c=_buff.get();
	while(c>='0'&&c<='9')r=r*10+c-'0',c=_buff.get();
	return ng?-r:r;
}
template<class T> inline void putnum(T x)
{
	if(x<0)putchar('-'),x=-x;
	register short a[20]={},sz=0;
	while(x)a[sz++]=x%10,x/=10;
	if(sz==0)putchar('0');
	for(int i=sz-1;i>=0;i--)putchar('0'+a[i]);
}
inline char getreal(){char c=_buff.get();while(c==' '||c=='\n')c=_buff.get();return c;}
int n;
const int mxn=250111;
struct newtree
{
	int a[mxn],tot;
	bool hs[mxn];
	int head[mxn],nxt[mxn*2],to[mxn*2],ew[mxn*2],etot;
	newtree()
	{
		tot=0;etot=1;
		memset(head,0,sizeof(head));
		memset(hs,0,sizeof(hs));
		memset(mk,0,sizeof(mk));
	}
	bool mk[mxn];
	void clear()
	{
		for(int i=1;i<=tot;i++)head[a[i]]=hs[a[i]]=mk[a[i]]=0;
		etot=1;
		tot=0;
	}
	void add(int x){if(!hs[x])hs[x]=1,a[++tot]=x;}
	void addedge(int x,int y,int w)
	{
//		cerr<<"add:"<<x<<" "<<y<<" "<<w<<" "<<etot<<endl;
		add(x);add(y);
		nxt[++etot]=head[y];
		head[y]=etot;
		to[etot]=x;
		ew[etot]=w;
	}
	void mark(int x){mk[x]=1;}
	ll dp[mxn];
	void dfs(int x)
	{
//		cerr<<"dfs:"<<x<<" "<<mk[x]<<endl;
		dp[x]=0;
		for(int i=head[x];i;i=nxt[i])
		{
			dfs(to[i]);
			if(mk[to[i]])dp[x]+=ew[i];
			else dp[x]+=min(ll(ew[i]),dp[to[i]]);
		}
	}
	ll solve()
	{
		dfs(1);
		return dp[1];
	}
	void out()
	{
		cerr<<"tot="<<tot<<endl;
		for(int i=1;i<=tot;i++)cout<<a[i]<<" ";cout<<endl;
	}
}key;//Many thanks to key for a lot of excellent works
int head[mxn],nxt[mxn*2],to[mxn*2],ew[mxn*2],etot=1;
void addedge(int x,int y,int w)
{
	nxt[++etot]=head[x];
	head[x]=etot;
	to[etot]=y;
	ew[etot]=w;
}
int lv[mxn],p[20][mxn],pmn[20][mxn],dfn[mxn],dfntot;
void dfs(int x)
{
	dfn[x]=++dfntot;
	for(int i=head[x];i;i=nxt[i])
	{
		if(to[i]==p[0][x])continue;
		lv[to[i]]=lv[x]+1;
		p[0][to[i]]=x;
		pmn[0][to[i]]=ew[i];
		dfs(to[i]);
	}
}
int getlca(int x,int y)
{
	if(lv[x]>lv[y])swap(x,y);
	for(int i=19;i>=0;i--)
		if((1<<i)<=lv[y]-lv[x])
			y=p[i][y];
	if(x==y)return y;
	for(int i=19;i>=0;i--)
		if(p[i][x]!=p[i][y])
			x=p[i][x],y=p[i][y];
	return p[0][x];
}
int getmn(int x,int y)//x to y
{
	int ret=Imx;
	for(int i=19;i>=0;i--)
	{
		if((1<<i)<=lv[x]-lv[y])
		{
			ret=min(ret,pmn[i][x]);
			x=p[i][x];
		}
	}
	return ret;
}
int a[mxn];
int st[mxn],stsz;
bool cmp(int x,int y){return dfn[x]<dfn[y];}
void adde(int x,int y){key.addedge(x,y,getmn(x,y));}
void popst()
{
	adde(st[stsz-1],st[stsz-2]);
	stsz--;
}
void buildtree(int m)
{
	key.clear();
	sort(a+1,a+m+1,cmp);
	stsz=0;
	st[stsz++]=1;
	for(int i=1;i<=m;i++)
	{
		int p=getlca(st[stsz-1],a[i]);
		while(stsz>1&&lv[st[stsz-2]]>lv[p])popst();
		if(lv[st[stsz-1]]>lv[p])adde(st[stsz-1],p),stsz--;
		if(st[stsz-1]!=p)st[stsz++]=p;
		if(st[stsz-1]!=a[i])st[stsz++]=a[i];
	}
	while(stsz>1)popst();
}
int main()
{
	geti(n);
	for(int i=1;i<n;i++)
	{
		int x,y,w;
		getiii(x,y,w);
		addedge(x,y,w);
		addedge(y,x,w);
	}
	lv[1]=1;
	dfs(1);
	for(int i=1;i<20;i++)
	{
		for(int j=1;j<=n;j++)
		{
			p[i][j]=p[i-1][p[i-1][j]];
			pmn[i][j]=min(pmn[i-1][j],pmn[i-1][p[i-1][j]]);
		}
	}
	int q;
	geti(q);
	while(q--)
	{
		int m;
		geti(m);
		for(int i=1;i<=m;i++)geti(a[i]);
		buildtree(m);
//		key.out();
		for(int i=1;i<=m;i++)key.mark(a[i]);
		ll ans=key.solve();
		putsi(ans);
	}
	return 0;
}
