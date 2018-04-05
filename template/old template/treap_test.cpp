//while(true)rp++;
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<deque>
#include<iostream>
#include<iomanip>
#include<map>
#include<queue>
#include<stack>
#include<string>
#include<set>
#include<utility>
#include<vector>
using namespace std;
#define debug(x) cerr<<#x<<"="<<x<<endl;
#define FF first
#define SS second
#define PB push_back 
#define MP make_pair
typedef long long ll;
const ll INF=1<<28;
const ll LINF=1ll<<61;
struct treap_node
{
	int v,fix,id;
	treap_node *l,*r;
	treap_node(){v=fix=0;l=r=NULL;}
};
treap_node *root;
void left_rotate(treap_node *&p)
{
	treap_node *t=p->r;
	p->r=t->l;
	t->l=p;
	p=t;
}
void right_rotate(treap_node *&p)
{
	treap_node *t=p->l;
	p->l=t->r;
	t->r=p;
	p=t;
}
void insert(treap_node *&p,int x,int id)
{
	if(!p)
	{
		p=new treap_node;
		p->v=x;p->id=id;
		p->fix=rand();
	}
	else if(x<=p->v)
	{
		insert(p->l,x,id);
		if(p->l->fix<p->fix)right_rotate(p);
	}
	else
	{
		insert(p->r,x,id);
		if(p->r->fix<p->fix)left_rotate(p);
	}
}
void del(treap_node *&p,int x)
{
	if(p->v==x)
	{
		if(p->l==NULL||p->r==NULL)
		{
			treap_node *t;t=p;
			if(p->l!=NULL)p=p->l;else p=p->r;
			delete t;
		}
		else
		{
			if(p->l->fix<p->r->fix)
			{
				right_rotate(p);
				del(p->r,x);
			}
			else
			{
				left_rotate(p);
				del(p->l,x);
			}
		}
	}
	else if(x<p->v&&p->l!=NULL)del(p->l,x);
	else if(x>p->v&&p->r!=NULL)del(p->r,x);
}
treap_node* search(treap_node *p,int x)
{
	if(x==p->v)return p;
	else if(x<=p->v&&p->l!=NULL)search(p->l,x);
	else if(x>p->v&&p->r!=NULL)search(p->r,x);
}
treap_node* findmin(treap_node *p)
{
	if(p->l!=NULL)return findmin(p->l);
	else return p;
}
treap_node* findmax(treap_node *p)
{
	if(p->r!=NULL)findmax(p->r);
	else return p;
}
void tdebug(treap_node *p)
{
	if(p==NULL){cout<<"NULL"<<endl;return;}
	cout<<p->v<<" "<<p->fix<<" "<<p->id<<endl;
	cout<<"left:"<<endl;tdebug(p->l);
	cout<<"right:"<<endl;tdebug(p->r);
	cout<<p->v<<"end"<<endl;
}
int main()
{
	ios::sync_with_stdio(false);
	int n,op,x,id;
	while(true)
	{
		cin>>op;
		if(op==0)break;
		if(op==1)cin>>id>>x;
		if(op==1)insert(root,x,id);
		else if(op==3)
		{
			if(root==NULL)cout<<0<<endl;
			else
			{
				treap_node *t=findmin(root);
				cout<<t->id<<endl;
				del(root,t->v);
			}
		}
		else if(op==2)
		{
			if(root==NULL)cout<<0<<endl;
			else
			{
				treap_node *t=findmax(root);
				cout<<t->id<<endl;
				del(root,t->v);
			}
		}
//		tdebug(root);
	}
	return 0;
}
