namespace Flow
{
	const int maxn=111,maxe=1111*2;
	int head[maxn],to[maxe],nxt[maxe],cap[maxe],tot=1;
	int dg[maxn];
	void init()
	{
		memset(head,0,sizeof(head));tot=1;
		memset(dg,0,sizeof(dg));
	}
	void adde(int x,int y,int c,int lb=0)
	{
//		cerr<<"adde:"<<x<<","<<y<<" "<<c<<" "<<lb<<endl;
		c-=lb;
		nxt[++tot]=head[x];
		head[x]=tot;
		to[tot]=y;
		cap[tot]=c;
		nxt[++tot]=head[y];
		head[y]=tot;
		to[tot]=x;
		cap[tot]=0;
		dg[x]+=lb;dg[y]-=lb;
	}
	void adde_2(int x,int y,int c,int c2)
	{
//		cerr<<"adde:"<<x<<","<<y<<" "<<c<<" "<<lb<<endl;
		nxt[++tot]=head[x];
		head[x]=tot;
		to[tot]=y;
		cap[tot]=c;
		nxt[++tot]=head[y];
		head[y]=tot;
		to[tot]=x;
		cap[tot]=c2;
	}
	
	int lv[maxn],q[maxn],qn;
	void bfs(int S,int N)
	{
		for(int i=0;i<=N;i++)lv[i]=-1;
		qn=0;
		q[qn++]=S;lv[S]=0;
		for(int i=0;i<qn;i++)
		{
			int u=q[i];
			for(int j=head[u];j;j=nxt[j])
			{
				if(cap[j]&&lv[to[j]]==-1)
				{
					lv[to[j]]=lv[u]+1;
					q[qn++]=to[j];
				}
			}
		}
	}
	int it[maxn];
	int dfs(int x,int T,int f)
	{
		if(x==T)return f;
		int of=f;
		for(int &i=it[x];i&&f;i=nxt[i])
		{
			int u=to[i];
			if(cap[i]&&lv[u]==lv[x]+1)
			{
				int d=dfs(u,T,min(f,cap[i]));
				if(d)
				{
					cap[i]-=d;
					cap[i^1]+=d;
					f-=d;
					if(f==0)return of;
				}
			}
		}
		return of-f;
	}
	int max_flow(int S,int T,int N=-1)
	{
		if(N==-1)N=maxn-1;
		int ans=0;
		while(true)
		{
			bfs(S,N);
			if(lv[T]==-1)return ans;
			for(int i=0;i<=N;i++)it[i]=head[i];
			ans+=dfs(S,T,2147483647);
		}
	}
	bool find_bound_flow(int s,int t,int N=-1)
	{
		if(N==-1)N=maxn-5;
		int S=N+1,T=N+2,pf=0;
		for(int i=0;i<=N;i++)
		{
			if(dg[i]>0)adde(i,T,dg[i]),pf+=dg[i];
			if(dg[i]<0)adde(S,i,-dg[i]);
			dg[i]=0;
		}N+=2;
		adde(t,s,2147483647);
		int flow=max_flow(S,T,N);
		return flow==pf;
	}
};
