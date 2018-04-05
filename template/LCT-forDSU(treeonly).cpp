struct LCT
{
	struct node
	{
		bool rev;
		int go[2],fa;
		node(){go[0]=go[1]=fa=rev=0;}
	}a[100111];
	#define ls a[p].go[0]
	#define rs a[p].go[1]
	void debug()
	{
		for(int i=1;i<=8;i++)
		{
			cout<<i<<":"<<a[i].go[0]<<","<<a[i].go[1]<<" "<<a[i].fa<<" "<<a[i].rev<<endl;
		}
	}
	void push_down(int p)
	{
		if(!p)return;
		push_down(a[p].fa);
		if(a[p].rev)
		{
			swap(ls,rs);
			a[ls].rev^=1;
			a[rs].rev^=1;
			a[p].rev=0;
		}
	}
	int getdir(int x)
	{
		int p=a[x].fa;
		if(!p)return -1;
		if(ls==x)return 0;
		else if(rs==x)return 1;
		else return -1;
	}
	void rotate(int p,bool dir)
	{
		int q=a[p].go[dir],r=a[q].go[!dir];
		if(getdir(p)!=-1)a[a[p].fa].go[getdir(p)]=q;
		a[p].go[dir]=r;
		a[q].go[!dir]=p;
		a[q].fa=a[p].fa;
		a[p].fa=q;
		a[r].fa=p;
	}
	void splay(int p)
	{
		while(getdir(p)!=-1)
		{
			int q=a[p].fa,r=a[q].fa;
			bool dq=getdir(p),dr=getdir(q);
			if(getdir(q)==-1)rotate(q,dq);
			else
			{
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
	}
	void access(int p)
	{
		push_down(p);
		splay(p);
		rs=0;
		while(a[p].fa)
		{
			splay(a[p].fa);
			a[a[p].fa].go[1]=p;
			splay(p);
		}
	}
	void makeroot(int p)
	{
		access(p);
		a[p].rev^=1;
	}
	void link(int x,int y)
	{
		makeroot(y);
		a[y].fa=x;
	}
	void cut(int x,int y)
	{
		makeroot(x);
		access(y);
		a[x].fa=0;
		a[y].go[0]=0;
	}
	bool same(int x,int y)
	{
		if(x==y)return true;
		makeroot(x);
		access(y);
		return getdir(x)!=-1;
	}
};
