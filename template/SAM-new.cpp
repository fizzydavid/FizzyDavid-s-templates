struct SAM
{
	int go[1234][26],par[1234],len[1234],last,tot;
	void init()
	{
		memset(go,0,sizeof(go));
		memset(par,0,sizeof(par));
		memset(len,0,sizeof(len));
		last=tot=1;
	}
	SAM()
	{
		init();
	}
	int newq(int p,int x)
	{
		int q=go[p][x];
		if(len[q]==len[p]+1)return q;
		int nq=++tot;
		len[nq]=len[p]+1;
		par[nq]=par[q];
		for(int i=0;i<26;i++)go[nq][i]=go[q][i];
		par[q]=nq;
		while(p&&go[p][x]==q)go[p][x]=nq,p=par[p];
		return nq;
	}
	void insert(int x)
	{
		int p=last,np;
		if(go[p][x])
		{
			int q=go[p][x];
			last=newq(p,x);
			return;
		}
		np=++tot;
		len[np]=len[p]+1;
		while(p&&!go[p][x])go[p][x]=np,p=par[p];
		if(p)
		{
			par[np]=newq(p,x);
			last=np;
		}
	}
};
