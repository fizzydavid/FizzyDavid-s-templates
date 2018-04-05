const int hs_sz=1<<22;
struct HashTable
{
	int key[hs_sz],val[hs_sz];
	void init(){memset(key,-1,sizeof(key));}
	HashTable(){init();}
	int hash(int x){return ((x<<2)+x)&(hs_sz-1);}
	int &get(int v)
	{
		int p=hash(v);
		while(key[p]!=-1&&key[p]!=v)p=(p+1)&(hs_sz-1);
		if(key[p]==-1)key[p]=v,val[p]=-1;
		return val[p];
	}
	int query(int v)
	{
		int p=hash(v);
		while(key[p]!=-1&&key[p]!=v)p=(p+1)&(hs_sz-1);
		if(key[p]==-1)return -1;
		return val[p];
	}
}rikka;

