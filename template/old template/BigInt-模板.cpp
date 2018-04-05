#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<map>
#include<queue>
#include<stack>
#include<string>
#include<set>
#include<utility>
#include<vector>
using namespace std;
#define ff first
#define ss second
#define pb push_back 
#define mp make_pair
const int BigIntMod=10000;
struct BigInt
{
	int a[1000],n;
	//verdict:accepted
	BigInt()
	{
		n=0;
		memset(a,0,sizeof(a));
	};
	BigInt(int x)
	{
		n=0;
		memset(a,0,sizeof(a));
		while(x>0)a[n++]=x%BigIntMod,x/=BigIntMod;
	}
	//verdict:accepted
	void out()
	{
		if(n==0)printf("0");
		for(int i=n-1;i>=0;i--)printf("%d",a[i]);
	}
	void outl()
	{
		out();puts("");
	}
	void outsp()
	{
		out();printf(" ");
	}
	//verdict:accepted
	void operator=(int x)
	{
		while(x>0)a[n++]=x%BigIntMod,x/=BigIntMod;
	}
	//verdict:accepted
	void operator=(const BigInt &x)
	{
		n=x.n;
		for(int i=0;i<n;i++)a[i]=x.a[i];
	}
	//verdict:
	bool operator==(const BigInt &x)
	{
		if(n!=x.n)return false;
		for(int i=0;i<n;i++)if(a[i]!=x.a[i])return false;
		return true;
	}
	bool operator<(const BigInt &x)        
	{
		if(n<x.n)return 1;
		else if(n>x.n)return 0;
		for(int i=n-1;i>=0;i--)
		{
			if(a[i]<x.a[i])return 1;else if(a[i]>x.a[i])return 0;
		}
		return 0;
	}
	//verdict:accepted
	bool operator!=(const BigInt &x){return !((*this)==x);}
	bool operator>=(const BigInt &x){return !((*this)<x);}
	bool operator<=(const BigInt &x){return (*this)<x||(*this)==x;}
	bool operator>(const BigInt &x){return !((*this)<=x);}
	bool operator==(const int &x){BigInt t;t=x;return (*this)==t;}
	bool operator!=(const int &x){BigInt t;t=x;return (*this)!=t;}
	bool operator<(const int &x){BigInt t;t=x;return (*this)<t;}
	bool operator>(const int &x){BigInt t;t=x;return (*this)>t;}
	bool operator<=(const int &x){BigInt t;t=x;return (*this)<=t;}
	bool operator>=(const int &x){BigInt t;t=x;return (*this)>=t;}

	//verdict:accepted
	BigInt operator+(const BigInt &x)
	{
		BigInt t(0);t.n=max(x.n,n);
		for(int i=0;i<t.n;i++)t.a[i]=x.a[i]+a[i];
		for(int i=0;i<t.n;i++)
		{
			t.a[i+1]+=t.a[i]/BigIntMod;
			t.a[i]%=BigIntMod;
		}
		if(t.a[t.n])t.n++;
		t.outl();
		return t;
	}
	BigInt operator+(const int tmp)
	{
		BigInt x;x=tmp;
		return (*this)+x;
	}
	void operator+=(const BigInt &x)
	{
		(*this)=(*this)+x;
	}
	void operator+=(const int tmp)
	{
		BigInt x;x=tmp;
		(*this)+=x;
	}
	//verdict:accepted
	BigInt operator-(const BigInt &x)
	{
		BigInt t(0);t.n=min(x.n,n);
		for(int i=0;i<t.n;i++)t.a[i]=a[i]-x.a[i];
		for(int i=0;i<t.n;i++)
		{
			if(t.a[i]<0)t.a[i+1]--,t.a[i]+=BigIntMod;
		}
		while(t.a[t.n-1]==0)t.n--;
		return t;
	}
	BigInt operator-(const int tmp)
	{
		BigInt x;x=tmp;
		return (*this)-x;
	}
	void operator-=(const BigInt &x)
	{
		(*this)=(*this)-x;
	}
	void operator-=(const int tmp)
	{
		BigInt x;x=tmp;
		(*this)-=x;
	}
	//verdict:accepted
	BigInt operator*(const BigInt &x)
	{
		BigInt t(0);t.n=x.n+n-1;
		for(int i=0;i<n;i++)
			for(int j=0;j<x.n;j++)
				t.a[i+j]+=a[i]*x.a[j];
		for(int i=0;i<t.n;i++)
		{
			t.a[i+1]+=t.a[i]/BigIntMod;
			t.a[i]%=BigIntMod;
		}
		if(t.a[t.n])t.n++;
		return t;
	}
	void operator*=(const BigInt &x)
	{
		(*this)=(*this)*x;
	}
	void operator*=(const int &x)
	{
		BigInt t;t=x;
		(*this)*=x;
	}
	//verdict: WRONG ANSWER!!!!!!!!!!!!!!!!!!!!!!!!!!!
	BigInt operator/(const int &x)
	{
		BigInt t(0);
		int base,pl,ans;
		t=*this; 
		base=x;
		while(base*BigIntMod<=(*this))
		{
			base.out();
			base*=BigIntMod,pl*=BigIntMod;
		}
		while(t.n>0&&base!=0)
		{
			t.outsp();base.outsp();ans.outl();
			while(t-base<0)base=base/BigIntMod,pl=pl/BigIntMod;
			t-=base;
			ans+=pl;
		}
		return ans;
	}
	BigInt operator/(const BigInt &x)
	{
		BigInt t(0),base,pl,ans;
		t=*this; 
		base=x;
		while(base*BigIntMod<=(*this))
		{
			base.out();
			base*=BigIntMod,pl*=BigIntMod;
		}
		while(t.n>0&&base!=0)
		{
			t.outsp();base.outsp();ans.outl();
			while(t-base<0)base=base/BigIntMod,pl=pl/BigIntMod;
			t-=base;
			ans+=pl;
		}
		return ans;
	}
};

//test:
int main()
{
	BigInt a,b,c;
	a=10;
	b=5;
	c=a/b;
	c.out();
}  
 
