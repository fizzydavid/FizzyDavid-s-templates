//by yjz
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FF first
#define SS second
#define MP make_pair
#define PB push_back
ll rdown(ll p,ll q)
{
	return q<0?rdown(-p,-q):(p>=0?p/q:-((-p+q-1)/q));
}
ll f_bf(ll a,ll b,ll c,ll n)
{
	ll ret=0;
	for(int i=0;i<=n;i++)ret+=rdown(1ll*a*i+b,c);
	return ret;
}
ll f(ll a,ll b,ll c,ll n)
{
	if(n<0)return 0;
	if(c<0)c=-c,a=-a,b=-b;
	ll ans=1ll*n*(n+1)/2*rdown(a,c)+rdown(b,c)*(n+1);
	a=(a%c+c)%c;b=(b%c+c)%c;
	if(n==0)return ans+rdown(b,c);
	if(a==0)return ans+rdown(b,c)*(n+1);
	ll m=rdown(a*n+b-c+1,c);
	return ans+n*(m+1)-f(c,c-b-1,a,m);
}

int main()
{
	while(true)
	{
		ll a=rand()-16384;
		ll b=rand()-16384;
		ll c=rand()-16384;
		ll n=rand();
		ll ans1=f(a,b,c,n);
		ll ans2=f_bf(a,b,c,n);
		if(ans1!=ans2)
		{
			cerr<<"WA"<<endl;
			cerr<<a<<" "<<b<<" "<<c<<" "<<n<<endl;
			return 0;
		}
	}
	return 0;
}
