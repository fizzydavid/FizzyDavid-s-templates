//FFT & polynomial
struct point
{
	double x,y;
	point(double _x=0,double _y=0){x=_x;y=_y;}
	point operator+(const point &t){return point(x+t.x,y+t.y);}
	point operator-(const point &t){return point(x-t.x,y-t.y);}
	point operator*(const point &t){return point(x*t.x-y*t.y,x*t.y+y*t.x);}
	point operator*(const double &t){return point(x*t,y*t);}
	point conj(){return point(x,-y);}
};
const int FFTmx=400111;
int FFTsz;
point _w[FFTmx];
void FFTinit(int n)
{
	FFTsz=1;
	while(FFTsz<n)FFTsz<<=1;
	double pi=acos(-1);
	for(int i=0;i<=FFTsz;i++)_w[i]=point(cos(2.0/FFTsz*i*pi),sin(2.0/FFTsz*i*pi));
}
void FFT(point a[],int coef)
{
	for(int i=0,j=0;i<FFTsz;i++)
	{
		if(i<j)swap(a[i],a[j]);
		for(int t=FFTsz>>1;(j^=t)<t;t>>=1);
	}
	for(int l=1;l<FFTsz;l<<=1)
	{
		int l2=l<<1;
		for(int i=0;i<FFTsz;i+=l2)
		{
			for(int j=0;j<l;j++)
			{
				point tmp=a[i+l+j]*(coef==1?_w[FFTsz/l2*j]:_w[FFTsz-FFTsz/l2*j]);
				a[i+l+j]=a[i+j]-tmp;
				a[i+j]=a[i+j]+tmp;
			}
		}
	}
	if(coef==-1)
	{
		for(int i=0;i<FFTsz;i++)a[i]=a[i]*(1.0/FFTsz);
	}
}
point _al[FFTmx],_ar[FFTmx],_bl[FFTmx],_br[FFTmx],_ta[FFTmx],_tb[FFTmx];
void FFTfor2(point a[],point b[],int coef)
{
	for(int i=0;i<FFTsz;i++)a[i]=a[i]+b[i]*point(0,1);
	if(coef==1)
	{
		FFT(a,1);
		for(int i=0;i<FFTsz;i++)_ta[i]=a[i];
		_ta[FFTsz]=a[0];
		for(int i=0;i<FFTsz;i++)a[i]=(_ta[i]+_ta[FFTsz-i].conj())*0.5;
		for(int i=0;i<FFTsz;i++)b[i]=(_ta[i]-_ta[FFTsz-i].conj())*point(0,-0.5);
	}
	else 
	{
		FFT(a,-1);
		for(int i=0;i<FFTsz;i++)b[i]=a[i].y;
		for(int i=0;i<FFTsz;i++)a[i]=a[i].x;
	}
}
ll ceill(double x){return x>0?ll(x+0.5):-ll(-x+0.5);}
void polymulti(int _a[],int _b[],int c[],int n,int m)
{
	FFTinit(n+m);
	for(int i=0;i<FFTsz;i++)_al[i]=point(i<n?_a[i]/32768:0,0);
	for(int i=0;i<FFTsz;i++)_ar[i]=point(i<n?_a[i]%32768:0,0);
	for(int i=0;i<FFTsz;i++)_bl[i]=point(i<m?_b[i]/32768:0,0);
	for(int i=0;i<FFTsz;i++)_br[i]=point(i<m?_b[i]%32768:0,0);
	FFTfor2(_al,_ar,1);
	FFTfor2(_bl,_br,1);
	for(int i=0;i<FFTsz;i++)_ta[i]=_al[i]*_br[i];
	for(int i=0;i<FFTsz;i++)_tb[i]=_ar[i]*_bl[i];
	for(int i=0;i<FFTsz;i++)_al[i]=_al[i]*_bl[i];
	for(int i=0;i<FFTsz;i++)_ar[i]=_ar[i]*_br[i];
	FFTfor2(_ta,_tb,-1);
	FFTfor2(_al,_ar,-1);
	for(int i=0;i<FFTsz;i++)c[i]=((ceill(_al[i].x)%mod)<<30)%mod;
	for(int i=0;i<FFTsz;i++)c[i]=(c[i]+ceill(_ar[i].x))%mod;
	for(int i=0;i<FFTsz;i++)c[i]=(c[i]+((ceill(_ta[i].x)%mod)<<15))%mod;
	for(int i=0;i<FFTsz;i++)c[i]=(c[i]+((ceill(_tb[i].x)%mod)<<15))%mod;
}
void polymulti(ll _a[],ll _b[],ll c[],int n,int m)
{
	FFTinit(n+m);
	for(int i=0;i<FFTsz;i++)_al[i]=point(i<n?_a[i]/32768:0,0);
	for(int i=0;i<FFTsz;i++)_ar[i]=point(i<n?_a[i]%32768:0,0);
	for(int i=0;i<FFTsz;i++)_bl[i]=point(i<m?_b[i]/32768:0,0);
	for(int i=0;i<FFTsz;i++)_br[i]=point(i<m?_b[i]%32768:0,0);
	FFTfor2(_al,_ar,1);
	FFTfor2(_bl,_br,1);
	for(int i=0;i<FFTsz;i++)_ta[i]=_al[i]*_br[i];
	for(int i=0;i<FFTsz;i++)_tb[i]=_ar[i]*_bl[i];
	for(int i=0;i<FFTsz;i++)_al[i]=_al[i]*_bl[i];
	for(int i=0;i<FFTsz;i++)_ar[i]=_ar[i]*_br[i];
	FFTfor2(_ta,_tb,-1);
	FFTfor2(_al,_ar,-1);
	for(int i=0;i<FFTsz;i++)c[i]=((ceill(_al[i].x)%mod)<<30)%mod;
	for(int i=0;i<FFTsz;i++)c[i]=(c[i]+ceill(_ar[i].x))%mod;
	for(int i=0;i<FFTsz;i++)c[i]=(c[i]+((ceill(_ta[i].x)%mod)<<15))%mod;
	for(int i=0;i<FFTsz;i++)c[i]=(c[i]+((ceill(_tb[i].x)%mod)<<15))%mod;
}
int _va[FFTmx],_vb[FFTmx],_vc[FFTmx];
//not tested
struct polypoly
{
	vector<int>v;
	polypoly operator+(const polypoly &t)const
	{
		polypoly ret;
		int sz=max(v.size(),t.v.size());
		for(int i=0;i<sz;i++)
		{
			ret.v.PB(((i<v.size()?v[i]:0)+(i<t.v.size()?t.v[i]:0))%mod);
		}
		return ret;
	}
	polypoly operator-(const polypoly &t)const
	{
		polypoly ret;
		int sz=max(v.size(),t.v.size());
		for(int i=0;i<sz;i++)
		{
			ret.v.PB(((i<v.size()?v[i]:0)-(i<t.v.size()?t.v[i]:0))%mod);
		}
		return ret;
	}
	polypoly operator>>(const int &t)const
	{
		polypoly ret;
		for(int i=t;i<v.size();i++)ret.v.PB(v[i]);
		return ret;
	}
	polypoly operator<<(const int &t)const
	{
		polypoly ret;
		for(int i=0;i<t;i++)ret.v.PB(0);
		for(int i=0;i<v.size();i++)ret.v.PB(v[i]);
		return ret;
	}
	void out()
	{
		for(int i=0;i<v.size();i++)printf("%d ",v[i]);
		puts("");
	}
	void outc()
	{
		for(int i=0;i<v.size();i++)printf("%d%c",v[i],i+1==v.size()?'\n':' ');
		puts("");
	}
	polypoly operator*(const polypoly &t)const
	{
		polypoly ret;
		int sz=max(v.size(),t.v.size());
		for(int i=0;i<sz;i++)
		{
			ret.v.PB(((i<v.size()?v[i]:0)-(i<t.v.size()?t.v[i]:0))%mod);
		}
		return ret;
	}
	polypoly FFTmulti(const polypoly &t)const
	{
		int sz=max(v.size(),t.v.size());
		polypoly ret;
		for(int i=0;i<v.size();i++)_va[i]=v[i];
		for(int i=0;i<t.v.size();i++)_vb[i]=t.v[i];
		polymulti(_va,_vb,_vc,sz);
		for(int i=0;i+1<v.size()+t.v.size();i++)ret.v.PB(_vc[i]);
		for(int i=0;i<v.size();i++)_va[i]=0;
		for(int i=0;i<t.v.size();i++)_vb[i]=0;
		return ret;
	}
	//not tested!
	polypoly inv(const int &f)const
	{
		polypoly ret;
		int sz=v.size();
		for(int i=0;i<sz;i++)_vc[i]=v[i];
		_va[0]=f;
		for(int i=1;i<sz;i<<=1)
		{
			for(int j=i;j<i*2;j++)_va[j]=0;
			polymulti(_va,_vc,_vb,i*2);
			for(int j=0;j<i*2;j++)_vb[j]=-_vb[j];
			_vb[0]+=2;
			polymulti(_vb,_va,_va,i*2);
		}
		for(int i=0;i<sz;i++)ret.v.PB(_va[i]),_vc[i]=0;
		for(int i=0;i<sz*4;i++)_va[i]=_vb[i]=0;
		return ret;
	}
};
