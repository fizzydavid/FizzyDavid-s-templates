//by yjz
#include<bits/stdc++.h>
#include<bitset>
using namespace std;
#define FF first
#define SS second
#define PB push_back
#define MP make_pair
typedef long long ll;
const int Imx=2147483647;
const int mod=1000000007;
const ll Lbg=2e18;
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
struct SAM
{
	int go[1234][26],par[1234],len[1234],last,tot;
	void init()
	{
		memset(go,0,sizeof(go));
		memset(par,0,sizeof(par));
		memset(len,0,sizeof(len));
		last=tot=1;
	}
	SAM()
	{
		init();
	}
	int newq(int p,int x)
	{
		int q=go[p][x];
		if(len[q]==len[p]+1)return q;
		int nq=++tot;
		len[nq]=len[p]+1;
		par[nq]=par[q];
		for(int i=0;i<26;i++)go[nq][i]=go[q][i];
		par[q]=nq;
		while(p&&go[p][x]==q)go[p][x]=nq,p=par[p];
		return nq;
	}
	void insert(int x)
	{
		cerr<<"insert:"<<x<<endl;
		cout<<"last="<<last<<endl;
		int p=last,np;
		if(go[p][x])
		{
			int q=go[p][x];
			last=newq(p,x);
			return;
		}
		np=++tot;
		last=np;
		len[np]=len[p]+1;
		while(p&&!go[p][x])go[p][x]=np,p=par[p];
		if(p)par[np]=newq(p,x);
		else par[np]=1;
	}
	void dfs(string s,int p=1)
	{
		cout<<p<<" "<<s<<endl;
//		ans.PB(s);
		for(int i=0;i<26;i++)
			if(go[p][i])
				dfs(s+char('a'+i),go[p][i]);
	}
}a;
int main()
{
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++)a.insert(s[i]-'a');
	a.dfs("");
	return 0;
}
