//while(true)rp++;
#include<bits/stdc++.h>
using namespace std;
#define debug(x) cerr<<#x<<"="<<x<<endl;
#define FF first
#define SS second
#define PB push_back 
#define MP make_pair
typedef long long ll;
const ll INF=1<<28;
const ll LINF=1ll<<61;
//My own input/output stream
#define input1(x) x=getnum()
#define input2(x,y) input1(x),y=getnum()
#define input3(x,y,z) input2(x,y),z=getnum()
#define input4(x,y,z,w) input3(x,y,z),w=getnum()
#define output1(x) putnum(x)
#define output2(x,y) output1(x),putnum(y)
#define output3(x,y,z) output2(x,y),putnum(z)
#define output4(x,y,z,w) output3(x,y,z),putnum(w)
inline ll getnum()
{
	register ll r=0;register bool ng=0;register char c;c=getchar();
	while(c!='-'&&(c<'0'||c>'9'))c=getchar();
	if(c=='-')ng=1,c=getchar();
	while(c!=' '&&c!='\n')r=r*10+c-'0',c=getchar();
	if(ng)r=-r;return r;
}
template <class T> inline void putnum(T x)
{
	if(x<0)putchar('-'),x=-x;
	register short a[20]={},sz=0;
	while(x>0)a[sz++]=x%10,x/=10;
	if(sz==0)putchar('0');
	for(int i=sz-1;i>=0;i--)putchar('0'+a[i]);
}
inline void putsp(){putchar(' ');}
inline void putendl(){putchar('\n');}

struct treap
{
	struct node
	{
		int val,fix,sz;
		node *l,*r;
		node()
		{
			val=fix=sz=0;
			l=r=NULL;
		}
	};
	node *root;
	void left_rotate(node *&p)
	{
		node *t=p->r;
		p->r=t->l;
		t->l=p;
		swap(t->sz,p->sz);
		p=t;
	}
	void right_rotate(node *&p)
	{
		node *t=p->l;
		p->l=t->r;
		t->r=p;
		swap(t->sz,p->sz);
		p=t;
	}
	void insert(int x,node *&p)
	{
		if(p==NULL)
		{
			p=new node;
			p->val=x;
			p->fix=rand();
		}
		else if(x<p->val)
		{
			insert(x,p->l);
			if(p->l->fix>p->fix)right_rotate(p);
		}
		else if(x>p->val)
		{
			insert(x,p->r);
			if(p->r->fix>p->fix)left_rotate(p);
		}
		p->sz++;
	}
	void remove(int x,node *&p)
	{
		if(p->v==x)
		{
			p->v=NULL
	}
	int rank(int x,node *p)
	{
	}
	int search(int x,node *p)
	{
	}
};
int main()
{
	return 0;
}
