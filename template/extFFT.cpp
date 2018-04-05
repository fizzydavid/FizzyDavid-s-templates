const double pi=acos(-1);
const int mxn=1024;
struct point
{
	double x,y;
	point(double _x=0,double _y=0){x=_x;y=_y;}
	point operator+(const point &t)const{return point(x+t.x,y+t.y);}
	point operator-(const point &t)const{return point(x-t.x,y-t.y);}
	point operator*(const point &t)const{return point(x*t.x-y*t.y,x*t.y+y*t.x);}
	point operator*(const double &t)const{return point(x*t,y*t);}
};
point makeunit(double x){return point(cos(x),sin(x));}
int sz;
point w[400111];
void init(int n)
{
	if(sz==n)return;
	sz=1;
	while(sz<n)sz<<=1;
	w[0]=point(1,0);
	point tw=makeunit(2*pi/sz);
	for(int i=1;i<=sz;i++)w[i]=w[i-1]*tw;
}
point FFT(point a[],bool rev)
{
	for(int i=0,j=0;i<sz;i++)
	{
		if(i>j)swap(a[i],a[j]);
		for(int l=sz>>1;(j^=l)<l;l>>=1);
	}
	for(int l=1;l<sz;l<<=1)
	{
		int l2=l<<1;
		for(int i=0;i<sz;i+=l2)
		{
			for(int j=0;j<l;j++)
			{
				point t=a[i+j+l]*w[rev?sz-sz/l2*j:sz/l2*j];
				a[i+j+l]=a[i+j]-t;
				a[i+j]=a[i+j]+t;
			}
		}
	}
	if(rev)for(int i=0;i<sz;i++)a[i]=a[i]*(1.0/sz);
}
void multi(point a[],point b[],point c[],int n)
{
//	int nsz=1;
//	while(nsz<2*n)nsz<<=1;
//	init(nsz);
	FFT(a,0);
	FFT(b,0);
	for(int i=0;i<sz;i++)c[i]=a[i]*b[i];
	FFT(c,1);
}
void FFT2(point (&a)[mxn][mxn],bool rev)
{
	for(int i=0;i<sz;i++)FFT(a[i],rev);
	for(int i=0;i<sz;i++)for(int j=i;j<sz;j++)swap(a[i][j],a[j][i]);
	for(int i=0;i<sz;i++)FFT(a[i],rev);
};

