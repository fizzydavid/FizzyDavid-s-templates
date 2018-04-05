struct hashing
{
	ull hs1,hs2;
	hashing(){hs1=hs2=0;}
	hashing(ull x,ull y){hs1=x;hs2=y;}
	bool operator==(const hashing &x){return hs1==x.hs1&&hs2==x.hs2;}
	bool operator!=(const hashing &x){return !(*this==x);}
	void operator=(const int &x){hs1=hs2=x;}
	hashing operator+(const int &x){hashing res;res.hs1=hs1+x;res.hs2=hs2+x;return res;}
	hashing operator+(const hashing &x){hashing res;res.hs1=hs1+x.hs1;res.hs2=hs2+x.hs2;return res;}
	hashing operator-(const int &x){hashing res;res.hs1=hs1-x;res.hs2=hs2-x;return res;}
	hashing operator-(const hashing &x){hashing res;res.hs1=hs1-x.hs1;res.hs2=hs2-x.hs2;return res;}
	hashing operator*(const int &x){hashing res;res.hs1=hs1*x;res.hs2=hs2*x;return res;}
	hashing operator*(const hashing &x){hashing res;res.hs1=hs1*x.hs1;res.hs2=hs2*x.hs2;return res;}
	bool operator<(const hashing &tmp)const
	{
		if(hs1==tmp.hs1)return hs2<tmp.hs2;
		else return hs1<tmp.hs1;
	}
};
hashing makehash(ull x,ull y)
{
	hashing tmp(x,y);
	return tmp;
}
const hashing C(1001,2003);
