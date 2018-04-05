struct SPLAY
{
	int a[300100],fa[300100],go[300100][2],tot;
	SPLAY()
	{
		memset(fa,-1,sizeof(fa));
		memset(go,-1,sizeof(go));
		tot=0;
	}
	void lrotate(int x)//左旋 
	{
		int y=fa[x]; 
		go[y][1]=go[x][0];
		go[x][0]=y;
		fa[x]=fa[y];
		fa[y]=x;
	}
	void rrotate(int x)//右旋 
	{
		int y=fa[x];
		go[y][0]=go[x][1];
		go[x][1]=y;
		fa[x]=fa[y];
		fa[y]=x;
	}
	void splay(int x,int k)//把x提到k的下面 
	{
		while(fa[x]!=k)
		{
			int y=fa[x],z=fa[y];
			bool f1=(go[y][0]==x);
			if(z==-1)
			{
				if(f1)rrotate(x);else lrotate(x);
			}
			else
			{
				bool f2=(go[z][0]==y);
				if(f1)
					if(f2)rrotate(y),rrotate(x);
					else lrotate(x),rrotate(x);
				else
					if(f2)rrotate(x),lrotate(x);
					else lrotate(y),lrotate(x);
			}
		}
	}
	int find(int x)//返回x的序号 
	{
		int p=0;
		while(p!=-1&&a[p]!=x)
		{
			if(x<=a[p])p=go[p][0];else p=go[p][1];
		}
		return p;
	}
	void insert(int x)//插入x 
	{
		int p=0,pre=-1;
		while(p!=-1&&a[p]!=x)
		{
			pre=p;
			if(x<=a[p])p=go[p][0];else p=go[p][1];
		}
		if(a[p]==x)return;
		p=pre;
		if(x<=a[p])go[p][0]=tot;else go[p][1]=tot;
		fa[tot]=p;
		a[tot++]=x;
	};
	int findpre(int x)//找x的前驱 
	{
		int p=go[x][0];
		if(p==-1)return fa[x];
		while(go[p][1]!=-1)
		{
			p=go[p][1];
		}
		return p;
	}
	int findsuf(int x)//找x的后缀 
	{
		int p=go[x][1];
		if(p==-1)return -1;
		while(go[p][0]==-1)
		{
			p=go[p][0];
		}
		return p;
	}
};
