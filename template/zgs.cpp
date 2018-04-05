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
const int prmxn=1e7;
bool np[prmxn];
int pr[prmxn/10],prtot;
int phi[prmxn],mu[prmxn];
void precalc_prtab()
{
	prtot=0;
	np[1]=1;phi[1]=mu[1]=1;
	for(int i=2;i<prmxn;i++)
	{
		if(!np[i])
		{
			pr[++prtot]=i;
			mu[i]=-1;
			phi[i]=i-1;
		}
		for(int j=1;j<=prtot&&i*pr[j]<prmxn;j++)
		{
			np[i*pr[j]]=1;
			if(i%pr[j]==0)
			{
				mu[i*pr[j]]=0;
				phi[i*pr[j]]=phi[i]*pr[j];
				break;
			}
			else
			{
				mu[i*pr[j]]=-mu[i];
				phi[i*pr[j]]=phi[i]*(pr[j]-1);
			}
		}
	}
}
ll N,n;
int m;
const int mxn2=5e5;
ll F0[mxn2],F1[mxn2],G0[mxn2],G1[mxn2];
int lz0[mxn2],lz1[mxn2],cntp[mxn2];
ll ppw[2][mxn2],pres[mxn2];
ll powersum(ll n,int k)
{
	n%=mod;
	if(k==0)return n;
	if(k==1)return (n*(n+1)/2)%mod;
	assert(false);
}
void zgs_part1(int k)
{
	for(int i=1;i<=m;i++)pres[i]=(ppw[k][i]+pres[i-1])%mod;
	for(int i=1;i<=n;i++)F0[i]=powersum(i,k),lz0[i]=0;
	for(int i=1;i<=n;i++)F1[i]=powersum(N/i,k),lz1[i]=0;
	for(int i=1;i<=m;i++)
	{
		ll lim=1ll*pr[i]*pr[i];
		for(int j=1;j<=n;j++)
		{
			ll j2=N/j,nj=j*pr[i];
			if(lim>j2)break;
			if(nj<=n)F1[j]=(F1[j]-(F1[nj]-(pres[i-1]-pres[lz1[nj]]))*ppw[k][i])%mod;
			else nj=j2/pr[i],F1[j]=(F1[j]-(F0[nj]-(pres[i-1]-pres[lz0[nj]]))*ppw[k][i])%mod,assert(i-1<=cntp[nj]);
			lz1[j]=i;
		}
		for(int j=n;j>=lim;j--)
		{
			int nj=j/pr[i];
			F0[j]=(F0[j]-(F0[nj]-(pres[i-1]-pres[lz0[nj]]))*ppw[k][i])%mod;
			lz0[j]=i;
		}
	}
	for(int j=1;j<=n;j++)F1[j]=((F1[j]-(pres[m]-pres[lz1[j]])-1)%mod+mod)%mod;
	for(int j=1;j<=n;j++)F0[j]=((F0[j]-(pres[cntp[j]]-pres[lz0[j]])-1)%mod+mod)%mod;
}
#define calcf(p) (p-1)
void zgs_part2()
{
	for(int i=1;i<=m;i++)pres[i]=(pres[i-1]+calcf(pr[i]))%mod;
	for(int i=1;i<=n;i++)lz1[i]=lz0[i]=0;
	for(int i=m;i>=1;i--)
	{
		ll lim=1ll*pr[i]*pr[i];
		for(int j=1;j<=n;j++)
		{
			ll j2=N/j,nj=1ll*j*pr[i],nj2=j2/pr[i],pw=1;
			if(lim>j2)break;
			if(!lz1[j])G1[j]=pres[m]-pres[i]+1,lz1[j]=1;
			for(int c=1;nj2;c++,nj*=pr[i],nj2/=pr[i],pw*=pr[i])
			{
				if(nj<=n)G1[j]=(G1[j]+(lz1[nj]?G1[nj]:pres[m]-pres[i]+1)*((pw*(pr[i]-1))%mod))%mod;
				else G1[j]=(G1[j]+(lz0[nj2]?G0[nj2]:pres[max(i,cntp[nj2])]-pres[i]+1)*((pw*(pr[i]-1))%mod))%mod;
			}
		}
		for(int j=n;j>=lim;j--)
		{
			int nj=j/pr[i],pw=1;
			if(!lz0[j])G0[j]=pres[cntp[j]]-pres[i]+1,lz0[j]=1;
			for(int c=1;nj;c++,nj/=pr[i],pw*=pr[i])G0[j]=(G0[j]+(lz0[nj]?G0[nj]:pres[max(i,cntp[nj])]-pres[i]+1)*(pw*(pr[i]-1)))%mod;
		}
	}
	for(int j=1;j<=n;j++)if(!lz0[j])G0[j]=pres[cntp[j]]+1;
	for(int j=1;j<=n;j++)if(!lz1[j])G1[j]=pres[m]+1;
}
ll Fs[mxn2];
ll zgs_query2(ll nn2)
{
	ll nn=N/nn2;
	ll ret=0;
	ll pre=0;
	for(ll i=1;i<=nn;i++)
	{
		ll i2=nn/i;
		i=nn/i2;
		ll cur;
		if(i<=n)cur=G0[i];
		else cur=G1[N/i];
		if(i2>n)ret+=(cur-pre)*(Fs[N/i2]+1)%mod;
		else ret+=cur-pre;
		pre=cur;
	}
	ret=(ret%mod+mod)%mod;
	return ret;
}
const int mxk=1;
void zgs_init(ll x)
{
	cerr<<"####zgs_init:"<<endl;
	N=x;
	n=ll(sqrt(N));
	while(1ll*(n+1)*(n+1)<=N)n++;
	cerr<<"n="<<n<<endl;
	assert(n<mxn2);
	m=0;
	while(pr[m+1]<=n)m++;
	cerr<<"m="<<m<<endl;
	for(int i=1;i<=n;i++)
	{
		cntp[i]=cntp[i-1];
		while(pr[cntp[i]+1]<=i)cntp[i]++;
	}
	for(int i=1;i<=n;i++)
	{
		ppw[0][i]=1;
		for(int j=1;j<=mxk;j++)ppw[j][i]=ppw[j-1][i]*pr[i]%mod;
	}
	cerr<<"###zgs_part1:"<<endl;
	zgs_part1(0);
//	cerr<<"F1:"<<endl;
//	for(int i=1;i<=n;i++)cerr<<F1[i]<<" ";cerr<<endl;
	for(int i=1;i<=n;i++)Fs[i]=-F1[i];
	zgs_part1(1);
//	cerr<<"F1:"<<endl;
//	for(int i=1;i<=n;i++)cerr<<F1[i]<<" ";cerr<<endl;
	for(int i=1;i<=n;i++)Fs[i]=(Fs[i]+F1[i])%mod;
//	cerr<<"Fs:"<<endl;
//	for(int i=1;i<=n;i++)cerr<<Fs[i]<<" ";cerr<<endl;
	cerr<<"###zgs_part2:"<<endl;
	zgs_part2();
//	cerr<<"G1:"<<endl;
//	for(int i=1;i<=n;i++)cerr<<G1[i]<<" ";cerr<<endl;
//	cerr<<"G0:"<<endl;
//	for(int i=1;i<=n;i++)cerr<<G0[i]<<" ";cerr<<endl;	
}

int main()
{
	precalc_prtab();
	while(true)
	{
		ll x;
		cin>>x;
		zgs_init(x);
		cout<<zgs_query2(1)<<endl;
	}
	return 0;
}

