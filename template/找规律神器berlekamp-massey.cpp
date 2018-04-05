//by yjz
#include<bits/stdc++.h>
#include<ctime>
using namespace std;
#define FF first
#define SS second
#define PB push_back
#define MP make_pair
#define bged(v) (v).begin(),(v).end()
#define foreach(it,s) for(__typeof((s).begin()) it=(s).begin();it!=(s).end();it++)
typedef long long ll;
const int Imx=2147483647;
const ll Lbig=2e18;
const int mod=1e9+7;
//My i/o stream
struct fastio
{
	char s[100000];
	int it,len;
	fastio(){it=len=0;}
	inline char get()
	{
		if(it<len)return s[it++];it=0;
		len=fread(s,1,100000,stdin);
		if(len==0)return EOF;else return s[it++];
	}
	bool notend()
	{
		char c=get();
		while(c==' '||c=='\n')c=get();
		if(it>0)it--;
		return c!=EOF;
	}
}_buff;
#define geti(x) x=getnum()
#define getii(x,y) geti(x),geti(y)
#define getiii(x,y,z) getii(x,y),geti(z)
#define puti(x) putnum(x),putchar(' ')
#define putii(x,y) puti(x),puti(y)
#define putiii(x,y,z) putii(x,y),puti(z)
#define putsi(x) putnum(x),putchar('\n')
#define putsii(x,y) puti(x),putsi(y)
#define putsiii(x,y,z) putii(x,y),putsi(z)
inline ll getnum()
{
	ll r=0;bool ng=0;char c;c=_buff.get();
	while(c!='-'&&(c<'0'||c>'9'))c=_buff.get();
	if(c=='-')ng=1,c=_buff.get();
	while(c>='0'&&c<='9')r=r*10+c-'0',c=_buff.get();
	return ng?-r:r;
}
template<class T> inline void putnum(T x)
{
	if(x<0)putchar('-'),x=-x;
	register short a[20]={},sz=0;
	while(x)a[sz++]=x%10,x/=10;
	if(sz==0)putchar('0');
	for(int i=sz-1;i>=0;i--)putchar('0'+a[i]);
}
inline char getreal(){char c=_buff.get();while(c==' '||c=='\n')c=_buff.get();return c;}
int n,fn,pfn,cfn,pre;
double a[1011];
double f[1011],cf[1011],pf[1011];
double getv(int x)
{
	double sum=0;
	for(int i=0;i<=fn&&x-i>=0;i++)sum+=a[x-i]*f[i];
	return sum;
}
double stand(double x){return fabs(x)<1e-8?0:x;}
int main()
{
	f[0]=-1;n=0;fn=0;pre=-1;
	while(true)
	{
		scanf("%lf",&a[n++]);
		double curv=getv(n-1);
		if(fabs(curv)<1e-8)continue;
		for(int i=0;i<=fn;i++)f[i]/=curv;
		cfn=fn;
		for(int i=0;i<=fn;i++)cf[i]=f[i];
		if(pre==-1)
		{
			fn=n;
			for(int i=1;i<=fn;i++)f[i]=0;
		}
		else
		{
			for(int i=fn+1;i<=pfn+n-pre;i++)f[i]=0;
			fn=pfn+n-pre;
			for(int i=0;i<=pfn;i++)f[i+n-pre]-=pf[i];
		}
		pfn=cfn;
		for(int i=0;i<=pfn;i++)pf[i]=cf[i];
		pre=n;
		cout<<"Fn=";
		for(int i=1;i<=fn;i++)
		{
			cout<<stand(-f[i]/f[0])<<"fn-"<<i;
			if(i<fn)cout<<" + ";
		}cout<<endl;
//		for(int i=0;i<=fn;i++)cerr<<f[i]<<" ";cerr<<endl;
	}
	return 0;
}
