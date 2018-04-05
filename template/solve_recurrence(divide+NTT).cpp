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

const int mod=998244353;
const int proot=3;
const int FFTmx=300111;
const int FFTpmx=262144;
int bitrev_pre[FFTmx],bitrev[FFTmx],fsz;
int w_pre[FFTmx],w[FFTmx];
void FFTinit(int sz)
{
	fsz=1;
	while(fsz<sz)fsz<<=1;
	int tmp=__builtin_ctz(FFTpmx/fsz);
	for(int i=0;i<fsz;i++)bitrev[i]=bitrev_pre[i]>>tmp;
}
ll qpow(ll x,ll k){return k==0?1:qpow(x*x%mod,k>>1)*(k&1?x:1)%mod;}
void FFT(int a[],int coef)
{
	for(int i=0;i<fsz;i++)if(i<bitrev[i])swap(a[i],a[bitrev[i]]);
	for(int l=1;l<fsz;l<<=1)
	{
		int l2=l+l,u=FFTpmx/l2;
		if(coef==1)for(int j=0;j<l;j++)w[j]=w_pre[u*j];
		else for(int j=0;j<l;j++)w[j]=w_pre[FFTpmx-u*j];
		for(int i=0;i<fsz;i+=l2)
		{
			for(int j=0;j<l;j++)
			{
				int tmp=1ll*a[i+l+j]*w[j]%mod;
				a[i+l+j]=a[i+j]-tmp<0?a[i+j]-tmp+mod:a[i+j]-tmp;
				a[i+j]=a[i+j]+tmp>=mod?a[i+j]+tmp-mod:a[i+j]+tmp;
			}
		}
	}
	if(coef==-1)
	{
		ll inv=qpow(fsz,mod-2);
		for(int i=0;i<fsz;i++)a[i]=a[i]*inv%mod;
	}
}
void FFTprecalc()
{
	for(int i=1;i<FFTpmx;i++)bitrev_pre[i]=bitrev_pre[i>>1]>>1|(i&1?FFTpmx>>1:0);
	w_pre[0]=1;
	int ww=qpow(proot,(mod-1)/FFTpmx);
	for(int i=1;i<=FFTpmx;i++)w_pre[i]=1ll*w_pre[i-1]*ww%mod;
}
int ta[FFTmx],tb[FFTmx],tc[FFTmx];
void dotmul(int a[],int b[],int c[],int sz)
{
	for(int i=0;i<sz;i++)c[i]=1ll*a[i]*b[i]%mod;
}
void polymul(int a[],int asz,int b[],int bsz,int c[])
{
	FFTinit(asz+bsz);
	for(int i=0;i<fsz;i++)ta[i]=i<asz?a[i]:0;
	for(int i=0;i<fsz;i++)tb[i]=i<bsz?b[i]:0;
	FFT(ta,1);
	FFT(tb,1);
	dotmul(ta,tb,tc,fsz);
	FFT(tc,-1);
	for(int i=0;i<asz+bsz;i++)c[i]=tc[i];
}
void push(int a[],int asz,int b[],int bsz,int c[],int cl,int cr)
{
	polymul(a,asz,b,bsz,tc);
	assert(cr<=fsz);
	for(int i=cl;i<=cr;i++)c[i]=c[i]+tc[i]>=mod?c[i]+tc[i]-mod:c[i]+tc[i];
}

int n,f[FFTmx],g[FFTmx],coef_f[FFTmx],init_f[FFTmx];
//f[i]=sigma(f[j]*coef_f[i-j])+init_f[i]
void solve_recurrence(int l,int r)
{
	if(r-l<=300)
	{
		for(int i=l;i<=r;i++)
		{
			for(int j=l;j<i;j++)
			{
				f[i]=(f[i]+1ll*f[j]*coef_f[i-j])%mod;
			}
			f[i]=(f[i]+init_f[i])%mod;
		}
		return;
	}
	int m=l+r>>1;
	solve_recurrence(l,m);
	push(f+l,m+1-l,coef_f,r-l+1,f+l,m+1-l,r-l);
	solve_recurrence(m+1,r);
}

//f[i]=sigma(f[j]*g[i-j])+init_f[i]
//g[i]=i==0?0:f[i-1]
void solve_recurrence_online(int l,int r)
{
	if(r-l<=300)
	{
		if(l==0)
		{
			for(int i=l;i<=r;i++)
			{
				g[i]=i==0?0:f[i-1];
				for(int j=l;j<i;j++)
				{
					f[i]=(f[i]+1ll*f[j]*g[i-j])%mod;
				}
				f[i]=(f[i]+init_f[i])%mod;
			}
		}
		else
		{
			for(int i=l;i<=r;i++)
			{
				g[i]=i==0?0:f[i-1];
				for(int j=l;j<i;j++)
				{
					f[i]=(f[i]+1ll*f[j]*g[i-j])%mod;
				}
				for(int j=l;j<=r;j++)
				{
					f[i]=(f[i]+1ll*g[j]*f[i-j])%mod;
				}
				f[i]=(f[i]+init_f[i])%mod;
			}
		}
		return;
	}
	int m=l+r>>1;
	solve_recurrence_online(l,m);
	if(l==0)push(f,m+1,g,m+1,f,m+1,r);
	else
	{
		push(f+l,m+1-l,g,r+1-l,f+l,m+1-l,r-l);
		push(g+l,m+1-l,f,r+1-l,f+l,m+1-l,r-l);
	}
	solve_recurrence_online(m+1,r);
}

int main()
{
	FFTprecalc();
}
