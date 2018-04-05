ll rd(ll x,ll y){return y<0?rd(-x,-y):(x<0?-rd(-x,y):(x+y/2)/y);}
struct number
{
	ll x,y;
	number(ll X=0,ll Y=0){x=X;y=Y;}
	ll len()const{return x*x+y*y;}
	number conj()const{return number(x,-y);}
	number operator*(const number &t)const{return number(x*t.x-y*t.y,x*t.y+y*t.x);}
	number operator*(const ll &t)const{return number(x*t,y*t);}
	number operator-(const number &t)const{return number(x-t.x,y-t.y);}
	number operator/(const number &t)const
	{
		number p=(*this)*t.conj();
		return number(rd(p.x,t.len()),rd(p.y,t.len()));
	}
	number operator%(const number &t)const{return (*this)-((*this)/t)*t;}
};
