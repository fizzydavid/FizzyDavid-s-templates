struct LCT
{
	static const int maxn=200111;
	struct node
	{
		int go[2],fa;
		ll v,rsum,isum,sum;
		node(){go[0]=go[1]=v=sum=isum=rsum=0;}
	}a[maxn];
	#define ls a[p].go[0]
	#define rs a[p].go[1]
	#define getpd(p) (a[a[p].fa].go[0]==p?0:(a[a[p].fa].go[1]==p?1:-1))
	void update(int p)
	{
		a[p].rsum=a[ls].rsum+a[rs].rsum+a[p].v;
		a[p].sum=a[ls].sum+a[rs].sum+a[p].v+a[p].isum;
	}
	void rotate(int p,bool d)
	{
		int q=a[p].go[d],r=a[q].go[d^1];
		if(getpd(p)!=-1)a[a[p].fa].go[getpd(p)]=q;
		a[q].go[d^1]=p;
		a[p].go[d]=r;
		a[q].fa=a[p].fa;
		a[p].fa=q;
		a[r].fa=p;
		update(p);
	}
	void splay(int p,int rt=0)
	{
		while(a[p].fa!=rt&&getpd(p)!=-1)
		{
			int q=a[p].fa,r=a[q].fa;
			int dq=getpd(p),dr=getpd(q);
			if(r==rt||dr==-1)rotate(q,dq);
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
		update(p);
	}
	void changeson(int p,bool d,int q)
	{
		if(a[p].go[d])a[p].isum+=a[a[p].go[d]].sum;
		if(q&&a[q].fa==p)a[p].isum-=a[q].sum;
		a[p].go[d]=q;
		update(p);
	}
	void access(int p)
	{
		for(splay(p),changeson(p,1,0);a[p].fa;splay(p))
		{
			splay(a[p].fa);
			changeson(a[p].fa,1,p);
		}
	}
	void changev(int p,int v)
	{
		access(p);
		a[p].v=v;
		update(p);
	}
	void link(int x,int p)//x must be root
	{
		access(p);
		splay(x);
		changeson(p,1,x);
		a[x].fa=p;
	}
	void cut(int x,int p)//p must be father
	{
		access(p);
		splay(x);
		a[x].fa=0;
		a[p].isum-=a[x].sum;
		update(p);
	}
	int query_subtree_sum(int x)//exclude_root
	{
		access(x);
		return a[x].isum;
	}
}lct;
struct SAM
{
	LCT preT;
	static const int maxn=100111*2;
	int go[maxn][26],pre[maxn],len[maxn],tot;
	void init()
	{
		memset(go,0,sizeof(go));
		memset(pre,0,sizeof(pre));
		memset(len,0,sizeof(len));
		tot=1;
	}
	void updv(int x)
	{
		preT.changev(x,len[x]-len[pre[x]]);
	}
	int append(int p,char _c)
	{
		int c=_c-'a';
		assert(go[p][c]==0);
		int np=++tot;
		len[np]=len[p]+1;
		while(p&&!go[p][c])
		{
			go[p][c]=np;
			p=pre[p];
		}
		if(!p)
		{
			pre[np]=1;
			preT.link(np,1);
			updv(np);
			return np;
		}
		int q=go[p][c];
		if(len[q]==len[p]+1)
		{
			pre[np]=q;
			updv(np);
			preT.link(np,q);
		}
		else
		{
			int nq=++tot;
			len[nq]=len[p]+1;
			preT.link(nq,pre[q]);
			preT.link(np,nq);
			preT.cut(q,pre[q]);
			preT.link(q,nq);
			pre[nq]=pre[q];
			pre[q]=nq;
			pre[np]=nq;
			updv(nq);updv(q);updv(np);
			for(int i=0;i<26;i++)go[nq][i]=go[q][i];
			while(p&&go[p][c]==q)go[p][c]=nq,p=pre[p];
		}
		return np;
	}
};
