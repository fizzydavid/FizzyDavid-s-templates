ll kissme(ll x,ll k){return k==0?1%mod:kissme(x*x%mod,k>>1)*(k&1?x:1)%mod;}
ll kissme(ll x,ll k,ll md){return k==0?1%md:kissme(x*x%md,k>>1,md)*(k&1?x:1)%md;}

const int combsz=100011;
ll fac[combsz],invf[combsz];
ll C(int x,int y){return x<y?0:1ll*fac[x]*invf[y]%mod*invf[x-y]%mod;}
//-----------------simple
void combinit()
{
	fac[0]=1;
	for(int i=1;i<combsz;i++)fac[i]=1ll*fac[i-1]*i%mod;
	invf[combsz-1]=kissme(fac[combsz-1],mod-2);
	for(int i=combsz-2;i>=0;i--)invf[i]=1ll*invf[i+1]*(i+1)%mod;
}
//-----------------complete
int modphi;
int getinv(int x){return kissme(x,modphi-1);}
void combinit()
{
	int tmp=mod;modphi=1;
	for(int i=2;i*i<=tmp;i++)
	{
		if(tmp%i==0)
		{
			modphi*=i-1;tmp/=i;
			while(tmp%i==0)tmp/=i,modphi*=i;
		}
	}
	if(tmp>1)modphi*=tmp-1;
	fac[0]=1;
	for(int i=1;i<combsz;i++)fac[i]=1ll*fac[i-1]*i%mod;
	invf[combsz-1]=getinv(fac[combsz-1]);
	for(int i=combsz;i>=0;i--)invf[i]=1ll*invf[i+1]*(i+1)%mod;
}
//------------------end


struct number
{
	int x,y;//x+ysqrt(5)
	number(int _x=0,int _y=0){x=_x;y=_y;}
	number operator+(number t){return number((x+t.x)%mod,(y+t.y)%mod);}
	number operator-(number t){return number((x-t.x+mod)%mod,(y-t.y+mod)%mod);}
	number operator*(number t){return number((1ll*x*t.x+1ll*y*t.y*5)%mod,(1ll*x*t.y+1ll*y*t.x)%mod);}
	number operator*(int t){return number((1ll*x*t)%mod,(1ll*y*t)%mod);}
	bool operator!=(number t){return x!=t.x||y!=t.y;}
	number inv()
	{
		ll t=(1ll*x*x%mod-5ll*y*y%mod+mod)%mod;
		t=kissme(t,mod-2);
		return number(x*t%mod,(-y*t%mod+mod)%mod);
	}
	void operator=(int t){x=t;y=0;}
	number operator^(ll t)
	{
		number ret(1,0),b=(*this);
		while(t>0)
		{
			if(t&1)ret=ret*b;
			b=b*b;
			t>>=1;
		}
		return ret;
	}
	void out(){cout<<x<<","<<y<<endl;}
};
number kissme(number x,ll t)
{
	number ans=1;
	while(t>0)
	{
		if(t&1)ans=ans*x;
		x=x*x;
		t>>=1;
	}
	return ans;
}


