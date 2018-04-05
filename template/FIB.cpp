struct fib
{
	int a,b;//a+bx
	fib(int X=0,int Y=0){a=X;b=Y;}
	fib operator*(const fib &t)const
	{
		ll x=1ll*b*t.b%mod;
		return fib((x+1ll*a*t.a)%mod,(x+1ll*b*t.a+1ll*a*t.b)%mod);
	}
	fib operator*(const int &t)const
	{
		return fib((1ll*a*t)%mod,(1ll*b*t)%mod);
	}
	fib operator+(const fib &t)const{return fib((a+t.a)%mod,(b+t.b)%mod);}
	fib operator-(const fib &t)const{return fib((a-t.a+mod)%mod,(b-t.b+mod)%mod);}
	bool operator==(const fib &t)const{return MP(a,b)!=MP(t.a,t.b);}
};
fib qpow(fib x,ll k){return k==0?fib(1,0):qpow(x*x,k>>1)*(k&1?x:1);}

