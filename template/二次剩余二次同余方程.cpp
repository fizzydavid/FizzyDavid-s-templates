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



ll qpow(ll x,ll k,ll md){return k==0?1:qpow(x*x%md,k>>1,md)*(k&1?x:1)%md;}
ll legendre(ll p,ll q){return qpow(p,(q-1)>>1,q);}
pair<ll,ll> merge(pair<ll,ll> x,pair<ll,ll> y,ll w,ll md)
{
	return MP((x.FF*y.FF+x.SS*y.SS%md*w)%md,(x.FF*y.SS+x.SS*y.FF)%md);
}
ll cipolla(ll a,ll md)
{
	a%=md;if(a==0)return 0;
	if(legendre(a,md)!=1)return -1;
	while(true)
	{
		ll r=rand()%(md-1)+1,w=((1ll*r*r-a)%md+md)%md,k=(md+1)>>1;
		pair<ll,ll> t=MP(r,1),ans=MP(1,0);
		while(k)
		{
			if(k&1)ans=merge(ans,t,w,md);
			t=merge(t,t,w,md);
			k>>=1;
		}
		if(1ll*ans.FF*ans.FF%md==a)return min(md-ans.FF,ans.FF);
	}
}
ll solve_sqrt(ll a,ll p,ll k)//a<p^k
{
	if(a==0)return 0;
	ll coef=1;bool flag=0;
	while(a%p==0)
	{
		a/=p;assert((--k)>0);
		if(!flag)flag=1;else flag=0,coef*=p;
	}
	if(flag)return -1;
	if(p==2)
	{
		if(a%8!=1)return -1;
		if(k<=3)return 1*coef;
		ll X0=1,X1=3,md=8;
		for(int i=3;i<k;i++)
		{
			ll nmd=md+md;
			if(X0*X0%nmd==a%nmd)X1=md-X0;
			else X0=md-X1;
			md=nmd;
		}
		assert(1ll*X0*X0%md==a&&1ll*X1*X1%md==a);
		return min(X0,X1)*coef;
	}
	else
	{
		ll x=cipolla(a,p),md=p;
		if(x==-1)return -1;
		for(int i=1;i<k;i++)
		{
			ll nmd=md*p;
			ll t=(p-((1ll*x*x-a)%nmd)/md)%p;
			x=(x+t*qpow(2*x%p,p-2,p)%p*md)%nmd;
			md=nmd;
		}
		assert(1ll*x*x%md==a%md);
		return min(md-x,x)*coef;
	}
}
pair<ll,ll> extgcd(ll x,ll y)
{
	if(y==0)return MP(1,0);
	pair<ll,ll> ret=extgcd(y,x%y);
	return MP(ret.SS,ret.FF-ret.SS*(x/y));
}
pair<ll,ll> merge_congruence(pair<ll,ll> A,pair<ll,ll> B)
{
	if(A.FF==-1||B.FF==-1)return MP(-1,-1);
	ll g=__gcd(A.SS,B.SS);
	ll md=A.SS/g*B.SS;
	if((A.FF-B.FF)%g!=0)return MP(-1,-1);
	ll p=extgcd(A.SS,B.SS).FF*((-A.FF+B.FF)/g)%md;
	return MP(((p*A.SS+A.FF)%md+md)%md,md);
}
ll solve_sqrt(ll a,ll m)//O(sqrt(m))  init to O(log^2(m))
{
	pair<ll,ll> ret=MP(0,1);
	ll x=m;
	for(int i=2;i<=x;i++)
	{
		i=x/(x/i);
		if(x%i==0)
		{
			ll pk=0,md=1;
			while(x%i==0)x/=i,pk++,md*=i;
			ll cur=solve_sqrt(a%md,i,pk);
			ret=merge_congruence(ret,MP(cur,md));
		}
	}
	return ret.FF;
}
ll solve_quadratic(ll a,ll b,ll c,ll m)//(2a,m)=1
{
	assert(__gcd(2*a,m)==1);
	ll delta=((b*b-4*a*c)%m+m)%m;
	ll s=solve_sqrt(delta,m);
	if(s==-1)return -1;
	return ((s-b)*extgcd(2*a,m).FF%m+m)%m;
}




//---------test----------
ll tsqrt[1000111];
void test(int m)
{
	cerr<<"test:"<<m<<endl;
	for(int i=0;i<m;i++)tsqrt[i]=-1;
	for(int i=0;i<m;i++)tsqrt[1ll*i*i%m]=i;
	for(int i=0;i<m;i++)
	{
		int x=solve_sqrt(i,m);
		if(x==-1)
		{
			if(tsqrt[i]!=-1)
			{
				cout<<"WA "<<i<<","<<m<<endl;
				exit(1);
			}
		}
		else if(1ll*x*x%m!=i)
		{
			cout<<"WA "<<i<<","<<m<<"  "<<x<<endl;
			exit(2);
		}
		
	}
}
void test2(int m)
{
	cerr<<"test2:"<<m<<endl;
	for(int i=0;i<1000;i++)
	{
		int x=(rand()<<15|rand())%m;
		ll t=1ll*x*x%m;
		int ans=solve_sqrt(t,m);
		if(ans==-1)
		{
			cout<<"WA "<<i<<","<<m<<endl;
			exit(1);
		}
		else if(1ll*ans*ans%m!=t)
		{
			cout<<"WA "<<i<<","<<m<<" "<<ans<<endl;
			exit(2);
		}
	}
}
int main()
{
	cout<<cipolla(73,127)<<endl;
	cout<<solve_sqrt(9,2,5)<<endl;
	cout<<solve_sqrt(889,2,10)<<endl;
	cout<<solve_sqrt(8*rand()+1,2,29)<<endl;
	cout<<solve_sqrt(7,3,2)<<endl;
	cout<<solve_sqrt(13,3,3)<<endl;
	cout<<solve_sqrt(233,101,4)<<endl;
	cout<<solve_sqrt(7*3*3*3*3,3,6)<<endl;
	cout<<solve_sqrt(4272943-286,4272943,1)<<endl;
	cout<<solve_sqrt(4272943-286,4272943)<<endl;
	cout<<solve_sqrt(13333,123456789)<<endl;
	
	cout<<solve_quadratic(2,3,3,17)<<endl;
	return 0;
	/*
	//test 1
	for(int m=1;m<=2333;m++)
	{
		test(m);
	}
	*/
	//test 2
	for(int i=0;i<=1000;i++)
	{
		int m=rand()<<15|rand();
		test2(m);
	}
	return 0;
}

