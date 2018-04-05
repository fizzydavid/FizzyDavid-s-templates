struct suffix_automaton
{
	int go[300111][26],len[300111],pre[300111],tot;
	void init()
	{
		memset(go,0,sizeof(go));
		memset(len,0,sizeof(len));
		memset(pre,0,sizeof(pre));
		tot=1;
	}
	int add(int p,int c)
	{
		assert(go[p][c]==0);
		int np=++tot;
		len[np]=len[p]+1;
		while(p&&!go[p][c])go[p][c]=np,p=pre[p];
		if(!p)
		{
			pre[np]=1;
			return np;
		}
		int q=go[p][c];
		if(len[q]==len[p]+1)
		{
			pre[np]=q;
			return np;
		}
		else
		{
			int nq=++tot;
			len[nq]=len[p]+1;
			pre[nq]=pre[q];
			pre[q]=nq;
			pre[np]=nq;
			for(int i=0;i<26;i++)go[nq][i]=go[q][i];
			while(p&&go[p][c]==q)go[p][c]=nq,p=pre[p];
			return np;
		}
	}
	int getval(int st){return len[st]-len[pre[st]];}
}sam;
