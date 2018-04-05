int depth=17;
int init_a[100111];
struct magic_array
{
	int tl[maxn],tr[maxn],a[maxn],tot;
	void clear(){tot=0;}
	int getval(int p,int id,int d=1)
	{
//		cout<<"getval1:"<<p<<" "<<id<<" "<<d<<endl;
		if(d==depth)return a[p];
		int sz=1<<(depth-d-1);
		if(id>=sz)return getval(tr[p],id-sz,d+1);
		else return getval(tl[p],id,d+1);
	}
	int newnode(int p)
	{
		tot++;
		tl[tot]=tl[p];
		tr[tot]=tr[p];
		return tot;
	}
	int change(int p,int id,int v,int d=1)
	{
//		cout<<"change:"<<p<<" "<<id<<" "<<v1<<" "<<v2<<" "<<d<<" "<<tl[p]<<","<<tr[p]<<endl;
		int np=newnode(p);
		if(d==depth)a[np]=v;
		else
		{
			int sz=1<<(depth-d-1);
			if(id>=sz)tr[np]=change(tr[p],id-sz,v,d+1);
			else tl[np]=change(tl[p],id,v,d+1);
		}
		return np;
	}
	int build(int id=0,int d=1)
	{
		int p=++tot;
		if(d==depth)tl[p]=tr[p]=0,a[p]=init_a[id];
		else
		{ 
			int sz=1<<(depth-d-1);
			tl[p]=build(id,d+1);
			tr[p]=build(id+sz,d+1);
		}
		return p;
	}
}kotori;
