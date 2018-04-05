struct data
{
	int a[500111];
	int len[500111];
	vector<pair<int,int> > tab[500111];
	void build(int l,int r)
	{
		if(len[l]==0)
		{
			len[l]=r-l+1;
			tab[l].resize(len[l]);
			tab[l][0]=MP(a[l],l);
			for(int i=1;i<len[l];i++)tab[l][i]=min(tab[l][i-1],MP(a[l+i],l+i));
		}
		int m=tab[l][r-l].SS;
		if(l<m)build(l,m-1);
		if(m<r)build(m+1,r);
	}
	void init(int l,int r,int ia[])
	{
		for(int i=l;i<=r;i++)a[i]=ia[i],len[i]=0;
		build(l,r);
	}
	pair<int,int> query(int l,int r)
	{
		assert(r-l<len[l]);
		return tab[l][r-l];
	}
}rikka;
