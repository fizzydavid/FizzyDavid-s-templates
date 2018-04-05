//geometry start
const double eps=1e-7;
const double pi=acos(-1);
bool is0(double x){return x>-eps&&x<eps;}
struct point
{
	double x,y;
	point(double _x=0,double _y=0){x=_x;y=_y;}
	point operator+(const point &t)const{return point(x+t.x,y+t.y);}
	point operator-(const point &t)const{return point(x-t.x,y-t.y);}
	point operator*(const point &t)const{return point(x*t.x-y*t.y,x*t.y+y*t.x);}
	point operator*(const double &t)const{return point(x*t,y*t);}
	point operator/(const double &t)const{return point(x/t,y/t);}
	point operator-()const{return point(-x,-y);}
	double len()const{return sqrt(x*x+y*y);}
	point operator/(const point &t)const{return point(x*t.x+y*t.y,-x*t.y+y*t.x)/t.len()/t.len();}
	double det(const point &t)const{return x*t.y-y*t.x;}
	double dot(const point &t)const{return x*t.x+y*t.y;}
	double len2()const{return x*x+y*y;}
	point unit()const{return (*this)/len();}
	bool operator<(const point &t)const{return is0(x-t.x)?y<t.y:x<t.x;}
	bool operator==(const point &t)const{return is0(x-t.x)&&is0(y-t.y);}
	void out(){cerr<<x<<","<<y<<endl;}
	double rad()const{return atan2(y,x);}
	point conj()const{return point(x,-y);}
};
bool cmpwithangle(point x,point y)
{
	double diff=x.rad()-y.rad();
	if(fabs(diff)>0.001)return diff<0;
	else return x.det(y)>eps;
}
double area(double x,double y,double z) 
{
	double p=(x+y+z)/2;
	return sqrt(p*(p-x)*(p-y)*(p-z));
}
bool parallel(const point &px,const point &py,const point &qx,const point &qy)
{
	return is0((px-py).det(qx-qy));
}
point intersection(const point &px,const point &py,const point &qx,const point &qy)
{
	double t=-(px-qx).det(qy-qx)/(py-px).det(qy-qx);
	return px+(py-px)*t;
}
point intersection(const pair<point,point> &p,const pair<point,point> &q)
{
	return intersection(p.FF,p.SS,q.FF,q.SS);
}
bool segcross_in(const point &px,const point &py,const point &qx,const point &qy)
{
	if(parallel(px,py,qx,qy))return false;
	point p=intersection(px,py,qx,qy);
	return (px-p).dot(py-p)<eps&&(qx-p).dot(qy-p)<eps;
}
bool segcross_ex(const point &px,const point &py,const point &qx,const point &qy) 
{
	if(parallel(px,py,qx,qy))return false;
	point p=intersection(px,py,qx,qy);
	return (px-p).dot(py-p)<-eps&&(qx-p).dot(qy-p)<-eps;
}
double pointtoseg(point p,point pl,point pr)
{
	double mndis=min((p-pl).len(),(p-pr).len());
	point q=intersection(pl,pr,p,p+(pr-pl)*point(0,1));
	if((pl-q).dot(pr-q)<0)mndis=min(mndis,(p-q).len());
	return mndis;
}
double pointtoline(point p,point pl,point pr)
{
	point q=intersection(pl,pr,p,p+(pr-pl)*point(0,1));
	return (p-q).len();
}

int cycle_intersect(point p,double pr,point q,double qr)
{
	if((p-q).sqrl()>(pr+qr)*(pr+qr)+eps)return 0;
	if(is0((p-q).sqrl()-(pr+qr)*(pr+qr)))
	{
		/**/(q-p)*(pr/(pr+qr))+p;
		return 1;
	}
	double sqrd=(p-q).sqrl();
	double x=(sqrd+pr*pr-qr*qr)/2/sqrd;
	point mid=(q-p)*x+p;
	double l=sqrt(pr*pr-(mid-p).sqrl());
	/**/mid+(q-p).unit()*point(0,+1)*l;
	/**/mid+(q-p).unit()*point(0,-1)*l;
	return 2;
}
//convex hull
const int tbmxsz=111;
point tmppt[tbmxsz];
int tb[tbmxsz],tbn;
void calcchull(point a[],int n)
{
	tbn=0;
	int t[tbmxsz],tn;
	tn=0;
	for(int i=1;i<=n;i++)
	{
		t[tn++]=i;
		while(tn>2&&(a[t[tn-2]]-a[t[tn-3]]).det(a[t[tn-1]]-a[t[tn-3]])>-eps)
		{
			t[tn-2]=t[tn-1];
			tn--;
		}
	}
	for(int i=0;i<tn;i++)tb[tbn++]=t[i];
	tn=0;
	for(int i=1;i<=n;i++)
	{
		t[tn++]=i;
		while(tn>2&&(a[t[tn-2]]-a[t[tn-3]]).det(a[t[tn-1]]-a[t[tn-3]])<eps)
		{
			t[tn-2]=t[tn-1];
			tn--;
		}
	}
	for(int i=tn-2;i>0;i--)tb[tbn++]=t[i];
}
int makechull(point a[],int n)
{
	calcchull(a,n);
	for(int i=1;i<=n;i++)tmppt[i]=a[i];
	for(int i=1;i<=tbn;i++)a[i]=tmppt[tb[i-1]];
	return tbn;
}


