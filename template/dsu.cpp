struct dsu
{
	int f[500111],sz[500111],tmp[1500111],tn;
	dsu()
	{
		for(int i=0;i<500111;i++)f[i]=i,sz[i]=1;
		tn=0;
	}
	int gf(int x)
	{
		return f[x]==x?x:gf(f[x]);
	}
	void un(int x,int y)
	{
		x=gf(x);y=gf(y);
		if(x==y)return;
		if(sz[x]>sz[y])swap(x,y);
		tmp[tn++]=x;
		tmp[tn++]=f[x];
		tmp[tn++]=y;
		f[x]=y;
		sz[y]+=sz[x];
	}
	void rollback(int v)
	{
		for(int i=tn-3;i>=v;i-=3)
		{
			f[tmp[i]]=tmp[i+1];
			sz[tmp[i+2]]-=sz[tmp[i]];
		}
		tn=v;
	}
}d;
