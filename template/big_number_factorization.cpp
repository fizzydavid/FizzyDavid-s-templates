//by yjz
#include<bits/stdc++.h>
using namespace std;
#define FF first
#define SS second
#define PB push_back
#define MP make_pair
typedef long long ll;
const int Imx=2147483647;
const ll Lbig=2e18;
const int mod=1e9+7;
namespace FAC
{
	const bool bign=1;//if n >= int_max
	ll kissmul(ll x,ll y,ll md)
	{
		ll tmp=x*y-ll((long double)1.0*x/md*y+1e-8)*md;
		while(tmp<0)tmp+=md;
		while(tmp>=md)tmp-=md;
		return tmp;
	}
	int kissme(int x,int k,int md){return k==0?1:1ll*kissme(1ll*x*x%md,k>>1,md)*(k&1?x:1)%md;}
	ll kissme2(ll x,ll k,ll md){return k==0?1:kissmul(kissme2(kissmul(x,x,md),k>>1,md),(k&1?x:1),md);}
	bool notp[1000111];
	ll fp[1000111];
	bool millerrabin(int d,ll k,ll n,ll a)
	{
		ll x=bign?kissme2(a,k,n):kissme(a,k,n);
		if(x==1)return true;
		for(int i=0;i<d;i++)
		{
			if(x==n-1)return true;
			x=bign?kissmul(x,x,n):x*x%n;
		}
		return false;
	}
	map<int,bool> prtab;
	bool is_prime(ll n)
	{
		if(n<=1000000)return !notp[n];
		if(!(n&1))return false;
		if(prtab.find(n)!=prtab.end())return prtab[n];
		prtab[n]=0;
		ll d=0,k=n-1;while(!(k&1))k>>=1,d++;
		int times=10;
		while(times--)if(!millerrabin(d,k,n,rand()+233))return false;
		prtab[n]=1;
		return true;
	}
	void init()
	{
		srand(time(NULL));
		notp[0]=notp[1]=1;
		for(int i=2;i<=1000000;i++)
		{
			if(notp[i])continue;
			for(int j=i+i;j<=1000000;j+=i)notp[j]=1,fp[j]=i;
		}
	}
	pair<ll,int> fac[100];
	int facsz;
	ll findfac(ll n,ll a,ll b)
	{
		ll px=a,x=a,d=1;
		for(int k=1;d==1;k<<=1)
		{
			int tk=k;
			while(d==1&&tk>0)
			{
				x=((bign?kissmul(x,x,n):x*x)+b)%n;
				d=__gcd(abs(x-px),n);
				tk--;
			}
			px=x;
		}
		return d;
	}
	void pollard_rho(ll n,int coef=1)
	{
		if(n<=1)return;
	//	cerr<<"pollard_rho:"<<n<<","<<coef<<endl;
		if(is_prime(n))
		{
			fac[facsz++]=MP(n,coef);
			return;
		}
		ll p;
		if(n<=1000000)p=fp[n];
		else
		{
			while((p=findfac(n,rand()%n,rand()%(n-1)+1))==n);
		}
		int tcnt=0;
		while(n%p==0)n/=p,tcnt+=coef;
		pollard_rho(p,tcnt);pollard_rho(n,coef);
	}
	bool primeans(ll x)
	{
		for(int i=2;1ll*i*i<=x;i++)
		{
			if(x%i==0)return false;
		}
		return true;
	}
	void standardize()
	{
		sort(fac,fac+facsz);
		int nn=0;
		pair<ll,int> pre=MP(0,0);
		for(int i=0;i<facsz;i++)
		{
			if(fac[i].FF==pre.FF)pre.SS+=fac[i].SS;
			else
			{
				if(pre.FF)fac[nn++]=pre;
				pre=fac[i];
			}
		}
		if(pre.FF)fac[nn++]=pre;
		facsz=nn;
	}
	void factorize(ll x)
	{
		facsz=0;
		if(is_prime(x))
		{
			fac[facsz++]=MP(x,1);
			return;
		}
		else
		{
			pollard_rho(x);
			standardize();
		}
	}
};
int main()
{
	FAC::init();
	int tn=0,sum=0;
	while(true)
	{
		ll n;
		cin>>n;
//		n=rand()<<15|rand();
//		sum+=is_prime(n);
//		cout<<sum<<endl;
		if(FAC::is_prime(n))
		{
			cout<<"true";
		}
		else cout<<"false";
		/*
		facsz=0;
		pollard_rho(n);
		standardize();
		for(int i=0;i<facsz;i++)cout<<fac[i].FF<<","<<fac[i].SS<<" ";cout<<endl;*/
	}
	return 0;
}
