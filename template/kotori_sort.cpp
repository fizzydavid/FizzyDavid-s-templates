const int msk=255;
const int times=2;
const int bitsz=16;
const int sortbase=0;
int na[1000111],b[msk+1];
int id[1000111],nid[1000111];
void kotori_sort(int a[],int n)
{
	for(int i=1;i<=n;i++)a[i]+=sortbase;
	for(int tt=0;tt<times;tt++)
	{
		memset(b,0,sizeof(b));
		int tmp=tt*bitsz;
		for(int i=1;i<=n;i++)b[(a[i]>>tmp)&msk]++;
		for(int i=1;i<=msk;i++)b[i]+=b[i-1];
		for(int i=n;i>=1;i--)na[b[(a[i]>>tmp)&msk]--]=a[i];
		memset(b,0,sizeof(b));
		tmp=tt*bitsz+bitsz/2;
		for(int i=1;i<=n;i++)b[(na[i]>>tmp)&msk]++;
		for(int i=1;i<=msk;i++)b[i]+=b[i-1];
		for(int i=n;i>=1;i--)a[b[(a[i]>>tmp)&msk]--]=na[i];
	}
	for(int i=1;i<=n;i++)a[i]-=sortbase;
}
void kotori_sort(int a[],int n,int rk[])
{
	for(int i=1;i<=n;i++)id[i]=i,a[i]-=sortbase;
	for(int tt=0;tt<times;tt++)
	{
		memset(b,0,sizeof(b));
		int tmp=tt*bitsz;
		for(int i=1;i<=n;i++)b[(a[i]>>tmp)&msk]++;
		for(int i=1;i<=msk;i++)b[i]+=b[i-1];
		for(int i=n;i>=1;i--)
		{
			int x=(a[i]>>tmp)&msk;
			nid[b[x]]=id[i];
			na[b[x]--]=a[i];
		}
		memset(b,0,sizeof(b));
		tmp=tt*bitsz+bitsz/2;
		for(int i=1;i<=n;i++)b[(na[i]>>tmp)&msk]++;
		for(int i=1;i<=msk;i++)b[i]+=b[i-1];
		for(int i=n;i>=1;i--)
		{
			int x=(na[i]>>tmp)&msk;
			id[b[x]]=nid[i];
			a[b[x]--]=na[i];
		}
	}
	int pre=1;
	for(int i=1;i<=n;i++)
	{
		if(i>1&&a[i]>a[i-1])pre=i;
		rk[id[i]]=pre;
	}
	for(int i=1;i<=n;i++)a[i]-=sortbase;
}

