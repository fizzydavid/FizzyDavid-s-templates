struct SAM
{
	int go[maxn][26],pre[maxn],len[maxn],tot,last;
	void init()
	{
		memset(go,-1,sizeof(go));
		memset(pre,-1,sizeof(pre));
		memset(len,0,sizeof(len));
		tot=1;last=0;
	}
	void insert(char c)
	{
		c-='a';
		int p=last,np=tot++;
		len[np]=len[last]+1;
		while(p!=-1&&go[p][c]==-1)
			go[p][c]=np,p=pre[p];
		if(p==-1)
			pre[np]=0;
		else
		{
			int q=go[p][c];
			if(len[p]+1==len[q])
				pre[np]=q;
			else
			{
				int nq=tot++;
				len[nq]=len[p]+1;
				for(int i=0;i<26;i++)
					go[nq][i]=go[q][i];
				pre[nq]=pre[q];
				pre[q]=pre[np]=nq;
				while(p!=-1&&go[p][c]==q)
					go[p][c]=nq,p=pre[p];
			}
		}
		last=np;
	}
};
