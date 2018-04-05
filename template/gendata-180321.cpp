//by yjz
#include<bits/stdc++.h>
using namespace std;
#define FF first
#define SS second
#define PB push_back
#define MP make_pair
#define bged(v) (v).begin(),(v).end()
#define foreach(it,s) for(__typeof((s).begin()) it=(s).begin();it!=(s).end();it++)
typedef long long ll;
const int Imx=2147483647;
const ll Lbig=2e18;
const int mod=1e9+7;
//My i/o stream
struct fastio
{
	char s[100000];
	int it,len;
	fastio(){it=len=0;}
	inline char get()
	{
		if(it<len)return s[it++];it=0;
		len=fread(s,1,100000,stdin);
		if(len==0)return EOF;else return s[it++];
	}
	bool notend()
	{
		char c=get();
		while(c==' '||c=='\n')c=get();
		if(it>0)it--;
		return c!=EOF;
	}
}_buff;
#define geti(x) x=getnum()
#define getii(x,y) geti(x),geti(y)
#define getiii(x,y,z) getii(x,y),geti(z)
#define puti(x) putnum(x),putchar(' ')
#define putii(x,y) puti(x),puti(y)
#define putiii(x,y,z) putii(x,y),puti(z)
#define putsi(x) putnum(x),putchar('\n')
#define putsii(x,y) puti(x),putsi(y)
#define putsiii(x,y,z) putii(x,y),putsi(z)
inline ll getnum()
{
	ll r=0;bool ng=0;char c;c=_buff.get();
	while(c!='-'&&(c<'0'||c>'9'))c=_buff.get();
	if(c=='-')ng=1,c=_buff.get();
	while(c>='0'&&c<='9')r=r*10+c-'0',c=_buff.get();
	return ng?-r:r;
}
template<class T> inline void putnum(T x)
{
	if(x<0)putchar('-'),x=-x;
	register short a[20]={},sz=0;
	while(x)a[sz++]=x%10,x/=10;
	if(sz==0)putchar('0');
	for(int i=sz-1;i>=0;i--)putchar('0'+a[i]);
}
inline char getreal(){char c=_buff.get();while(c==' '||c=='\n')c=_buff.get();return c;}
const string fname="kagari";
const string stdname="kagari.exe";
const string in_suf=".in";
const string out_suf=".out";
const string ans_suf=".ans";
const int testcase_count=20;
const int testcase_count_digit_n=2;
const bool is_0based=0;
const int rnd_seed=20020626;//-1 for realtime

int rnd(){return rand()<<15|rand();}
int rnd(int x,int y)
{
	int ret=0;
	for(int i=0;i<x;i++)ret+=rnd()%y+1;
	return ret;
}


void gen_init()
{
}

void print_case()
{
}

#define in_seg(x,l,r) ((l)<=(x)&&(x)<=(r))
void gen(int testcase)
{
	gen_init();
	int len; 
	if(in_seg(testcase,1,2))len=1;
	if(in_seg(testcase,3,4))len=10;
	if(in_seg(testcase,5,6))len=100;
	if(in_seg(testcase,7,8))len=1000;
	if(in_seg(testcase,9,12))len=5000;
	if(in_seg(testcase,13,16))len=30000;
	if(in_seg(testcase,17,20))len=100000;
	
	print_case();
}
int main()
{
	string ifname=fname+in_suf;
	string ofname=fname+out_suf;
	
	if(rnd_seed==-1)srand(time(NULL));
	else srand(rnd_seed);
	
	for(int tc=(is_0based^1);tc<testcase_count+(is_0based^1);tc++)
	{
		cerr<<"gen testcase:"<<tc<<endl;
		freopen(ifname.c_str(),"w",stdout);
		gen(tc);
		fclose(stdout);
		
		cerr<<"runing..."<<endl;
		int pret=clock();
		system(stdname.c_str());
		cerr<<"time="<<clock()-pret<<endl;
		
		string s="";
		for(int x=tc,step=0;step<testcase_count_digit_n;x/=10,step++)
		{
			s+=char(x%10+'0');
		}
		reverse(s.begin(),s.end());
		string tc_ifname=fname+s+in_suf;
		string tc_ofname=fname+s+ans_suf;
		
		system(("copy "+ifname+" "+tc_ifname).c_str());
		system(("copy "+ofname+" "+tc_ofname).c_str());
	}
	system(("del "+ifname).c_str());
	system(("del "+ofname).c_str());
	return 0;
}
