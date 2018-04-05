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
int n,m;
vector<pair<int,ll> >con[300111],tcon[300111];
bool tmpf[300111];
int tmpcnt;
void tmpdfs(int x)
{
	tmpf[x]=1;tmpcnt++;
	for(int i=0;i<tcon[x].size();i++)
	{
		int u=tcon[x][i].FF;
		if(!tmpf[u])tmpdfs(u);
	}
}
vector<pair<int,ll> > newcon[300111];
int g[300111],pre[300111];
int gf(int x){return g[x]==x?x:g[x]=gf(g[x]);}
bool vis[300111],inst[300111],flag;
void dfs(int x)
{
	vis[x]=1;inst[x]=1;
	int u=gf(pre[x]);
	if(u&&u!=x)
	{
		if(!vis[u])dfs(u);
		else if(inst[u])
		{
			flag=1;
			int p=u;
			while(true)
			{
				g[gf(p)]=x;p=gf(pre[p]);
				if(p==x)break;
			}
			pre[x]=0;
		}
	}
	inst[x]=0;
}
ll solve(int rt)
{
	for(int i=1;i<=n;i++)g[i]=i,pre[i]=0;
	ll ans=0;
	while(true)
	{
		flag=0;
		for(int i=1;i<=n;i++)
		{
			vis[i]=0;
			if(gf(i)!=i||i==rt||pre[i])continue;
			ll mn=1ll*mod*mod;
			for(int j=0;j<con[i].size();j++)mn=min(mn,con[i][j].SS);
			ans+=mn;
			for(int j=0;j<con[i].size();j++)
			{
				con[i][j].SS-=mn;
				if(con[i][j].SS==0)pre[i]=con[i][j].FF;
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(gf(i)==i&&!vis[i])dfs(i);
			vector<pair<int,ll> >().swap(newcon[i]);
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<con[i].size();j++)
			{
				int u=con[i][j].FF;
				if(gf(u)!=gf(i))newcon[gf(i)].PB(con[i][j]);
			}
		}
		for(int i=1;i<=n;i++)swap(newcon[i],con[i]);
		if(!flag)return ans;
	}
}
int main()
{
	getii(n,m);
	for(int i=1;i<=m;i++)
	{
		int x,y,w;
		getiii(x,y,w);
		if(x==y)continue;//×¢Òâ×Ô»·£¡£¡£¡ 
		tcon[x].PB(MP(y,w));
		con[y].PB(MP(x,w));
	}
	tmpdfs(1);
	if(tmpcnt<n)
	{
		puts("NO");
		return 0;
	}
	puts("YES");
	cout<<solve(1)<<endl;
	return 0;
}
