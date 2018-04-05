struct HSU 
{
	pair<point,point> a[100111];
	int n;
	bool emp;
	void clear()
	{
		n=0;emp=0;
	}
	void add(point px,point py)
	{
//		cout<<"add:"<<px.x<<","<<px.y<<" "<<py.x<<","<<py.y<<endl;
		if(emp)return;
		a[n++]=MP(px,py);
		while(n>1)
		{
			pair<point,point> &l1=a[n-1];
			pair<point,point> &l2=a[n-2];
			if(equal0((l1.SS-l1.FF).det((l2.SS-l2.FF))))
			{
				if((l2.SS-l2.FF).det(l1.SS-l2.FF)>-eps)l2=l1;
				n--;
			}
			else break;
		}
		while(n>2)
		{
			pair<point,point> &l1=a[n-1];
			pair<point,point> &l2=a[n-2];
			pair<point,point> &l3=a[n-3];
			point p=intersection(l2.FF,l2.SS,l3.FF,l3.SS);
			point p2=intersection(l1.FF,l1.SS,l2.FF,l2.SS);
			if((p2-p).dot(l2.SS-l2.FF)<-eps)
			{
				if((l1.SS-l1.FF).det(l3.SS-l3.FF)>-eps)
				{
					emp=1;
					break;
				}
				else
				{
					l2=l1;
					n--;
				}
			}
			else break;
		}
//		cout<<"n="<<n<<endl;
//		for(int i=0;i<n;i++)cout<<a[i].FF.x<<","<<a[i].FF.y<<" "<<a[i].SS.x<<","<<a[i].SS.y<<endl;
	}
};
