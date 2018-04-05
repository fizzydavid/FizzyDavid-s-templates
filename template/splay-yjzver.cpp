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
struct SPLAY
{
	struct node
	{
		bool rev;
		int val,sz,go[2];
		node(){go[0]=go[1]=0;val=sz=rev=0;}
	}a[300111];
	int root,tot;
	SPLAY(){root=1;tot=1;}
	#define ls a[x].go[0]
	#define rs a[x].go[1]
	void update(int x){a[x].sz=a[ls].sz+a[rs].sz+1;}
	void push_down(int x)
	{
		if(a[x].rev)
		{
			a[x].rev=0;
			a[ls].rev^=1;
			a[rs].rev^=1;
			swap(ls,rs);
		}
	}
	void rotate(int y,bool dir)
	{
		int x=a[y].go[dir];
		a[y].go[dir]=a[x].go[dir^1];
		a[x].go[dir^1]=y;
		update(y);update(x);
	}
	int find(int x,int rk,int &px,int pdir)
	{
		push_down(x);
		int currk=a[ls].sz;
		if(rk==currk)return x;
		else
		{
			bool dir=currk<rk;
			int y=a[x].go[dir];
			int ret=find(y,rk-(dir?currk+1:0),a[x].go[dir],dir);
			if(a[x].go[dir]!=ret)
			{
				rotate(x,dir);
				rotate(y,dir);
				px=ret;
			}
			else if(pdir!=dir)
			{
				rotate(x,dir);
				px=ret;
			}
			return ret;
		}
	}
	#define splay(rk,x) find(x,rk,x,-1)
	int newnode(int v)
	{
		a[++tot].val=v;
		return tot;
	}
	void insert(int x,int v)
	{
		splay(x,root);
		int t=a[root].go[1],p=newnode(v);
		a[root].go[1]=p;
		a[p].go[1]=t;
		update(p);
		update(root);
	}
	void reverse(int x,int y)
	{
		splay(x-1,root);
		splay(y-a[a[root].go[0]].sz,a[root].go[1]);
		a[a[a[root].go[1]].go[0]].rev^=1;
	}
	int get(int x)
	{
		splay(x,root);
		return a[root].val;
	}
	void debug(int x)
	{
		if(x==0)return;
		cout<<x<<":"<<a[x].go[0]<<","<<a[x].go[1]<<" "<<a[x].sz<<" "<<a[x].val<<" "<<a[x].rev<<endl;
		debug(a[x].go[0]);
		debug(a[x].go[1]);
	}
	void debug(){debug(root);}
}spl;
int n,a[300111];
int main()
{
	freopen("splay.in","r",stdin);
	freopen("splay.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n+1;i++)
	{
		spl.insert(i-1,a[i]);
	}
	int ans=0;
	while(true)
	{
		int p=spl.get(1);
		if(p==1)
		{
			printf("%d\n",ans);
			return 0;
		}
		spl.reverse(1,p);
		ans++;
		if(ans>100011)break;
	}
	puts("-1");
	return 0;
}
