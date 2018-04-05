//long long matrix with multiplication
const int mat_sz=100+5;
struct matrix
{
	ll a[mat_sz][mat_sz];
	void init()
	{
		memset(a,0,sizeof(a));
	}
	void init1()
	{
		init();
		for(int i=0;i<mat_sz;i++)a[i][i]=1;
	}
	matrix()
	{
		init();
	}
	matrix operator*(const matrix &t)const
	{
		matrix ret;
		for(int i=0;i<mat_sz;i++)
		{
			for(int j=0;j<mat_sz;j++)
			{
				if(!a[i][j])continue;
				for(int k=0;k<mat_sz;k++)
				{
					ret.a[i][k]+=a[i][j]*t.a[j][k]%mod;
				}
			}
		}
		for(int i=0;i<mat_sz;i++)for(int j=0;j<mat_sz;j++)ret.a[i][j]%=mod;
		return ret;
	}
	matrix getpw(ll k)
	{
		matrix ret,base=(*this);
		ret.init1();
		assert(k>=0);
		while(k)
		{
			if(k&1)ret=ret*base;
			base=base*base;
			k>>=1;
		}
		return ret;
	}
	matrix getT()
	{
		matrix ret;
		for(int i=0;i<mat_sz;i++)
		{
			for(int j=0;j<mat_sz;j++)
			{
				ret.a[j][i]=a[i][j];
			}
		}
		return ret;
	}
	void out(int n)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				cout<<a[i][j]<<" ";
			}
			cout<<endl;
		}
	}
};
