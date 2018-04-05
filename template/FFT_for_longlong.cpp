const int magic=31622;
struct FFT_for_longlong
{
	struct point
	{
		double x,y;
		point(double _x=0,double _y=0){x=_x;y=_y;}
		point operator+(const point &t){return point(x+t.x,y+t.y);}
		point operator-(const point &t){return point(x-t.x,y-t.y);}
		point operator*(const point &t){return point(x*t.x-y*t.y,x*t.y+y*t.x);}
		point operator*(const double &t){return point(x*t,y*t);}
	};
	int sz;
	point w[FFTmx];
	void init(int n)
	{
		sz=1;
		while(sz<2*n)sz<<=1;
		double pi=acos(-1);
		for(int i=0;i<=sz;i++)w[i]=point(cos(2.0/sz*i*pi),sin(2.0/sz*i*pi));
	}
	void FFT(point a[],int coef)
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
					point tmp=a[i+l+j]*(coef==1?w[sz/l2*j]:w[sz-sz/l2*j]);
					a[i+l+j]=a[i+j]-tmp;
					a[i+j]=a[i+j]+tmp;
				}
			}
		}
		if(coef==-1)
		{
			for(int i=0;i<sz;i++)a[i]=a[i]*(1.0/sz);
		}
	}
	point al[FFTmx],ar[FFTmx],bl[FFTmx],br[FFTmx],ta[FFTmx];
	void multi(int _a[],int _b[],int c[],ll mod,int n)
	{
		init(n);
		for(int i=0;i<sz;i++)al[i]=point(i<n?_a[i]/magic:0,0);
		for(int i=0;i<sz;i++)ar[i]=point(i<n?_a[i]%magic:0,0);
		for(int i=0;i<sz;i++)bl[i]=point(i<n?_b[i]/magic:0,0);
		for(int i=0;i<sz;i++)br[i]=point(i<n?_b[i]%magic:0,0);
		FFT(al,1);FFT(ar,1);FFT(bl,1);FFT(br,1);
		for(int i=0;i<sz;i++)ta[i]=al[i]*bl[i];
		FFT(ta,-1);
		for(int i=0;i<sz;i++)c[i]=ll(ta[i].x+0.5)%mod*magic%mod*magic%mod;
		for(int i=0;i<sz;i++)ta[i]=ar[i]*br[i];
		FFT(ta,-1);
		for(int i=0;i<sz;i++)c[i]=(c[i]+ll(ta[i].x+0.5)%mod)%mod;
		for(int i=0;i<sz;i++)ta[i]=al[i]*br[i]+ar[i]*bl[i];
		FFT(ta,-1);
		for(int i=0;i<sz;i++)c[i]=(c[i]+ll(ta[i].x+0.5)%mod*magic%mod)%mod;
	}
}T;

