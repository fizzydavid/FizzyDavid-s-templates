ll qpow(ll x,ll k){return k==0?1:1ll*qpow(1ll*x*x%mod,k>>1)*(k&1?x:1)%mod;}
const int msz=305;
struct matrix
{
	int a[msz][msz];
	void clear(){memset(a,0,sizeof(a));}
	matrix(){clear();}
	void seti(){clear();for(int i=0;i<msz;i++)a[i][i]=1;}
	matrix operator*(ll t)const
	{
		matrix ret;
		t%=mod;
		for(int i=0;i<msz;i++)for(int j=0;j<msz;j++)ret.a[i][j]=a[i][j]*t%mod;
		return ret;
	}
	matrix operator*(const matrix &t)const
	{
		matrix ret;
		for(int i=0;i<msz;i++)
		{
			for(int j=0;j<msz;j++)
			{
				if(!a[i][j])continue;
				for(int k=0;k<msz;k++)
				{
					ret.a[i][k]=(ret.a[i][k]+1ll*a[i][j]*t.a[j][k])%mod;
				}
			}
		}
		return ret;
	}
	matrix transpose()const
	{
		matrix ret;
		for(int i=0;i<msz;i++)for(int j=0;j<msz;j++)ret.a[j][i]=a[i][j];
		return ret;
	}
	ll calcdet(int n)
	{
		matrix tmp=(*this);
		ll det=1;
		for(int i=0;i<n;i++)
		{
			int pivot=-1;
			for(int j=i;j<n;j++)if(a[j][i]!=0)pivot=j;
			if(pivot==-1)return 0;
			if(pivot!=i)det=-det;
			for(int j=0;j<n;j++)swap(a[i][j],a[pivot][j]);
			ll inv=qpow(a[i][i],mod-2);
			det=det*a[i][i]%mod;
			for(int j=0;j<n;j++)
			{
				if(i==j)continue;
				ll tmp=inv*a[j][i]%mod;
				for(int k=0;k<n;k++)a[j][k]=(a[j][k]-a[i][k]*tmp%mod+mod)%mod;
			}
		}
		(*this)=tmp;
		return det=((det%mod)+mod)%mod;
	}
	matrix calcinv(int n)
	{
		matrix ret;ret.seti();
		matrix tmp=(*this);
		for(int i=0;i<n;i++)
		{
			int pivot=-1;
			for(int j=i;j<n;j++)if(a[j][i]!=0)pivot=j;
			assert(pivot!=-1);
			for(int j=0;j<n;j++)swap(a[i][j],a[pivot][j]),swap(ret.a[i][j],ret.a[pivot][j]);
			ll inv=qpow(a[i][i],mod-2);
			for(int j=0;j<n;j++)a[i][j]=a[i][j]*inv%mod,ret.a[i][j]=ret.a[i][j]*inv%mod;
			for(int j=0;j<n;j++)
			{
				if(i==j)continue;
				ll tmp=a[j][i];
				for(int k=0;k<n;k++)
				{
					a[j][k]=(a[j][k]-a[i][k]*tmp%mod+mod)%mod;
					ret.a[j][k]=(ret.a[j][k]-ret.a[i][k]*tmp%mod+mod)%mod;
				}
			}
		}
		(*this)=tmp;
		return ret;
	}
	matrix calcadj(int n)
	{
		matrix ret=calcinv(n);
		ret=ret*calcdet(n);
		return ret;
	}
	void out(int n)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				cerr<<a[i][j]<<" ";
			}
			cerr<<endl;
		}
	}
};
