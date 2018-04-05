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
typedef unsigned long long ull;
const int mod=998244353;
ll qpow(ll x,ll k){return k==0?1:qpow(x*x%mod,k>>1)*(k&1?x:1)%mod;}

const int comb_mx=200111;
ll inv[comb_mx],fac[comb_mx],ifac[comb_mx];
void comb_init()//mod should be prime
{
	fac[0]=1;
	for(int i=1;i<comb_mx;i++)fac[i]=fac[i-1]*i%mod;
	ifac[comb_mx-1]=qpow(fac[comb_mx-1],mod-2);
	for(int i=comb_mx-2;i>=0;i--)ifac[i]=ifac[i+1]*(i+1)%mod;
	inv[1]=1;
	for(int i=2;i<comb_mx;i++)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
}
//-----NTT head-----
const int proot=3;
const int FFTbitn=18;
const int FFTmx=(1<<FFTbitn)+111;
const int FFTpmx=1<<FFTbitn;
int fsz;
int w_pre[FFTmx];
int w[FFTmx];
void FFTinit(int sz)
{
	fsz=1;
	while(fsz<sz)fsz<<=1;
	assert(fsz<=FFTpmx);
}
inline void FFT(int a[],int coef)
{
	static ull f_a[FFTmx];
	for(int i=0,j=0;i<fsz;i++)
	{
		f_a[j]=a[i];
		for(int l=fsz>>1;(j^=l)<l;l>>=1);
	}
	ull mxmd=1ll*mod*mod;
	for(int l=1;l<fsz;l<<=1)
	{
		int l2=l<<1,u=FFTpmx/l2;
		if(coef==1)for(int j=0,j2=0;j<l;j++,j2+=u)w[j]=w_pre[j2];
		else for(int j=0,j2=FFTpmx;j<l;j++,j2-=u)w[j]=w_pre[j2];
		for(int i=0;i<fsz;i+=l2)
		{
			for(int j=0;j<l;j++)
			{
				ull tmp=f_a[i+j+l]%mod*w[j];
				f_a[i+j+l]=f_a[i+j]+mxmd-tmp;
				f_a[i+j]+=tmp;
			}
		}
		if(l==(1<<18))for(int j=0;j<fsz;j++)f_a[j]%=mod;
	}
	for(int i=0;i<fsz;i++)a[i]=f_a[i]%mod;
	if(coef==-1)
	{
		int inv=qpow(fsz,mod-2);
		for(int i=0;i<fsz;i++)a[i]=1ll*a[i]*inv%mod;
	}
}
//you need to precalculate before using all the polynomial function!!!
void FFTprecalc()
{
	w_pre[0]=1;
	int ww=qpow(proot,(mod-1)/FFTpmx);
	for(int i=1;i<=FFTpmx;i++)w_pre[i]=1ll*w_pre[i-1]*ww%mod;
}
void polymul(int a[],int asz,int b[],int bsz,int c[],int csz=-1)
{
	static int mul_a[FFTmx],mul_b[FFTmx];
	if(csz==-1)csz=asz+bsz;
	if(asz+bsz<=150)
	{
		for(int i=0;i<asz+bsz;i++)mul_a[i]=0;
		for(int i=0;i<asz;i++)
		{
			for(int j=0;j<bsz;j++)
			{
				mul_a[i+j]=(mul_a[i+j]+1ll*a[i]*b[j])%mod;
			}
		}
		for(int i=0;i<csz;i++)c[i]=mul_a[i];
		return;
	}
	FFTinit(asz+bsz);
	for(int i=0;i<fsz;i++)mul_a[i]=i<asz?a[i]:0;
	for(int i=0;i<fsz;i++)mul_b[i]=i<bsz?b[i]:0;
	FFT(mul_a,1);
	FFT(mul_b,1);
	for(int i=0;i<fsz;i++)mul_a[i]=1ll*mul_a[i]*mul_b[i]%mod;
	FFT(mul_a,-1);
	for(int i=0;i<csz;i++)c[i]=mul_a[i];
}
//-----NTT head end-----

