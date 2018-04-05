const ll mod1=26214401;
const ll mod2=104857601;
const ll mod3=998244353;
const int proot=3;
ll kissme(ll x,ll k,ll mod)
{
	ll ans=1;
	while(k>0)
	{
		if(k&1)ans=ans*x%mod;
		x=x*x%mod;
		k>>=1;
	}
	return ans;
}
struct NTT
{
	int sz,mod,w[FFTmx];
	void init(int n)
	{
		sz=1;
		while(sz<2*n)sz<<=1;
		ll p=kissme(proot,(mod-1)/sz,mod);
		w[0]=1;
		for(int i=1;i<=sz;i++)
		{
			w[i]=1ll*w[i-1]*p%mod;
			if(w[i]==1&&i<sz)
			{
				cerr<<"WTF";
				exit(1);
			}
		}
	}
	void FFT(int a[],int coef)
	{
		for(int i=0,j=0;i<sz;i++)
		{
			if(i<j)swap(a[i],a[j]);
			for(int t=sz>>1;(j^=t)<t;t>>=1);
		}
		for(int l=1;l<sz;l<<=1)
		{
			int l2=l<<1;
			for(int i=0;i<sz;i+=l2)
			{
				for(int j=0;j<l;j++)
				{
					ll tmp=1ll*a[i+l+j]*(coef==1?w[sz/l2*j]:w[sz-sz/l2*j])%mod;
					a[i+l+j]=a[i+j]-tmp<0?a[i+j]-tmp+mod:a[i+j]-tmp;
					a[i+j]=a[i+j]+tmp>=mod?a[i+j]+tmp-mod:a[i+j]+tmp;
				}
			}
		}
		if(coef==-1)
		{
			ll tmp=kissme(sz,mod-2,mod);
			for(int i=0;i<sz;i++)a[i]=1ll*a[i]*tmp%mod;
		}
	}
	int a[FFTmx];
	void multi(int _a[],int _b[],int c[],int n)
	{
		init(n);
		for(int i=0;i<sz;i++)a[i]=(i<n?_a[i]:0);
		FFT(a,1);
		for(int i=0;i<sz;i++)c[i]=a[i];
		for(int i=0;i<sz;i++)a[i]=(i<n?_b[i]:0);
		FFT(a,1);
		for(int i=0;i<sz;i++)c[i]=1ll*c[i]*a[i]%mod;
		FFT(c,-1);
		for(int i=n;i<sz;i++)c[i]=0;
	}
}T1,T2,T3;
int _c1[FFTmx],_c2[FFTmx],_c3[FFTmx];
void multi(int a[],int b[],int c[],ll mod,int sz)
{
	T1.mod=mod1;
	T2.mod=mod2;
	T3.mod=mod3;
	T1.multi(a,b,_c1,sz);
	T2.multi(a,b,_c2,sz);
	T3.multi(a,b,_c3,sz);
	for(int i=0;i<2*sz;i++)
	{
		ll X=_c1[i],Y=_c2[i],Z=_c3[i];
		ll t1=1ll*(Y-X+mod2)*kissme(mod1,mod2-2,mod2)%mod2;
		ll t2=1ll*(Z-(t1*mod1+X)%mod3+mod3)*kissme(mod1*mod2%mod3,mod3-2,mod3)%mod3;
		c[i]=(t2*mod1%mod*mod2%mod+t1*mod1%mod+X)%mod;
	}
}//----------------------------
