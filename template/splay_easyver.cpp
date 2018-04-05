//by yjz
#include<bits/stdc++.h>
using namespace std;
#define FF first
#define SS second
#define PB push_back 
#define MP make_pair
typedef long long ll;
const ll INF=1<<28;
const ll LINF=1ll<<61;
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
	while(c!=' '&&c!='\n')r=r*10+c-'0',c=getchar();
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
int n;
struct SPLAY
{
	struct node
	{
		int go[2],fa,sz;
		bool v;
		node(){go[0]=go[1]=fa=sz=0;v=1;}
	}a[1000111];
	int root;
	SPLAY(){root=1;}
	#define ls a[p].go[0]
	#define rs a[p].go[1]
	inline int getdir(int q)
	{
		int p=a[q].fa;
		if(ls==q)return 0;else if(rs==q)return 1;
		return -1;
	}
	inline void update(int p){a[p].sz=a[ls].sz+a[rs].sz+a[p].v;}
	void rotate(int p,bool dir)
	{
		int q=a[p].go[dir];
		int r=a[q].go[!dir];
		if(a[p].fa)a[a[p].fa].go[getdir(p)]=q;
		a[p].go[dir]=r;
		a[q].go[!dir]=p;
		a[q].fa=a[p].fa;
		a[p].fa=q;
		a[r].fa=p;
		update(p);
		update(q);
	}
	void splay(int p)
	{
		while(getdir(p)!=-1)
		{
			int q=a[p].fa,dq=getdir(p);
			if(!a[q].fa)rotate(q,dq);
			else
			{
				int r=a[q].fa,dr=getdir(q);
				if(dq==dr)
				{
					rotate(r,dr);
					rotate(q,dq);
				}
				else
				{
					rotate(q,dq);
					rotate(r,dr);
				}
			}
		}
		root=p;
	}
	int query(int x)
	{
		int p=root,rk=0;
		while(true)
		{
			int cur=rk+a[ls].sz+a[p].v;
			if(cur==x&&a[p].v==1)break;
			if(cur<x)p=rs,rk=cur;
			else p=ls;
		}
		splay(p);
		a[p].v=0;
		update(p);
		return p;
	}
	void debug()
	{
		for(int i=1;i<=n;i++)cout<<i<<":"<<a[i].go[0]<<","<<a[i].go[1]<<" "<<a[i].fa<<" "<<a[i].v<<" "<<a[i].sz<<endl;
	}
}kotori;
int ans[1000111];
int main()
{
	geti(n);
	for(int i=1;i<n;i++)kotori.a[i].go[1]=i+1,kotori.a[i+1].fa=i;
	for(int i=n;i>=1;i--)kotori.update(i);
	for(int i=1;i<=n;i++)
	{
		int x;
		geti(x);
		int tmp=kotori.query(x+1);
		ans[tmp]=i;
	}
	for(int i=1;i<=n;i++)puti(ans[i]);
	return 0;
}
