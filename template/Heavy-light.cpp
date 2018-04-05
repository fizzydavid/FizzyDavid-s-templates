struct SGT
{
	int a[800111];
	void init(){memset(a,63,sizeof(a));}
	#define ls p<<1
	#define rs p<<1|1
	void mini(int x,int y,int v,int l,int r,int p)
	{
		if(x<=l&&r<=y)
		{
			a[p]=min(a[p],v);
			return;
		}
		int m=l+r>>1;
		if(x<=m)mini(x,y,v,l,m,ls);
		if(m<y)mini(x,y,v,m+1,r,rs);
	}
	int query(int x,int y,int l,int r,int p)
	{
		if(x<=l&&r<=y)return a[p];
		int m=l+r>>1;
		if(x<=m&&m<y)return min(a[p],min(query(x,y,l,m,ls),query(x,y,m+1,r,rs)));
		else if(x<=m)return min(a[p],query(x,y,l,m,ls));
		else return min(a[p],query(x,y,m+1,r,rs));
	}
}sgt;
int n,m;
vector<int>con[200111];
int p[201111],lv[200111],top[200111],son[200111],sz[200111],dfn[200111],dfntot;
void dfs(int x,int pre)
{
	p[x]=pre;
	sz[x]=1;
	for(int i=0;i<con[x].size();i++)
	{
		int u=con[x][i];
		if(u==pre)continue;
		lv[u]=lv[x]+1;
		dfs(u,x);
		sz[x]+=sz[u];
	}
}
void dfs2(int x)
{
	dfn[x]=++dfntot;
	for(int i=0;i<con[x].size();i++)
	{
		int u=con[x][i];
		if(u==p[x])continue;
		if(sz[son[x]]<sz[u])
		{
			son[x]=u;
		}
	}
	if(son[x])
	{
		top[son[x]]=top[x];
		dfs2(son[x]);
	}
	for(int i=0;i<con[x].size();i++)
	{
		int u=con[x][i];
		if(u==p[x]||u==son[x])continue;
		top[u]=u;
		dfs2(u);
	}
}
void mini(int x,int y,int w)
{
	while(true)
	{
		if(top[x]==top[y])
		{
			if(lv[x]>lv[y])swap(x,y);
			sgt.mini(dfn[x]+1,dfn[y],w,1,n,1);
			return;
		}
		else
		{
			if(lv[top[x]]>lv[top[y]])swap(x,y);
			sgt.mini(dfn[top[y]],dfn[y],w,1,n,1);
			y=p[top[y]];
		}
	}
}
int query(int x,int y)
{
	int ret=sgt.a[0];
	while(true)
	{
		if(top[x]==top[y])
		{
			if(lv[x]>lv[y])swap(x,y);
			ret=min(ret,sgt.query(dfn[x]+1,dfn[y],1,n,1));
			return ret;
		}
		else
		{
			if(lv[top[x]]>lv[top[y]])swap(x,y);
			ret=min(ret,sgt.query(dfn[top[y]],dfn[y],1,n,1));
			y=p[top[y]];
		}
	}
}
int main()
{
	dfs(1,0);
	dfntot=0;
	top[1]=1;
	dfs2(1);
	return 0;
}
