//while(true)rp++;
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<deque>
#include<iostream>
#include<iomanip>
#include<map>
#include<queue>
#include<stack>
#include<string>
#include<set>
#include<utility>
#include<vector>
using namespace std;
#define FF first
#define SS second
#define PB push_back 
#define MP make_pair
typedef long long ll;
const ll INF=1<<28;
const ll LINF=1ll<<61;
//My own input/output stream
#define input1(x) x=getnum()
#define input2(x,y) input1(x),y=getnum()
#define input3(x,y,z) input2(x,y),z=getnum()
#define input4(x,y,z,w) input3(x,y,z),w=getnum()
#define output1(x) putnum(x)
#define output2(x,y) output1(x),putnum(y)
#define output3(x,y,z) output2(x,y),putnum(z)
#define output4(x,y,z,w) output3(x,y,z),putnum(w)
inline ll getnum()
{
	register ll r=0;register bool ng=0;register char c;c=getchar();
	while(c!='-'&&(c<'0'||c>'9'))c=getchar();
	if(c=='-')ng=1,c=getchar();
	while(c!=' '&&c!='\n')r=r*10+c-'0',c=getchar();
	if(ng)r=-r;return r;
}
template <class T> inline void putnum(T x)
{
	if(x<0)putchar('-'),x=-x;
	register short a[20]={},sz=0;
	while(x>0)a[sz++]=x%10,x/=10;
	if(sz==0)putchar('0');
	for(int i=sz-1;i>=0;i--)putchar('0'+a[i]);
}
inline void putsp(){putchar(' ');}
inline void putendl(){putchar('\n');}
const int maxn=10011;
int n,m,q;
struct edge
{
	int to,rev,cap,cost;
};
vector<edge>con[maxn],g[maxn];
edge make_edge(int to,int cap,int rev,int cost)
{
	edge tmp;
	tmp.to=to;
	tmp.rev=rev;
	tmp.cap=cap;
	tmp.cost=cost;
	return tmp;
}
void add_edge(int x,int y,int cap,int cost)
{
	g[x].PB(make_edge(y,cap,g[y].size(),cost));
	g[y].PB(make_edge(x,0,g[x].size()-1,-cost));
}
int pe[maxn],pv[maxn],dis[maxn];
bool inq[maxn];
ll mincostflow(int s,int t,int flow)
{
	for(int i=1;i<=n;i++)con[i]=g[i];
	ll cost=0;
	while(flow>0)
	{
		queue<int>q;
		q.push(s);inq[s]=1;
		for(int i=1;i<=n;i++)
			dis[i]=INF;
		dis[s]=0;
		while(!q.empty())
		{
			int x=q.front();
			inq[x]=0;
			q.pop();
			for(int i=0;i<con[x].size();i++)
			{
				edge &e=con[x][i];
				if(e.cap>0&&dis[x]+e.cost<dis[e.to])
				{
					dis[e.to]=dis[x]+e.cost;
					if(!inq[e.to])
						inq[e.to]=1,q.push(e.to);
					pv[e.to]=x;
					pe[e.to]=i;
				}
			}
		}
		if(dis[t]==INF)
			return -1;
		int f=flow;
		for(int u=t;u!=s;u=pv[u])
			f=min(f,con[pv[u]][pe[u]].cap);
		for(int u=t;u!=s;u=pv[u])
		{
			edge &e=con[pv[u]][pe[u]];
			e.cap-=f;
			con[e.to][e.rev].cap+=f;
		}
		cost+=1ll*f*dis[t];flow-=f;
	}
	return cost;
}
int main()
{
	freopen("mincostflow.in","r",stdin);
	freopen("mincostflow.out","w",stdout);
	input2(n,m);
	int x,y,cap,cost;
	for(int i=1;i<=m;i++)
	{
		input4(x,y,cap,cost);
		add_edge(x,y,cap,cost);
	}
	input1(q);
	while(q--)
	{
		input3(x,y,cap);
		putnum(mincostflow(x,y,cap));
		putendl();
	}
	return 0;
}

