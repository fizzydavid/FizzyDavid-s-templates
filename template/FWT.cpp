//common
void FMT(ll a[],int n,int coef)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<(1<<n);j++)
		{
			if(!((j>>i)&1))a[j+(1<<i)]=a[j+(1<<i)]+(coef==1?a[j]:-a[j]);
		}
	}
}
void FWT(ll a[],int n,int coef)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<(1<<n);j++)
		{
			if(!((j>>i)&1))
			{
				ll tmp=a[j+(1<<i)];
				a[j+(1<<i)]=a[j]-a[j+(1<<i)];
				a[j]=a[j]+tmp;
			}
		}
	}
	if(coef==-1)for(int i=0;i<(1<<n);i++)a[i]>>=n;
}
//combinatorial
void FMT(ll a[],int n,int coef)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<(1<<n);j++)
		{
			if(!((j>>i)&1))a[j+(1<<i)]=(a[j+(1<<i)]+(coef==1?a[j]:mod-a[j]))%mod;
		}
	}
}
void FWT(ll a[],int n,int coef)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<(1<<n);j++)
		{
			if(!((j>>i)&1))
			{
				ll tmp=a[j+(1<<i)];
				a[j+(1<<i)]=(a[j]-a[j+(1<<i)]+mod)%mod;
				a[j]=(a[j]+tmp)%mod;
			}
		}
	}
	ll inv=kissme(1<<n,mod-2);
	if(coef==-1)for(int i=0;i<(1<<n);i++)a[i]=a[i]*inv%mod;
}
//polynomial
const int mxn=19;
const int mxsz=1<<mxn;
void FMTp(int a[][mxn+1],int n,int coef)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<(1<<n);j++)
		{
			if(!((j>>i)&1))
			{
				for(int t=0;t<=n;t++)a[j+(1<<i)][t]=(a[j+(1<<i)][t]+(coef==1?a[j][t]:mod-a[j][t]))%mod;
			}
		}
	}
}
int _ta[mxsz][mxn+1],_tb[mxsz][mxn+1],_cnt1[mxsz];//160Mb
void subsetconv(int a[],int b[],int c[],int n)
{
//	for(int i=1;i<(1<<n);i++)_cnt1[i]=_cnt1[i-(i&(-i))]+1;
	for(int i=0;i<(1<<n);i++)
	{
		for(int j=0;j<n;j++)_ta[i][j]=_tb[i][j]=0;
		_ta[i][_cnt1[i]]=a[i];
		_tb[i][_cnt1[i]]=b[i];
	}
	FMTp(_ta,n,1);
	FMTp(_tb,n,1);
	for(int i=0;i<(1<<n);i++)
	{
		for(int j=n;j>=0;j--)
		{
			ll sum=0;
			for(int k=0;k<=j;k++)
			{
				sum=(sum+1ll*_ta[i][k]*_tb[i][j-k])%mod;
			}
			_ta[i][j]=sum;
		}
	}
	FMTp(_ta,n,-1);
	for(int i=0;i<(1<<n);i++)c[i]=_ta[i][_cnt1[i]];
}