//-----FFT head-----
const double pi=acos(-1);
struct point
{
	double x,y;
	point(double _x=0,double _y=0){x=_x;y=_y;}
	point operator+(const point &t)const{return point(x+t.x,y+t.y);}
	point operator-(const point &t)const{return point(x-t.x,y-t.y);}
	point operator*(const point &t)const{return point(x*t.x-y*t.y,x*t.y+y*t.x);}
	point conj()const{return point(x,-y);}
};
const int FFTmx=400111;
const int FFTbitn=18;
const int FFTpmx=1<<FFTbitn;
const int FFTbit=15;//max_value<=2^(2*FFTbit)
int FFTsz,pbitrev[FFTmx],bitrev[FFTmx];
point _prew[FFTmx],_w[FFTmx];
void FFTprecalc()
{
	for(int i=0;i<=FFTpmx;i++)_prew[i]=point(cos(2.0/FFTpmx*i*pi),sin(2.0/FFTpmx*i*pi));
	for(int i=0,j=0;i<=FFTpmx;i++)
	{
		pbitrev[i]=j;
		for(int t=FFTpmx>>1;(j^=t)<t;t>>=1);
	}
}
void FFTinit(int n)
{
	FFTsz=1;
	while(FFTsz<n)FFTsz<<=1;
	int tmp=__builtin_ctz(FFTpmx/FFTsz);
	for(int i=0;i<FFTsz;i++)bitrev[i]=pbitrev[i]>>tmp;
}
void FFT(point a[],int coef)
{
	for(int i=0,j=0;i<FFTsz;i++)if(i<bitrev[i])swap(a[i],a[bitrev[i]]);
	for(int l=1,k=1;l<FFTsz;l<<=1,k++)
	{
		if(coef==1)for(int i=0;i<l;i++)_w[i]=_prew[(FFTpmx>>k)*i];
		else for(int i=0;i<l;i++)_w[i]=_prew[FFTpmx-(FFTpmx>>k)*i];
		for(int i=0;i<FFTsz;i+=l+l)
		{
			for(int j=0;j<l;j++)
			{
				point tmp=a[i+l+j]*_w[j];
				a[i+l+j]=a[i+j]-tmp;
				a[i+j]=a[i+j]+tmp;
			}
		}
	}
	if(coef==-1)
	{
		for(int i=0;i<FFTsz;i++)a[i]=a[i]*(1.0/FFTsz);
	}
}
void polymul(int a[],int asz,int b[],int bsz,int c[],int csz=-1)
{
	static point _tl[FFTmx],_tr[FFTmx],_ta[FFTmx],_tb[FFTmx];
	if(csz==-1)csz=asz+bsz;
	for(int i=0;i<asz;i++)a[i]=a[i]<0?a[i]+mod:a[i];
	for(int i=0;i<bsz;i++)b[i]=b[i]<0?b[i]+mod:b[i];
	FFTinit(asz+bsz);
	int msk=(1<<FFTbit)-1;
	for(int i=0;i<FFTsz;i++)
	{
		_ta[i]=i<asz?point(a[i]&msk,a[i]>>FFTbit):0;
		_tb[i]=i<bsz?point(b[i]&msk,b[i]>>FFTbit):0;
	}
	FFT(_ta,1);_ta[FFTsz]=_ta[0];
	FFT(_tb,1);_tb[FFTsz]=_tb[0];
	for(int i=0;i<FFTsz;i++)
	{
		point a0=(_ta[i]+_ta[FFTsz-i].conj())*point(+0.5,0),a1=(_ta[i]-_ta[FFTsz-i].conj())*point(0,-0.5);
		point b0=(_tb[i]+_tb[FFTsz-i].conj())*point(+0.5,0),b1=(_tb[i]-_tb[FFTsz-i].conj())*point(0,-0.5);
		_tl[i]=a0*b0+a0*b1*point(0,1);
		_tr[i]=a1*b0+a1*b1*point(0,1);
	}
	FFT(_tl,-1);
	FFT(_tr,-1);
	for(int i=0;i<FFTsz;i++)
	{
		c[i]=(ll(_tl[i].x+0.5)+
		    ((ll(_tr[i].y+0.5)%mod)<<FFTbit+FFTbit)+
	       (((ll(_tl[i].y+0.5)+ll(_tr[i].x+0.5))%mod)<<FFTbit))%mod;
	}
}

//-----FFT head end-----

