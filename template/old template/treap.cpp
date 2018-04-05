struct treap_node
{
	int v,fix;
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
void insert(treap_node *&p,int x)
{
	if(!p)
	{
		p=new treap_node;
		p->v=x;
		p->fix=rand();
	}
	else if(x<=p->v)
	{
		insert(p->l,x);
		if(p->l->fix<p->fix)right_rotate(p);
	}
	else
	{
		insert(p->r,x);
		if(p->r->fix<p->fix)left_rotate(p);
	}
}
void del(treap_node *&p,int x)
{
	if(p->v==x)
	{
		if(p->l==NULL||p->r==NULL)
		{
			treap_node *t=p;
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
	cout<<p->v<<" "<<p->fix<<endl;
	if(p->l!=NULL){cout<<"left:"<<endl;tdebug(p->l);}else cout<<"NULL"<<endl;
	if(p->r!=NULL){cout<<"right:"<<endl;tdebug(p->r);}else cout<<"NULL"<<endl;
	cout<<p->v<<"end"<<endl;
}
