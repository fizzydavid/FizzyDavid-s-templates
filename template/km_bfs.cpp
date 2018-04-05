struct KM
{
	int n;
	int w[511][511];
	int mx[511],my[511],lx[511],ly[511];
	int slk[511],mkx[511],mky[511],pre[511];
	int que[511],qsz;
	void init(int sz)
	{
		n=sz;
		memset(w,0,sizeof(w));
	}
	void findpath(int y)
	{
		int x,ny;
		while(y!=-1)
		{
			x=pre[y],ny=mx[x];
			mx[x]=y;
			my[y]=x;
			y=ny;
		}
	}
	void bfs(int X)
	{
		memset(slk,127,sizeof(slk));
		qsz=0;
		que[qsz++]=X;
		mkx[X]=X;
		int i=0;
		while(true)
		{
			for(;i<qsz;i++)
			{
				int x=que[i];
				for(int y=1;y<=n;y++)
				{
					if(mky[y]==X)continue;
					if(lx[x]+ly[y]==w[x][y])
					{
						mky[y]=X;
						pre[y]=x;
						if(my[y]==-1)
						{
							findpath(y);
							return;
						}
						que[qsz++]=my[y];
						mkx[my[y]]=X;
					}
					else if(lx[x]+ly[y]-w[x][y]<slk[y])
					{
						slk[y]=lx[x]+ly[y]-w[x][y];
						pre[y]=x;
					}
				}
			}
			int d=slk[0];
			for(int y=1;y<=n;y++)if(mky[y]!=X)d=min(d,slk[y]);
			for(int x=1;x<=n;x++)if(mkx[x]==X)lx[x]-=d;
			for(int y=1;y<=n;y++)
			{
				if(mky[y]==X)ly[y]+=d;
				else if(slk[y]!=slk[0])slk[y]-=d;
			}
			for(int y=1;y<=n;y++)
			{
				if(mky[y]!=X&&!slk[y])
				{
					if(my[y]==-1)
					{
						findpath(y);
						return;
					}
					mky[y]=mkx[my[y]]=X;
					que[qsz++]=my[y];
				}
			}
		}
	}
	void matching()
	{
		memset(mx,-1,sizeof(mx));
		memset(my,-1,sizeof(my));
		memset(mkx,0,sizeof(mkx));
		memset(mky,0,sizeof(mky));
		for(int i=1;i<=n;i++)lx[i]=*max_element(w[i]+1,w[i]+n+1),ly[i]=0;
		for(int i=1;i<=n;i++)bfs(i);
	}
}km;

