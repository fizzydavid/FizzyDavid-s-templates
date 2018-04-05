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
inline char getreal(){char c=_buff.get();while(c<=32)c=_buff.get();return c;}
ll qpow(ll x,ll k){return k==0?1:1ll*qpow(1ll*x*x%mod,k>>1)*(k&1?x:1)%mod;}
int n1,n2;
ll w[2700][2700];
ll dp[2700][2700];
ll C[2700][2700];
ll s1[2700],s2[2700];
ll p1[2700],p2[2700];
int dfn1[2700],dfnr1[2700],dfn2[2700],dfnr2[2700],dtot1,dtot2;
vector<int> con1[2700],con2[2700];
void dfs1(int x)
{
	dfn1[x]=++dtot1;
	for(int i=0;i<con1[x].size();i++)
	{
		dfs1(con1[x][i]);
	}
	dfnr1[x]=dtot1;
}
void dfs2(int x)
{
	dfn2[x]=++dtot2;
	for(int i=0;i<con2[x].size();i++)
	{
		dfs2(con2[x][i]);
	}
	dfnr2[x]=dtot2;
}

int main()
{
	getii(n1,n2);
	for(int i=2;i<=n1;i++)geti(s1[i]);
	for(int i=2;i<=n2;i++)geti(s2[i]);
	for(int i=2;i<=n1;i++)
	{
		geti(p1[i]);
		con1[p1[i]].PB(i);
		s1[i]+=s1[p1[i]];
	}
	for(int i=2;i<=n2;i++)
	{
		geti(p2[i]);
		con2[p2[i]].PB(i);
		s2[i]+=s2[p2[i]];
	}
	dfs1(1);
	dfs2(1);
	for(int i=2;i<=n1;i++)
	{
		for(int j=2;j<=n2;j++)
		{
			geti(w[i][j]);
		}
	}
	for(int i=1;i<=n1;i++)for(int j=1;j<=n2;j++)
	{
		C[i][j]=-1ll*s1[i]*s1[i]-1ll*s2[j]*s2[j];
	}
	for(int i=n1;i>=1;i--)
	{
		for(int j=n2;j>=1;j--)
		{
			ll mx=0;
			for(int ni=n1;ni>i;ni--)
			{
				if(!(dfn1[i]<=dfn1[ni]&&dfnr1[ni]<=dfnr1[i]))continue;
				for(int nj=n2;nj>j;nj--)
				{
					if(!(dfn2[j]<=dfn2[nj]&&dfnr2[nj]<=dfnr2[j]))continue;
					mx=max(mx,dp[ni][nj]+C[p1[ni]][p2[nj]]+2ll*s1[i]*s1[p1[ni]]+
					                                       2ll*s2[j]*s2[p2[nj]]+C[i][j]);
					
				}
			}
			dp[i][j]=mx+w[i][j];
		}
	}
	cout<<dp[1][1]<<endl;
	return 0;
}

