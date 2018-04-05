const int bisz=1000;
const int bibs=10000;
const int bibsn=4;
struct bigint
{
	int a[bisz],len;
	void clear()
	{
		memset(a,0,sizeof(a));
		len=0;
	}
	bigint(){clear();}
	void shrink(int tmp=-1)
	{
		if(tmp!=-1)len=tmp;
		while(len>0&&a[len-1]==0)len--;
	}
	int push(int it)
	{
		while(a[it]>=bibs)a[it+1]+=a[it]/bibs,a[it++]%=bibs;
		return it;
	}
	int pull(int it)
	{
		while(a[it]<0)a[it+1]++,a[it++]+=bibs;
		return it;
	}
	void operator=(const bigint &t)
	{
		len=t.len;
		for(int i=0;i<bisz;i++)a[i]=t.a[i];
	}
	void operator=(const int &t)
	{
		a[0]=t;
		len=push(0)+1;
	}
	bigint operator+(bigint &t)const
	{
		bigint ret;
		for(int i=0;i<max(len,t.len);i++)
		{
			ret.a[i]+=a[i]+t.a[i];
			if(ret.a[i]>=bibs)ret.a[i+1]++,ret.a[i]-=bibs;
		}
		ret.shrink(max(len,t.len)+1);
		return ret;
	}
	void operator+=(const int &t)
	{
		a[0]+=t;
		len=max(len,push(0)+1);
	}
	bigint operator+(int &t)const
	{
		bigint ret=(*this);
		ret+=t;
		return ret;
	}
	bigint operator-(bigint &t)const
	{
		bigint ret;
		for(int i=0;i<len;i++)
		{
			ret.a[i]+=a[i]-t.a[i];
			if(ret.a[i]<0)ret.a[i+1]--,ret.a[i]+=bibs;
		}
		ret.shrink(len);
		return ret;
	}
	void operator-=(const int &t)
	{
		a[0]-=t;
		pull(0);
		shrink(len);
	}
	bigint operator-(int &t)const
	{
		bigint ret=(*this);
		ret-=t;
		return ret;
	}
	void operator*=(const int &t)
	{
		ll v=0;
		for(int i=0;i<len;i++)
		{
			v=v+a[i]*t;
			a[i]=v%bibs;
			v/=bibs;
		}
		a[len]=v;
		shrink(max(push(len)+1,len));
	}
	bigint operator*(const int &t)const
	{
		bigint ret=(*this);
		ret*=t;
		return ret;
	}
	bigint operator/(const int &t)const
	{
		bigint ret=(*this);
		int v=0;
		for(int i=len-1;i>=0;i--)
		{
			v=v*bibs+a[i];
			ret.a[i]=v/t;
			v%=t;
		}
		ret.shrink(len);
		return ret;
	}
	int operator%(const int &t)const
	{
		int v=0;
		for(int i=len-1;i>=0;i--)
		{
			v=v*bibs+a[i];
			v%=t;
		}
		return v;
	}
	bool operator<(const bigint &t)const
	{
		if(len!=t.len)return len<t.len;
		for(int i=len-1;i>=0;i--)if(a[i]!=t.a[i])return a[i]<t.a[i];
		return 0;
	}
	bool operator<=(const bigint &t)const
	{
		if(len!=t.len)return len<t.len;
		for(int i=len-1;i>=0;i--)if(a[i]!=t.a[i])return a[i]<t.a[i];
		return 1;
	}
	void out(char ch='\n')
	{
		if(len==0)putchar('0');
		else
		{
			printf("%d",a[len-1]);
			for(int i=len-2;i>=0;i--)
			{
				int tmp=bibs/10;
				while(tmp>1&&a[i]<tmp)putchar('0'),tmp/=10;
				printf("%d",a[i]);
			}
		}
		putchar(ch);
	}
	void in(char s[],int l)
	{
		len=0;
		for(int i=l;i>0;i-=bibsn)
		{
			int num=0;
			for(int j=max(0,i-bibsn);j<i;j++)
			{
				num=num*10+s[j]-'0';
			}
			a[len++]=num;
		}
	}
	int func(int t)//divided by t and return the value modulo t
	{
		int v=0;
		for(int i=len-1;i>=0;i--)
		{
			v=v*bibs+a[i];
			a[i]=v/t;
			v%=t;
		}
		shrink(len);
		return v;
	}
};
