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
const int mod=1000000007;
const ll Lbig=2e18;
//My own input/output stream
#define geti(x) x=getnum()
#define getii(x,y) geti(x),geti(y)
#define getiii(x,y,z) getii(x,y),geti(z)
#define puti(x) putnum(x),putsp()
#define putii(x,y) puti(x),putnum(y),putsp()
#define putiii(x,y,z) putii(x,y),putnum(z),putsp()
#define putsi(x) putnum(x),putendl()
#define putsii(x,y) puti(x),putnum(y),putendl()
#define putsiii(x,y,z) putii(x,y),putnum(z),putendl()
inline ll getnum()
{
	register ll r=0;register bool ng=0;register char c;c=getchar();
	while(c!='-'&&(c<'0'||c>'9'))c=getchar();
	if(c=='-')ng=1,c=getchar();
	while(c>='0'&&c<='9')r=r*10+c-'0',c=getchar();
	if(ng)r=-r;return r;
}
template <class T> inline void putnum(T x)
{
	if(x<0)putchar('-'),x=-x;
	register short a[20]={},sz=0;
	while(x>0)a[sz++]=x%10,x/=10;
	if(sz==0)putchar('0');
	for(int i=sz-1;i>=0;i--)putchar('0'+a[i]);
}
inline void putsp(){putchar(' ');}
inline void putendl(){putchar('\n');}
inline char mygetchar(){register char c=getchar();while(c==' '||c=='\n')c=getchar();return c;}
//bad!!!!!!!!!!!!
typedef unsigned long long ull;
typedef unsigned int ui;
unsigned int fmsk=(1ll<<32)-1;
ull bs;
const int mod1=1e9+7;
const int mod2=1e9+9;
ull f(ull a,ull b)
{
	ui ax=a>>32,ay=a&fmsk,bx=b>>32,by=b&fmsk;
	ui cx=ax*bx-ay*by,cy=ax*by+ay*bx;
	return ull(cx)<<32|cy;
}
ull pw[100111];
void calchs(char s[],ull hs[],int n)
{
	hs[0]=s[0];
	for(int i=1;i<=n;i++)hs[i]=f(hs[i-1],bs)+s[i];
}
ull geths(ull hs[],int x,int y)
{
	return x==0?hs[y]:hs[y]-f(hs[x-1],pw[y-x+1]);
}
char s[100111];
ull hs[100111];
int main()
{
	srand(time(NULL));
	bs=12345678987654321ll+rand();
	pw[0]=1ll<<32;
	for(int i=1;i<=100100;i++)pw[i]=f(pw[i-1],bs);
	cout<<f(pw[0],pw[1])<<" "<<pw[1]<<endl;
	while(true)
	{
		scanf("%s",s);
		int n=strlen(s);
		calchs(s,hs,n);
		set<ull>st;
		for(int i=0;i<n;i++)
		{
			for(int j=i;j<n;j++)
			{
				st.insert(geths(hs,i,j));
				cerr<<i<<" "<<j<<" "<<geths(hs,i,j)<<endl;
			}
		}
		for(int i=0;i<n;i++)
		{
			ull sum=0;
			for(int j=0;j<=i;j++)
			{
				sum+=f(s[j],pw[i-j]);
			}
			cerr<<i<<":"<<sum<<" "<<hs[i]<<endl;
		}
		cout<<st.size()<<endl;
	}
	return 0;
}
