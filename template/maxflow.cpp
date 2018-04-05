const int mxn=23333;
const int mxe=200111;
int head[mxn],nxt[mxe],to[mxe],cap[mxe],cost[mxe],tot=1;
int dis[mxn];
void add_edge(int x,int y,int c)
{
	nxt[++tot]=head[x];
	head[x]=tot;
	to[tot]=y;
	cap[tot]=c;
	nxt[++tot]=head[y];
	head[y]=tot;
	to[tot]=x;
	cap[tot]=0;
}
int q[mxn],qn;
void bfs(int S)
{
	memset(dis,-1,sizeof(dis));
	q[qn++]=S;
	dis[S]=0;
	for(int t=0;t<qn;t++)
	{
		int u=q[t];
		for(int i=head[u];i;i=nxt[i])
		{
			if(cap[i]&&dis[to[i]]==-1)
			{
				dis[to[i]]=dis[u]+1;
				q[qn++]=to[i];
			}
		}
	}
};
int it[mxn];
int dfs(int x,int T,int f)
{
	if(x==T)return f;
	int F=f;
	for(int i=head[x];i;i=nxt[i])
	{
		if(dis[to[i]]==dis[x]+1&&min(f,cap[i]))
		{
			int d=dfs(to[i],T,min(f,cap[i]));
			if(d>0)
			{
				cap[i]-=d;
				cap[i^1]+=d;
				f-=d;
			}
		}
	}
	return F-f;
}
int maxflow(int S,int T)
{
	int ret=0;
	while(true)
	{
		for(int i=0;i<mxn;i++)it[i]=head[i];
		bfs(S);
		if(dis[T]==-1)return ret;
		int f;
		while(f=dfs(S,T,2147483647))ret+=f;
	}
}
