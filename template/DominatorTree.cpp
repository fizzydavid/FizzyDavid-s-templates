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
const int mxn=100111;
const int mxm=500111;
int n,m,rt;
int head[mxn],nxt[mxm],to[mxm],tot;
vector<int> rcon[mxn],sch[mxn];
void adde(int x,int y)
{
	nxt[++tot]=head[x];
	head[x]=tot;
	to[tot]=y;
}
int par[mxn],dfn[mxn],dtot,idom[mxn],sdom[mxn],arr[mxn];
void predfs(int x)
{
	dfn[x]=++dtot;arr[dtot]=x;
	for(int i=head[x];i;i=nxt[i])
	{
		int u=to[i];
		if(!dfn[u])
		{
			predfs(u);
			par[dfn[u]]=dfn[x];
		}
		rcon[dfn[u]].PB(dfn[x]);
	}
}
int f[mxn],fmn[mxn];
int gf(int x)
{
	if(f[x]==x)return x;
	int y=f[x];if(gf(y)==y)return y;
	if(sdom[fmn[y]]<sdom[fmn[x]])fmn[x]=fmn[y];
	return f[x]=f[y];
}
vector<int> dt[mxn];
int main()
{
	getii(n,m);
	rt=1;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		getii(x,y);
		adde(x,y);
	}
	predfs(rt);
	for(int i=1;i<=dtot;i++)f[i]=fmn[i]=sdom[i]=i;
	for(int i=dtot;i>=1;i--)
	{
		for(int j=0;j<rcon[i].size();j++)
		{
			int u=rcon[i][j];gf(u);
			sdom[i]=min(sdom[i],sdom[fmn[u]]);
		}
		if(i>1)sch[sdom[i]].PB(i);
		for(int j=0;j<sch[i].size();j++)
		{
			int u=sch[i][j];gf(u);
			if(sdom[fmn[u]]==sdom[u])idom[u]=i;
			else idom[u]=fmn[u]; 
		}
		f[i]=par[i];
	}
	for(int i=2;i<=dtot;i++)
	{
		if(idom[i]!=sdom[i])idom[i]=idom[idom[i]];
		dt[idom[i]].PB(i);
	}
	return 0;
}