int polyqpow(int a[],int n,int k,int m,int b[])
{
	static int pow_a[FFTmx],pow_b[FFTmx];
	copy(a,a+n,pow_b);
	pow_a[0]=1;
	int ansn=1;
	while(k>0)
	{
		if(k&1)
		{
			polymul(pow_a,ansn,pow_b,n,pow_a);
			ansn+=n;
			ansn=min(ansn,m);
		}
		polymul(pow_b,n,pow_b,n,pow_b);
		k>>=1;
		n<<=1;
		n=min(n,m);
	}
	for(int i=0;i<ansn;i++)b[i]=pow_a[i];
	return ansn;
}

void dotmul(int a[],int b[],int c[],int sz)
{
	for(int i=0;i<sz;i++)c[i]=1ll*a[i]*b[i]%mod;
}
void polyadd(int a[],int b[],int c[],int sz)
{
	for(int i=0;i<sz;i++)c[i]=(a[i]+b[i])%mod;
}
void polyaddinv(int a[],int sz)
{
	for(int i=0;i<sz;i++)a[i]=(mod-a[i])%mod;
}
void polysub(int a[],int b[],int c[],int sz)
{
	for(int i=0;i<sz;i++)c[i]=(a[i]-b[i]+mod)%mod;
}
void polyclear(int a[],int sz)
{
	for(int i=0;i<sz;i++)a[i]=0;
}
void polymulnum(int a[],int sz,int coef)
{
	for(int i=0;i<sz;i++)a[i]=1ll*a[i]*coef%mod;
}
int uptopow(int x)
{
	while(x!=(x&(-x)))x+=x&(-x);
	return x;
}
int uptopow(int a[],int n)
{
	int nn=uptopow(n);
	for(int i=n;i<nn;i++)a[i]=0;
	return nn;
}

