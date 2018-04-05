//by yjz
#include<bits/stdc++.h>
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
void updmx(int &x,int v){x=max(x,v);}
void updmn(int &x,int v){x=min(x,v);}
ll sqr(ll x){return x*x;}
struct node
{
	int tl,tr,d[2];
	int lb[2],ub[2];
	int f,id;
	ll gmin(int x,int y){return sqr(max(0,max(x-ub[0],lb[0]-x)))+sqr(max(0,max(y-ub[1],lb[1]-y)));}
	ll rdis(int x,int y){return sqr(x-d[0])+sqr(y-d[1]);}
};
int cmp_d;
bool cmp(const node &x,const node &y){return x.d[cmp_d]<y.d[cmp_d];}
node a[100111];
int rt;
#define ls a[p].tl
#define rs a[p].tr
void update(int p)
{
	if(ls)
	{
		updmn(a[p].lb[0],a[ls].lb[0]);updmn(a[p].lb[1],a[ls].lb[1]);
		updmx(a[p].ub[0],a[ls].ub[0]);updmx(a[p].ub[1],a[ls].ub[1]);
	}
	if(rs)
	{
		updmn(a[p].lb[0],a[rs].lb[0]);updmn(a[p].lb[1],a[rs].lb[1]);
		updmx(a[p].ub[0],a[rs].ub[0]);updmx(a[p].ub[1],a[rs].ub[1]);
	}
}
int build(int l,int r,int d,int pre=0)
{
	int p=l+r>>1;
	cmp_d=d;
	nth_element(a+l,a+p,a+r+1,cmp);
	a[p].f=pre;	
	a[p].lb[0]=a[p].ub[0]=a[p].d[0];
	a[p].lb[1]=a[p].ub[1]=a[p].d[1];
	ls=l<p?build(l,p-1,d^1,p):0;
	rs=r>p?build(p+1,r,d^1,p):0;
	return update(p),p;
}
int build(int l,int r)
{
	return rt=build(l,r,0);
}
int Ox,Oy,mnid;
ll mnd;
void query(int p)
{
	ll curd=a[p].rdis(Ox,Oy);
//	cerr<<"query:"<<p<<" "<<curd<<endl;
	if(curd>0&&(curd<mnd||curd==mnd&&MP(a[p].d[0],a[p].d[1])<MP(a[mnid].d[0],a[mnid].d[1])))
	{
		mnd=curd;
		mnid=p;
	}
	ll ld=ls?a[ls].gmin(Ox,Oy):mnd+1,rd=rs?a[rs].gmin(Ox,Oy):mnd+1;
	if(ld<rd)
	{
		if(ld<=mnd)query(ls);
		if(rd<=mnd)query(rs);
	}
	else
	{
		if(rd<=mnd)query(rs);
		if(ld<=mnd)query(ls);
	}
}
int queryn(int x,int y)
{
	Ox=x;Oy=y;mnd=5e18;mnid=-1;
	query(rt);
	return mnid;
}
int n,q,f[100111];
int gf(int x){return f[x]==x?x:f[x]=gf(f[x]);}
int main()
{
	getii(n,q);
	for(int i=1;i<=n;i++)getii(a[i].d[0],a[i].d[1]),a[i].id=f[i]=i;
	build(1,n);
	for(int i=1;i<=n;i++)
	{
		int tmp=queryn(a[i].d[0],a[i].d[1]);
//		cerr<<a[i].id<<":"<<a[tmp].id<<" "<<mnd<<endl;
		f[gf(a[i].id)]=gf(a[tmp].id);
	}
	for(int i=1;i<=q;i++)
	{
		int x,y;
		getii(x,y);
		if(gf(x)==gf(y))puts("hi");else puts("oops");
	}
	return 0;
}

