//BIT with addition
const int BITsz=100000+10;
struct BITadd
{
	ll a[BITsz];
	void init(){memset(a,0,sizeof(a));}
	BITadd(){init();}
	void add(int p,ll x)
	{
//		p=BITsz-5-p;
		for(int i=p;i<BITsz;i+=i&(-i))a[i]=a[i]+x;
	}
	ll query(int p)
	{
//		p=BITsz-5-p;
		ll ans=0;
		for(int i=p;i>0;i-=i&(-i))ans=ans+a[i];
		return ans;
	}
};
//BIT with maximize
const int BITsz=100000+10;
struct BITmx
{
	ll a[BITsz];
	void init(){memset(a,0,sizeof(a));}
	BITmx(){init();}
	void maxi(int p,ll x)
	{
//		p=BITsz-5-p;
		for(int i=p;i<BITsz;i+=i&(-i))a[i]=max(a[i],x);
	}
	ll query(int p)
	{
//		p=BITsz-5-p;
		ll ans=0;
		for(int i=p;i>0;i-=i&(-i))ans=max(ans,a[i]);
		return ans;
	}
};
//BIT with minimize
const int BITsz=100000+10;
struct BITmn
{
	ll a[BITsz];
	void init(){memset(a,127,sizeof(a));}
	BITmn(){init();}
	void mini(int p,ll x)
	{
//		p=BITsz-5-p;
		for(int i=p;i<BITsz;i+=i&(-i))a[i]=min(a[i],x);
	}
	ll query(int p)
	{
//		p=BITsz-5-p;
		ll ans=0;
		for(int i=p;i>0;i-=i&(-i))ans=min(ans,a[i]);
		return ans;
	}
};
