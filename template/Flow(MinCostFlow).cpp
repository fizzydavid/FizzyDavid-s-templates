namespace Flow
{
	const int maxn=1011,maxm=2011*2;
	int head[maxn],nxt[maxm],cap[maxm],to[maxm],tot;
	ll cost[maxm];
	ll ftot=0;
	void init()
	{
		memset(head,0,sizeof(head));
		tot=1;
	}
	void adde(int x,int y,int c,int w)
	{
		nxt[++tot]=head[x];
		head[x]=tot;
		to[tot]=y;
		cap[tot]=c;
		cost[tot]=w;
		nxt[++tot]=head[y];
		head[y]=tot;
		to[tot]=x;
		cap[tot]=0;
		cost[tot]=-w;
	}
	ll dis[maxn];
	bool inq[maxn];
	int q[maxn],qb,qe,pe[maxn];
	void spfa(int S,int T,int N)
	{
		for(int i=0;i<=N;i++)dis[i]=4e18,pe[i]=0;
		qb=qe=0;
		q[qe++]=S;dis[S]=0;inq[S]=1;
		while(qb!=qe)
		{
			int x=q[qb++];inq[x]=0;
			if(qb==maxn)qb=0;
			for(int i=head[x];i;i=nxt[i])
			{
				int u=to[i];
				if(cap[i]&&dis[u]>dis[x]+cost[i])
				{
					dis[u]=dis[x]+cost[i];
					pe[u]=i;
					if(!inq[u])
					{
						inq[u]=1;
						if(qb==qe||dis[u]>dis[q[qb]])
						{
							q[qe++]=u;
							if(qe==maxn)qe=0;
						}
						else
						{
							qb--;
							if(qb<0)qb=maxn-1;
							q[qb]=u;
						}
					}
				}
			}
		}
	}
	ll MinCostFlow(int S,int T,int K,bool mini,int N=-1)
	{
		if(N==-1)N=maxn-1;
		ll ans=0;
		while(K>0)
		{
			spfa(S,T,N);
			if(pe[T]==0)break;
			if(dis[T]>0&&mini)break;
			int flow=K;
			for(int x=T;x!=S;x=to[pe[x]^1])flow=min(flow,cap[pe[x]]);
			ans+=flow*dis[T];
			K-=flow;ftot+=flow;
			for(int x=T;x!=S;x=to[pe[x]^1])cap[pe[x]]-=flow,cap[pe[x]^1]+=flow;
		}
		return ans;
	}
	bool vis[maxn];
	int dfs(int x,int T,int f)
	{
		if(x==T)return f;
		int of=f;
		vis[x]=1;
		for(int i=head[x];i;i=nxt[i])
		{
			int u=to[i];
			if(dis[x]+cost[i]==dis[u]&&cap[i]>0&&!vis[u])
			{
				int d=dfs(u,T,min(f,cap[i]));
				if(d>0)
				{
					f-=d;
					cap[i]-=d;
					cap[i^1]+=d;
					if(f==0)return of;
				}
			}
		}
		return of-f;
	}
	bool modlabel(int N)
	{
		ll mn=5e18;
		for(int i=0;i<=N;i++)if(vis[i])
			for(int j=head[i];j;j=nxt[j])if(!vis[to[j]]&&cap[j])
				mn=min(mn,cost[j]-(dis[to[j]]-dis[i]));
		for(int i=0;i<=N;i++)if(!vis[i])dis[i]+=mn;
		return mn<4e18;
	}
	ll MinCostFlow_zkw(int S,int T,int K,bool mini,int N=-1)
	{
		if(N==-1)N=maxn-1;
		spfa(S,T,N);
		ll ans=0;
		do
		{
			if(dis[T]>0&&mini)break;
			int f=0;
			do
			{
				ans+=dis[T]*f;
				K-=f;ftot+=f;
				if(K==0)break;
				memset(vis,0,sizeof(vis));
			}while(f=dfs(S,T,K));
		}while(K>0&&modlabel(N));
		return ans;
	}
};