int ta[FFTmx],tb[FFTmx],tc[FFTmx];
//a and b should be different  a[0] shouldn't be 0  n should be 2^k  need 1.5n space  use: ta
void polyinv(int a[],int n,int b[])
{
	assert(a!=b);
	polyclear(b,n);
	if(n==1)
	{
		assert(a[0]!=0);
		b[0]=qpow(a[0],mod-2);
		return;
	}
	polyinv(a,n>>1,b);
	polymul(b,n>>1,a,n,ta,n);
	polyaddinv(ta,n);
	ta[0]=(ta[0]+2)%mod;
	polymul(b,n>>1,ta,n,b,n);
}
void polydrv(int a[],int n,int b[])
{
	for(int i=1;i<n;i++)b[i-1]=1ll*a[i]*i%mod;
	b[n-1]=0;
}
void polyitg(int a[],int n,int b[])
{
	for(int i=n-2;i>=0;i--)b[i+1]=1ll*a[i]*inv[i+1]%mod;
	b[0]=0;
}
//b shouldn't be 0  size should be slightly greater than degree  need 2asz space  return size
int polydiv(int a[],int asz,int b[],int bsz,int c[])
{
	static int div_a[FFTmx],div_b[FFTmx];
	while(asz>0&&a[asz-1]==0)asz--;
	while(bsz>0&&b[bsz-1]==0)bsz--;
	if(asz<bsz)
	{
		c[0]=0;
		return 1;
	}
	for(int i=0;i<bsz;i++)div_b[i]=b[bsz-i-1];
	int csz=asz-bsz+1;
	int tsz=uptopow(div_b,csz);
	polyinv(div_b,tsz,div_a);
	for(int i=0;i<asz;i++)div_b[i]=a[asz-i-1];
	polymul(div_b,asz,div_a,csz,c,csz);
	for(int i=0;i<csz-i;i++)swap(c[i],c[csz-i-1]);
	return asz-bsz+1;
}
//b shouldn't be 0  size should be slightly greater than degree  need 2asz space  return size (of modulo)
int polymod(int a[],int asz,int b[],int bsz,int c[])
{
	static int mod_a[FFTmx];
	while(bsz>0&&b[bsz-1]==0)bsz--;
	if(asz<bsz)
	{
		copy(a,a+asz,c);
		return bsz;
	}
	int csz=polydiv(a,asz,b,bsz,mod_a);
	polymul(mod_a,csz,b,bsz,mod_a,asz);
	polysub(a,mod_a,c,bsz);
	return bsz;
}
//a[0] should be 1  a and b should be different  n should be 2^k  need 2n space  use: ta tb
void polyln(int a[],int n,int b[])
{
	assert(a!=b&&a[0]==1);
	polyclear(b,n);
	polyinv(a,n,tb);
	polydrv(a,n,ta);
	polymul(ta,n,tb,n,b,n);
	polyitg(b,n,b);
}
//a[0] should be 0  a and b should be different  n should be 2^k  need 2n space  use: ta tb
void polyexp(int a[],int n,int b[])
{
	static int ex_a[FFTmx],ex_b[FFTmx];
	polyclear(b,n);
	if(n==1)
	{
		b[0]=1;
		assert(a[0]==0);
		return;
	}
	polyexp(a,n>>1,b);
	polyln(b,n,ex_a);
	polysub(ex_a,a,ex_a,n);
	polymul(ex_a,n,b,n,ex_b,n);
	polysub(b,ex_b,b,n);
}
//solve x*x-a=0  x=x'-f(x')/f'(x')
//a[0] should be 1  n should be 2^k  need 2n space
void polysqrt(int a[],int n,int b[])
{
	static int sqrt_a[FFTmx],sqrt_b[FFTmx];
	polyclear(b,n);
	if(n==1)
	{
		b[0]=1;
		return;
	}
	polysqrt(a,n>>1,b);
	polymul(b,n>>1,b,n>>1,sqrt_a,n);
	polyadd(sqrt_a,a,sqrt_a,n);
	polyinv(b,n,sqrt_b);
	polymulnum(sqrt_b,n,qpow(2,mod-2));
	polymul(sqrt_a,n,sqrt_b,n,b,n);
}
//solve x'=1/2*a*x*x+1  r=exp(-itg(f'(x)))  x=itg((f(x')-f'(x')*x')*r)/r
//a and b should be different  n should be 2^k
void solve(int a[],int n,int b[])
{
	static int sl_a[FFTmx],sl_r[FFTmx];
	polyclear(b,n);
	if(n==1)
	{
		b[0]=0;
		return;
	}
	solve(a,n>>1,b);
	polymul(b,n>>1,a,n,sl_a,n);
	polymul(sl_a,n,b,n>>1,b,n);
	polyitg(sl_a,n,sl_a);
	polyaddinv(sl_a,n);
	polymulnum(b,n,qpow(2,mod-2));
	polyaddinv(b,n);
	polyexp(sl_a,n,sl_r);
	b[0]=(b[0]+1)%mod;
	polymul(b,n,sl_r,n,b,n);
	polyitg(b,n,b);
	polyinv(sl_r,n,sl_a);
	polymul(sl_a,n,b,n,b,n);
}
int ev_tab[FFTbitn][FFTmx<<1];
int ev_ta[FFTbitn][FFTmx<<1];
void eval_prework(int a[],int n)
{
	for(int i=0;(1<<i)<n;i++)
	{
		int l=1<<i;
		for(int j=0;j<n;j+=l)
		{
			if(i==0)
			{
				ev_tab[i][j<<1]=(mod-a[i])%mod;
				ev_tab[i][j<<1|1]=1;
			}
			else
			{
				polymulti(ev_tab[i-1]+(j<<1),l,ev_tab[i-1]+(j<<1)+l,l,ev_tab[i]+(j<<1));
			}
		}
	}
}
int ev_ans[FFTmx];
void polyeval(int a[],int n,int b[],int M,int c[])
{
	int m=uptopow(b,M);
	eval_prework(b,m);
	int t=0;
	while((1<<t)<m)t++;
	for(int i=t-1;i>=0;i--)
	{
		int l=1<<i;
		for(int j=0;j<n;j++)
		{
			polymod(a
		}
	}
}

int n,ans[FFTmx],coef_f[FFTmx];
int main()
{
	FFTprecalc();
	comb_init();
	geti(n);
	for(int i=0;i<n;i++)
	{
		char c=getreal();
		if(c=='1')coef_f[i]=qpow(fac[i],mod-2);
		else coef_f[i]=0;
	}
	solve(coef_f,uptopow(n+1),ans);
	for(int i=1;i<=n;i++)putsi(1ll*fac[i]*ans[i]%mod);
	return 0;
}
