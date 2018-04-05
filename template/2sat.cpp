//template:  2-SAT
//author:    fizzydavid
//last edit: 17/2/18
//variables: 
//stot - number of variable 
//nn   - maximum number of variable (also bound for oppo)
//mxm  - maximum number of edges (remember *2)
//status:
//check2sat() tested
//solve2sat() not tested
const int nn=80000;
const int mxn=nn*2+111;
int head[mxn],nxt[mxm],to[mxm],tot=1,stot;
#define nt(v) ((v)<=nn?(v)+nn:(v)-nn)
void addedge(int x,int y)
{
//	cout<<"add:"<<x<<" "<<y<<"  "<<nt(y)<<" "<<nt(x)<<endl;
	nxt[++tot]=head[x];
	head[x]=tot;
	to[tot]=y;
	nxt[++tot]=head[nt(y)];
	head[nt(y)]=tot;
	to[tot]=nt(x);
}

int dfn[mxn],low[mxn],dfntot,g[mxn],gtot,st[mxn],sttot;
bool live[mxn];
void dfs(int x)
{
	dfn[x]=++dfntot;low[x]=dfn[x];
	live[x]=1;
	st[sttot++]=x;
	for(int i=head[x];i;i=nxt[i])
	{
		if(live[to[i]])
		{
			low[x]=min(low[x],dfn[to[i]]);
		}
		else if(!dfn[to[i]])
		{
			dfs(to[i]);
			low[x]=min(low[x],low[to[i]]);
		}
	}
	if(dfn[x]==low[x])
	{
		gtot++;
		while(st[sttot]!=x)
		{
			sttot--;
			g[st[sttot]]=gtot;
			live[st[sttot]]=0;
		}
	}
}
bool check2sat()
{
	dfntot=0;
	memset(dfn,0,sizeof(dfn));
	sttot=0;
	gtot=0;
	for(int i=1;i<=stot;i++)
	{
		if(!dfn[i])
		{
			dfs(i);
		}
		if(!dfn[i+nn])
		{
			dfs(i+nn);
		}
	}
//	for(int i=1;i<=stot;i++)cout<<g[i]<<" ";cout<<endl;
//	for(int i=1;i<=stot;i++)cout<<g[nn+i]<<" ";cout<<endl;
	for(int i=1;i<=stot;i++)
	{
		if(g[i]==g[i+nn])return false;
	}
	return true;
}
bool ansf[mxn];
void solve2sat()
{
	check2sat();
	for(int i=1;i<=nn;i++)
	{
		if(g[i]>g[i+nn])
		{
			ansf[i]=1;
		}
	}
}
