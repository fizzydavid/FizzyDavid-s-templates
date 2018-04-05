const int maxn=100;
struct bigint
{
	int a[maxn], sz;
	int size()
	{
		return sz;
	}
	void init()
	{
		memset(a, 0, sizeof(a));
		sz = 0;
	}
	void operator = (const int &tmp)
	{
		init();
		int digit = 0, base = 1;
		while(tmp > 0)
		{
			if(digit < 4)
			{
				a[sz] += (tmp % 10) * base;
				tmp = tmp / 10;
				digit++;
				base *= 10;
			}
			else
			{
				a[++sz] = tmp % 10;
				tmp = tmp / 10;
				digit = 0;
				base = 1;
			}
		}
	}
	void operator = (const string &tmp)
	{
		init();
		int digit = 0, base = 1;
		for(int i = int(tmp[i].size()); i>=0; i--)
		{
			if(digit < 4)
			{
				a[sz] += (s[i] - '0') * base;
				base *= 10;
				digit++;
			}
			else
			{
				a[++sz] += s[i] - '0';
				digit = 0;
				base = 1;
			}
		}
	}
	bool operator == (const bigint &tmp) const
	{
		if(sz != tmp.size())
		{
			return false;
		}
		else
		{
			for(int i = 0; i < sz; i++)
			{
				if(a[i] != tmp.a[i])
				{
					return false;
				}
			}
			return true;
		}
	}
	bool operator != (const bigint &tmp) const
	{
		return !((*this) == tmp);
	}
	bool operator < (const bigint &tmp) const
	{
		
};
