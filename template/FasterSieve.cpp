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
const int prmxn=1e6;
bool np[prmxn];
int pr[prmxn/10],prtot;
void precalc_prtab()
{
	prtot=0;
	np[1]=1;
	for(int i=2;i<prmxn;i++)
	{
		if(!np[i])
		{
			pr[++prtot]=i;
		}
		for(int j=1;j<=prtot&&i*pr[j]<prmxn;j++)
		{
			np[i*pr[j]]=1;
			if(i%pr[j]==0)break;
		}
	}
}

ll N,n;
int m;
const int mxn2=5e5;
ll F[mxn2],F0[mxn2],F1[mxn2],Fs0[mxn2],Fs1[mxn2];
void calc_prpowersum(int k)
{
	for(int i=1;i<=n;i++)F0[i]=i;
	for(int i=1;i<=n;i++)F1[i]=N/i;
	for(int i=1;i<=m;i++)
	{
		ll lim=1ll*pr[i]*pr[i];
		for(int j=1;j<=n;j++)
		{
			ll j2=N/j,nj=j*pr[i];
			if(lim>j2)break;
			if(nj<=n)F1[j]=F1[j]-(F1[nj]-F0[pr[i]-1]);
			else nj=j2/pr[i],F1[j]=F1[j]-(F0[nj]-F0[pr[i]-1]);
		}
		for(int j=n;j>=lim;j--)
		{
			int nj=j/pr[i];
			F0[j]=F0[j]-(F0[nj]-F0[pr[i]-1]);
		}
	}
	for(int i=1;i<=n;i++)F0[i]--,F1[i]--;
}
ll query(ll x,int p)
{
	ll ret=1;
	ret+=(x<=n?Fs0[x]:Fs1[N/x])-Fs0[pr[p-1]];
	for(int i=p;1ll*pr[i]*pr[i]<=x;i++)
	{
		for(ll pw=pr[i],c=1;pw<=x;pw*=pr[i],c++)
		{
			ret+=(3*c+1)*((pr[i+1]<=x/pw?query(x/pw,i+1):1)-(c==1));
		}
	}
	return ret;
}
void prefixsum_init(ll x)
{
	N=x;
	n=ll(sqrt(N));while(1ll*(n+1)*(n+1)<=N)n++;
	assert(n<mxn2);
	m=0;while(pr[m+1]<=n)m++;
	calc_prpowersum(0);
	for(int i=1;i<=n;i++)Fs1[i]=F1[i]*4,Fs0[i]=F0[i]*4;
}
int main()
{
	precalc_prtab();
	int Tn;
	geti(Tn);
	Tn=1;
	while(Tn--)
	{
		ll x;
		geti(x);
		prefixsum_init(x);
		ll ans=query(x,1);
		putsi(ans);
	}
	return 0;
}

