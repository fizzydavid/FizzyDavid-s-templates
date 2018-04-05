const int maxn=200000;
struct SPLAY
{
	struct node
	{
		int go[2],fa,sz;
		void init(){go[0]=go[1]=fa=sz=0;}
		node(){init();}
	}a[maxn*2+111];
	int root;
	#define ls a[p].go[0]
	#define rs a[p].go[1]
	#define pdir(x) (a[x].fa?(a[a[x].fa].go[0]==x?0:1):-1)
	void debug(int p)
	{
		cout<<"node:"<<p<<" ("<<ls<<","<<rs<<") "<<a[p].fa<<" "<<a[p].sz<<endl;
		if(ls)debug(ls);
		if(rs)debug(rs);
	}
	void debug()
	{
		debug(root);
	}
	inline void update(int p){a[p].sz=a[ls].sz+a[rs].sz+1;}
	inline void rotate(int p,bool dir)
	{
		int q=a[p].go[dir],r=a[q].go[!dir];
		if(a[p].fa)a[a[p].fa].go[pdir(p)]=q;
		else root=q;
		a[q].fa=a[p].fa;
		a[p].fa=q;
		a[r].fa=p;
		a[q].go[!dir]=p;
		a[p].go[dir]=r;
		update(p);
		update(q);
	}
	void splay(int p,int t=0)
	{
		while(a[p].fa!=t)
		{
			int q=a[p].fa,r=a[q].fa,pd=pdir(p),qd=pdir(q);
			if(r==t)rotate(q,pd);
			else
			{
				if(pd==qd)
				{
					rotate(r,qd);
					rotate(q,pd);
				}
				else
				{
					rotate(q,pd);
					rotate(r,qd);
				}
			}
		}
	}
	int rightmost(int p)
	{
		while(a[p].go[1])p=a[p].go[1];
		return p;
	}
	//findrank not guaranteed
	int findrank(int x)
	{
		int p=root,rk=0;
		while(true)
		{
			int nrk=rk+a[ls].sz;
			if(nrk==x)return p;
			else if(nrk<x)p=rs,rk=nrk;
			else p=ls;
		}
	}
	void insert(int x,int y)
	{
		x+=maxn;
		splay(x);
		splay(rightmost(a[x].go[0]),x);
		int p=a[root].go[0],ty=y+maxn;
		a[y].init();a[ty].init();
		rs=y;a[y].go[1]=ty;
		a[y].fa=p;
		a[ty].fa=y;
		update(ty);
		update(y);
		update(p);
		update(root);
	}
	void del(int x)
	{
		splay(x);
		splay(x+maxn,x);
		splay(rightmost(a[x].go[0]),x);
		int p=a[a[root].go[1]].go[1];
		root=a[root].go[0];
		a[root].fa=0;a[p].fa=root;
		a[root].go[1]=p;
		update(p);
		update(root);
	}
	void init(int n){for(int i=0;i<=n;i++)a[i].init(),a[i+maxn].init();}
	void prework()
	{
		a[1].init();a[maxn+1].init();
		root=1;
		a[1].go[1]=maxn+1;
		a[maxn+1].fa=1;
		update(maxn+1);
		update(1);
	}
	int query(int p)
	{
		splay(p);
		return a[ls].sz;
	}
}QvQ;