struct point//integer
{
	ll x,y;
	point(ll X=0,ll Y=0){x=X;y=Y;}
	point operator+(const point &t)const{return point(x+t.x,y+t.y);}
	point operator-(const point &t)const{return point(x-t.x,y-t.y);}
	ll det(const point &t)const
	{
		double tmp=1.0*x*t.y-1.0*y*t.x;
		if(tmp>1e18)return 1e18;
		if(tmp<-1e18)return -1e18;
		return x*t.y-y*t.x;
	}
	bool operator<(const point &t)const{return MP(x,y)<MP(t.x,t.y);}
};
struct point_cmp
{
	point p;
	bool operator<(const point_cmp &t)const{return p.det(t.p)>0;}
};
point_cmp mkcmp(const point &p){point_cmp ret;ret.p=p;return ret;}
struct DynamicConvexHull
{
	set<point> a;
	int type;//1 up  -1 down
	set<pair<point_cmp,point> > st;
	#define checkt(p,q,r) ((q)-(p)).det((r)-(p))*type>=0
	void del(set<point>::iterator it)
	{
		point pre,nxt;
		bool ip=0,in=0;
		if(it!=a.begin())it--,ip=1,pre=*it,it++;
		it++;if(it!=a.end())in=1,nxt=*it;it--;
		if(ip)st.erase(MP(mkcmp(*it-pre),pre));
		if(in)st.erase(MP(mkcmp(nxt-*it),*it));
		if(ip&&in)st.insert(MP(mkcmp(nxt-pre),pre));
		a.erase(it);
	}
	void ins(point p)
	{
		a.insert(p);
		point pre,nxt;
		set<point>::iterator it=a.lower_bound(p);
		bool ip=0,in=0;
		if(it!=a.begin())it--,ip=1,pre=*it,it++;
		it++;if(it!=a.end())in=1,nxt=*it;it--;
		if(ip)st.insert(MP(mkcmp(*it-pre),pre));
		if(in)st.insert(MP(mkcmp(nxt-*it),*it));
		if(ip&&in)st.erase(MP(mkcmp(nxt-pre),pre));
	}
	void insert(point p)
	{
		if(a.find(p)!=a.end())return;
		if(a.size()>=2)
		{
			set<point>::iterator i,j=a.lower_bound(p),ni;
			if(j!=a.end()&&j!=a.begin())
			{
				i=j;i--;
				if(checkt(*i,p,*j))return;
			}
			i=j;ni=i;if(ni!=a.end())ni++;
			for(;ni!=a.end();i=ni,ni++)
			{
				if(checkt(p,*i,*ni))del(i);
			}
			i=a.lower_bound(p);if(i!=a.begin())i--;
			ni=i;if(ni!=a.begin())ni--;
			for(;i!=ni;i=ni,ni--)
			{
				if(checkt(*ni,*i,p))del(i);
				if(ni==a.begin())break;
			}
		}
		ins(p);
	}
	ll querymn(ll k)//(x,y) k*x+y
	{
		assert(type==-1);
		ll ret=9e18;
		if(a.size()==0)return ret;
		if(a.size()==1)return k*a.begin()->x+a.begin()->y;
		pair<point_cmp,point> tmp=MP(mkcmp(point(1,-k)),point(0,0));
		set<pair<point_cmp,point> >::iterator it=st.lower_bound(tmp);
		if(it==st.end())it--;
		assert(st.size()>0);
		point p=it->SS;
		ret=min(ret,k*p.x+p.y);
		p=p+it->FF.p;
		ret=min(ret,k*p.x+p.y);
		return ret;
	}
};
