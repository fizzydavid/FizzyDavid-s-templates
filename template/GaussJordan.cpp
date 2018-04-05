namespace GJ
{
	const int maxn=305;
	ll a[maxn][maxn];
	ll gauss(int n)
	{
		ll ret=1;
		for(int i=0;i<n;i++)
		{
			int pivot=-1;
			for(int j=0;j<n;j++)
			{
				if(a[j][i]!=0)
				{
					pivot=j;
					break;
				}
			}
			if(pivot==-1)return 0;
			if(pivot!=i)ret=-ret;
			for(int j=0;j<n;j++)swap(a[i][j],a[pivot][j]);
			ll inv=qpow(a[i][i],mod-2);
			ret=ret*a[i][i]%mod;
			for(int j=0;j<n;j++)
			{
				if(i==j)continue;
				ll tmp=inv*a[j][i]%mod;
				for(int k=0;k<n;k++)a[j][k]=(a[j][k]-a[i][k]*tmp%mod+mod)%mod;
			}
		}
		return ((ret%mod)+mod)%mod;
	}
};
